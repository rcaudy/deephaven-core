/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "highlevel/impl/query_table_impl.h"

#include <map>
#include <set>
#include <boost/variant.hpp>
#include "core/callbacks.h"
#include "lowlevel/generated/dhworker_requests.h"
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/dhworker_session.h"
#include "lowlevel/util/protocol_container_classes.h"
#include "highlevel/impl/boolean_expression_impl.h"
#include "highlevel/impl/columns_impl.h"
#include "highlevel/impl/query_scope_impl.h"
#include "highlevel/impl/apply_aggregates_operation.h"
#include "highlevel/columns.h"
#include "highlevel/openapi.h"
#include "utility/utility.h"

using io::deephaven::proto::backplane::grpc::ComboAggregateRequest;
using io::deephaven::proto::backplane::grpc::TableReference;
using io::deephaven::proto::backplane::script::grpc::BindTableToVariableResponse;
using deephaven::openAPI::core::Callback;
using deephaven::openAPI::lowlevel::remoting::DHWorker;
using deephaven::openAPI::lowlevel::remoting::DHWorkerAPIListenerDefault;
using deephaven::openAPI::lowlevel::remoting::DHWorkerSession;
using deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Batch;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ComboAggregate;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ConstructSnapshotQuery;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HeadBy;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Join;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Select;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Subscribe;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TailBy;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Snapshot;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Unsubscribe;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Update;
using deephaven::openAPI::highlevel::impl::ApplyAggregatesOperation;
using deephaven::openAPI::highlevel::fluent::SortDirection;
using deephaven::openAPI::highlevel::fluent::impl::ColumnImpl;
using deephaven::openAPI::highlevel::fluent::impl::DateTimeColImpl;
using deephaven::openAPI::highlevel::fluent::impl::NumColImpl;
using deephaven::openAPI::highlevel::fluent::impl::StrColImpl;
using deephaven::openAPI::highlevel::XXXTableSnapshot;
using deephaven::openAPI::highlevel::XXXTableUpdate;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::utility::stringVecToShared;
using deephaven::openAPI::utility::Void;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {

namespace {
std::shared_ptr<BitSet> getColumnsBitSet(const std::vector<std::string> &desiredColumns,
    const InitialTableDefinition &itd);
}  // namespace

namespace internal {
class LowToHighSnapshotAdaptor final : public DHWorkerSession::snapshotCallback_t {
  struct Private {};
public:
  std::shared_ptr<LowToHighSnapshotAdaptor> create(
      std::shared_ptr<QueryTableImpl> queryTableImpl,
      std::shared_ptr<QueryTable::snapshotCallback_t> highLevelHandler);

  LowToHighSnapshotAdaptor(Private, QueryTable queryTable,
      std::shared_ptr<QueryTable::snapshotCallback_t> highLevelHandler);
  ~LowToHighSnapshotAdaptor() final;

  void invoke(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<TableSnapshot> &snapshot) final;

  const std::shared_ptr<QueryTable::snapshotCallback_t> &highLevelHandler() const { return highLevelHandler_; }

private:
  // Keep one of these around so we can reuse it in our callback
  QueryTable queryTable_;
  std::shared_ptr<QueryTable::snapshotCallback_t> highLevelHandler_;
};

class LowToHighUpdateAdaptor final : public DHWorkerSession::updateCallback_t {
  struct Private {};
public:
  static std::shared_ptr<LowToHighUpdateAdaptor> create(
      std::shared_ptr<QueryTableImpl> queryTableImpl,
      std::shared_ptr<QueryTable::updateCallback_t> highLevelHandler);

  LowToHighUpdateAdaptor(Private, QueryTable queryTable,
      std::shared_ptr<QueryTable::updateCallback_t> highLevelHandler);
  ~LowToHighUpdateAdaptor() final;

  void invoke(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<DeltaUpdates> &deltaUpdates) final;

  const std::shared_ptr<QueryTable::updateCallback_t> &highLevelHandler() const { return highLevelHandler_; }

private:
  // Keep one of these around so we can reuse it in our callback
  QueryTable queryTable_;
  std::shared_ptr<QueryTable::updateCallback_t> highLevelHandler_;
};
}  // namespace internal

std::shared_ptr<internal::LazyState> QueryTableImpl::createItdCallback(std::shared_ptr<Executor> executor) {
  return std::make_shared<internal::LazyState>(std::move(executor));
}

std::shared_ptr<internal::LazyStateOss> QueryTableImpl::createEtcCallback(std::shared_ptr<Executor> executor) {
  return std::make_shared<internal::LazyStateOss>(std::move(executor));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::create(std::shared_ptr<QueryScopeImpl> scope,
    std::shared_ptr<TableHandle> tableHandle, std::shared_ptr<internal::LazyState> itdCallback) {
  auto result = std::make_shared<QueryTableImpl>(Private(), std::move(scope), std::move(tableHandle),
      std::move(itdCallback));
  result->weakSelf_ = result;
  return result;
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::createOss(std::shared_ptr<QueryScopeImpl> scope,
    Ticket ticket, std::shared_ptr<internal::LazyStateOss> etcCallback) {
  auto result = std::make_shared<QueryTableImpl>(Private(), std::move(scope), std::move(ticket),
      std::move(etcCallback));
  result->weakSelf_ = result;
  return result;
}

QueryTableImpl::QueryTableImpl(Private, std::shared_ptr<QueryScopeImpl> scope,
    std::shared_ptr<TableHandle> tableHandle, std::shared_ptr<internal::LazyState> lazyState) :
    scope_(std::move(scope)), lazyState_(std::move(lazyState)) {
}

QueryTableImpl::QueryTableImpl(Private, std::shared_ptr<QueryScopeImpl> scope,
    Ticket ticket, std::shared_ptr<internal::LazyStateOss> lazyStateOss) :
    scope_(std::move(scope)), ticket_(std::move(ticket)), lazyStateOss_(std::move(lazyStateOss)) {
}

QueryTableImpl::~QueryTableImpl() = default;

std::shared_ptr<QueryTableImpl> QueryTableImpl::freeze() {
  throw std::runtime_error("SAD");
//  auto emptyColumns = std::make_shared<std::vector<std::shared_ptr<std::string>>>();
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->snapshotAsync(nullptr, tableHandle_, true,
//      std::move(emptyColumns), itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::snapshot(
    std::shared_ptr<QueryTableImpl> targetTable, bool doInitialSnapshot,
    std::vector<std::string> stampColumns) {
  throw std::runtime_error("SAD");
//  auto sharedSc = stringVecToShared(std::move(stampColumns));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->snapshotAsync(tableHandle_, targetTable->tableHandle_,
//      doInitialSnapshot, std::move(sharedSc), itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::select(std::vector<std::string> columnSpecs) {
  auto cb = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->selectAsync(ticket_, std::move(columnSpecs), cb);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::update(std::vector<std::string> columnSpecs) {
  auto cb = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->updateAsync(ticket_, std::move(columnSpecs), cb);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::view(std::vector<std::string> columnSpecs) {
  auto cb = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->viewAsync(ticket_, std::move(columnSpecs), cb);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::dropColumns(std::vector<std::string> columnSpecs) {
  throw std::runtime_error("SAD");
//  auto sharedSpecs = stringVecToShared(std::move(columnSpecs));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->dropColumnsAsync(tableHandle_, std::move(sharedSpecs),
//      itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::updateView(std::vector<std::string> columnSpecs) {
  auto cb = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->updateViewAsync(ticket_, std::move(columnSpecs), cb);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::where(std::string condition) {
  auto cb = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->whereAsync(ticket_, std::move(condition), cb);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::sort(std::vector<SortPair> sortPairs) {
  throw std::runtime_error("SAD");
//  auto sortDescriptors = std::make_shared<std::vector<std::shared_ptr<SortDescriptor>>>();
//  sortDescriptors->reserve(sortPairs.size());
//  auto ascDir = std::make_shared<std::string>("asc");
//  auto descDir = std::make_shared<std::string>("desc");
//  for (auto &sp : sortPairs) {
//    const auto &which = sp.direction() == SortDirection::Ascending ? ascDir : descDir;
//    auto spCol = std::make_shared<std::string>(sp.column());
//    // Re the 0 (columnIndex), I don't think this argument is used.
//    auto sd = SortDescriptor::create(0, which, std::move(spCol), sp.abs());
//    sortDescriptors->push_back(std::move(sd));
//  }
//
//  auto sharedSortPairs = std::make_shared<std::vector<SortPair>>(std::move(sortPairs));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->sortAsync(tableHandle_, std::move(sortDescriptors),
//      itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::preemptive(int32_t sampleIntervalMs) {
  throw std::runtime_error("SAD");
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->preemptiveAsync(tableHandle_, sampleIntervalMs,
//      itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::defaultAggregateByDescriptor(
    ComboAggregateRequest::Aggregate descriptor, std::vector<std::string> columnSpecs) {
  std::vector<ComboAggregateRequest::Aggregate> descriptors;
  descriptors.reserve(1);
  descriptors.push_back(std::move(descriptor));

  auto cb = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->comboAggregateDescriptorAsync(ticket_,
      std::move(descriptors), std::move(columnSpecs), false, cb);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::defaultAggregateByType(
    ComboAggregateRequest::AggType aggregateType, std::vector<std::string> columnSpecs) {
  ComboAggregateRequest::Aggregate descriptor;
  descriptor.set_type(aggregateType);
  return defaultAggregateByDescriptor(std::move(descriptor), std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::by(std::vector<std::string> columnSpecs) {
  throw std::runtime_error("SAD");
//  return defaultAggregateByType(ApplyAggregatesOperation::AggType::Array, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::by(
    std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> descriptors,
    std::vector<std::string> groupByColumns) {
  throw std::runtime_error("SAD");
//  auto spCols = stringVecToShared(std::move(groupByColumns));
//  auto aggStrategy = std::make_shared<std::string>(ApplyAggregatesOperation::Strategy::Default);
//
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->comboAggregateDescriptorAsync(tableHandle_,
//      std::move(aggStrategy), std::move(descriptors), std::move(spCols), false, itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::minBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::MIN, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::maxBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::MAX, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::sumBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::SUM, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::absSumBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::ABS_SUM, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::varBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::VAR, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::stdBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::STD, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::avgBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::AVG, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::lastBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::LAST, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::firstBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::FIRST, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::medianBy(std::vector<std::string> columnSpecs) {
  return defaultAggregateByType(ComboAggregateRequest::MEDIAN, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::percentileBy(double percentile, bool avgMedian,
    std::vector<std::string> columnSpecs) {
  ComboAggregateRequest::Aggregate descriptor;
  descriptor.set_type(ComboAggregateRequest::PERCENTILE);
  descriptor.set_percentile(percentile);
  descriptor.set_avg_median(avgMedian);
  return defaultAggregateByDescriptor(std::move(descriptor), std::move(columnSpecs));
  return defaultAggregateByDescriptor(std::move(descriptor), std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::percentileBy(double percentile,
    std::vector<std::string> columnSpecs) {
  return percentileBy(percentile, false, std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::countBy(std::string countByColumn,
    std::vector<std::string> columnSpecs) {
  auto spAggType = std::make_shared<std::string>(ApplyAggregatesOperation::AggType::Count);
  auto spColumn = std::make_shared<std::string>(std::move(countByColumn));
  auto descriptor = AggregateDescriptor::create(std::move(spAggType), nullptr, spColumn, nullptr);
  return defaultAggregateByDescriptor(std::move(descriptor), std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::wAvgBy(std::string weightColumn,
    std::vector<std::string> columnSpecs) {
  auto spAggType = std::make_shared<std::string>(ApplyAggregatesOperation::AggType::WeightedAvg);
  auto spColumn = std::make_shared<std::string>(std::move(weightColumn));
  auto descriptor = AggregateDescriptor::create(std::move(spAggType), nullptr,
      std::move(spAggType), nullptr);
  return defaultAggregateByDescriptor(std::move(descriptor), std::move(columnSpecs));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::tailBy(int64_t n,
    std::vector<std::string> columnSpecs) {
  throw std::runtime_error("SAD");
//  auto spColumnSpecs = stringVecToShared(std::move(columnSpecs));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->tailByAsync(tableHandle_, n, std::move(spColumnSpecs),
//      itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::headBy(int64_t n,
    std::vector<std::string> columnSpecs) {
  throw std::runtime_error("SAD");
//  auto spColumnSpecs = stringVecToShared(std::move(columnSpecs));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->headByAsync(tableHandle_, n, std::move(spColumnSpecs),
//      itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::tail(int64_t n) {
  return headOrTailHelper(false, n);
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::head(int64_t n) {
  return headOrTailHelper(true, n);
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::headOrTailHelper(bool head, int64_t n) {
  auto itdCallback = QueryTableImpl::createEtcCallback(scope_->lowLevelSession()->executor());
  auto resultTicket = scope_->lowLevelSession()->headOrTailAsync(ticket_, head, n, itdCallback);
  return QueryTableImpl::createOss(scope_, std::move(resultTicket), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::ungroup(bool nullFill,
    std::vector<std::string> groupByColumns) {
  throw std::runtime_error("SAD");
//  auto spCols = stringVecToShared(std::move(groupByColumns));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->ungroupAsync(tableHandle_, nullFill, std::move(spCols),
//      itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::merge(std::string keyColumn,
    std::shared_ptr<std::vector<std::shared_ptr<TableHandle>>> sourceHandles) {
  throw std::runtime_error("SAD");
//  auto spKeyColumn = std::make_shared<std::string>(std::move(keyColumn));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->mergeAsync(std::move(sourceHandles),
//      std::move(spKeyColumn), itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryTableImpl::internalJoin(JoinType joinType,
    const QueryTableImpl &rightSide, std::vector<std::string> columnsToMatch,
    std::vector<std::string> columnsToAdd) {
  throw std::runtime_error("SAD");
//  auto spCtm = stringVecToShared(std::move(columnsToMatch));
//  auto spCta = stringVecToShared(std::move(columnsToAdd));
//  auto itdCallback = QueryTableImpl::createItdCallback(scope_->lowLevelSession()->executor());
//  auto resultHandle = scope_->lowLevelSession()->internalJoinAsync(joinType, tableHandle_,
//      rightSide.tableHandle(), std::move(spCtm), std::move(spCta), itdCallback);
//  return QueryTableImpl::create(scope_, std::move(resultHandle), std::move(itdCallback));
}

void QueryTableImpl::getTableDataAsync(int64_t first, int64_t last,
    std::vector<std::string> columns,
    std::shared_ptr<SFCallback<std::shared_ptr<TableSnapshot>>> callback) {
  throw std::runtime_error("SAD");
//  auto self = weakSelf_.lock();
//
//  auto rangeVec = std::make_shared<std::vector<std::shared_ptr<Range>>>();
//  rangeVec->reserve(1);
//  rangeVec->push_back(Range::create(first, last));
//  auto rows = RangeSet::create(std::move(rangeVec));
//
//  auto colSet = std::set<std::string>(std::make_move_iterator(columns.begin()),
//      std::make_move_iterator(columns.end()));
//
//  struct adapter_t final : public SFCallback<std::shared_ptr<InitialTableDefinition>> {
//    adapter_t(std::shared_ptr<QueryTableImpl> &&outer, std::shared_ptr<RangeSet> &&rows,
//        std::set<std::string> &&colSet, std::shared_ptr<SFCallback<std::shared_ptr<TableSnapshot>>> &&callback) :
//        outer_(std::move(outer)), rows_(std::move(rows)), colSet_(std::move(colSet)), callback_(std::move(callback)) {}
//
//    void onSuccess(std::shared_ptr<InitialTableDefinition> item) final {
//      const auto &itd = *item;
//
//      std::vector<int32_t> indices;
//      const auto &cds = *itd.definition()->columns();
//      for (size_t i = 0; i < cds.size(); ++i) {
//        if (colSet_.find(*cds[i]->name()) != colSet_.end()) {
//          indices.push_back(i);
//        }
//      }
//      auto cols = BitSet::create(std::move(indices));
//      outer_->scope_->lowLevelSession()->getTableDataAsync(outer_->tableHandle_, std::move(rows_),
//          std::move(cols), std::move(callback_));
//    }
//
//    void onFailure(std::exception_ptr ep) final {
//      callback_->onFailure(std::move(ep));
//    }
//
//    std::shared_ptr<QueryTableImpl> outer_;
//    std::shared_ptr<RangeSet> rows_;
//    std::set<std::string> colSet_;
//    std::shared_ptr<SFCallback<std::shared_ptr<TableSnapshot>>> callback_;
//  };
//
//  auto adapter = std::make_shared<adapter_t>(weakSelf_.lock(), std::move(rows), std::move(colSet),
//      std::move(callback));
//  lazyState_->invoke(std::move(adapter));
}

void QueryTableImpl::subscribeAllAsync(std::vector<std::string> columns,
    std::shared_ptr<SFCallback<Void>> callback) {
  auto self = weakSelf_.lock();
  auto spColumns = std::make_shared<std::vector<std::string>>(std::move(columns));

  auto outer = [self, spColumns, callback](
      boost::variant<std::shared_ptr<InitialTableDefinition>, std::exception_ptr> v) mutable {
    auto *ep = boost::get<std::exception_ptr>(&v);
    if (ep != nullptr) {
      callback->onFailure(std::move(*ep));
      return;
    }
    const auto &itd = *boost::get<std::shared_ptr<InitialTableDefinition>>(v);

    if (!itd.isPreemptive()) {
      callback->onFailure(std::make_exception_ptr(std::runtime_error(
          "Cannot subscribe to non-preemptive table (call .preemptive() first).")));
      return;
    }

    auto colBitset = getColumnsBitSet(*spColumns, itd);
//    streamf(std::cerr, "Sending server a subscribe nubbin of %o %o\n",
//        self->tableHandle_->custom().serverId(), self->tableHandle_->custom().clientId());
//    self->scope_->lowLevelSession()->subscribeAllAsync(self->tableHandle_, std::move(colBitset),
//        false, std::move(callback));
  };

  lazyState_->invokeCallable(std::move(outer));
}

void QueryTableImpl::unsubscribeAsync(std::shared_ptr<SFCallback<Void>> callback) {
//  scope_->lowLevelSession()->unsubscribeAsync(tableHandle_, std::move(callback));
}

void QueryTableImpl::addTableUpdateHandler(const std::shared_ptr<QueryTable::updateCallback_t> &handler) {
  auto self = weakSelf_.lock();
  auto adaptor = internal::LowToHighUpdateAdaptor::create(std::move(self), std::move(handler));
  mutex_.lock();
  adaptors_.push_back(adaptor);
  mutex_.unlock();
//  streamf(std::cerr, "Adding a table handle update handler %o %o\n", tableHandle_->custom().serverId(), tableHandle_->custom().clientId());
//  scope_->lowLevelSession()->addTableUpdateHandler(tableHandle_, adaptor);
}

void QueryTableImpl::removeTableUpdateHandler(
    const std::shared_ptr<QueryTable::updateCallback_t> &handler) {
  std::unique_lock<std::mutex> lock(mutex_);
  auto pred = [&handler](const std::shared_ptr<internal::LowToHighUpdateAdaptor> &a) {
    return a->highLevelHandler() == handler;
  };
  auto ip = std::find_if(adaptors_.begin(), adaptors_.end(), pred);
  if (ip == adaptors_.end()) {
    return;
  }
  auto adaptor = std::move(*ip);
  adaptors_.erase(ip);
  lock.unlock();
//  streamf(std::cerr, "Removing a table handle update handler %o %o\n", tableHandle_->custom().serverId(), tableHandle_->custom().clientId());
//  scope_->lowLevelSession()->removeTableUpdateHandler(tableHandle_, adaptor);
}

std::vector<std::shared_ptr<ColumnImpl>> QueryTableImpl::getColumnImpls() {
  const auto &colDefs = lazyState_->columnDefinitions();
  std::vector<std::shared_ptr<ColumnImpl>> result;
  result.reserve(colDefs.size());
  for (const auto &cd : colDefs) {
    result.push_back(ColumnImpl::create(cd.first));
  }
  return result;
}

std::shared_ptr<NumColImpl> QueryTableImpl::getNumColImpl(boost::string_view columnName) {
//  const auto &colDefs = lazyState_->columnDefinitions();
//  // TODO(kosak): save yourself this copy
  std::string temp = columnName.to_string();
//  auto ip = colDefs.find(temp);
//  if (ip == colDefs.end()) {
//    throw std::runtime_error(stringf(R"(Column name "%o" is not in the table)", columnName));
//  }
  return NumColImpl::create(std::move(temp));
}

std::shared_ptr<StrColImpl> QueryTableImpl::getStrColImpl(boost::string_view columnName) {
//  const auto &colDefs = lazyState_->columnDefinitions();
//  // TODO(kosak): save yourself this copy
  std::string temp = columnName.to_string();
//  auto ip = colDefs.find(temp);
//  if (ip == colDefs.end()) {
//    throw std::runtime_error(stringf(R"(Column name "%o" is not in the table)", columnName));
//  }
  return StrColImpl::create(std::move(temp));
}

std::shared_ptr<DateTimeColImpl> QueryTableImpl::getDateTimeColImpl(boost::string_view columnName) {
//  const auto &colDefs = lazyState_->columnDefinitions();
//  // TODO(kosak): save yourself this copy
  std::string temp = columnName.to_string();
//  auto ip = colDefs.find(temp);
//  if (ip == colDefs.end()) {
//    throw std::runtime_error(stringf(R"(Column name "%o" is not in the table)", columnName));
//  }
  return DateTimeColImpl::create(std::move(temp));
}

void QueryTableImpl::bindToVariableAsync(std::string variable,
    std::shared_ptr<SFCallback<Void>> callback) {
  struct cb_t : public SFCallback<const Ticket &>, public SFCallback<BindTableToVariableResponse> {
    cb_t(std::shared_ptr<QueryScopeImpl> scope, std::string variable,
        std::shared_ptr<SFCallback<Void>> outerCb) : scope_(std::move(scope)),
        variable_(std::move(variable)), outerCb_(std::move(outerCb)) {}

    void onSuccess(const Ticket &ticket) final {
      std::cerr << "This is completely unnecessary, as ticket is known already...lazystateoss doesn't even need a ticketeroo\n";
      scope_->lowLevelSession()->bindToVariableAsync(ticket, std::move(variable_), weakSelf_.lock());
    }

    void onSuccess(BindTableToVariableResponse /*item*/) final {
      outerCb_->onSuccess(Void());
    }

    void onFailure(std::exception_ptr ep) override {
      outerCb_->onFailure(std::move(ep));
    }

    std::shared_ptr<QueryScopeImpl> scope_;
    std::string variable_;
    std::shared_ptr<SFCallback<Void>> outerCb_;
    std::weak_ptr<cb_t> weakSelf_;
  };
  auto cb = std::make_shared<cb_t>(scope_, std::move(variable), std::move(callback));
  cb->weakSelf_ = cb;
  lazyStateOss_->invoke(std::move(cb));
}

void QueryTableImpl::observe() {
  lazyStateOss_->waitUntilReady();
}

namespace internal {
LazyState::LazyState(std::shared_ptr<Executor> executor) : executor_(std::move(executor)) {}
LazyState::~LazyState() = default;

bool LazyState::ready() {
  std::unique_lock<std::mutex> lock(mutex_);
  return readyLocked(&lock);
}

void LazyState::waitUntilReady() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (true) {
    if (error_ != nullptr) {
      std::rethrow_exception(error_);
    }
    if (initialTableDefinition_ != nullptr) {
      return;
    }
    condVar_.wait(lock);
  }
}

void LazyState::onSuccess(std::shared_ptr<InitialTableDefinition> initialTableDefinition) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (readyLocked(&lock)) {
    return;
  }

  const auto &cds = *initialTableDefinition->definition()->columns();
  for (const auto &cd : cds) {
    columnDefinitions_[*cd->name()] = cd;
  }
  initialTableDefinition_ = initialTableDefinition;

  auto spLocalWaiters = std::make_shared<std::vector<std::shared_ptr<waiter_t>>>();
  spLocalWaiters->swap(waiters_);
  lock.unlock();
  condVar_.notify_all();

  if (spLocalWaiters->empty()) {
    return;
  }

  auto cb = [spLocalWaiters, initialTableDefinition](Void) {
    for (const auto &waiter : *spLocalWaiters) {
      waiter->onSuccess(initialTableDefinition);
    }
  };
  executor_->invokeCallable(std::move(cb));
}

void LazyState::onFailure(std::exception_ptr error) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (readyLocked(&lock)) {
    return;
  }
  error_ = error;

  auto spLocalWaiters = std::make_shared<std::vector<std::shared_ptr<waiter_t>>>();
  spLocalWaiters->swap(waiters_);
  lock.unlock();
  condVar_.notify_all();

  if (spLocalWaiters->empty()) {
    return;
  }

  auto cb = [spLocalWaiters, error](Void) {
    for (const auto &waiter : *spLocalWaiters) {
      waiter->onFailure(error);
    }
  };
  executor_->invokeCallable(std::move(cb));
}

void LazyState::invoke(std::shared_ptr<waiter_t> callback) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (!readyLocked(&lock)) {
    waiters_.push_back(std::move(callback));
    return;
  }
  // Already ready, so grab state
  auto itd = initialTableDefinition_;
  auto ep = error_;
  lock.unlock();

  // And then invoke callback (but not under lock)
  if (ep != nullptr) {
    callback->onFailure(std::move(ep));
  }
  callback->onSuccess(std::move(itd));
}

bool LazyState::readyLocked(std::unique_lock<std::mutex> */*lock*/) {
  return error_ != nullptr || initialTableDefinition_ != nullptr;
}

LazyStateOss::LazyStateOss(std::shared_ptr<Executor> executor) : executor_(std::move(executor)) {}
LazyStateOss::~LazyStateOss() = default;

//void LazyStateOss::onSuccess(ExportedTableCreationResponse item) {
//  std::cerr << "ZAMBONI TIME SUCCESS!!!\n";
//  streamf(std::cerr, "Zamboni time succ=%o err=%o\n", item.success(), item.error_info());
//  streamf(std::cerr, "Zamboni ref case=%o\n", item.result_id().ref_case());
//  if (item.result_id().ref_case() == TableReference::RefCase::kTicket) {
//    const char *q = item.result_id().ticket().ticket().data();
//    (void)q;
//    std::cerr << "ZAMBONI TICKET\n";
//  }
//  std::cerr << "ZAMBONI TIME SUCCESS2222!!!\n";
//}

//void LazyStateOss::onFailure(std::exception_ptr ep) {
//  std::cerr << "ZAMBONI FAILURE\n";
//}

void LazyStateOss::onSuccess(ExportedTableCreationResponse item) {
  if (!item.result_id().has_ticket()) {
    auto ep = std::make_exception_ptr(std::runtime_error(
        "ExportedTableCreationResponse did not contain a ticket"));
    onFailure(std::move(ep));
    return;
  }

  std::unique_lock<std::mutex> lock(mutex_);
  if (readyLocked(&lock)) {
    return;
  }

  ticket_ = std::move(*item.mutable_result_id()->mutable_ticket());
  success_ = true;

  // Notify any waiters
  auto spLocalWaiters = std::make_shared<std::vector<std::shared_ptr<waiter_t>>>();
  spLocalWaiters->swap(waiters_);
  lock.unlock();
  condVar_.notify_all();

  if (spLocalWaiters->empty()) {
    return;
  }

  auto spTicket = std::make_shared<Ticket>(ticket_);
  auto cb = [spLocalWaiters, spTicket](Void) {
    for (const auto &waiter : *spLocalWaiters) {
      waiter->onSuccess(*spTicket);
    }
  };
  executor_->invokeCallable(std::move(cb));
}

void LazyStateOss::onFailure(std::exception_ptr error) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (readyLocked(&lock)) {
    return;
  }
  error_ = error;

  auto spLocalWaiters = std::make_shared<std::vector<std::shared_ptr<waiter_t>>>();
  spLocalWaiters->swap(waiters_);
  lock.unlock();
  condVar_.notify_all();

  if (spLocalWaiters->empty()) {
    return;
  }

  auto cb = [spLocalWaiters, error](Void) {
    for (const auto &waiter : *spLocalWaiters) {
      waiter->onFailure(error);
    }
  };
  executor_->invokeCallable(std::move(cb));
}

void LazyStateOss::invoke(std::shared_ptr<waiter_t> callback) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (!readyLocked(&lock)) {
    waiters_.push_back(std::move(callback));
    return;
  }
  // Already ready, so grab state
  auto ep = error_;
  lock.unlock();

  // And then invoke callback (but not under lock)
  if (ep != nullptr) {
    callback->onFailure(std::move(ep));
  }
  callback->onSuccess(ticket_);
}

void LazyStateOss::waitUntilReady() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (true) {
    if (error_ != nullptr) {
      std::rethrow_exception(error_);
    }
    if (success_) {
      return;
    }
    condVar_.wait(lock);
  }
}

bool LazyStateOss::readyLocked(std::unique_lock<std::mutex> */*lock*/) {
  return error_ != nullptr || success_;
}

std::shared_ptr<LowToHighSnapshotAdaptor> LowToHighSnapshotAdaptor::create(
    std::shared_ptr<QueryTableImpl> queryTableImpl,
    std::shared_ptr<QueryTable::snapshotCallback_t> handler) {
  QueryTable queryTable(std::move(queryTableImpl));
  return std::make_shared<LowToHighSnapshotAdaptor>(Private(), std::move(queryTable),
      std::move(handler));
}

LowToHighSnapshotAdaptor::LowToHighSnapshotAdaptor(Private, QueryTable queryTable,
    std::shared_ptr<QueryTable::snapshotCallback_t> highLevelHandler) :
    queryTable_(std::move(queryTable)), highLevelHandler_(std::move(highLevelHandler)) {}
LowToHighSnapshotAdaptor::~LowToHighSnapshotAdaptor() = default;

void LowToHighSnapshotAdaptor::invoke(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<TableSnapshot> &snapshot) {
  XXXTableSnapshot highLevelSnapshot;
  highLevelHandler_->invoke(queryTable_, highLevelSnapshot);
}

std::shared_ptr<LowToHighUpdateAdaptor> LowToHighUpdateAdaptor::create(
    std::shared_ptr<QueryTableImpl> queryTableImpl,
    std::shared_ptr<QueryTable::updateCallback_t> handler) {
  QueryTable queryTable(std::move(queryTableImpl));
  return std::make_shared<LowToHighUpdateAdaptor>(Private(), std::move(queryTable), std::move(handler));
}

LowToHighUpdateAdaptor::LowToHighUpdateAdaptor(Private, QueryTable queryTable,
    std::shared_ptr<QueryTable::updateCallback_t> highLevelHandler) :
    queryTable_(std::move(queryTable)), highLevelHandler_(std::move(highLevelHandler)) {}
LowToHighUpdateAdaptor::~LowToHighUpdateAdaptor() = default;

void LowToHighUpdateAdaptor::invoke(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<DeltaUpdates> &deltaUpdates) {
  // assert tableHandle == queryTable_.tableHandle()
  // TODO(kosak): translate deltaUpdates here
  XXXTableUpdate update;
  highLevelHandler_->invoke(queryTable_, update);
}
}  // namespace internal

namespace {
std::shared_ptr<BitSet> getColumnsBitSet(const std::vector<std::string> &desiredColumns,
    const InitialTableDefinition &itd) {
  std::vector<int32_t> items;

  const auto &tableColumns = *itd.definition()->columns();
  // create the columns bit set
  if (desiredColumns.empty()) {
    // empty vector means "all".
    items.reserve(tableColumns.size());
    for (size_t i = 0; i < tableColumns.size(); ++i) {
      items.push_back(i);
    }
  } else {
    std::vector<boost::string_view> lookup;
    lookup.reserve(desiredColumns.size());
    for (const auto &s : desiredColumns) {
      lookup.emplace_back(s);
    }
    std::sort(lookup.begin(), lookup.end());
    for (size_t i = 0; i < tableColumns.size(); ++i) {
      if (std::binary_search(lookup.begin(), lookup.end(), *tableColumns[i]->name())) {
        items.push_back(i);
      }
    }
  }
  return BitSet::create(std::move(items));
}
}  // namespace
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
