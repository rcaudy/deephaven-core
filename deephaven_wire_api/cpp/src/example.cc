#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include <proto/session.pb.h>
#include <proto/session.grpc.pb.h>
#include <proto/table.pb.h>
#include <proto/table.grpc.pb.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using io::deephaven::proto::backplane::grpc::HandshakeRequest;
using io::deephaven::proto::backplane::grpc::HandshakeResponse;
using io::deephaven::proto::backplane::grpc::ExportNotificationRequest;
using io::deephaven::proto::backplane::grpc::ExportNotification;

using io::deephaven::proto::backplane::grpc::SessionService;
using io::deephaven::proto::backplane::grpc::TableService;
using io::deephaven::proto::backplane::grpc::EmptyTableRequest;
using io::deephaven::proto::backplane::grpc::TimeTableRequest;
using io::deephaven::proto::backplane::grpc::ExportedTableCreationResponse;

// using namespace io::deephaven::barrage::flatbuf;

namespace {

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

      EmptyTableRequest etReq;
      ExportedTableCreationResponse ttRes;

      char ticket[8];
      uint64_t ticketId = 1;
      memcpy(ticket, &ticketId, sizeof(ticketId));

      *(etReq.mutable_result_id()->mutable_ticket()) = std::string(ticket, 8);
      etReq.set_size(5);
      etReq.mutable_column_names()->Add("col1");
      etReq.mutable_column_types()->Add("qqint");
      auto succ = tableService_->EmptyTable(ctxt.get(), etReq, &ttRes);

//      auto foo = tableService_->AsyncEmptyTable();

      std::cout << "succ is " << succ.error_code() << "\n";
      std::cout << "em is " << succ.error_message() << "\n";
      std::cout << "ok is " << succ.ok() << "\n";

      ExportNotificationRequest req;

      ctxt = getClientContext();
      std::unique_ptr<ClientReader<ExportNotification>> response = sessionService_->ExportNotifications(ctxt.get(), req);

      ExportNotification n;
      while (response->Read(&n)) {
        long id = *(reinterpret_cast<const long *>(n.ticket().ticket().c_str()));
        std::cout << "Export Notification: " << id << " is " << ExportNotification_State_Name(n.export_state()) << std::endl;
      }
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
