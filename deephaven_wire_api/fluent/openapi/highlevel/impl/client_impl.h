/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once

#include <memory>
#include "utility/callbacks.h"
#include "lowlevel/dhserver.h"
#include "utility/executor.h"
#include "utility/utility.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
class WorkerSessionImpl;
class WorkerOptionsImpl;

class ClientImpl {
  struct Private {};
  typedef deephaven::openAPI::lowlevel::remoting::DHServer DHServer;
  typedef deephaven::openAPI::utility::Executor Executor;
  typedef deephaven::openAPI::utility::FailureCallback FailureCallback;
  typedef deephaven::openAPI::utility::Void Void;

  template<typename... Args>
  using SFCallback = deephaven::openAPI::utility::SFCallback<Args...>;

  enum class LoginState { NotLoggedIn, Pending, LoggedIn };

public:
  static std::shared_ptr<ClientImpl> create(std::shared_ptr<DHServer> dhServer,
      std::shared_ptr<Executor> executor, std::shared_ptr<Executor> flightExecutor);

  ClientImpl(Private, std::shared_ptr<DHServer> &&dhServer, std::shared_ptr<Executor> &&executor,
      std::shared_ptr<Executor> &&flightExecutor);
  ~ClientImpl();

  void loginAsync(std::string user, std::string password, std::string operateAs,
      std::shared_ptr<SFCallback<>> callback);

  void startWorkerAsync(const std::shared_ptr<WorkerOptionsImpl> &options,
      std::shared_ptr<SFCallback<std::shared_ptr<WorkerSessionImpl>>> callback);

private:
  bool assertLoggedInState(LoginState expected, FailureCallback *onFailure);

  std::shared_ptr<DHServer> dhServer_;
  std::shared_ptr<Executor> executor_;
  std::shared_ptr<Executor> flightExecutor_;
  std::atomic<LoginState> loginState_;
  std::weak_ptr<ClientImpl> weakSelf_;
};
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
