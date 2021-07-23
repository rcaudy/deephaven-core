#include "dhserver.h"

#include <grpcpp/grpcpp.h>

#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"
#include "lowlevel/generated/dhserver_notifications.h"
#include "lowlevel/generated/dhserver_requests.h"
#include "lowlevel/generated/shared_objects.h"
#include "utility/utility.h"

using namespace std;
using io::deephaven::proto::backplane::grpc::HandshakeRequest;
using io::deephaven::proto::backplane::grpc::HandshakeResponse;
using io::deephaven::proto::backplane::grpc::SessionService;
using io::deephaven::proto::backplane::script::grpc::ConsoleService;
using io::deephaven::proto::backplane::script::grpc::StartConsoleRequest;
using io::deephaven::proto::backplane::grpc::TableService;
using deephaven::openAPI::core::remoting::util::Deserializer;
using deephaven::openAPI::core::remoting::Notification;
using deephaven::openAPI::core::remoting::Server;
using deephaven::openAPI::core::remoting::ServerCQCallback;
using deephaven::openAPI::core::remoting::ServerResponseHolder;
using deephaven::openAPI::lowlevel::remoting::generated::DHServerNotificationVisitor;
using deephaven::openAPI::lowlevel::remoting::generated::deserializeDHServerNotification;
using deephaven::openAPI::lowlevel::remoting::generated::dynamicDeserializerNames;
using deephaven::openAPI::lowlevel::remoting::generated::dynamicDeserializerMethods;
using deephaven::openAPI::lowlevel::remoting::generated::ServerRequestHash;
using deephaven::openAPI::lowlevel::remoting::generated::ServerSharedHash;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleAddress;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::CreateAuthToken;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::StartWorker;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::Login;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryAdded;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryModified;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryRemoved;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::ConsoleDeath;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::Ids6976;
using deephaven::openAPI::utility::Executor;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace {
// For its internal purposes, the server needs to listen for QueryConfig notifications. So, it
// becomes the first client of the ServerNotificationHandler.
class MyQueryConfigListener final : public DHServerAPIListenerDefault {
public:
  void onQueryConfigAdded(const std::shared_ptr<QueryConfig> &cfg) final;
  void onQueryConfigModified(const std::shared_ptr<QueryConfig> &cfg) final;
  void onQueryConfigRemoved(const std::shared_ptr<QueryConfig> &cfg) final;
};
}  // namespace

std::shared_ptr<DHServer> DHServer::createFromTarget(const std::string &target,
    std::shared_ptr<Executor> executor) {
  auto server = Server::createFromTarget(target);
  auto self = std::make_shared<DHServer>(Private(), std::move(server), std::move(executor));
  return self;
}

std::shared_ptr<DHServer> DHServer::createFromHostAndPort(boost::string_view host, int port,
    std::shared_ptr<Executor> executor) {
  auto url = stringf("wss://%o:%o/socket", host, port);
  return createFromUrl(url, std::move(executor));
}

std::shared_ptr<DHServer> DHServer::createFromUrl(boost::string_view url,
    std::shared_ptr<Executor> executor) {
  auto urlToUse = stringf("%o?checksum=%o%o", url,
      ServerRequestHash::hash, ServerSharedHash::hash);

  auto myListener = std::make_shared<MyQueryConfigListener>();

  static_assert(dynamicDeserializerNames.size() == dynamicDeserializerMethods.size(),
      "programming error");
  return std::make_shared<DHServer>(Private(), nullptr, nullptr,
      std::move(executor));
}

DHServer::DHServer(Private, std::shared_ptr<Server> server,
    std::shared_ptr<internal::ServerNotificationHandler> notificationHandler,
    std::shared_ptr<Executor> executor) : server_(std::move(server)),
    notificationHandler_(std::move(notificationHandler)),
    executor_(std::move(executor)) {
}

DHServer::DHServer(Private, std::shared_ptr<Server> server, std::shared_ptr<Executor> executor) :
    server_(std::move(server)), executor_(std::move(executor)) {
}

DHServer::~DHServer() = default;

void DHServer::loginAsync(std::shared_ptr<std::string> user, std::shared_ptr<std::string> password,
    std::shared_ptr<std::string> operateAs,
    std::shared_ptr<SFCallback<std::shared_ptr<RefreshToken>>> callback) {
  auto req = Login::create(std::move(user), std::move(password), std::move(operateAs));
  return invoke(std::move(req), std::move(callback));
}

void DHServer::newSessionAsync(std::shared_ptr<SFCallback<HandshakeResponse>> callback) {
  HandshakeRequest req;
  req.set_auth_protocol(1);
  server_->sendRpc(req, std::move(callback), server_->sessionStub(),
      &SessionService::Stub::AsyncNewSession, false);
}

void DHServer::startConsoleAsync(std::shared_ptr<SFCallback<StartConsoleResponse>> callback) {
  auto ticket = server_->newTicket();
  StartConsoleRequest req;
  *req.mutable_result_id() = std::move(ticket);
  req.set_session_type("groovy");
  server_->sendRpc(req, std::move(callback), server_->consoleStub(),
      &ConsoleService::Stub::AsyncStartConsole, true);
}

void DHServer::createAuthTokenAsync(std::shared_ptr<std::string> service,
    std::shared_ptr<SFCallback<std::shared_ptr<ConnectToken>>> callback) {
  auto req = CreateAuthToken::create(std::move(service));
  invoke(std::move(req), std::move(callback));
}

void DHServer::addListener(std::shared_ptr<DHServerAPIListener> listener) {
  // notificationHandler_->addListener(std::move(listener));
}

void DHServer::removeListener(const std::shared_ptr<DHServerAPIListener> &listener) {
  // notificationHandler_->removeListener(listener);
}

namespace {
void MyQueryConfigListener::onQueryConfigAdded(const std::shared_ptr<QueryConfig> &cfg) {
  // TODO(kosak)
  streamf(std::cerr, "QueryConfigAdded %o\n", *cfg->name());
}

void MyQueryConfigListener::onQueryConfigModified(const std::shared_ptr<QueryConfig> &cfg) {
  // TODO(kosak)
  streamf(std::cerr, "QueryConfigModified %o\n", *cfg->name());
}

void MyQueryConfigListener::onQueryConfigRemoved(const std::shared_ptr<QueryConfig> &cfg) {
  // TODO(kosak)
  streamf(std::cerr, "QueryConfigRemoved %o\n", *cfg->name());
}

}  // namespace
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
