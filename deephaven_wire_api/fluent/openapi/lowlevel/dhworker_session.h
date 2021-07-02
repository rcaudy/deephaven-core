#pragma once

#include <atomic>
#include <future>
#include <memory>
#include "core/server.h"
#include "core/callbacks.h"
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/dhworker.h"
#include "utility/executor.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
class DHServer;

namespace internal {
class SnapshotAndDeltaUpdateHandler;
}  // namespace internal

class DHWorkerSession {
  struct Private {};
  typedef arrow::flight::protocol::Ticket Ticket;
  typedef io::deephaven::proto::backplane::grpc::ComboAggregateRequest ComboAggregateRequest;
  typedef io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse ExportedTableCreationResponse;
  typedef io::deephaven::proto::backplane::script::grpc::BindTableToVariableResponse BindTableToVariableResponse;

  typedef deephaven::openAPI::core::remoting::Server Server;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor AggregateDescriptor;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps SerializedTableOps;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest BatchTableRequest;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableResponse BatchTableResponse;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ConnectionSuccess ConnectionSuccess;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType JoinType;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Catalog Catalog;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder ColumnHolder;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken ConnectToken;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates DeltaUpdates;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition InitialTableDefinition;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet RangeSet;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor SortDescriptor;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle TableHandle;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot TableSnapshot;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet BitSet;
  typedef deephaven::openAPI::utility::Executor Executor;
  typedef deephaven::openAPI::utility::Void Void;

  template<typename... Args>
  using Callback = deephaven::openAPI::core::Callback<Args...>;
  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

  typedef SFCallback<std::shared_ptr<InitialTableDefinition>> ItdCallback;
  typedef SFCallback<ExportedTableCreationResponse> EtcCallback;

public:
  typedef Callback<const std::shared_ptr<TableHandle> &, const std::shared_ptr<TableSnapshot> &> snapshotCallback_t;
  typedef Callback<const std::shared_ptr<TableHandle> &, const std::shared_ptr<DeltaUpdates> &> updateCallback_t;

  static std::shared_ptr<DHWorkerSession> createOss(Ticket consoleId, std::shared_ptr<Server> server,
      std::shared_ptr<Executor> executor);

  DHWorkerSession(Private, Ticket &&consoleId, std::shared_ptr<Server> server,
      std::shared_ptr<Executor> executor);
  DHWorkerSession(const DHWorkerSession &other) = delete;
  DHWorkerSession &operator=(const DHWorkerSession &other) = delete;
  ~DHWorkerSession();

  Ticket emptyTableAsync(int64_t size, std::vector<std::string> columnNames,
      std::vector<std::string> columnTypes, std::shared_ptr<EtcCallback> etcCallback);

  std::shared_ptr<TableHandle> historicalTableAsync(std::shared_ptr<std::string> nameSpace,
      std::shared_ptr<std::string> tableName, std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> tempTableAsync(std::shared_ptr<std::vector<std::shared_ptr<ColumnHolder>>> columnHolders,
      std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> timeTableAsync(int64_t startTimeNanos, int64_t periodNanos,
      std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> snapshotAsync(std::shared_ptr<TableHandle> leftTableHandle,
      std::shared_ptr<TableHandle> rightTableHandle,
      bool doInitialSnapshot, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns,
      std::shared_ptr<ItdCallback> itdCallback);

  Ticket selectAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket updateAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket viewAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  Ticket updateViewAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
      std::shared_ptr<EtcCallback> etcCallback);

  std::shared_ptr<TableHandle> dropColumnsAsync(std::shared_ptr<TableHandle> parentTableHandle,
      std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs, std::shared_ptr<ItdCallback> itdCallback);

  Ticket whereAsync(Ticket parentTicket, std::string condition,
      std::shared_ptr<EtcCallback> etcCallback);

  std::shared_ptr<TableHandle> sortAsync(std::shared_ptr<TableHandle> parentTableHandle,
      std::shared_ptr<std::vector<std::shared_ptr<SortDescriptor>>> sortDescriptors,
      std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> preemptiveAsync(std::shared_ptr<TableHandle> parentTableHandle,
      int32_t sampleIntervalMs, std::shared_ptr<ItdCallback> itdCallback);

  Ticket comboAggregateDescriptorAsync(Ticket parentTicket,
      std::vector<ComboAggregateRequest::Aggregate> aggregates,
      std::vector<std::string> groupByColumns, bool forceCombo,
      std::shared_ptr<EtcCallback> etcCallback);

  std::shared_ptr<TableHandle> tailByAsync(std::shared_ptr<TableHandle> parentTableHandle,
      int64_t n, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs,
      std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> headByAsync(std::shared_ptr<TableHandle> parentTableHandle,
      int64_t n, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs,
      std::shared_ptr<ItdCallback> itdCallback);

  Ticket headOrTailAsync(const Ticket &parentTicket,
      bool head, int64_t n, std::shared_ptr<EtcCallback> etcCallback);

  std::shared_ptr<TableHandle> ungroupAsync(std::shared_ptr<TableHandle> parentTableHandle,
      bool nullFill, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns,
      std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> mergeAsync(
      std::shared_ptr<std::vector<std::shared_ptr<TableHandle>>> sourceHandles,
      std::shared_ptr<std::string> keyColumn, std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> internalJoinAsync(JoinType joinType,
      std::shared_ptr<TableHandle> leftTableHandle, std::shared_ptr<TableHandle> rightTableHandle,
      std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch,
      std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd,
      std::shared_ptr<ItdCallback> itdCallback);

  void getTableDataAsync(std::shared_ptr<TableHandle> parentTableHandle,
      std::shared_ptr<RangeSet> rows, std::shared_ptr<BitSet> columns,
      std::shared_ptr<SFCallback<std::shared_ptr<TableSnapshot>>> callback);

  void subscribeAllAsync(std::shared_ptr<TableHandle> tableHandle, std::shared_ptr<BitSet> colBitset,
      bool isViewport, std::shared_ptr<SFCallback<std::shared_ptr<Void>>> callback);
  void unsubscribeAsync(std::shared_ptr<TableHandle> tableHandle,
      std::shared_ptr<SFCallback<std::shared_ptr<Void>>> callback);

  void getDatabaseCatalogAsync(bool systemNamespaces, bool userNamespaces,
      std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex,
      std::shared_ptr<SFCallback<std::shared_ptr<Catalog>>> callback);

  std::shared_ptr<TableHandle> catalogTableAsync(std::shared_ptr<ItdCallback> itdCallback);

  void bindToVariableAsync(const Ticket &tableId, std::string variable,
      std::shared_ptr<SFCallback<BindTableToVariableResponse>> callback);

  Ticket fetchTableAsync(std::string tableName, std::shared_ptr<EtcCallback> callback);

  void addTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<snapshotCallback_t> &handler);
  void removeTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<snapshotCallback_t> &handler);

  void addTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<updateCallback_t> &handler);
  void removeTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<updateCallback_t> &handler);

  Server *server() const { return server_.get(); }
  const std::shared_ptr<Executor> &executor() const { return executor_; }

private:
  void processBatchOperation(std::shared_ptr<SerializedTableOps> tableOps,
      const std::shared_ptr<TableHandle> &resultHandle, std::shared_ptr<ItdCallback> itdCallback);

  std::shared_ptr<TableHandle> createTableHandle();

  Ticket consoleId_;
  std::shared_ptr<Server> server_;
  std::shared_ptr<Executor> executor_;
};
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
