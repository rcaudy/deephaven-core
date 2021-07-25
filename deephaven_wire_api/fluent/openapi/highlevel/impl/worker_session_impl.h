/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once

#include <boost/utility/string_view.hpp>
#include "lowlevel/dhworker_session.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
class QueryScopeImpl;
class WorkerOptionsImpl {
  struct Private {
  };
public:
  static std::shared_ptr<WorkerOptionsImpl> create(std::string profile);
  WorkerOptionsImpl(Private);
  ~WorkerOptionsImpl();
};

class WorkerSessionImpl {
  typedef deephaven::openAPI::lowlevel::DHWorkerSession DHWorkerSession;
  typedef deephaven::openAPI::utility::Executor Executor;
  struct Private {};
public:
  static std::shared_ptr<WorkerSessionImpl> create(std::shared_ptr<DHWorkerSession> lowlevelSession,
      std::shared_ptr<Executor> executor);
  WorkerSessionImpl(Private, std::shared_ptr<DHWorkerSession> lowlevelSession,
      std::shared_ptr<Executor> executor);
  ~WorkerSessionImpl();

  std::shared_ptr<QueryScopeImpl> queryScope();

private:
  std::shared_ptr<DHWorkerSession> lowlevelSession_;
  std::shared_ptr<Executor> executor_;
  std::weak_ptr<WorkerSessionImpl> self_;
};
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
