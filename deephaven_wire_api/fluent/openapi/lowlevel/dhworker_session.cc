#include "lowlevel/dhworker_session.h"

#include <map>
#include "lowlevel/dhserver.h"
#include "lowlevel/generated/dhworker_requests.h"
#include "utility/executor.h"
#include "utility/utility.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"

typedef arrow::flight::protocol::Wicket Ticket;

using io::deephaven::proto::backplane::grpc::DropColumnsRequest;
using io::deephaven::proto::backplane::grpc::EmptyTableRequest;
using io::deephaven::proto::backplane::grpc::HeadOrTailRequest;
using io::deephaven::proto::backplane::grpc::HeadOrTailByRequest;
using io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse;
using io::deephaven::proto::backplane::grpc::JoinTablesRequest;
using io::deephaven::proto::backplane::grpc::MergeTablesRequest;
using io::deephaven::proto::backplane::grpc::SelectOrUpdateRequest;
using io::deephaven::proto::backplane::grpc::SortDescriptor;
using io::deephaven::proto::backplane::grpc::SortTableRequest;
using io::deephaven::proto::backplane::grpc::TableService;
using io::deephaven::proto::backplane::grpc::TimeTableRequest;
using io::deephaven::proto::backplane::grpc::UngroupRequest;
using io::deephaven::proto::backplane::grpc::UnstructuredFilterTableRequest;
using io::deephaven::proto::backplane::script::grpc::BindTableToVariableRequest;
using io::deephaven::proto::backplane::script::grpc::FetchTableRequest;
using io::deephaven::proto::backplane::script::grpc::ConsoleService;
using deephaven::openAPI::core::remoting::ServerCQCallback;
using deephaven::openAPI::core::remoting::ServerResponseHolder;
using deephaven::openAPI::core::remoting::Server;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableResponse;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Batch;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ComboAggregate;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ConstructSnapshotQuery;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::EmptyTable;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::GetCatalog;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::GetCatalogTable;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HeadBy;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HistoricalTable;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Join;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::MergeTables;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::NewTable;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Select;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Snapshot;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Subscribe;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TailBy;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TimeTable;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Unsubscribe;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Ungroup;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Update;
using deephaven::openAPI::utility::Callback;
using deephaven::openAPI::utility::Executor;
using deephaven::openAPI::utility::FailureCallback;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::utility::Void;

typedef SFCallback<std::shared_ptr<InitialTableDefinition>> itdCallback_t;

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace internal {
class TableHandleKey {
public:
  static bool tryCreate(const TableHandle &th, TableHandleKey *result);
  static TableHandleKey create(const TableHandle &th);

  TableHandleKey() = default;
  TableHandleKey(int32_t connectionId, int32_t clientId) : connectionId_(connectionId),
      clientId_(clientId) {}

private:
  int32_t connectionId_ = 0;
  int32_t clientId_ = 0;

  friend bool operator<(const TableHandleKey &lhs, const TableHandleKey &rhs) {
    auto l = std::tie(lhs.connectionId_, lhs.clientId_);
    auto r = std::tie(rhs.connectionId_, rhs.clientId_);
    return l < r;
  }

  friend bool operator==(const TableHandleKey &lhs, const TableHandleKey &rhs) {
    auto l = std::tie(lhs.connectionId_, lhs.clientId_);
    auto r = std::tie(rhs.connectionId_, rhs.clientId_);
    return l == r;
  }

  friend bool operator!=(const TableHandleKey &lhs, const TableHandleKey &rhs) {
    return !(lhs == rhs);
  }
};

class SnapshotAndDeltaUpdateHandler final : public DHWorkerAPIListenerDefault {
  struct Private {};

public:
  typedef Callback<const std::shared_ptr<TableHandle> &, const std::shared_ptr<TableSnapshot> &> snapshotCallback_t;
  typedef Callback<const std::shared_ptr<TableHandle> &, const std::shared_ptr<DeltaUpdates> &> updateCallback_t;

  static std::shared_ptr<SnapshotAndDeltaUpdateHandler> create(std::shared_ptr<Executor> executor);

  SnapshotAndDeltaUpdateHandler(Private, std::shared_ptr<Executor> executor);
  ~SnapshotAndDeltaUpdateHandler() final;

  void onInitialSnapshot(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<TableSnapshot> &snapshot) final;

  void onIncrementalUpdates(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<DeltaUpdates> &deltaUpdates) final;

  void addTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<snapshotCallback_t> &handler);

  void removeTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<snapshotCallback_t> &handler);

  void addTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<updateCallback_t> &handler);

  void removeTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
      const std::shared_ptr<updateCallback_t> &handler);

private:
  std::shared_ptr<Executor> executor_;
  std::weak_ptr<SnapshotAndDeltaUpdateHandler> weakSelf_;

  // Reads and mutations to this map are only done on the executor thread.
  std::map<TableHandleKey, std::vector<std::shared_ptr<snapshotCallback_t>>> snapshotHandlers_;
  // Reads and mutations to this map are only done on the executor thread.
  std::map<TableHandleKey, std::vector<std::shared_ptr<updateCallback_t>>> updateHandlers_;
};
}  // namespace internal

namespace {
void moveVectorData(std::vector<std::string> src, google::protobuf::RepeatedPtrField<std::string> *dest);
}  // namespace
std::shared_ptr<DHWorkerSession> DHWorkerSession::create(Ticket consoleId,
    std::shared_ptr<Server> server, std::shared_ptr<Executor> executor,
    std::shared_ptr<Executor> flightExecutor) {
  return std::make_shared<DHWorkerSession>(Private(), std::move(consoleId), std::move(server),
      std::move(executor), std::move(flightExecutor));
}

DHWorkerSession::DHWorkerSession(Private, Ticket &&consoleId, std::shared_ptr<Server> &&server,
    std::shared_ptr<Executor> &&executor, std::shared_ptr<Executor> &&flightExecutor) :
    consoleId_(std::move(consoleId)), server_(std::move(server)), executor_(std::move(executor)),
    flightExecutor_(std::move(flightExecutor)) {}
DHWorkerSession::~DHWorkerSession() = default;

Ticket DHWorkerSession::emptyTableAsync(int64_t size, std::vector<std::string> columnNames,
    std::vector<std::string> columnTypes, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  EmptyTableRequest req;
  *req.mutable_result_id() = result;
  req.set_size(size);
  for (auto &cn : columnNames) {
    *req.mutable_column_names()->Add() = std::move(cn);
  }
  for (auto &ct : columnTypes) {
    *req.mutable_column_types()->Add() = std::move(ct);
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncEmptyTable, true);
  return result;
}

Ticket DHWorkerSession::fetchTableAsync(std::string tableName, std::shared_ptr<EtcCallback> callback) {
  auto result = server_->newTicket();
  FetchTableRequest req;
  *req.mutable_console_id() = consoleId_;
  *req.mutable_table_id() = result;
  req.set_table_name(std::move(tableName));
  server_->sendRpc(req, std::move(callback), server_->consoleStub(),
      &ConsoleService::Stub::AsyncFetchTable, true);
  return result;
}

namespace {
//struct SuperNub2 final : public ServerCQCallback {
//  SuperNub2(std::shared_ptr<FailureCallback> failureCallback,
//     std::unique_ptr< ::grpc::ClientAsyncReader< ::arrow::flight::protocol::FlightData>> readerParty)
//     : ServerCQCallback(std::move(failureCallback)), readerParty_(std::move(readerParty)) {}
//  ~SuperNub2() final {
//    std::cerr << "I AM NOT READY TO BE DELETED EITHER\n";
//  }
//
//  void onSuccess() final {
//    streamf(std::cerr, "Small miracles: %o\n", fd_.DebugString());
//    std::cerr << "LET US READ AGAIN\n";
//    readerParty_->Read(&fd_, this);
//  }
//
//  std::unique_ptr< ::grpc::ClientAsyncReader< ::arrow::flight::protocol::FlightData>> readerParty_;
//  ::arrow::flight::protocol::FlightData fd_;
//};

//struct SuperNub final : public ServerCQCallback {
//  SuperNub(std::shared_ptr<FailureCallback> failureCallback) : ServerCQCallback(std::move(failureCallback)) {}
//  ~SuperNub() final {
//    std::cerr << "I AM NOT READY TO BE DELETED\n";
//  }
//
//  void onSuccess() final {
//    std::cerr << "Getting here simply means that the call worked. Now we want another bunch of callbacks to handle the reading\n";
//    std::cerr << "and so the pain begins. Also this is wrong..... need ctx_ and status_ to live on. so sad\n";
//    auto nub2 = new SuperNub2(std::move(failureCallback_), std::move(readerParty_));
//    nub2->readerParty_->Read(&nub2->fd_, nub2);
//  }
//
//  std::unique_ptr< ::grpc::ClientAsyncReader< ::arrow::flight::protocol::FlightData>> readerParty_;
//};
}  // namespace

void DHWorkerSession::getDataAsync(const Ticket &ticket, std::shared_ptr<getDataCallback_t> handler) const {
//  auto sn = new SuperNub(nullptr);
//  server_->bless(sn);
//  if (false) {
//    io::deephaven::proto::backplane::grpc::SubscriptionRequest sr;
//    *sr.mutable_ticket() = ticket;
//    std::string pain;
//    pain.push_back(0);
//    pain.push_back(1);
//    *sr.mutable_columns() = std::move(pain);
//    // no idea what the viewport is and what data structure it has
//    std::string vp;
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//
//    vp.push_back(1);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    vp.push_back(0);
//    *sr.mutable_viewport() = std::move(vp);
//
//    auto pain5 = server_->barrageStub()->DoSubscribe(&sn->ctx_);
//    auto wResult = pain5->Write(sr);
//    streamf(std::cerr, "wResult is %o", wResult);
//
//    io::deephaven::proto::backplane::grpc::BarrageData bd;
//    auto rResult = pain5->Read(&bd);
//    streamf(std::cerr, "rResult is %o", rResult);
//
//    streamf(std::cerr, "yeargh %o\n", bd.DebugString());
//  }
//
//  if (false) {
//    auto stupido = server_->flightStub()->DoGet(&sn->ctx_, ticket);
//    std::cerr << "starting\n";
//    ::arrow::flight::protocol::FlightData fd;
//    while (stupido->Read(&fd)) {
//      streamf(std::cerr, "Small miracles: %o\n", fd.DebugString());
//    }
//  }
//  streamf(std::cerr, "SuperNub is %o\n", (void*)sn);
//  auto qqq = server_->flightStub()->PrepareAsyncDoGet(&sn->ctx_, ticket, &server_->cq());
//  sn->readerParty_ = std::move(qqq);
//  sn->readerParty_->StartCall(sn);
//  auto qqq = server_->flightStub()->AsyncDoGet(&sn->ctx_, ticket, &server_->cq(), sn);
//  qqq->StartCall()
}

std::shared_ptr<TableHandle> DHWorkerSession::historicalTableAsync(
    std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName,
    std::shared_ptr<ItdCallback> itdCallback) {
  throw std::runtime_error("SAD003");
//  auto resultHandle = createTableHandle();
//  auto req = HistoricalTable::create(resultHandle, std::move(nameSpace), std::move(tableName));
//  dhWorker_->invoke(std::move(req), std::move(itdCallback));
//  return resultHandle;
}

std::shared_ptr<TableHandle> DHWorkerSession::tempTableAsync(
    std::shared_ptr<std::vector<std::shared_ptr<ColumnHolder>>> columnHolders,
    std::shared_ptr<ItdCallback> itdCallback) {
  throw std::runtime_error("SAD004");
//  auto resultHandle = createTableHandle();
//  auto req = NewTable::create(resultHandle, std::move(columnHolders));
//  dhWorker_->invoke(std::move(req), std::move(itdCallback));
//  return resultHandle;
}

Ticket DHWorkerSession::timeTableAsync(int64_t startTimeNanos, int64_t periodNanos,
    std::shared_ptr<EtcCallback> callback) {
  auto result = server_->newTicket();
  TimeTableRequest req;
  *req.mutable_result_id() = result;
  req.set_start_time_nanos(startTimeNanos);
  req.set_period_nanos(periodNanos);
  server_->sendRpc(req, std::move(callback), server_->tableStub(),
      &TableService::Stub::AsyncTimeTable, true);
  return result;
}

std::shared_ptr<TableHandle> DHWorkerSession::snapshotAsync(std::shared_ptr<TableHandle> leftTableHandle,
    std::shared_ptr<TableHandle> rightTableHandle, bool doInitialSnapshot,
    std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns,
    std::shared_ptr<ItdCallback> itdCallback) {
  throw std::runtime_error("SAD005");
//  auto resultHandle = createTableHandle();
//  auto req = Snapshot::create(std::move(leftTableHandle), std::move(rightTableHandle),
//      resultHandle, doInitialSnapshot, std::move(stampColumns));
//  dhWorker_->invoke(std::move(req), std::move(itdCallback));
//  return resultHandle;
}

Ticket DHWorkerSession::selectAsync(Ticket parentTicket,
    std::vector<std::string> columnSpecs, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  SelectOrUpdateRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  for (auto &cs : columnSpecs) {
    *req.mutable_column_specs()->Add() = std::move(cs);
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncSelect, true);
  return result;
}

Ticket DHWorkerSession::updateAsync(Ticket parentTicket,
    std::vector<std::string> columnSpecs, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  SelectOrUpdateRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  for (auto &cs : columnSpecs) {
    *req.mutable_column_specs()->Add() = std::move(cs);
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncUpdate, true);
  return result;
}

Ticket DHWorkerSession::viewAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
    std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  SelectOrUpdateRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  for (auto &cs : columnSpecs) {
    *req.mutable_column_specs()->Add() = std::move(cs);
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(), &TableService::Stub::AsyncView,
      true);
  return result;
}

Ticket DHWorkerSession::updateViewAsync(Ticket parentTicket,
    std::vector<std::string> columnSpecs, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  SelectOrUpdateRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  for (auto &cs : columnSpecs) {
    *req.mutable_column_specs()->Add() = std::move(cs);
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncUpdateView, true);
  return result;
}

Ticket DHWorkerSession::dropColumnsAsync(Ticket parentTicket, std::vector<std::string> columnSpecs,
    std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  DropColumnsRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  moveVectorData(std::move(columnSpecs), req.mutable_column_names());
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncDropColumns, true);
  return result;
}

Ticket DHWorkerSession::whereAsync(Ticket parentTicket, std::string condition,
    std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  UnstructuredFilterTableRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  *req.mutable_filters()->Add() = std::move(condition);
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncUnstructuredFilter, true);
  return result;
}

Ticket DHWorkerSession::sortAsync(Ticket parentTicket, std::vector<SortDescriptor> sortDescriptors,
    std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  SortTableRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  for (auto &sd : sortDescriptors) {
    *req.mutable_sorts()->Add() = std::move(sd);
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncSort, true);
  return result;
}

std::shared_ptr<TableHandle> DHWorkerSession::preemptiveAsync(std::shared_ptr<TableHandle> parentTableHandle,
    int32_t sampleIntervalMs, std::shared_ptr<ItdCallback> itdCallback) {
  auto resultHandle = createTableHandle();
  auto handleMapping = HandleMapping::create(std::move(parentTableHandle), resultHandle);
  auto tableOps = SerializedTableOps::create(
      nullptr,
      nullptr,
      std::move(handleMapping),
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      false,
      sampleIntervalMs
  );
  processBatchOperation(std::move(tableOps), resultHandle, std::move(itdCallback));
  return resultHandle;
}

Ticket DHWorkerSession::comboAggregateDescriptorAsync(Ticket parentTicket,
    std::vector<ComboAggregateRequest::Aggregate> aggregates,
    std::vector<std::string> groupByColumns, bool forceCombo,
    std::shared_ptr<EtcCallback> etcCallback) {

  auto result = server_->newTicket();
  ComboAggregateRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  for (auto &agg : aggregates) {
    *req.mutable_aggregates()->Add() = std::move(agg);
  }
  for (auto &gbc : groupByColumns) {
    *req.mutable_group_by_columns()->Add() = std::move(gbc);
  }
  req.set_force_combo(forceCombo);
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncComboAggregate, true);
  return result;
}

Ticket DHWorkerSession::headOrTailByAsync(Ticket parentTicket, bool head,
    int64_t n, std::vector<std::string> columnSpecs, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  HeadOrTailByRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  req.set_num_rows(n);
  for (auto &cs : columnSpecs) {
    req.mutable_group_by_column_specs()->Add(std::move(cs));
  }
  const auto &which = head ? &TableService::Stub::AsyncHeadBy : &TableService::Stub::AsyncTailBy;
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(), which, true);
  return result;
}

Ticket DHWorkerSession::headOrTailAsync(Ticket parentTicket,
    bool head, int64_t n, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  HeadOrTailRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  req.set_num_rows(n);
  const auto &which = head ? &TableService::Stub::AsyncHead : &TableService::Stub::AsyncTail;
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(), which, true);
  return result;
}

Ticket DHWorkerSession::ungroupAsync(Ticket parentTicket, bool nullFill,
    std::vector<std::string> groupByColumns, std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  UngroupRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_source_id()->mutable_ticket() = std::move(parentTicket);
  req.set_null_fill(nullFill);
  moveVectorData(std::move(groupByColumns), req.mutable_columns_to_ungroup());
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncUngroup, true);
  return result;
}

Ticket DHWorkerSession::mergeAsync(std::vector<Ticket> sourceTickets, std::string keyColumn,
    std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  MergeTablesRequest req;
  *req.mutable_result_id() = result;
  for (auto &t : sourceTickets) {
    *req.mutable_source_ids()->Add()->mutable_ticket() = std::move(t);
  }
  req.set_key_column(std::move(keyColumn));
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncMergeTables, true);
  return result;
}

Ticket DHWorkerSession::internalJoinAsync(JoinType joinType,
    Ticket leftTableTicket, Ticket rightTableTicket,
    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd,
    std::shared_ptr<EtcCallback> etcCallback) {
  auto result = server_->newTicket();
  JoinTablesRequest req;
  *req.mutable_result_id() = result;
  *req.mutable_left_id()->mutable_ticket() = std::move(leftTableTicket);
  *req.mutable_right_id()->mutable_ticket() = std::move(rightTableTicket);
  for (auto &ctm : columnsToMatch) {
    req.mutable_columns_to_match()->Add(std::move(ctm));
  }
  for (auto &cta : columnsToAdd) {
    req.mutable_columns_to_add()->Add(std::move(cta));
  }
  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
      &TableService::Stub::AsyncJoinTables, true);
  return result;
}

void DHWorkerSession::getTableDataAsync(std::shared_ptr<TableHandle> parentTableHandle,
    std::shared_ptr<RangeSet> rows, std::shared_ptr<BitSet> columns,
    std::shared_ptr<SFCallback<std::shared_ptr<TableSnapshot>>> callback) {
  throw std::runtime_error("SAD011");
//  auto req = ConstructSnapshotQuery::create(std::move(parentTableHandle), std::move(rows),
//      std::move(columns));
//  dhWorker_->invoke(std::move(req), std::move(callback));
}

void DHWorkerSession::subscribeAllAsync(std::shared_ptr<TableHandle> tableHandle,
    std::shared_ptr<BitSet> colBitset, bool isViewport,
    std::shared_ptr<SFCallback<std::shared_ptr<Void>>> callback) {
  throw std::runtime_error("SAD012");
//  streamf(std::cerr, "Sending server a subscribe nubbin of %o %o\n",
//      tableHandle->custom().serverId(), tableHandle->custom().clientId());
//  auto req = Subscribe::create(std::move(tableHandle), std::move(colBitset), isViewport);
//  dhWorker_->invoke(std::move(req), std::move(callback));
}

void DHWorkerSession::unsubscribeAsync(std::shared_ptr<TableHandle> tableHandle,
    std::shared_ptr<SFCallback<std::shared_ptr<Void>>> callback) {
  throw std::runtime_error("SAD013");
//  auto req = Unsubscribe::create(std::move(tableHandle));
//  dhWorker_->invoke(std::move(req), std::move(callback));
}

void DHWorkerSession::getDatabaseCatalogAsync(bool systemNamespaces, bool userNamespaces,
    std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex,
    std::shared_ptr<SFCallback<std::shared_ptr<Catalog>>> callback) {
  throw std::runtime_error("SAD014");
//  auto req = GetCatalog::create(systemNamespaces, userNamespaces, std::move(namespaceRegex),
//      std::move(tableRegex));
//  dhWorker_->invoke(std::move(req), std::move(callback));
}

std::shared_ptr<TableHandle> DHWorkerSession::catalogTableAsync(
    std::shared_ptr<ItdCallback> itdCallback) {
  throw std::runtime_error("SAD015");
//  auto resultHandle = createTableHandle();
//  auto req = GetCatalogTable::create(resultHandle);
//  dhWorker_->invoke(std::move(req), std::move(itdCallback));
//  return resultHandle;
}

void DHWorkerSession::bindToVariableAsync(const Ticket &tableId, std::string variable,
    std::shared_ptr<SFCallback<BindTableToVariableResponse>> callback) {
  BindTableToVariableRequest req;
  *req.mutable_console_id() = consoleId_;
  req.set_variable_name(std::move(variable));
  *req.mutable_table_id() = tableId;

  server_->sendRpc(req, std::move(callback), server_->consoleStub(),
      &ConsoleService::Stub::AsyncBindTableToVariable, true);
}

namespace {
class BatchOperationCallback final : public SFCallback<std::shared_ptr<BatchTableResponse>>, public DHWorkerAPIListenerDefault {
  typedef internal::TableHandleKey TableHandleKey;

  struct Private {};
public:
  static std::shared_ptr<BatchOperationCallback> create(std::shared_ptr<DHWorker> dhWorker,
      const std::shared_ptr<TableHandle> &resultHandle, std::shared_ptr<itdCallback_t> itdCallback);

  BatchOperationCallback(Private, std::shared_ptr<DHWorker> &&dhWorker,
      const TableHandleKey &targetKey, std::shared_ptr<itdCallback_t> &&itdCallback);
  ~BatchOperationCallback() final;

  void onExportedTableCreationMessage(const std::shared_ptr<InitialTableDefinition> &itd) final;

  void onSuccess(std::shared_ptr<BatchTableResponse> item) final;
  void onFailure(std::exception_ptr ep) final;

private:
  void unregisterSelf();

  std::shared_ptr<DHWorker> dhWorker_;
  TableHandleKey targetKey_;
  std::shared_ptr<itdCallback_t> itdCallback_;
  std::atomic<bool> haveResult_;
  std::weak_ptr<BatchOperationCallback> weakSelf_;
};
}  // namespace

// This gets a little complicated. The server protocol is to send a BatchTableRequest and wait for a
// BatchTableResponse, but then asynchronously send an InitialTableDefinition notification, which
// contains the information that we *actually* want. We have to do some extra effort to make this
// happen.
// 1. Make a BatchOperationCallback. This object serves as both the callback for the BatchTableResponse,
//    and also the listener for the DHWorker (to listen for the ITDCallback)
// 2. Register this as a DHWorker listener
// 3. Then send a BatchTableRequest, with this same object as callback.
// 4. If the BatchTableResponse is an exception, or if it's "successful" but contains an error message
//    from the server, then unregister the listener and propagate an error to the caller.
// 5. If the response is success, then wait forever for the InitialTableDefinition callback which is
//    hopefully coming soon. When it arrives, notify the caller and unregister the listener.
void DHWorkerSession::processBatchOperation(std::shared_ptr<SerializedTableOps> tableOps,
    const std::shared_ptr<TableHandle> &resultHandle, std::shared_ptr<ItdCallback> itdCallback) {
  auto boc = BatchOperationCallback::create(nullptr, resultHandle, std::move(itdCallback));
  throw std::runtime_error("super sad");
//  dhWorker_->addListener(boc);
//
//  auto ops = std::make_shared<std::vector<std::shared_ptr<SerializedTableOps>>>();
//  ops->reserve(1);
//  ops->emplace_back(std::move(tableOps));
//  auto btr = BatchTableRequest::create(ops);
//  auto btRequest = Batch::create(std::move(btr));
//  dhWorker_->invoke(std::move(btRequest), std::move(boc));
}

std::shared_ptr<TableHandle> DHWorkerSession::createTableHandle() {
  throw std::runtime_error("SAD016");
//  int32_t handleId = nextFreeTableHandleId_++;
//  return TableHandle::create(connectionId_, handleId, -1);
}

void DHWorkerSession::addTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<snapshotCallback_t> &handler) {
//  snapshotAndDeltaUpdateHandler_->addTableSnapshotHandler(tableHandle, handler);
}

void DHWorkerSession::removeTableSnapshotHandler(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<snapshotCallback_t> &handler) {
//  snapshotAndDeltaUpdateHandler_->removeTableSnapshotHandler(tableHandle, handler);
}

void DHWorkerSession::addTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<updateCallback_t> &handler) {
//  snapshotAndDeltaUpdateHandler_->addTableUpdateHandler(tableHandle, handler);
}

void DHWorkerSession::removeTableUpdateHandler(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<updateCallback_t> &handler) {
//  snapshotAndDeltaUpdateHandler_->removeTableUpdateHandler(tableHandle, handler);
}

namespace internal {
bool TableHandleKey::tryCreate(const TableHandle &th, TableHandleKey *result) {
  const auto &c = th.custom();
  if (c.connectionId() < 0 || c.clientId() < 0) {
    return false;
  }
  *result = TableHandleKey(c.connectionId(), c.clientId());
  return true;
}

TableHandleKey TableHandleKey::create(const TableHandle &th) {
  TableHandleKey result;
  if (!tryCreate(th, &result)) {
    const auto &c = th.custom();
    throw std::runtime_error(stringf("Can't create a TableHandleKey from TableHandle (%o, %o, %o)",
        c.connectionId(), c.clientId(), c.serverId()));
  }
  return result;
}

std::shared_ptr<SnapshotAndDeltaUpdateHandler> SnapshotAndDeltaUpdateHandler::create(
    std::shared_ptr<Executor> executor) {
  auto result = std::make_shared<SnapshotAndDeltaUpdateHandler>(Private(), std::move(executor));
  result->weakSelf_ = result;
  return result;
}

SnapshotAndDeltaUpdateHandler::SnapshotAndDeltaUpdateHandler(Private,
    std::shared_ptr<Executor> executor) : executor_(std::move(executor)) {}

SnapshotAndDeltaUpdateHandler::~SnapshotAndDeltaUpdateHandler() = default;

void SnapshotAndDeltaUpdateHandler::onInitialSnapshot(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<TableSnapshot> &snapshot) {
  auto self = weakSelf_.lock();
  auto cb = [self, tableHandle, snapshot]() {
    TableHandleKey thk;
    if (!TableHandleKey::tryCreate(*tableHandle, &thk)) {
      // Server sent a table handle that we don't want to deal with (one without clientId set)
      return;
    }
    auto up = self->snapshotHandlers_.find(thk);
    if (up == self->snapshotHandlers_.end()) {
      return;
    }
    for (const auto &handler : up->second) {
      handler->invoke(tableHandle, snapshot);
    }
  };
  executor_->invokeCallable(std::move(cb));
}

void SnapshotAndDeltaUpdateHandler::onIncrementalUpdates(const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<DeltaUpdates> &updates) {
  auto self = weakSelf_.lock();
  auto cb = [self, tableHandle, updates]() {
    TableHandleKey thk;
    if (!TableHandleKey::tryCreate(*tableHandle, &thk)) {
      // Server sent a table handle that we don't want to deal with (one without clientId set)
      return;
    }
    auto up = self->updateHandlers_.find(thk);
    if (up == self->updateHandlers_.end()) {
      return;
    }
    for (const auto &handler : up->second) {
      handler->invoke(tableHandle, updates);
    }
  };
  executor_->invokeCallable(std::move(cb));
}

namespace {
template<typename Map, typename K, typename V>
void removeFromMap(Map &map, const K &key, const V &value) {
  auto mp = map.find(key);
  if (mp == map.end()) {
    return;
  }
  auto &vec = mp->second;
  auto ep = std::find(vec.begin(), vec.end(), value);
  if (ep != vec.end()) {
    vec.erase(ep);
    if (vec.empty()) {
      map.erase(key);
    }
  }
}
}  // namespace

void SnapshotAndDeltaUpdateHandler::addTableSnapshotHandler(
    const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<snapshotCallback_t> &handler) {
  auto self = weakSelf_.lock();
  auto thk = TableHandleKey::create(*tableHandle);
  auto cb = [self, thk, handler]() {
    self->snapshotHandlers_[thk].push_back(handler);
  };
  executor_->invokeCallable(std::move(cb));
}

void SnapshotAndDeltaUpdateHandler::removeTableSnapshotHandler(
    const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<snapshotCallback_t> &handler) {
  auto self = weakSelf_.lock();
  auto thk = TableHandleKey::create(*tableHandle);
  auto cb = [self, thk, handler]() {
    removeFromMap(self->snapshotHandlers_, thk, handler);
  };
  executor_->invokeCallable(std::move(cb));
}

void SnapshotAndDeltaUpdateHandler::addTableUpdateHandler(
    const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<updateCallback_t> &handler) {
  auto self = weakSelf_.lock();
  auto thk = TableHandleKey::create(*tableHandle);
  auto cb = [self, thk, handler]() {
    self->updateHandlers_[thk].push_back(handler);
  };
  executor_->invokeCallable(std::move(cb));
}

void SnapshotAndDeltaUpdateHandler::removeTableUpdateHandler(
    const std::shared_ptr<TableHandle> &tableHandle,
    const std::shared_ptr<updateCallback_t> &handler) {
  auto self = weakSelf_.lock();
  auto thk = TableHandleKey::create(*tableHandle);
  auto cb = [self, thk, handler]() {
    removeFromMap(self->updateHandlers_, thk, handler);
  };
  executor_->invokeCallable(std::move(cb));
}
}  // namespace internal

namespace {
std::shared_ptr<BatchOperationCallback> BatchOperationCallback::create(
    std::shared_ptr<DHWorker> dhWorker, const std::shared_ptr<TableHandle> &resultHandle,
    std::shared_ptr<itdCallback_t> itdCallback) {
  auto targetKey = TableHandleKey::create(*resultHandle);
  auto result = std::make_shared<BatchOperationCallback>(Private(), std::move(dhWorker),
      targetKey, std::move(itdCallback));
  result->weakSelf_ = result;
  return result;
}

BatchOperationCallback::BatchOperationCallback(Private, std::shared_ptr<DHWorker> &&dhWorker,
    const TableHandleKey &targetKey, std::shared_ptr<itdCallback_t> &&itdCallback) :
    dhWorker_(std::move(dhWorker)), targetKey_(targetKey), itdCallback_(std::move(itdCallback)),
    haveResult_(false) {}

BatchOperationCallback::~BatchOperationCallback() = default;

void BatchOperationCallback::onExportedTableCreationMessage(
    const std::shared_ptr<InitialTableDefinition> &itd) {
  TableHandleKey incomingKey;
  // Ignore duplicates, TableHandleKeys which don't have clientIds, and results not meant for us.
  if (haveResult_ ||
      !TableHandleKey::tryCreate(*itd->id(), &incomingKey) ||
      incomingKey != targetKey_) {
    return;
  }
  itdCallback_->onSuccess(itd);
  unregisterSelf();
}

void BatchOperationCallback::onSuccess(std::shared_ptr<BatchTableResponse> item) {
  if (!item->success()->empty()) {
    // This is the good case. In this case we do nothing now. This same object will be listening
    // for the InitialTableDefinition message.
    return;
  }

  std::exception_ptr ep;
  const auto &fms = *item->failureMessages();
  if (fms.empty()) {
    ep = std::make_exception_ptr(std::runtime_error("Batch table request failed but there was no failure message"));
  } else {
    ep = std::make_exception_ptr(std::runtime_error(*fms[0]));
  }
  onFailure(std::move(ep));
}

void BatchOperationCallback::onFailure(std::exception_ptr ep) {
  if (haveResult_) {
    return;
  }
  itdCallback_->onFailure(std::move(ep));
  unregisterSelf();
}

void BatchOperationCallback::unregisterSelf() {
  haveResult_ = true;
  auto self = weakSelf_.lock();
  dhWorker_->removeListener(self);
}

void moveVectorData(std::vector<std::string> src, google::protobuf::RepeatedPtrField<std::string> *dest) {
  for (auto &s : src) {
    dest->Add(std::move(s));
  }
}
}  // namespace
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
