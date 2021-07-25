#pragma once

#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <map>
#include <string>
#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>
#include "core/server.h"
#include "highlevel/openapi.h"
#include "utility/callbacks.h"
#include "utility/cbfuture.h"
#include "utility/executor.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace fluent {
// TODO(kosak): Not sure I'm ok with this.
class SortPair;
namespace impl {
class BooleanExpressionImpl;
class ColumnImpl;
class DateTimeColImpl;
class NumColImpl;
class StrColImpl;
}  // namespace impl
}  // namespace fluent
namespace impl {
class QueryScopeImpl;

namespace internal {
class GetColumnDefsCallback;

class LazyState final : public deephaven::openAPI::utility::SFCallback<io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse> {
  struct Private {};

  typedef arrow::flight::protocol::Wicket Ticket;
  typedef io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse ExportedTableCreationResponse;
  typedef deephaven::openAPI::core::Server Server;
  typedef deephaven::openAPI::utility::Executor Executor;

  template<typename T>
  using SFCallback = deephaven::openAPI::utility::SFCallback<T>;
  template<typename T>
  using CBPromise = deephaven::openAPI::utility::CBPromise<T>;
  template<typename T>
  using CBFuture = deephaven::openAPI::utility::CBFuture<T>;

public:
  typedef std::map<std::string, std::shared_ptr<arrow::DataType>> columnDefinitions_t;

  static std::shared_ptr<LazyState> create(std::shared_ptr<Server> server,
      std::shared_ptr<Executor> flightExecutor);

  LazyState(Private, std::shared_ptr<Server> &&server, std::shared_ptr<Executor> &&flightExecutor);
  ~LazyState() final;

  bool ready();
  void waitUntilReady();

  void onSuccess(ExportedTableCreationResponse item) final;
  void onFailure(std::exception_ptr ep) final;

  const columnDefinitions_t *getColumnDefinitions();
  void getColumnDefinitionsAsync(std::shared_ptr<SFCallback<const columnDefinitions_t *>> cb);

private:
  bool readyLocked(std::unique_lock<std::mutex> */*lock*/);

  std::shared_ptr<Server> server_;
  std::shared_ptr<Executor> flightExecutor_;

  CBPromise<Ticket> ticketPromise_;
  CBFuture<Ticket> ticketFuture_;
  CBPromise<columnDefinitions_t> colDefsPromise_;
  CBFuture<columnDefinitions_t> colDefsFuture_;

  std::weak_ptr<LazyState> weakSelf_;

  friend class GetColumnDefsCallback;
};
}  // namespace internal

class QueryTableImpl {
  struct Private {};
  typedef arrow::flight::protocol::Wicket Ticket;
  typedef deephaven::openAPI::highlevel::fluent::SortPair SortPair;
  typedef deephaven::openAPI::highlevel::fluent::impl::ColumnImpl ColumnImpl;
  typedef deephaven::openAPI::highlevel::fluent::impl::DateTimeColImpl DateTimeColImpl;
  typedef deephaven::openAPI::highlevel::fluent::impl::NumColImpl NumColImpl;
  typedef deephaven::openAPI::highlevel::fluent::impl::StrColImpl StrColImpl;
  typedef deephaven::openAPI::highlevel::fluent::impl::BooleanExpressionImpl BooleanExpressionImpl;
  typedef deephaven::openAPI::utility::Executor Executor;
  typedef io::deephaven::proto::backplane::grpc::ComboAggregateRequest ComboAggregateRequest;

  template<typename ...Args>
  using SFCallback = deephaven::openAPI::utility::SFCallback<Args...>;
public:
  static std::shared_ptr<internal::LazyState> createEtcCallback(const QueryScopeImpl *scope);

  static std::shared_ptr<QueryTableImpl> create(std::shared_ptr<QueryScopeImpl> scope,
      Ticket ticket, std::shared_ptr<internal::LazyState> etcCallback);
  QueryTableImpl(Private, std::shared_ptr<QueryScopeImpl> scope,
      Ticket ticket, std::shared_ptr<internal::LazyState> lazyStateOss);
  ~QueryTableImpl();

  std::shared_ptr<QueryTableImpl> freeze();
  std::shared_ptr<QueryTableImpl> snapshot(std::shared_ptr<QueryTableImpl> targetTable,
      bool doInitialSnapshot, std::vector<std::string> stampColumns);
  std::shared_ptr<QueryTableImpl> select(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> update(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> view(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> dropColumns(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> updateView(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> where(std::string condition);
  std::shared_ptr<QueryTableImpl> sort(std::vector<SortPair> sortPairs);
  std::shared_ptr<QueryTableImpl> preemptive(int32_t sampleIntervalMs);

  std::shared_ptr<QueryTableImpl> by(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> by(std::vector<ComboAggregateRequest::Aggregate> descriptors,
      std::vector<std::string> groupByColumns);
  std::shared_ptr<QueryTableImpl> minBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> maxBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> sumBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> absSumBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> varBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> stdBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> avgBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> lastBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> firstBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> medianBy(std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> percentileBy(double percentile, bool avgMedian,
      std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> percentileBy(double percentile, std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> countBy(std::string countByColumn, std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> wAvgBy(std::string weightColumn, std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> tailBy(int64_t n, std::vector<std::string> columnSpecs);
  std::shared_ptr<QueryTableImpl> headBy(int64_t n, std::vector<std::string> columnSpecs);

  std::shared_ptr<QueryTableImpl> tail(int64_t n);
  std::shared_ptr<QueryTableImpl> head(int64_t n);
  std::shared_ptr<QueryTableImpl> ungroup(bool nullFill, std::vector<std::string> groupByColumns);
  std::shared_ptr<QueryTableImpl> merge(std::string keyColumn, std::vector<Ticket> sourceTickets);

//  std::shared_ptr<QueryTableImpl> internalJoin(JoinType joinType, const QueryTableImpl &rightSide,
//      std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd);

  void subscribeAllAsync(std::vector<std::string> columns,
      std::shared_ptr<SFCallback<>> callback);
  void unsubscribeAsync(std::shared_ptr<SFCallback<>> callback);

  void getData(std::shared_ptr<QueryTable::getDataCallback_t> handler) const;

  std::vector<std::shared_ptr<ColumnImpl>> getColumnImpls();
  std::shared_ptr<StrColImpl> getStrColImpl(std::string columnName);
  std::shared_ptr<NumColImpl> getNumColImpl(std::string columnName);
  std::shared_ptr<DateTimeColImpl> getDateTimeColImpl(std::string columnName);

  void bindToVariableAsync(std::string variable, std::shared_ptr<SFCallback<>> callback);

  // For debugging
  void observe();

  const std::shared_ptr<QueryScopeImpl> &scope() const { return scope_; }
  const Ticket &ticket() const { return ticket_; }

private:
  void lookupHelper(const std::string &columnName,
      std::initializer_list<arrow::Type::type> validTypes);

  std::shared_ptr<QueryTableImpl> defaultAggregateByDescriptor(
      ComboAggregateRequest::Aggregate descriptor, std::vector<std::string> groupByColumns);
  std::shared_ptr<QueryTableImpl> defaultAggregateByType(ComboAggregateRequest::AggType aggregateType,
      std::vector<std::string> groupByColumns);

  std::shared_ptr<QueryTableImpl> headOrTailHelper(bool head, int64_t n);
  std::shared_ptr<QueryTableImpl> headOrTailByHelper(int64_t n, bool head,
      std::vector<std::string> columnSpecs);

  std::shared_ptr<QueryScopeImpl> scope_;
  Ticket ticket_;
  std::shared_ptr<internal::LazyState> lazyStateOss_;
  std::weak_ptr<QueryTableImpl> weakSelf_;
};
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
