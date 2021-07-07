#include "server.h"

#include <exception>
#include <grpcpp/grpcpp.h>
#include <regex>

#include "core/protocol_base_classes.h"
#include "utility/utility.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"

using namespace std;
using arrow::flight::protocol::Ticket;
using deephaven::openAPI::utility::bit_cast;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::core::remoting::Constants;

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
std::shared_ptr<Server> Server::createFromTarget(const std::string &target) {
  auto channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
  auto bs = BarrageService::NewStub(channel);
  auto cs = ConsoleService::NewStub(channel);
  auto fs = FlightService::NewStub(channel);
  auto ss = SessionService::NewStub(channel);
  auto ts = TableService::NewStub(channel);
  auto result = std::make_shared<Server>(Private(), std::move(bs), std::move(cs), std::move(fs),
      std::move(ss), std::move(ts));
  result->self_ = result;

  std::thread t(&processCompletionQueueForever, result);
  t.detach();

  return result;
}

Server::Server(Private,
    std::unique_ptr<BarrageService::Stub> barrageStub,
    std::unique_ptr<ConsoleService::Stub> consoleStub,
    std::unique_ptr<FlightService::Stub> flightStub,
    std::unique_ptr<SessionService::Stub> sessionStub,
    std::unique_ptr<TableService::Stub> tableStub) :
    barrageStub_(std::move(barrageStub)),
    consoleStub_(std::move(consoleStub)),
    flightStub_(std::move(flightStub)),
    sessionStub_(std::move(sessionStub)),
    tableStub_(std::move(tableStub)),
    nextFreeTicketId_(1) {}

Server::~Server() = default;

Ticket Server::newTicket() {
  auto ticketId = nextFreeTicketId_++;
  constexpr auto ticketSize = sizeof(ticketId);
  static_assert(ticketSize == 8, "Unexpected ticket size");
  char buffer[ticketSize];
  memcpy(buffer, &ticketId, ticketSize);
  Ticket result;
  *result.mutable_ticket() = std::string(buffer, ticketSize);
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
  streamf(std::cerr, "gotEvent is %o, tag is %o, ok is %o\n", gotEvent, tag, ok);
  std::cerr << "GOT TO LINE " << __LINE__ << '\n';
  if (!gotEvent) {
    std::cerr << "GOT TO LINE " << __LINE__ << '\n';
    return false;
  }

  std::cerr << "GOT TO LINE " << __LINE__ << '\n';

  try {
    std::cerr << "GOT TO LINE " << __LINE__ << '\n';
    // Destruct/deallocate on the way out.
    auto *cqcb = static_cast<ServerCQCallback *>(tag);
    std::cerr << "NOT DESTRUCTING\n";

    std::cerr << "OK can mean different things in different contexts. In a streaming read, it just means no more streameroo baby\n";
    if (!ok) {
      std::cerr << "GOT TO LINE " << __LINE__ << '\n';
      cqcb->failureCallback_->onFailure(
          std::make_exception_ptr(std::runtime_error("Some GRPC network or connection error")));
      return true;
    }

    std::cerr << "GOT TO LINE " << __LINE__ << '\n';
    const auto &stat = cqcb->status_;
    if (!stat.ok()) {
      std::cerr << "GOT TO LINE " << __LINE__ << '\n';
      auto message = stringf("Error %o. Message: %o", stat.error_code(), stat.error_message());
      cqcb->failureCallback_->onFailure(std::make_exception_ptr(std::runtime_error(message)));
      return true;
    }

    std::cerr << "GOT TO LINE " << __LINE__ << '\n';
    cqcb->onSuccess();
    std::cerr << "GOT TO LINE " << __LINE__ << '\n';
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
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
