#pragma once

#include <atomic>
#include <future>
#include <memory>
#include "core/server.h"
#include "utility/callbacks.h"
#include "utility/executor.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"

namespace deephaven {
namespace openAPI {
namespace lowlevel {
class DHServer;

namespace internal {
class SnapshotAndDeltaUpdateHandler;
}  // namespace internal

class DHWorkerSession {
  struct Private {};
  typedef arrow::flight::protocol::Wicket Ticket;
  typedef io::deephaven::proto::backplane::grpc::ComboAggregateRequest ComboAggregateRequest;
  typedef io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse ExportedTableCreationResponse;
  typedef io::deephaven::proto::backplane::grpc::SortDescriptor SortDescriptor;
  typedef io::deephaven::proto::backplane::script::grpc::BindTableToVariableResponse BindTableToVariableResponse;

  typedef deephaven::openAPI::core::Server Server;
  typedef deephaven::openAPI::utility::Executor Executor;

  template<typename... Args>
  using Callback = deephaven::openAPI::utility::Callback<Args...>;
  template<typename T>
  using SFCallback = deephaven::openAPI::utility::SFCallback<T>;

  typedef SFCallback<ExportedTableCreationResponse> EtcCallback;

public:
  static std::shared_ptr<DHWorkerSession> create(Ticket consoleId, std::shared_ptr<Server> server,
      std::shared_ptr<Executor> executor, std::shared_ptr<Executor> flightExecutor);

  DHWorkerSession(Private, Ticket &&consoleId, std::shared_ptr<Server> &&server,
      std::shared_ptr<Executor> &&executor, std::shared_ptr<Executor> &&flightExecutor);
  DHWorkerSession(const DHWorkerSession &other) = delete;
  DHWorkerSession &operator=(const DHWorkerSession &other) = delete;
  ~DHWorkerSession();

  Ticket emptyTableAsync(int64_t size, std::vector<std::string> columnNames,
      std::vector<std::string> columnTypes, std::shared_ptr<EtcCallback> etcCallback);

//  std::shared_ptr<TableHandle> historicalTableAsync(std::shared_ptr<std::string> nameSpace,
//      std::shared_ptr<std::string> tableName, std::shared_ptr<ItdCallback> itdCallback);
//
//  std::shared_ptr<TableHandle> tempTableAsync(std::shared_ptr<std::vector<std::shared_ptr<ColumnHolder>>> columnHolders,
//      std::shared_ptr<ItdCallback> itdCallback);

  Ticket timeTableAsync(int64_t startTimeNanos, int64_t periodNanos,
      std::shared_ptr<EtcCallback> etcCallback);
//
//  std::shared_ptr<TableHandle> snapshotAsync(std::shared_ptr<TableHandle> leftTableHandle,
//      std::shared_ptr<TableHandle> rightTableHandle,
//      bool doInitialSnapshot, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns,
//      std::shared_ptr<ItdCallback> itdCallback);

  Ticket selectAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket updateAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket viewAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket updateViewAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket dropColumnsAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket whereAsync(Ticket parentTicket, std::string condition,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket sortAsync(Ticket parentTicket, std::vector<SortDescriptor> sortDescriptors,
      std::shared_ptr<EtcCallback> etcCallback);

//  std::shared_ptr<TableHandle> preemptiveAsync(std::shared_ptr<TableHandle> parentTableHandle,
//      int32_t sampleIntervalMs, std::shared_ptr<ItdCallback> itdCallback);

  Ticket comboAggregateDescriptorAsync(Ticket parentTicket,
      std::vector<ComboAggregateRequest::Aggregate> aggregates,
      std::vector<std::string> groupByColumns, bool forceCombo,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket headOrTailByAsync(Ticket parentTicket, bool head, int64_t n,
      std::vector<std::string> columnSpecs, std::shared_ptr<EtcCallback> etcCallback);

  Ticket headOrTailAsync(Ticket parentTicket,
      bool head, int64_t n, std::shared_ptr<EtcCallback> etcCallback);

  Ticket ungroupAsync(Ticket parentTicket, bool nullFill, std::vector<std::string> groupByColumns,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket mergeAsync(std::vector<Ticket> sourceTickets, std::string keyColumn,
      std::shared_ptr<EtcCallback> etcCallback);

//  Ticket internalJoinAsync(JoinType joinType, Ticket leftTableTicket, Ticket rightTableTicket,
//      std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd,
//      std::shared_ptr<EtcCallback> etcCallback);

//  void getTableDataAsync(std::shared_ptr<TableHandle> parentTableHandle,
//      std::shared_ptr<RangeSet> rows, std::shared_ptr<BitSet> columns,
//      std::shared_ptr<SFCallback<std::shared_ptr<TableSnapshot>>> callback);
//
//  void subscribeAllAsync(std::shared_ptr<TableHandle> tableHandle, std::shared_ptr<BitSet> colBitset,
//      bool isViewport, std::shared_ptr<SFCallback<std::shared_ptr<Void>>> callback);
//  void unsubscribeAsync(std::shared_ptr<TableHandle> tableHandle,
//      std::shared_ptr<SFCallback<std::shared_ptr<Void>>> callback);

//  void getDatabaseCatalogAsync(bool systemNamespaces, bool userNamespaces,
//      std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex,
//      std::shared_ptr<SFCallback<std::shared_ptr<Catalog>>> callback);

//   std::shared_ptr<TableHandle> catalogTableAsync(std::shared_ptr<ItdCallback> itdCallback);

  void bindToVariableAsync(const Ticket &tableId, std::string variable,
      std::shared_ptr<SFCallback<BindTableToVariableResponse>> callback);

  Ticket fetchTableAsync(std::string tableName, std::shared_ptr<EtcCallback> callback);

//  void addTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
//      const std::shared_ptr<snapshotCallback_t> &handler);
//  void removeTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
//      const std::shared_ptr<snapshotCallback_t> &handler);
//
//  void addTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
//      const std::shared_ptr<updateCallback_t> &handler);
//  void removeTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
//      const std::shared_ptr<updateCallback_t> &handler);

  const std::shared_ptr<Server> &server() const { return server_; }
  const std::shared_ptr<Executor> &executor() const { return executor_; }
  const std::shared_ptr<Executor> &flightExecutor() const { return flightExecutor_; }

private:
  Ticket consoleId_;
  std::shared_ptr<Server> server_;
  std::shared_ptr<Executor> executor_;
  std::shared_ptr<Executor> flightExecutor_;
};
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
