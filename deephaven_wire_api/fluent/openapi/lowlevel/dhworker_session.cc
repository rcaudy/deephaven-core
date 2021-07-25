#include "lowlevel/dhworker_session.h"

#include <map>
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
using deephaven::openAPI::utility::Callback;
using deephaven::openAPI::utility::Executor;
using deephaven::openAPI::utility::FailureCallback;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;


namespace deephaven {
namespace openAPI {
namespace lowlevel {

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

// void DHWorkerSession::getDataAsync(const Ticket &ticket, std::shared_ptr<getDataCallback_t> handler) const {
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
// }

//std::shared_ptr<TableHandle> DHWorkerSession::historicalTableAsync(
//    std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName,
//    std::shared_ptr<ItdCallback> itdCallback) {
//  throw std::runtime_error("SAD003");
////  auto resultHandle = createTableHandle();
////  auto req = HistoricalTable::create(resultHandle, std::move(nameSpace), std::move(tableName));
////  dhWorker_->invoke(std::move(req), std::move(itdCallback));
////  return resultHandle;
//}

//std::shared_ptr<TableHandle> DHWorkerSession::tempTableAsync(
//    std::shared_ptr<std::vector<std::shared_ptr<ColumnHolder>>> columnHolders,
//    std::shared_ptr<ItdCallback> itdCallback) {
//  throw std::runtime_error("SAD004");
////  auto resultHandle = createTableHandle();
////  auto req = NewTable::create(resultHandle, std::move(columnHolders));
////  dhWorker_->invoke(std::move(req), std::move(itdCallback));
////  return resultHandle;
//}

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

//std::shared_ptr<TableHandle> DHWorkerSession::snapshotAsync(std::shared_ptr<TableHandle> leftTableHandle,
//    std::shared_ptr<TableHandle> rightTableHandle, bool doInitialSnapshot,
//    std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns,
//    std::shared_ptr<ItdCallback> itdCallback) {
//  throw std::runtime_error("SAD005");
////  auto resultHandle = createTableHandle();
////  auto req = Snapshot::create(std::move(leftTableHandle), std::move(rightTableHandle),
////      resultHandle, doInitialSnapshot, std::move(stampColumns));
////  dhWorker_->invoke(std::move(req), std::move(itdCallback));
////  return resultHandle;
//}

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

//std::shared_ptr<TableHandle> DHWorkerSession::preemptiveAsync(std::shared_ptr<TableHandle> parentTableHandle,
//    int32_t sampleIntervalMs, std::shared_ptr<ItdCallback> itdCallback) {
//  auto resultHandle = createTableHandle();
//  auto handleMapping = HandleMapping::create(std::move(parentTableHandle), resultHandle);
//  auto tableOps = SerializedTableOps::create(
//      nullptr,
//      nullptr,
//      std::move(handleMapping),
//      nullptr,
//      nullptr,
//      nullptr,
//      nullptr,
//      nullptr,
//      false,
//      sampleIntervalMs
//  );
//  processBatchOperation(std::move(tableOps), resultHandle, std::move(itdCallback));
//  return resultHandle;
//}

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

//Ticket DHWorkerSession::internalJoinAsync(JoinType joinType,
//    Ticket leftTableTicket, Ticket rightTableTicket,
//    std::vector<std::string> columnsToMatch, std::vector<std::string> columnsToAdd,
//    std::shared_ptr<EtcCallback> etcCallback) {
//  auto result = server_->newTicket();
//  JoinTablesRequest req;
//  *req.mutable_result_id() = result;
//  *req.mutable_left_id()->mutable_ticket() = std::move(leftTableTicket);
//  *req.mutable_right_id()->mutable_ticket() = std::move(rightTableTicket);
//  for (auto &ctm : columnsToMatch) {
//    req.mutable_columns_to_match()->Add(std::move(ctm));
//  }
//  for (auto &cta : columnsToAdd) {
//    req.mutable_columns_to_add()->Add(std::move(cta));
//  }
//  server_->sendRpc(req, std::move(etcCallback), server_->tableStub(),
//      &TableService::Stub::AsyncJoinTables, true);
//  return result;
//}

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
void moveVectorData(std::vector<std::string> src,
    google::protobuf::RepeatedPtrField<std::string> *dest) {
  for (auto &s : src) {
    dest->Add(std::move(s));
  }
}
}  // namespace
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
