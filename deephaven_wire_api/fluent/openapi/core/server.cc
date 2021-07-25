#include "server.h"

#include <exception>
#include <grpcpp/grpcpp.h>
#include <regex>
#include <arrow/flight/client.h>
#include <arrow/flight/types.h>
#include <arrow/array.h>
#include <arrow/array/array_primitive.h>

#include "utility/utility.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"


using namespace std;
using arrow::flight::protocol::Wicket;
using arrow::flight::FlightClient;
typedef Wicket Ticket;
using deephaven::openAPI::utility::bit_cast;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;
using io::deephaven::proto::backplane::grpc::HandshakeRequest;
using io::deephaven::proto::backplane::script::grpc::StartConsoleRequest;

namespace deephaven {
namespace openAPI {
namespace core {
std::shared_ptr<Server> Server::createFromTarget(const std::string &target) {
  auto channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
  auto bs = BarrageService::NewStub(channel);
  auto cs = ConsoleService::NewStub(channel);
  auto ss = SessionService::NewStub(channel);
  auto ts = TableService::NewStub(channel);

  auto flightTarget = "grpc://" + target;
  streamf(std::cerr, "TODO(kosak): Converting %o to %o for Arrow Flight\n", target, flightTarget);
  arrow::flight::Location location;
  auto rc1 = arrow::flight::Location::Parse(flightTarget, &location);
  if (!rc1.ok()) {
    auto message = stringf("Location::Parse(%o) failed, error = %o", flightTarget, rc1.ToString());
    throw std::runtime_error(message);
  }

  std::unique_ptr<arrow::flight::FlightClient> fc;
  auto rc2 = arrow::flight::FlightClient::Connect(location, &fc);
  if (!rc2.ok()) {
    auto message = stringf("FlightClient::Connect() failed, error = %o", rc2.ToString());
    throw std::runtime_error(message);
  }

  auto result = std::make_shared<Server>(Private(), std::move(bs), std::move(cs),
      std::move(ss), std::move(ts), std::move(fc));
  result->self_ = result;

  std::thread t(&processCompletionQueueForever, result);
  t.detach();

  return result;
}

Server::Server(Private,
    std::unique_ptr<BarrageService::Stub> barrageStub,
    std::unique_ptr<ConsoleService::Stub> consoleStub,
    std::unique_ptr<SessionService::Stub> sessionStub,
    std::unique_ptr<TableService::Stub> tableStub,
    std::unique_ptr<arrow::flight::FlightClient> flightClient) :
    barrageStub_(std::move(barrageStub)),
    consoleStub_(std::move(consoleStub)),
    sessionStub_(std::move(sessionStub)),
    tableStub_(std::move(tableStub)),
    flightClient_(std::move(flightClient)),
    nextFreeTicketId_(1) {}

Server::~Server() = default;

Ticket Server::newTicket() {
  auto ticketId = nextFreeTicketId_++;
  constexpr auto ticketSize = sizeof(ticketId);
  static_assert(ticketSize == 4, "Unexpected ticket size");
  char buffer[ticketSize + 1];
  buffer[0] = 'e';
  memcpy(buffer + 1, &ticketId, ticketSize);
  Ticket result;
  *result.mutable_ticket() = std::string(buffer, sizeof(buffer));
  return result;
}

void Server::setAuthentication(std::string metadataHeader, std::string sessionToken) {
  if (haveAuth_) {
    throw std::runtime_error("Can't reset authentication token");
  }
  haveAuth_ = true;
  metadataHeader_ = std::move(metadataHeader);
  sessionToken_ = std::move(sessionToken);
}

void Server::newSessionAsync(std::shared_ptr<SFCallback<HandshakeResponse>> callback) {
  HandshakeRequest req;
  req.set_auth_protocol(1);
  sendRpc(req, std::move(callback), sessionStub_.get(), &SessionService::Stub::AsyncNewSession,
      false);
}

void Server::startConsoleAsync(std::shared_ptr<SFCallback<StartConsoleResponse>> callback) {
  auto ticket = newTicket();
  StartConsoleRequest req;
  *req.mutable_result_id() = std::move(ticket);
  req.set_session_type("groovy");
  sendRpc(req, std::move(callback), consoleStub_.get(), &ConsoleService::Stub::AsyncStartConsole,
      true);
}

std::pair<std::string, std::string> Server::makeBlessing() const {
  return std::make_pair(metadataHeader_, sessionToken_);
}

void Server::processCompletionQueueForever(const std::shared_ptr<Server> &self) {
  std::cerr << "Completion queue thread waking up\n";
  while (true) {
    if (!self->processNextCompletionQueueItem()) {
      break;
    }
  }
  std::cerr << "Completion queue thread shutting down\n";
}

bool Server::processNextCompletionQueueItem() {
  void *tag;
  bool ok;
  auto gotEvent = completionQueue_.Next(&tag, &ok);
  // streamf(std::cerr, "gotEvent is %o, tag is %o, ok is %o\n", gotEvent, tag, ok);
  if (!gotEvent) {
    return false;
  }

  try {
    // Destruct/deallocate on the way out.
    std::unique_ptr<ServerCQCallback> cqcb(static_cast<ServerCQCallback *>(tag));

    if (!ok) {
      cqcb->failureCallback_->onFailure(
          std::make_exception_ptr(std::runtime_error("Some GRPC network or connection error")));
      return true;
    }

    const auto &stat = cqcb->status_;
    if (!stat.ok()) {
      auto message = stringf("Error %o. Message: %o", stat.error_code(), stat.error_message());
      cqcb->failureCallback_->onFailure(std::make_exception_ptr(std::runtime_error(message)));
      return true;
    }

    cqcb->onSuccess();
  } catch (const std::exception &e) {
    std::cerr << "Caught exception on callback, aborting: " << e.what() << "\n";
    return false;
  } catch (...) {
    std::cerr << "Caught exception on callback, aborting\n";
    return false;
  }
  return true;
}

ServerCQCallback::ServerCQCallback(std::shared_ptr<FailureCallback> failureCallback) :
    failureCallback_(std::move(failureCallback)) {}
ServerCQCallback::~ServerCQCallback() = default;
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
