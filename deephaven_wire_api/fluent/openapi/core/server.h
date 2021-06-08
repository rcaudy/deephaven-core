#pragma once

#include <future>
#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/utility/string_view.hpp>

#include "core/protocol_base_classes.h"
#include "core/deserializer.h"
#include "core/serializer.h"
#include "core/callbacks.h"
#include "core/protocol_base_classes.h"
#include "utility/executor.h"
#include "proto/console.pb.h"
#include "proto/console.grpc.pb.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
class ServerCQCallback {
public:
  ServerCQCallback(std::shared_ptr<FailureCallback> failureCallback);
  ServerCQCallback(const ServerCQCallback &other) = delete;
  ServerCQCallback(ServerCQCallback &&other) = delete;
  virtual ~ServerCQCallback();

  virtual void onSuccess() = 0;

  std::shared_ptr<FailureCallback> failureCallback_;
  grpc::ClientContext ctx_;
  grpc::Status status_;
};

template<typename Response>
class ServerResponseHolder final : public ServerCQCallback {
public:
  explicit ServerResponseHolder(std::shared_ptr<SFCallback<Response>> callback) :
  ServerCQCallback(callback), callback_(std::move(callback)) {}

  ~ServerResponseHolder() final = default;

  void onSuccess() final {
    deephaven::openAPI::utility::streamf(std::cerr, "*** RESPONSE %o\n%o\n*** END RESPONSE ***\n",
        typeid(Response).name(), resp_.DebugString());
    callback_->onSuccess(std::move(resp_));
  }

  std::shared_ptr<SFCallback<Response>> callback_;
  Response resp_;
};

class Server {
  typedef arrow::flight::protocol::Ticket Ticket;
  typedef io::deephaven::proto::backplane::grpc::SessionService SessionService;
  typedef io::deephaven::proto::backplane::grpc::TableService TableService;
  typedef io::deephaven::proto::backplane::script::grpc::ConsoleService ConsoleService;

  typedef deephaven::openAPI::utility::Executor Executor;
  typedef deephaven::openAPI::core::remoting::Request Request;
  typedef deephaven::openAPI::utility::Void Void;

  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

  struct Private {};

public:
  static std::shared_ptr<Server> createFromTarget(const std::string &target);
  Server(const Server &other) = delete;
  Server &operator=(const Server &other) = delete;
  Server(Private, std::unique_ptr<ConsoleService::Stub> consoleStub,
      std::unique_ptr<SessionService::Stub> sessionStub,
      std::unique_ptr<TableService::Stub> tableStub);
  ~Server();

  ConsoleService::Stub *consoleStub() { return consoleStub_.get(); }
  SessionService::Stub *sessionStub() { return sessionStub_.get(); }
  TableService::Stub *tableStub() { return tableStub_.get(); }

  Ticket newTicket();

  void setAuthentication(std::string metadataHeader, std::string sessionToken);

  template<typename TReq, typename TResp, typename TStub, typename TPtrToMember>
  void sendRpc(const TReq &req, std::shared_ptr<SFCallback<TResp>> responseCallback,
      TStub *stub, const TPtrToMember &pm, bool needAuth);

private:
  static void processCompletionQueueForever(const std::shared_ptr<Server> &self);
  bool processNextCompletionQueueItem();

  std::unique_ptr<ConsoleService::Stub> consoleStub_;
  std::unique_ptr<SessionService::Stub> sessionStub_;
  std::unique_ptr<TableService::Stub> tableStub_;
  grpc::CompletionQueue completionQueue_;

  bool haveAuth_ = false;
  std::string metadataHeader_;
  std::string sessionToken_;

  std::atomic<int64_t> nextFreeTicketId_;

  // We occasionally need a shared pointer to ourself.
  std::weak_ptr<Server> self_;
};

template<typename TReq, typename TResp, typename TStub, typename TPtrToMember>
void Server::sendRpc(const TReq &req, std::shared_ptr<SFCallback<TResp>> responseCallback,
    TStub *stub, const TPtrToMember &pm, bool needAuth) {
  using deephaven::openAPI::utility::streamf;
  streamf(std::cerr, "*** REQUEST %o\n%o\n*** END REQUEST ***\n", typeid(TReq).name(), req.DebugString());
  auto *response = new ServerResponseHolder<TResp>(std::move(responseCallback));
  if (needAuth) {
    if (!haveAuth_) {
      throw std::runtime_error("Caller needed authorization but I don't have it");
    }
    response->ctx_.AddMetadata(metadataHeader_, sessionToken_);
  }
  auto rpc = (stub->*pm)(&response->ctx_, req, &completionQueue_);
  rpc->Finish(&response->resp_, &response->status_, response);
}
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
