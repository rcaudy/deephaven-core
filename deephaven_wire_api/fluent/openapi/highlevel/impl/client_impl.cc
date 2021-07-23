#include "highlevel/impl/client_impl.h"

#include <stdexcept>
#include "utility/utility.h"
#include "utility/callbacks.h"
#include "highlevel/impl/worker_session_impl.h"
#include "lowlevel/dhserver.h"
#include "lowlevel/dhworker.h"
#include "lowlevel/dhworker_session.h"

using io::deephaven::proto::backplane::grpc::HandshakeResponse;
using io::deephaven::proto::backplane::script::grpc::StartConsoleResponse;
using deephaven::openAPI::core::remoting::Server;
using deephaven::openAPI::lowlevel::DHServer;
using deephaven::openAPI::lowlevel::DHWorker;
using deephaven::openAPI::lowlevel::DHWorkerSession;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ConnectionSuccess;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleAddress;
using deephaven::openAPI::utility::Executor;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::utility::streamf;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
namespace {
// const char remoteQueryProcessorName[] = "RemoteQueryProcessor";
}  // namespace

std::shared_ptr<ClientImpl> ClientImpl::create(std::shared_ptr<DHServer> server,
    std::shared_ptr<Executor> executor, std::shared_ptr<Executor> flightExecutor) {
  auto result = std::make_shared<ClientImpl>(Private(), std::move(server), std::move(executor),
      std::move(flightExecutor));
  result->weakSelf_ = result;
  return result;
}

ClientImpl::ClientImpl(Private, std::shared_ptr<DHServer> &&dhServer,
    std::shared_ptr<Executor> &&executor, std::shared_ptr<Executor> &&flightExecutor) :
    dhServer_(std::move(dhServer)), executor_(std::move(executor)),
    flightExecutor_(std::move(flightExecutor)), loginState_(LoginState::NotLoggedIn) {}
ClientImpl::~ClientImpl() = default;

void ClientImpl::loginAsync(std::string user, std::string password, std::string operateAs,
    std::shared_ptr<SFCallback<>> callback) {
  if (!assertLoggedInState(LoginState::NotLoggedIn, callback.get())) {
    return;
  }
  std::cerr << "Warning: ignoring login credentials (for now)\n";
  loginState_ = LoginState::LoggedIn;
  callback->onSuccess();
}

namespace {
class Everything final : public SFCallback<HandshakeResponse>, public SFCallback<StartConsoleResponse> {
  struct Private {};

public:
  static std::shared_ptr<Everything> create(std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> outerCb,
      std::shared_ptr<DHServer> dhServer, std::shared_ptr<Executor> executor,
      std::shared_ptr<Executor> flightExecutor);
  Everything(Private, std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> &&outerCb,
      std::shared_ptr<DHServer> &&dhServer, std::shared_ptr<Executor> &&executor,
      std::shared_ptr<Executor> &&flightExecutor);
  ~Everything() final;
  void onSuccess(HandshakeResponse item) final;
  void onSuccess(StartConsoleResponse item) final;
  void onFailure(std::exception_ptr ep) final;

private:
  std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> outerCb_;
  std::shared_ptr<DHServer> dhServer_;
  std::shared_ptr<Executor> executor_;
  std::shared_ptr<Executor> flightExecutor_;
  std::weak_ptr<Everything> weakSelf_;
};
}  // namespace

void ClientImpl::startWorkerAsync(const std::shared_ptr<WorkerOptionsImpl> &options,
    std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> callback) {
  if (!assertLoggedInState(LoginState::LoggedIn, callback.get())) {
    return;
  }

  auto cb = Everything::create(std::move(callback), dhServer_, executor_, flightExecutor_);
  dhServer_->newSessionAsync(std::move(cb));
}

bool ClientImpl::assertLoggedInState(LoginState expected, FailureCallback *onFailure) {
  if (loginState_ == expected) {
    return true;
  }
  auto message = stringf("Expected logged-in to be state %o, got %o", (int) expected,
      (int) (LoginState) loginState_);
  auto ep = std::make_exception_ptr(std::runtime_error(message));
  onFailure->onFailure(std::move(ep));
  return false;
}

namespace {
std::shared_ptr<Everything> Everything::create(
    std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> outerCb,
    std::shared_ptr<DHServer> dhServer, std::shared_ptr<Executor> executor,
    std::shared_ptr<Executor> flightExecutor) {
  auto result = std::make_shared<Everything>(Private(), std::move(outerCb), std::move(dhServer),
      std::move(executor), std::move(flightExecutor));
  result->weakSelf_ = result;
  return result;
}

Everything::Everything(Private,
    std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> &&outerCb,
    std::shared_ptr<DHServer> &&dhServer,
    std::shared_ptr<Executor> &&executor,
    std::shared_ptr<Executor> &&flightExecutor) :
    outerCb_(std::move(outerCb)), dhServer_(std::move(dhServer)), executor_(std::move(executor)),
    flightExecutor_(std::move(flightExecutor)) {}

Everything::~Everything() = default;

void Everything::onSuccess(HandshakeResponse item) {
  std::string mh = std::move(*item.mutable_metadata_header());
  std::string st = std::move(*item.mutable_session_token());
  std::transform(mh.begin(), mh.end(), mh.begin(), ::tolower);

  dhServer_->server()->setAuthentication(std::move(mh), std::move(st));
  dhServer_->startConsoleAsync(weakSelf_.lock());
}

void Everything::onSuccess(StartConsoleResponse item) {
  streamf(std::cerr, "WE HAVE A CONSOLE\n");
  auto lls = DHWorkerSession::create(std::move(*item.mutable_result_id()),
      dhServer_->server(), executor_, flightExecutor_);
  auto ws = WorkerSessionImpl::create(std::move(lls), std::move(executor_));
  outerCb_->onSuccess(std::move(ws));
}

void Everything::onFailure(std::exception_ptr ep) {
  outerCb_->onFailure(std::move(ep));
}
}  // namespace
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
