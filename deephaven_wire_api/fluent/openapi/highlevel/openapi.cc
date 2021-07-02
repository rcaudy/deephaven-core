#include "highlevel/openapi.h"

#include <boost/variant.hpp>
#include "highlevel/impl/columns_impl.h"
#include "highlevel/impl/boolean_expression_impl.h"
#include "highlevel/impl/aggregate_impl.h"
#include "highlevel/impl/client_impl.h"
#include "highlevel/impl/query_scope_impl.h"
#include "highlevel/impl/query_table_impl.h"
#include "highlevel/impl/worker_session_impl.h"
#include "highlevel/columns.h"
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/dhserver.h"
#include "utility/utility.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using io::deephaven::proto::backplane::grpc::HandshakeRequest;
using io::deephaven::proto::backplane::grpc::HandshakeResponse;
using deephaven::openAPI::core::SFCallback;
using deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void;
using deephaven::openAPI::lowlevel::remoting::DHServer;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Catalog;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot;
using deephaven::openAPI::highlevel::fluent::Column;
using deephaven::openAPI::highlevel::fluent::DateTimeCol;
using deephaven::openAPI::highlevel::fluent::NumCol;
using deephaven::openAPI::highlevel::fluent::StrCol;
using deephaven::openAPI::highlevel::fluent::impl::StrColImpl;
using deephaven::openAPI::highlevel::impl::AggregateComboImpl;
using deephaven::openAPI::highlevel::impl::AggregateImpl;
using deephaven::openAPI::highlevel::impl::ClientImpl;
using deephaven::openAPI::highlevel::impl::WorkerOptionsImpl;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::utility::stringVecToShared;
using deephaven::openAPI::utility::Executor;

namespace deephaven {
namespace openAPI {
namespace highlevel {
Client OpenApi::connect(boost::string_view host, int port) {
  auto executor = Executor::create();
  auto server = DHServer::createFromHostAndPort(host, port, executor);
  auto impl = ClientImpl::create(std::move(server), executor);
  return Client(std::move(impl));
}

Client OpenApi::connectOss(const std::string &target) {
  auto executor = Executor::create();
  auto server = DHServer::createFromTarget(target, executor);
  auto impl = ClientImpl::create(std::move(server), executor);
  return Client(std::move(impl));
}

Client::Client(std::shared_ptr<impl::ClientImpl> impl) : impl_(std::move(impl)) {}
Client::Client(Client &&other) noexcept = default;
Client &Client::operator=(Client &&other) noexcept = default;
Client::~Client() {
  // TODO(kosak)
  std::cerr << "tear down client\n";
}

void Client::login(std::string user, std::string password, std::string operateAs) {
  auto res = SFCallback<Void>::createForFuture();
  loginAsync(std::move(user), std::move(password), std::move(operateAs), std::move(res.first));
  (void)res.second.get();
}

void Client::loginAsync(std::string user, std::string password, std::string operateAs,
    std::shared_ptr<SFCallback<Void>> callback) {
  impl_->loginAsync(std::move(user), std::move(password), std::move(operateAs), std::move(callback));
}

WorkerSession Client::startWorker(const WorkerOptions &options) {
  auto res = SFCallback<WorkerSession>::createForFuture();
  startWorkerAsync(options, std::move(res.first));
  auto result = res.second.get();
  return result;
}

void Client::startWorkerAsync(const WorkerOptions &options,
    std::shared_ptr<SFCallback<WorkerSession>> callback) {
  struct innerCb_t final : public SFCallback<std::shared_ptr<impl::WorkerSessionImpl>> {
    explicit innerCb_t(std::shared_ptr<SFCallback<WorkerSession>> outer) : outer_(std::move(outer)) {}

    void onSuccess(std::shared_ptr<impl::WorkerSessionImpl> item) final {
      WorkerSession result(std::move(item));
      outer_->onSuccess(std::move(result));
    }

    void onFailure(std::exception_ptr ep) final {
      outer_->onFailure(std::move(ep));
    }

    std::shared_ptr<SFCallback<WorkerSession>> outer_;
  };

  auto innerCb = std::make_shared<innerCb_t>(std::move(callback));
  impl_->startWorkerAsync(options.impl(), std::move(innerCb));
}

WorkerSession::WorkerSession(std::shared_ptr<impl::WorkerSessionImpl> impl) : impl_(std::move(impl)) {}
WorkerSession::WorkerSession(WorkerSession &&other) noexcept = default;
WorkerSession &WorkerSession::operator=(WorkerSession &&other) noexcept = default;
WorkerSession::~WorkerSession() {
  // TODO(kosak)
  std::cerr << "tear down worker session\n";
}

QueryScope WorkerSession::queryScope() {
  auto qsImpl = impl_->queryScope();
  return QueryScope(std::move(qsImpl));
}

RowRangeSet::RowRangeSet(std::shared_ptr<RangeSet> rs) : rs_(std::move(rs)) {
  count_ = 0;
  for (const auto &r : *rs_->sortedRanges()) {
    count_ += r->last() - r->first() + 1;
  }
}

TableData TableData::create(const std::vector<std::shared_ptr<ColumnDefinition>> &colDefs,
    const TableSnapshot &snapshot) {
  RowRangeSet rrs(snapshot.includedRows());

  const auto &dataCols = *snapshot.dataColumns();
  std::vector<std::shared_ptr<ColumnData>> columnData;
  columnData.reserve(dataCols.size());
  for (size_t i = 0; i < dataCols.size(); ++i) {
    const auto *dc = dataCols[i].get();
    columnData.push_back(dc == nullptr ? nullptr : ColumnData::createFromColdef(*colDefs[i], *dc));
  }
  return TableData(std::move(columnData), snapshot.tableSize(), std::move(rrs));
}

TableData::TableData(std::vector<std::shared_ptr<ColumnData>> &&columnData, int64_t tableSize,
    RowRangeSet &&includedRows) : columnData_(std::move(columnData)), tableSize_(tableSize),
    includedRows_(std::move(includedRows)) {}
TableData::TableData(TableData &&other) noexcept = default;
TableData &TableData::operator=(TableData &&other) noexcept = default;
TableData::~TableData() = default;

DatabaseCatalogTable::DatabaseCatalogTable(std::shared_ptr<impl::DatabaseCatalogTableImpl> impl) :
    impl_(std::move(impl)) {}
DatabaseCatalogTable::~DatabaseCatalogTable() = default;

const std::string &DatabaseCatalogTable::nameSpaceSet() const {
  return *impl_->catalog()->namespaceSet();
}

const std::string &DatabaseCatalogTable::nameSpace() const {
  return *impl_->catalog()->nameSpace();
}

const std::string & DatabaseCatalogTable::tableName() const {
  return *impl_->catalog()->tableName();
}

DatabaseCatalog::DatabaseCatalog(std::vector<DatabaseCatalogTable> tables) : tables_(std::move(tables)) {}
DatabaseCatalog::~DatabaseCatalog() = default;

NullableString::NullableString(const char *s) {
  if (s != nullptr) {
    value_ = std::make_shared<std::string>(s);
  }
}

NullableString::NullableString(std::string s) : value_(std::make_shared<std::string>(std::move(s))) {
}

std::shared_ptr<std::string> NullableString::release() {
  return std::move(value_);
}

QueryScope::QueryScope(std::shared_ptr<impl::QueryScopeImpl> impl) : impl_(std::move(impl)) {}
QueryScope::QueryScope(QueryScope &&other) noexcept = default;
QueryScope &QueryScope::operator=(QueryScope &&other) noexcept = default;
QueryScope::~QueryScope() {
  // TODO(kosak)
  std::cerr << "tear down query scope\n";
}

QueryTable QueryScope::emptyTable(int64_t size, std::vector<std::string> columnNames,
    std::vector<std::string> columnTypes) const {
  auto qsImpl = impl_->emptyTable(size, std::move(columnNames), std::move(columnTypes));
  return QueryTable(std::move(qsImpl));
}

QueryTable QueryScope::fetchTable(std::string tableName) const {
  auto qsImpl = impl_->fetchTable(std::move(tableName));
  return QueryTable(std::move(qsImpl));
}

QueryTable QueryScope::historicalTable(std::string nameSpace, std::string tableName) const {
  auto qsImpl = impl_->historicalTable(std::move(nameSpace), std::move(tableName));
  return QueryTable(std::move(qsImpl));
}

QueryTable QueryScope::tempTable(const std::vector<ColumnDataHolder> &columnDataHolders) const {
  auto qsImpl = impl_->tempTable(columnDataHolders);
  return QueryTable(std::move(qsImpl));
}

QueryTable QueryScope::timeTable(int64_t startTimeNanos, int64_t periodNanos) const {
  auto qsImpl = impl_->timeTable(startTimeNanos, periodNanos);
  return QueryTable(std::move(qsImpl));
}

QueryTable QueryScope::timeTable(std::chrono::system_clock::time_point startTime,
    std::chrono::system_clock::duration period) const {
  auto stNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(startTime.time_since_epoch()).count();
  auto dNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(period).count();
  return timeTable(stNanos, dNanos);
}

DatabaseCatalog QueryScope::getDatabaseCatalog(bool systemNamespaces, bool userNamespaces,
    NullableString namespaceRegex, NullableString tableRegex) const {
  auto res = SFCallback<DatabaseCatalog>::createForFuture();
  getDatabaseCatalogAsync(systemNamespaces, userNamespaces, std::move(namespaceRegex),
      std::move(tableRegex), std::move(res.first));
  return res.second.get();
}

void QueryScope::getDatabaseCatalogAsync(bool systemNamespaces, bool userNamespaces,
    NullableString namespaceRegex, NullableString tableRegex,
    std::shared_ptr<SFCallback<DatabaseCatalog>> callback) const {
  struct inner_t final : public SFCallback<std::shared_ptr<Catalog>> {
    explicit inner_t(std::shared_ptr<SFCallback<DatabaseCatalog>> outer) : outer_(std::move(outer)) {}

    void onSuccess(std::shared_ptr<Catalog> item) final {
      std::vector<DatabaseCatalogTable> tables;
      tables.reserve(item->tables()->size());

      for (const auto &innerTable : *item->tables()) {
        auto impl = impl::DatabaseCatalogTableImpl::create(innerTable);
        tables.emplace_back(std::move(impl));
      }
      outer_->onSuccess(DatabaseCatalog(std::move(tables)));
    }

    void onFailure(std::exception_ptr ep) final {
      outer_->onFailure(std::move(ep));
    }

    std::shared_ptr<SFCallback<DatabaseCatalog>> outer_;
  };

  auto innerCallback = std::make_shared<inner_t>(std::move(callback));
  impl_->lowLevelSession()->getDatabaseCatalogAsync(systemNamespaces, userNamespaces,
      namespaceRegex.release(), tableRegex.release(), std::move(innerCallback));
}

QueryTable QueryScope::catalogTable() const {
  auto qsImpl = impl_->catalogTable();
  return QueryTable(std::move(qsImpl));
}

namespace {
class AggType {
public:
  static constexpr const char count[] = "Count";
  static constexpr const char min[] = "Min";
  static constexpr const char max[] = "Max";
  static constexpr const char sum[] = "Sum";
  static constexpr const char absSum[] = "AbsSum";
  static constexpr const char var[] = "Var";
  static constexpr const char avg[] = "Avg";
  static constexpr const char std[] = "Std";
  static constexpr const char first[] = "First";
  static constexpr const char last[] = "Last";
  static constexpr const char array[] = "Array";
  static constexpr const char percentile[] = "Percentile";
  static constexpr const char weightedAvg[] = "WeightedAvg";
  static constexpr const char median[] = "Median";
};

const char AggType::count[];
const char AggType::min[];
const char AggType::max[];
const char AggType::sum[];
const char AggType::absSum[];
const char AggType::var[];
const char AggType::avg[];
const char AggType::std[];
const char AggType::first[];
const char AggType::last[];
const char AggType::array[];
const char AggType::percentile[];
const char AggType::weightedAvg[];
const char AggType::median[];

std::shared_ptr<AggregateDescriptor> createDescForMatchPairs(const char *aggregateType,
    std::vector<std::string> columnSpecs) {
  auto spAggType = std::make_shared<std::string>(aggregateType);
  auto spMatchPairs = stringVecToShared(std::move(columnSpecs));
  return AggregateDescriptor::create(std::move(spAggType), std::move(spMatchPairs), nullptr, nullptr);
}

std::shared_ptr<AggregateDescriptor> createDescForColumn(const char *aggregateType,
    std::string columnSpec) {
  auto spAggType = std::make_shared<std::string>(aggregateType);
  auto spColSpec = std::make_shared<std::string>(std::move(columnSpec));
  return AggregateDescriptor::create(std::move(spAggType), nullptr, std::move(spColSpec), nullptr);
}
}

Aggregate::Aggregate(std::shared_ptr<impl::AggregateImpl> impl) : impl_(std::move(impl)) {
}

Aggregate Aggregate::absSum(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::array, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::avg(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::avg, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::count(std::string columnSpec) {
  auto ad = createDescForColumn(AggType::count, std::move(columnSpec));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::first(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::first, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::last(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::last, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::max(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::max, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::med(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::median, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::min(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::min, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::pct(double percentile, bool avgMedian, std::vector<std::string> columnSpecs) {
  auto pd = PercentileDescriptor::create(percentile, avgMedian);
  auto spMatchPairs = stringVecToShared(std::move(columnSpecs));
  auto spAggType = std::make_shared<std::string>(AggType::percentile);
  auto ad = AggregateDescriptor::create(std::move(spAggType), std::move(spMatchPairs), nullptr,
      std::move(pd));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::std(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::std, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::sum(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::sum, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::var(std::vector<std::string> columnSpecs) {
  auto ad = createDescForMatchPairs(AggType::var, std::move(columnSpecs));
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

Aggregate Aggregate::wavg(std::string weightColumn, std::vector<std::string> columnSpecs) {
  auto spWeightColumn = std::make_shared<std::string>(std::move(weightColumn));
  auto spMatchPairs = stringVecToShared(std::move(columnSpecs));
  auto spAgg = std::make_shared<std::string>(AggType::weightedAvg);
  auto ad = AggregateDescriptor::create(std::move(spAgg), std::move(spMatchPairs),
      std::move(spWeightColumn), nullptr);
  auto impl = AggregateImpl::create(std::move(ad));
  return Aggregate(std::move(impl));
}

AggregateCombo AggregateCombo::create(std::initializer_list<Aggregate> list) {
  auto aggregates = std::make_shared<std::vector<std::shared_ptr<AggregateDescriptor>>>();
  aggregates->reserve(list.size());
  for (const auto &item : list) {
    aggregates->push_back(item.impl()->descriptor());
  }
  auto impl = AggregateComboImpl::create(std::move(aggregates));
  return AggregateCombo(std::move(impl));
}

AggregateCombo AggregateCombo::create(std::vector<Aggregate> vec) {
  auto aggregates = std::make_shared<std::vector<std::shared_ptr<AggregateDescriptor>>>();
  aggregates->reserve(vec.size());
  for (const auto &item : vec) {
    aggregates->push_back(item.impl()->descriptor());
  }
  auto impl = AggregateComboImpl::create(std::move(aggregates));
  return AggregateCombo(std::move(impl));
}

AggregateCombo::AggregateCombo(std::shared_ptr<impl::AggregateComboImpl> impl) : impl_(std::move(impl)) {}
AggregateCombo::~AggregateCombo() = default;

XXXTableSnapshot::XXXTableSnapshot() = default;
XXXTableSnapshot::~XXXTableSnapshot() = default;

XXXTableUpdate::XXXTableUpdate() = default;
XXXTableUpdate::~XXXTableUpdate() = default;

QueryTable::QueryTable(std::shared_ptr<impl::QueryTableImpl> impl) : impl_(std::move(impl)) {}
QueryTable::QueryTable(const QueryTable &other) = default;
QueryTable & QueryTable::operator=(const QueryTable &other) = default;
QueryTable::QueryTable(QueryTable &&other) noexcept = default;
QueryTable &QueryTable::operator=(QueryTable &&other) noexcept = default;
QueryTable::~QueryTable() {
  // TODO(kosak)
  std::cerr << "tear down query table\n";
}

QueryScope QueryTable::scope() const {
  return QueryScope(impl_->scope());
}

QueryTable QueryTable::freeze() const {
  auto qtImpl = impl_->freeze();
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::snapshot(const QueryTable &targetTable, bool doInitialSnapshot,
    std::vector<std::string> stampColumns) const {
  auto qtImpl = impl_->snapshot(targetTable.impl_, doInitialSnapshot, std::move(stampColumns));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::where(const BooleanExpression &condition) const {
  // TODO(kosak): get rid of the temporary shared ptr created here
  auto conditionAsString = condition.implAsBooleanExpressionImpl()->toIrisRepresentation();
  return where(std::move(conditionAsString));
}

QueryTable QueryTable::where(std::string condition) const {
  auto qtImpl = impl_->where(std::move(condition));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::sort(std::vector<SortPair> sortPairs) const {
  auto qtImpl = impl_->sort(std::move(sortPairs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::preemptive(int sampleIntervalMs) {
  std::cerr << "TODO(kosak): what to do about preemptive?\n";
  return QueryTable(impl_);
}

TableData QueryTable::getTableData(long first, long last, std::vector<std::string> columns) const {
  auto res = SFCallback<TableData>::createForFuture();
  getTableDataAsync(first, last, std::move(columns), std::move(res.first));
  return res.second.get();
}

void QueryTable::getTableDataAsync(long first, long last,
    std::vector<std::string> columns, std::shared_ptr<SFCallback<TableData>> callback) const {

  struct adapter_t final : public SFCallback<std::shared_ptr<TableSnapshot>> {
    adapter_t(std::shared_ptr<impl::QueryTableImpl> impl, std::shared_ptr<SFCallback<TableData>> outer) :
        impl_(std::move(impl)), outer_(std::move(outer)) {}

    void onSuccess(std::shared_ptr<TableSnapshot> snapshot) final {
      // This is not blocking because we won't be called back until we have an initial table definition ready
      const auto &colDefs = impl_->getColumnDefinitions();
      auto td = TableData::create(*colDefs, *snapshot);
      outer_->onSuccess(std::move(td));
    }

    void onFailure(std::exception_ptr ep) final {
      outer_->onFailure(std::move(ep));
    }

    std::shared_ptr<impl::QueryTableImpl> impl_;
    std::shared_ptr<SFCallback<TableData>> outer_;
  };

  auto outerCallback = std::make_shared<adapter_t>(impl_, std::move(callback));
  impl_->getTableDataAsync(first, last, std::move(columns), std::move(outerCallback));
}

void QueryTable::subscribeAll(std::vector<std::string> columnSpecs) const {
  auto res = SFCallback<Void>::createForFuture();
  subscribeAllAsync(std::move(columnSpecs), std::move(res.first));
  res.second.get();
}

void QueryTable::subscribeAllAsync(std::vector<std::string> columnSpecs,
    std::shared_ptr<SFCallback<Void>> callback) const {
  impl_->subscribeAllAsync(std::move(columnSpecs), std::move(callback));
}

void QueryTable::unsubscribe() const {
  auto res = SFCallback<Void>::createForFuture();
  unsubscribeAsync(std::move(res.first));
  res.second.get();
}

void QueryTable::unsubscribeAsync(std::shared_ptr<SFCallback<Void>> callback) const {
  impl_->unsubscribeAsync(std::move(callback));
}

void QueryTable::addTableUpdateHandler(const std::shared_ptr<updateCallback_t> &handler) const {
  return impl_->addTableUpdateHandler(handler);
}

void QueryTable::removeTableUpdateHandler(const std::shared_ptr<updateCallback_t> &handler) const {
  return impl_->removeTableUpdateHandler(handler);
}

std::vector<Column> QueryTable::getColumns() const {
  auto columnImpls = impl_->getColumnImpls();
  std::vector<Column> result;
  result.reserve(columnImpls.size());
  for (const auto &ci : columnImpls) {
    result.emplace_back(ci);
  }
  return result;
}

StrCol QueryTable::getStrCol(boost::string_view columnName) const {
  auto scImpl = impl_->getStrColImpl(columnName);
  return StrCol(std::move(scImpl));
}

NumCol QueryTable::getNumCol(boost::string_view columnName) const {
  auto ncImpl = impl_->getNumColImpl(columnName);
  return NumCol(std::move(ncImpl));
}

DateTimeCol QueryTable::getDateTimeCol(boost::string_view columnName) const {
  auto dtImpl = impl_->getDateTimeColImpl(columnName);
  return DateTimeCol(std::move(dtImpl));
}

int64_t QueryTable::hackGetSizeFromTableDefinition() const {
  return impl_->hackGetSizeFromTableDefinition();
}

QueryTable QueryTable::select(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->select(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::update(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->update(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::view(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->view(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::dropColumns(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->dropColumns(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::updateView(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->updateView(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::by(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->by(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::by(AggregateCombo combo, std::vector<std::string> groupByColumns) const {
  auto qtImpl = impl_->by(combo.impl()->aggregates(), std::move(groupByColumns));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::minBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->minBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::maxBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->maxBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::sumBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->sumBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::absSumBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->absSumBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::varBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->varBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::stdBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->stdBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::avgBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->avgBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::lastBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->lastBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::firstBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->firstBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::medianBy(std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->medianBy(std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::percentileBy(double percentile, bool avgMedian,
    std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->percentileBy(percentile, avgMedian, std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::percentileBy(double percentile, std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->percentileBy(percentile, std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::countBy(std::string countByColumn, std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->countBy(std::move(countByColumn), std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::wAvgBy(std::string weightColumn, std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->wAvgBy(std::move(weightColumn), std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::tailBy(int64_t n, std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->tailBy(n, std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::headBy(int64_t n, std::vector<std::string> columnSpecs) const {
  auto qtImpl = impl_->headBy(n, std::move(columnSpecs));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::head(int64_t n) const {
  auto qtImpl = impl_->head(n);
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::tail(int64_t n) const {
  auto qtImpl = impl_->tail(n);
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::ungroup(bool nullFill, std::vector<std::string> groupByColumns) const {
  auto qtImpl = impl_->ungroup(nullFill, std::move(groupByColumns));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::merge(std::string keyColumn, std::vector<QueryTable> sources) const {
  auto sourceHandles = std::make_shared<std::vector<std::shared_ptr<TableHandle>>>();
  sourceHandles->reserve(sources.size() + 1);
//  sourceHandles->push_back(impl_->tableHandle());
//  for (const auto &source : sources) {
//    sourceHandles->push_back(source.impl()->tableHandle());
//  }

  auto qtImpl = impl_->merge(std::move(keyColumn), std::move(sourceHandles));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::internalJoin(JoinType joinType, const QueryTable &rightSide,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const {
  auto qtImpl = impl_->internalJoin(joinType, *rightSide.impl_, std::move(columnsToMatch),
      std::move(columnsToAdd));
  return QueryTable(std::move(qtImpl));
}

QueryTable QueryTable::internalJoin(JoinType joinType, const QueryTable &rightSide,
    std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const {
  std::vector<std::string> ctmStrings;
  std::vector<std::string> ctaStrings;
  ctmStrings.reserve(columnsToMatch.size());
  ctaStrings.reserve(columnsToAdd.size());
  for (const auto &ctm : columnsToMatch) {
    ctmStrings.push_back(ctm.getIrisRepresentableImpl()->toIrisRepresentation());
  }
  for (const auto &cta : columnsToAdd) {
    ctaStrings.push_back(cta.getIrisRepresentableImpl()->toIrisRepresentation());
  }
  return internalJoin(joinType, rightSide, std::move(ctmStrings), std::move(ctaStrings));
}

QueryTable QueryTable::naturalJoin(const QueryTable &rightSide,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const {
  return internalJoin(JoinType::Natural, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::naturalJoin(const QueryTable &rightSide,
    std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const {
  return internalJoin(JoinType::Natural, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::exactJoin(const QueryTable &rightSide,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const {
  return internalJoin(JoinType::ExactJoin, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::exactJoin(const QueryTable &rightSide,
    std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const {
  return internalJoin(JoinType::ExactJoin, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::leftJoin(const QueryTable &rightSide,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const {
  return internalJoin(JoinType::LeftJoin, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::leftJoin(const QueryTable &rightSide,
    std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const {
  return internalJoin(JoinType::LeftJoin, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::asOfJoin(const QueryTable &rightSide,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const {
  return internalJoin(JoinType::AJ, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::asOfJoin(const QueryTable &rightSide,
    std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const {
  return internalJoin(JoinType::AJ, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::reverseAsOfJoin(const QueryTable &rightSide,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const {
  return internalJoin(JoinType::ReverseAJ, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

QueryTable QueryTable::reverseAsOfJoin(const QueryTable &rightSide,
    std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const {
  return internalJoin(JoinType::ReverseAJ, rightSide, std::move(columnsToMatch), std::move(columnsToAdd));
}

void QueryTable::bindToVariable(std::string variable) const {
  auto res = SFCallback<Void>::createForFuture();
  bindToVariableAsync(std::move(variable), std::move(res.first));
  res.second.get();
}

void QueryTable::bindToVariableAsync(std::string variable,
    std::shared_ptr<SFCallback<Void>> callback) const {
  return impl_->bindToVariableAsync(std::move(variable), std::move(callback));
}

void QueryTable::observe() {
  impl_->observe();
}

WorkerOptions WorkerOptions::create(std::string profile) {
  auto woImpl = WorkerOptionsImpl::create(std::move(profile));
  return WorkerOptions(std::move(woImpl));
}

WorkerOptions::WorkerOptions(std::shared_ptr<impl::WorkerOptionsImpl> impl) : impl_(std::move(impl)) {}
WorkerOptions::WorkerOptions(WorkerOptions &&other) noexcept = default;
WorkerOptions &WorkerOptions::operator=(WorkerOptions &&other) noexcept = default;
WorkerOptions::~WorkerOptions() = default;

void WorkerOptions::addJvmArg(std::string arg) {
  impl_->addJvmArg(std::move(arg));
}

auto WorkerOptions::config() const -> const std::shared_ptr<ConsoleConfig> & {
  return impl_->config();
}

namespace internal {
std::string ConvertToString::toString(
    const deephaven::openAPI::highlevel::fluent::SelectColumn &selectColumn) {
  return selectColumn.getIrisRepresentableImpl()->toIrisRepresentation();
}
}  // namespace internal
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
