#pragma once

#include <future>
#include <memory>
#include <boost/utility/string_view.hpp>
#include "core/callbacks.h"
#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/columns.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
class AggregateComboImpl;
class AggregateImpl;
class ClientImpl;
class DatabaseCatalogTableImpl;
class QueryScopeImpl;
class QueryTableImpl;
class WorkerOptionsImpl;
class WorkerSessionImpl;
}  // namespace impl
class Client;
class WorkerSession;
class QueryScope;
class QueryTable;
class WorkerOptions;

class OpenApi {
public:
  static Client connect(boost::string_view host, int port = 8123);
  static Client connectOss(const std::string &target);
};

class Client {
  typedef deephaven::openAPI::utility::Void Void;

  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

public:
  explicit Client(std::shared_ptr<impl::ClientImpl> impl);
  Client(Client &&other) noexcept;
  Client &operator=(Client &&other) noexcept;
  ~Client();

  void login(std::string user, std::string password, std::string operateAs);
  void loginAsync(std::string user, std::string password, std::string operateAs,
      std::shared_ptr<SFCallback<Void>> callback);

  WorkerSession startWorker(const WorkerOptions &options);
  void startWorkerAsync(const WorkerOptions &options,
      std::shared_ptr<SFCallback<WorkerSession>> callback);

private:
  std::shared_ptr<impl::ClientImpl> impl_;
};

class WorkerSession {
public:
  WorkerSession() = default;
  explicit WorkerSession(std::shared_ptr<impl::WorkerSessionImpl> impl);
  WorkerSession(WorkerSession &&other) noexcept;
  WorkerSession &operator=(WorkerSession &&other) noexcept;
  ~WorkerSession();

  QueryScope queryScope();

private:
  std::shared_ptr<impl::WorkerSessionImpl> impl_;
};

class RowRangeSet {
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet RangeSet;
public:
  explicit RowRangeSet(std::shared_ptr<RangeSet> rs);

  const std::shared_ptr<RangeSet> &rs() const { return rs_; }
  int64_t count() const { return count_; }

private:
  std::shared_ptr<RangeSet> rs_;
  int64_t count_ = 0;
};

class TableData {
  typedef deephaven::openAPI::highlevel::data::ColumnData ColumnData;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition ColumnDefinition;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot TableSnapshot;

public:
  static TableData create(const std::vector<std::shared_ptr<ColumnDefinition>> &colDefs,
      const TableSnapshot &snapshot);
  TableData(const TableData &other) = delete;
  TableData &operator=(const TableData &other) = delete;
  TableData(TableData &&other) noexcept;
  TableData &operator=(TableData &&other) noexcept;
  ~TableData();

  const std::vector<std::shared_ptr<ColumnData>> &columnData() const { return columnData_; }
  int64_t tableSize() const { return tableSize_; }
  const RowRangeSet &includedRows() const { return includedRows_; }

private:
  TableData(std::vector<std::shared_ptr<ColumnData>> &&columnData, int64_t tableSize,
      RowRangeSet &&includedRows);

  std::vector<std::shared_ptr<ColumnData>> columnData_;
  int64_t tableSize_ = 0;
  RowRangeSet includedRows_;
};

class DatabaseCatalogTable {
public:
  explicit DatabaseCatalogTable(std::shared_ptr<impl::DatabaseCatalogTableImpl> impl);
  ~DatabaseCatalogTable();

  const std::string &nameSpaceSet() const;
  const std::string &nameSpace() const;
  const std::string &tableName() const;

private:
  std::shared_ptr<impl::DatabaseCatalogTableImpl> impl_;
};

class DatabaseCatalog {
public:
  explicit DatabaseCatalog(std::vector<DatabaseCatalogTable> tables);
  ~DatabaseCatalog();

  const std::vector<DatabaseCatalogTable> &tables() const { return tables_; }

private:
  std::vector<DatabaseCatalogTable> tables_;
};

class NullableString {
public:
  NullableString() = default;
  NullableString(const char *s);
  NullableString(std::string s);
  NullableString(const NullableString &) = default;
  NullableString &operator=(const NullableString &) = default;
  NullableString(NullableString &&) noexcept = default;
  NullableString &operator=(NullableString &&) noexcept = default;
  ~NullableString() = default;

  std::shared_ptr<std::string> release();

private:
  std::shared_ptr<std::string> value_;
};

class QueryScope {
  typedef deephaven::openAPI::highlevel::data::ColumnDataHolder ColumnDataHolder;

  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

public:
  explicit QueryScope(std::shared_ptr<impl::QueryScopeImpl> impl);
  QueryScope(QueryScope &&other) noexcept;
  QueryScope &operator=(QueryScope &&other) noexcept;
  ~QueryScope();

  QueryTable emptyTable(size_t size, std::vector<std::string> columnNames,
      std::vector<std::string> columnTypes) const;
  QueryTable historicalTable(std::string nameSpace, std::string tableName) const;
  QueryTable tempTable(const std::vector<ColumnDataHolder> &columnDataHolders) const;
  QueryTable timeTable(int64_t startTimeNanos, int64_t periodNanos) const;
  QueryTable timeTable(std::chrono::system_clock::time_point startTime,
      std::chrono::system_clock::duration period) const;

  DatabaseCatalog getDatabaseCatalog(bool systemNamespaces, bool userNamespaces,
      NullableString namespaceRegex, NullableString tableRegex) const;

  void getDatabaseCatalogAsync(bool systemNamespaces, bool userNamespaces,
      NullableString namespaceRegex, NullableString tableRegex,
      std::shared_ptr<SFCallback<DatabaseCatalog>> callback) const;

  QueryTable catalogTable() const;

private:
  std::shared_ptr<impl::QueryScopeImpl> impl_;
};

class XXXTableSnapshot {
public:
  XXXTableSnapshot();
  ~XXXTableSnapshot();

private:
  // TODO(kosak): put the high-level version of TableSnapshot here.
};

class XXXTableUpdate {
public:
  XXXTableUpdate();
  ~XXXTableUpdate();

private:
  // TODO(kosak): put the high-level version of DeltaUpdates here.
};

class Aggregate {
public:
  template<typename ...Args>
  static Aggregate absSum(Args &&... args);
  static Aggregate absSum(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate array(Args &&... args);
  static Aggregate array(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate avg(Args &&... args);
  static Aggregate avg(const std::vector<std::string> columnSpecs);

  template<typename ColArg>
  static Aggregate count(ColArg &&arg);
  static Aggregate count(std::string columnSpec);

  template<typename ...Args>
  static Aggregate first(Args &&... args);
  static Aggregate first(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate last(Args &&... args);
  static Aggregate last(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate max(Args &&... args);
  static Aggregate max(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate med(Args &&... args);
  static Aggregate med(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate min(Args &&... args);
  static Aggregate min(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate pct(double percentile, bool avgMedian, Args &&... args);
  static Aggregate pct(double percentile, bool avgMedian, std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate std(Args &&... args);
  static Aggregate std(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate sum(Args &&... args);
  static Aggregate sum(std::vector<std::string> columnSpecs);

  template<typename ...Args>
  static Aggregate var(Args &&... args);
  static Aggregate var(std::vector<std::string> columnSpecs);

  template<typename ColArg, typename ...Args>
  static Aggregate wavg(ColArg &&weightColumn, Args &&... args);
  static Aggregate wavg(std::string weightColumn, std::vector<std::string> columnSpecs);

  explicit Aggregate(std::shared_ptr<impl::AggregateImpl> impl);

  const std::shared_ptr<impl::AggregateImpl> &impl() const { return impl_; }

private:
  std::shared_ptr<impl::AggregateImpl> impl_;
};

class AggregateCombo {
public:
  static AggregateCombo create(std::initializer_list<Aggregate> list);
  static AggregateCombo create(std::vector<Aggregate> vec);

  ~AggregateCombo();

  const std::shared_ptr<impl::AggregateComboImpl> &impl() const { return impl_; }

private:
  explicit AggregateCombo(std::shared_ptr<impl::AggregateComboImpl> impl);

  std::shared_ptr<impl::AggregateComboImpl> impl_;
};

template<typename ...Args>
Aggregate aggAbsSum(Args &&... args) {
  return Aggregate::absSum(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggArray(Args &&... args) {
  return Aggregate::array(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggAvg(Args &&... args) {
  return Aggregate::avg(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggCount(Args &&... args) {
  return Aggregate::count(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggFirst(Args &&... args) {
  return Aggregate::first(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggLast(Args &&... args) {
  return Aggregate::last(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggMax(Args &&... args) {
  return Aggregate::max(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggMed(Args &&... args) {
  return Aggregate::med(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggMin(Args &&... args) {
  return Aggregate::min(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggPct(double percentile, Args &&... args) {
  return Aggregate::pct(percentile, std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggStd(Args &&... args) {
  return Aggregate::std(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggSum(Args &&... args) {
  return Aggregate::sum(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggVar(Args &&... args) {
  return Aggregate::var(std::forward<Args>(args)...);
}

template<typename ...Args>
Aggregate aggWavg(Args &&... args) {
  return Aggregate::wavg(std::forward<Args>(args)...);
}

inline AggregateCombo aggCombo(std::initializer_list<Aggregate> args) {
  return AggregateCombo::create(args);
}

class QueryTable {
  typedef deephaven::openAPI::highlevel::fluent::BooleanExpression BooleanExpression;
  typedef deephaven::openAPI::highlevel::fluent::Column Column;
  typedef deephaven::openAPI::highlevel::fluent::DateTimeCol DateTimeCol;
  typedef deephaven::openAPI::highlevel::fluent::MatchWithColumn MatchWithColumn;
  typedef deephaven::openAPI::highlevel::fluent::NumCol NumCol;
  typedef deephaven::openAPI::highlevel::fluent::SelectColumn SelectColumn;
  typedef deephaven::openAPI::highlevel::fluent::SortPair SortPair;
  typedef deephaven::openAPI::highlevel::fluent::StrCol StrCol;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType JoinType;
  typedef deephaven::openAPI::utility::Void Void;

  template<typename... Args>
  using Callback = deephaven::openAPI::core::Callback<Args...>;
  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

public:
  typedef Callback<const QueryTable&, const XXXTableSnapshot&> snapshotCallback_t;
  typedef Callback<const QueryTable&, const XXXTableUpdate&> updateCallback_t;

  explicit QueryTable(std::shared_ptr<impl::QueryTableImpl> impl);
  QueryTable(const QueryTable &other);
  QueryTable &operator=(const QueryTable &other);
  QueryTable(QueryTable &&other) noexcept;
  QueryTable &operator=(QueryTable &&other) noexcept;
  ~QueryTable();

  QueryScope scope() const;

  QueryTable freeze() const;

  QueryTable snapshot(const QueryTable &targetTable, bool doInitialSnapshot = true,
      std::vector<std::string> stampColumns = {}) const;

  template<typename ...Args>
  QueryTable select(Args &&... args) const;
  QueryTable select(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable view(Args &&... args) const;
  QueryTable view(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable dropColumns(Args &&... args) const;
  QueryTable dropColumns(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable update(Args &&... args) const;
  QueryTable update(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable updateView(Args &&... args) const;
  QueryTable updateView(std::vector<std::string> columnSpecs) const;

  QueryTable where(const BooleanExpression &condition) const;
  QueryTable where(std::string condition) const;

  QueryTable sort(std::vector<SortPair> sortPairs) const;

  QueryTable preemptive(int sampleIntervalMs);

  template<typename ...Args>
  QueryTable by(Args &&... args) const;
  QueryTable by(std::vector<std::string> columnSpecs) const;

  QueryTable by(AggregateCombo combo, std::vector<std::string> groupByColumns) const;
  template<typename ...Args>
  QueryTable by(AggregateCombo combo, Args &&... args) const;

  template<typename ...Args>
  QueryTable minBy(Args &&... args) const;
  QueryTable minBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable maxBy(Args &&... args) const;
  QueryTable maxBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable sumBy(Args &&... args) const;
  QueryTable sumBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable absSumBy(Args &&... args) const;
  QueryTable absSumBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable varBy(Args &&... args) const;
  QueryTable varBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable stdBy(Args &&... args) const;
  QueryTable stdBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable avgBy(Args &&... args) const;
  QueryTable avgBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable firstBy(Args &&... args) const;
  QueryTable firstBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable lastBy(Args &&... args) const;
  QueryTable lastBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable medianBy(Args &&... args) const;
  QueryTable medianBy(std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable percentileBy(double percentile, bool avgMedian, Args &&... args) const;
  QueryTable percentileBy(double percentile, bool avgMedian, std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable percentileBy(double percentile, Args &&... args) const;
  QueryTable percentileBy(double percentile, std::vector<std::string> columnSpecs) const;

  template<typename CCol, typename ...Args>
  QueryTable countBy(CCol &&countByColumn, Args &&... args) const;
  QueryTable countBy(std::string countByColumn, std::vector<std::string> columnSpecs) const;

  template<typename WCol, typename ...Args>
  QueryTable wAvgBy(WCol &&weightColumn, Args &&... args) const;
  QueryTable wAvgBy(std::string weightColumn, std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable tailBy(int64_t n, Args &&... args) const;
  QueryTable tailBy(int64_t n, std::vector<std::string> columnSpecs) const;

  template<typename ...Args>
  QueryTable headBy(int64_t n, Args &&... args) const;
  QueryTable headBy(int64_t n, std::vector<std::string> columnSpecs) const;

  QueryTable head(int64_t n) const;
  QueryTable tail(int64_t n) const;

  template<typename ...Args>
  QueryTable ungroup(bool nullFill, Args &&... args) const;
  QueryTable ungroup(bool nullFill, std::vector<std::string> groupByColumns) const;

  template<typename ...Args>
  QueryTable ungroup(Args &&... args) const {
    return ungroup(false, std::forward<Args>(args)...);
  }
  QueryTable ungroup(std::vector<std::string> groupByColumns) const {
    return ungroup(false, std::move(groupByColumns));
  }

  QueryTable merge(std::string keyColumn, std::vector<QueryTable> sources) const;
  QueryTable merge(std::vector<QueryTable> sources) const {
    // TODO(kosak): may need to support null
    return merge("", std::move(sources));
  }

  QueryTable internalJoin(JoinType joinType, const QueryTable &rightSide,
      std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd) const;
  QueryTable internalJoin(JoinType joinType, const QueryTable &rightSide,
      std::vector<MatchWithColumn> columnsToMatch, std::vector<SelectColumn> columnsToAdd) const;

  QueryTable naturalJoin(const QueryTable &rightSide, std::vector<std::string> columnsToMatch,
      std::vector<std::string> columnsToAdd) const;
  QueryTable naturalJoin(const QueryTable &rightSide, std::vector<MatchWithColumn> columnsToMatch,
      std::vector<SelectColumn> columnsToAdd) const;

  QueryTable exactJoin(const QueryTable &rightSide, std::vector<std::string> columnsToMatch,
      std::vector<std::string> columnsToAdd) const;
  QueryTable exactJoin(const QueryTable &rightSide, std::vector<MatchWithColumn> columnsToMatch,
      std::vector<SelectColumn> columnsToAdd) const;

  QueryTable leftJoin(const QueryTable &rightSide, std::vector<std::string> columnsToMatch,
      std::vector<std::string> columnsToAdd) const;
  QueryTable leftJoin(const QueryTable &rightSide, std::vector<MatchWithColumn> columnsToMatch,
      std::vector<SelectColumn> columnsToAdd) const;

  QueryTable asOfJoin(const QueryTable &rightSide, std::vector<std::string> columnsToMatch,
      std::vector<std::string> columnsToAdd) const;
  QueryTable asOfJoin(const QueryTable &rightSide, std::vector<MatchWithColumn> columnsToMatch,
      std::vector<SelectColumn> columnsToAdd) const;

  QueryTable reverseAsOfJoin(const QueryTable &rightSide, std::vector<std::string> columnsToMatch,
      std::vector<std::string> columnsToAdd) const;
  QueryTable reverseAsOfJoin(const QueryTable &rightSide, std::vector<MatchWithColumn> columnsToMatch,
      std::vector<SelectColumn> columnsToAdd) const;

  void bindToVariable(std::string variable);
  void bindToVariableAsync(std::string variable, std::shared_ptr<SFCallback<Void>> callback);

  TableData getTableData() const {
    return getTableData(0, std::numeric_limits<int64_t>::max(), {});
  }
  TableData getTableData(const std::vector<std::string> &columns) const {
    return getTableData(0, std::numeric_limits<int64_t>::max(), columns);
  }
  TableData getTableData(long first, long last) const {
    return getTableData(first, last, {});
  }
  TableData getTableData(long first, long last, std::vector<std::string> columns) const;
  void getTableDataAsync(long first, long last, std::vector<std::string> columns,
      std::shared_ptr<SFCallback<TableData>> callback) const;

  void subscribeAll(std::vector<std::string> columnSpecs) const;
  template<typename ...Args>
  void subscribeAll(Args &&... args) const;

  void subscribeAllAsync(std::vector<std::string> columnSpecs,
      std::shared_ptr<SFCallback<Void>> callback) const;
  template<typename ...Args>
  void subscribeAllAsync(std::shared_ptr<SFCallback<Void>> callback, Args &&... args) const;

  void unsubscribe() const;
  void unsubscribeAsync(std::shared_ptr<SFCallback<Void>> callback) const;

  void addTableUpdateHandler(const std::shared_ptr<updateCallback_t> &handler) const;
  void removeTableUpdateHandler(const std::shared_ptr<updateCallback_t> &handler) const;

  std::vector<Column> getColumns() const;

  StrCol getStrCol(boost::string_view columnName) const;
  NumCol getNumCol(boost::string_view columnName) const;
  DateTimeCol getDateTimeCol(boost::string_view columnName) const;

  int64_t hackGetSizeFromTableDefinition() const;

  // for debugging
  void observe();

  const std::shared_ptr<impl::QueryTableImpl> &impl() const { return impl_; }

private:
  std::shared_ptr<impl::QueryTableImpl> impl_;
};

class WorkerOptions {
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig ConsoleConfig;
public:
  static WorkerOptions create(std::string profile);

  explicit WorkerOptions(std::shared_ptr<impl::WorkerOptionsImpl> impl);
  WorkerOptions(WorkerOptions &&other) noexcept;
  WorkerOptions &operator=(WorkerOptions &&other) noexcept;
  ~WorkerOptions();

  void addJvmArg(std::string arg);

  const std::shared_ptr<ConsoleConfig> &config() const;

  const std::shared_ptr<impl::WorkerOptionsImpl> &impl() const { return impl_; }

private:
  std::shared_ptr<impl::WorkerOptionsImpl> impl_;
};

namespace internal {
struct ConvertToString {
  static std::string toString(const char *s) {
    return s;
  }

  static std::string toString(const boost::string_view sv) {
    return sv.to_string();
  }

  static std::string toString(std::string s) {
    return s;
  }

  static std::string toString(const deephaven::openAPI::highlevel::fluent::SelectColumn &selectColumn);
};
}  // namespace internal

template<typename ...Args>
Aggregate Aggregate::absSum(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return absSum(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::array(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return array(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::avg(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return avg(std::move(columnSpecs));
}

template<typename ColArg>
Aggregate Aggregate::count(ColArg &&arg) {
  auto columnSpec = internal::ConvertToString::toString(std::forward<ColArg>(arg));
  return count(std::move(columnSpec));
}

template<typename ...Args>
Aggregate Aggregate::first(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return first(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::last(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return last(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::max(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return max(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::med(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return max(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::min(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return max(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::pct(double percentile, bool avgMedian, Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return pct(percentile, avgMedian, std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::std(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return std(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::sum(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return sum(std::move(columnSpecs));
}

template<typename ...Args>
Aggregate Aggregate::var(Args &&... args) {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return var(std::move(columnSpecs));
}

template<typename ColArg, typename ...Args>
Aggregate Aggregate::wavg(ColArg &&weightColumn, Args &&... args) {
  auto weightCol = internal::ConvertToString::toString(std::forward<ColArg>(weightColumn));
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return wavg(std::move(weightCol), std::move(columnSpecs));
}



template<typename ...Args>
QueryTable QueryTable::select(Args &&... args) const {
  std::vector<std::string> selectColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return select(std::move(selectColumns));
}

template<typename ...Args>
QueryTable QueryTable::view(Args &&... args) const {
  std::vector<std::string> viewColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return view(std::move(viewColumns));
}

template<typename ...Args>
QueryTable QueryTable::dropColumns(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return dropColumns(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::update(Args &&... args) const {
  std::vector<std::string> updateColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return update(std::move(updateColumns));
}

template<typename ...Args>
QueryTable QueryTable::updateView(Args &&... args) const {
  std::vector<std::string> updateColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return updateView(std::move(updateColumns));
}

template<typename ...Args>
QueryTable QueryTable::by(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return by(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::by(AggregateCombo combo, Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return by(std::move(combo), std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::minBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return minBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::maxBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return maxBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::sumBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return sumBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::absSumBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return absSumBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::varBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return varBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::stdBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return stdBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::avgBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return avgBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::firstBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return firstBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::lastBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return lastBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::medianBy(Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return medianBy(std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::percentileBy(double percentile, bool avgMedian, Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return percentileBy(percentile, avgMedian, std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::percentileBy(double percentile, Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return percentileBy(percentile, std::move(columns));
}

template<typename CCol, typename ...Args>
QueryTable QueryTable::countBy(CCol &&countByColumn, Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return countBy(internal::ConvertToString::toString(countByColumn), std::move(columns));
}

template<typename WCol, typename ...Args>
QueryTable QueryTable::wAvgBy(WCol &&weightColumn, Args &&... args) const {
  std::vector<std::string> columns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return wAvgBy(internal::ConvertToString::toString(weightColumn), std::move(columns));
}

template<typename ...Args>
QueryTable QueryTable::tailBy(int64_t n, Args &&... args) const {
  std::vector<std::string> lastByColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return tailBy(n, std::move(lastByColumns));
}

template<typename ...Args>
QueryTable QueryTable::headBy(int64_t n, Args &&... args) const {
  std::vector<std::string> lastByColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return headBy(n, std::move(lastByColumns));
}

template<typename ...Args>
QueryTable QueryTable::ungroup(bool nullFill, Args &&... args) const {
  std::vector<std::string> groupByColumns = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return ungroup(nullFill, std::move(groupByColumns));
}

template<typename ...Args>
void QueryTable::subscribeAll(Args &&... args) const {
  auto res = SFCallback<Void>::createForFuture();
  subscribeAllAsync(std::move(res.first), std::forward<Args>(args)...);
  (void)res.second.get();
}

template<typename ...Args>
void QueryTable::subscribeAllAsync(std::shared_ptr<SFCallback<Void>> callback,
    Args &&... args) const {
  std::vector<std::string> columnSpecs = {
      internal::ConvertToString::toString(std::forward<Args>(args))...
  };
  return subscribeAllAsync(std::move(columnSpecs), std::move(callback));
}


}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
