#pragma once

#include <atomic>
#include <future>
#include <memory>
#include <boost/utility/string_view.hpp>
#include "core/server.h"
#include "openapi/utility/callbacks.h"
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/util/server_callbacks.h"
#include "proto/console.pb.h"
#include "proto/console.grpc.pb.h"
#include "proto/session.pb.h"
#include "proto/session.grpc.pb.h"
#include "proto/table.pb.h"
#include "proto/table.grpc.pb.h"
#include "utility/executor.h"

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
class DHServerAPIListener;

namespace internal {
class ServerNotificationHandler;
}  // namespace internal

class DHServer {
  typedef io::deephaven::proto::backplane::grpc::HandshakeResponse HandshakeResponse;
  typedef io::deephaven::proto::backplane::script::grpc::StartConsoleResponse StartConsoleResponse;

  typedef deephaven::openAPI::core::remoting::Server Server;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleAddress ConsoleAddress;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig ConsoleConfig;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken ConnectToken;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken RefreshToken;
  typedef deephaven::openAPI::utility::Executor Executor;
  struct Private {};

  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

public:
  static std::shared_ptr<DHServer> createFromTarget(const std::string &target,
      std::shared_ptr<Executor> executor);
  static std::shared_ptr<DHServer> createFromHostAndPort(boost::string_view host, int port,
      std::shared_ptr<Executor> executor);
  static std::shared_ptr<DHServer> createFromUrl(boost::string_view url,
      std::shared_ptr<Executor> executor);

  DHServer(Private, std::shared_ptr<Server> server,
      std::shared_ptr<internal::ServerNotificationHandler> handler,
      std::shared_ptr<Executor> executor);
  DHServer(Private, std::shared_ptr<Server> server, std::shared_ptr<Executor> executor);
  DHServer(const DHServer &other) = delete;
  DHServer &operator=(const DHServer &other) = delete;
  ~DHServer();

  void loginAsync(std::shared_ptr<std::string> user, std::shared_ptr<std::string> password,
      std::shared_ptr<std::string> operateAs,
      std::shared_ptr<SFCallback<std::shared_ptr<RefreshToken>>> callback);

  void newSessionAsync(std::shared_ptr<SFCallback<HandshakeResponse>> callback);
  void startConsoleAsync(std::shared_ptr<SFCallback<StartConsoleResponse>> callback);

  void createAuthTokenAsync(std::shared_ptr<std::string> service,
      std::shared_ptr<SFCallback<std::shared_ptr<ConnectToken>>> callback);

  void addListener(std::shared_ptr<DHServerAPIListener> listener);
  void removeListener(const std::shared_ptr<DHServerAPIListener> &listener);

  template<typename REQUEST>
  void invoke(std::shared_ptr<REQUEST> request,
      std::shared_ptr<SFCallback<std::shared_ptr<typename REQUEST::correspondingResponseType_t>>> callback);

  // for debugging
  const std::shared_ptr<Server> &server() const { return server_; }

private:
  std::shared_ptr<Server> server_;
  std::shared_ptr<internal::ServerNotificationHandler> notificationHandler_;
  std::shared_ptr<Executor> executor_;
};

class DHServerAPIListener {
protected:
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig QueryConfig;
public:
  virtual ~DHServerAPIListener() = default;

  virtual void onQueryConfigAdded(const std::shared_ptr<QueryConfig> &cfg) = 0 ;
  virtual void onQueryConfigModified(const std::shared_ptr<QueryConfig> &cfg) = 0;
  virtual void onQueryConfigRemoved(const std::shared_ptr<QueryConfig> &cfg) = 0;
  virtual void onConsoleDeath() = 0;
};

// TODO(kosak): name?
class DHServerAPIListenerDefault : public DHServerAPIListener {
public:
  void onQueryConfigAdded(const std::shared_ptr<QueryConfig> &cfg) override {}
  void onQueryConfigModified(const std::shared_ptr<QueryConfig> &cfg) override {}
  void onQueryConfigRemoved(const std::shared_ptr<QueryConfig> &cfg) override {}
  void onConsoleDeath() override {}
};

template<typename REQUEST>
void DHServer::invoke(std::shared_ptr<REQUEST> request,
    std::shared_ptr<SFCallback<std::shared_ptr<typename REQUEST::correspondingResponseType_t>>> callback) {
using deephaven::openAPI::lowlevel::remoting::util::createResponseHandler;
auto responseHandler = createResponseHandler(std::move(callback), executor_);
throw new std::runtime_error("SAD001"); // TODO(kosak)
// server_->invoke(std::move(request), std::move(responseHandler));
}
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
