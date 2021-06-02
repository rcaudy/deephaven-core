#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include <proto/session.pb.h>
#include <proto/session.grpc.pb.h>
#include <proto/table.pb.h>
#include <proto/table.grpc.pb.h>
#include <proto/flight.pb.h>
#include <proto/flight.grpc.pb.h>

#include <arrow/type.h>
#include <arrow/flight/types.h>
#include <arrow/flight/client.h>

#include "barrage/Barrage_generated.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using arrow::Status;

using arrow::flight::FlightCallOptions;
using io::deephaven::proto::backplane::grpc::HandshakeRequest;
using io::deephaven::proto::backplane::grpc::HandshakeResponse;
using io::deephaven::proto::backplane::grpc::ExportNotificationRequest;
using io::deephaven::proto::backplane::grpc::ExportNotification;

using io::deephaven::proto::backplane::grpc::SessionService;
using io::deephaven::proto::backplane::grpc::TableService;
using io::deephaven::proto::backplane::grpc::TimeTableRequest;
using io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse;

using namespace io::deephaven::barrage::flatbuf;

namespace {

Status FlightDemo(const FlightCallOptions& options, const char* dest) {
  arrow::flight::Location workerDest;
  ARROW_RETURN_NOT_OK(arrow::flight::Location::Parse(dest, &workerDest));

  std::unique_ptr<arrow::flight::FlightClient> client;
  ARROW_RETURN_NOT_OK(arrow::flight::FlightClient::Connect(workerDest, &client));

  std::unique_ptr<arrow::flight::FlightListing> listing;
  ARROW_RETURN_NOT_OK(client->ListFlights(options, {}, &listing));

  std::unique_ptr<arrow::flight::FlightInfo> nextInfo;

  std::cout << "Flight List: " << std::endl;
  do {
    ARROW_RETURN_NOT_OK(listing->Next(&nextInfo));
    if (!nextInfo) {
      break;
    }

    arrow::ipc::DictionaryMemo memo;
    std::shared_ptr<arrow::Schema> schema;

    std::cout << "Descriptor: " << nextInfo->descriptor().ToString() << std::endl;
    std::cout << "TotalRecords: " << nextInfo->total_records() << std::endl;
    std::cout << "TotalBytes: " << nextInfo->total_bytes() << std::endl;
    for (const arrow::flight::FlightEndpoint fe : nextInfo->endpoints()) {
      std::cout << "\tEndPoint: " << fe.ticket.ticket << std::endl;
    }
    std::cout << std::endl;

    // This should work; it claims that our flatbuffer is invalid:
    // ARROW_RETURN_NOT_OK(nextInfo->GetSchema(&memo, &schema));
    // std::cout << "Schema: " << schema->ToString() << std::endl;
  } while (true);
  std::cout << "(complete)" << std::endl;

  return Status::OK();
}

class Client {
  public:
    Client(std::shared_ptr<Channel> channel)
      : sessionService_(SessionService::NewStub(channel))
      , tableService_(TableService::NewStub(channel))
    {}

    void newSession() {
      HandshakeRequest req;
      req.set_auth_protocol(1);

      HandshakeResponse res;

      std::unique_ptr<ClientContext> ctxt = getClientContext();

      grpc::Status status = sessionService_->NewSession(ctxt.get(), req, &res);

      if (status.ok()) {
        metadata_header = res.metadata_header();
        session_token = res.session_token();
        std::transform(metadata_header.begin(), metadata_header.end(), metadata_header.begin(), ::tolower);

        std::cout << "New Session Established: " << res.session_token() << std::endl;
      } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      }
    }

    void exportNotifications() {
      std::unique_ptr<ClientContext> ctxt = getClientContext();

      TimeTableRequest ttReq;
      ExportedTableCreationResponse ttRes;

      char ticket[8];
      long* ticketId = reinterpret_cast<long *>(ticket);
      *ticketId = 1;

      std::string tid(ticket, 8);
      *(ttReq.mutable_result_id()->mutable_ticket()) = tid;
      ttReq.set_period_nanos(1000000000L);
      tableService_->TimeTable(ctxt.get(), ttReq, &ttRes);

      ExportNotificationRequest req;

      ctxt = getClientContext();
      std::unique_ptr<ClientReader<ExportNotification>> response = sessionService_->ExportNotifications(ctxt.get(), req);

      ExportNotification n;
      while (response->Read(&n)) {
        long id = *(reinterpret_cast<const long *>(n.ticket().ticket().c_str()));
        std::cout << "Export Notification: " << id << " is " << ExportNotification_State_Name(n.export_state()) << std::endl;
      }
    }

    FlightCallOptions getFlightOptions() {
      FlightCallOptions opts;
      if (!metadata_header.empty()) {
        opts.headers.push_back({metadata_header, session_token});
      }
      return opts;
    }

    std::unique_ptr<ClientContext> getClientContext() {
      std::unique_ptr<ClientContext> ctxt(new ClientContext());
      if (!metadata_header.empty()) {
        ctxt->AddMetadata(metadata_header, session_token);
      }
      return ctxt;
    }

  private:
    std::unique_ptr<SessionService::Stub> sessionService_;
    std::unique_ptr<TableService::Stub> tableService_;

    std::string metadata_header;
    std::string session_token;
};

void RunMain(const char *dest) {
  Client api(grpc::CreateChannel(dest, grpc::InsecureChannelCredentials()));

  api.newSession();

  Status st = FlightDemo(api.getFlightOptions(), "grpc://localhost:10000");
  if (!st.ok()) {
    std::cerr << "Error: " << st << std::endl;
  }

  api.exportNotifications();
}

}  // anonymous namespace

int main(int argc, char** argv) {
  try {
    const char *dest = argc <= 1 ? "grpc://localhost:10000" : argv[1];
    RunMain(dest);
  } catch (...) {
    std::cerr << "Unknown Error" << std::endl;
  }
}
