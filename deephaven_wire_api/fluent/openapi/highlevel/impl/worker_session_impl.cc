#include "highlevel/impl/query_scope_impl.h"
#include "highlevel/impl/worker_session_impl.h"
#include "utility/utility.h"

using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {

std::shared_ptr<WorkerOptionsImpl> WorkerOptionsImpl::create(std::string profile) {
  if (profile != "Default") {
    throw std::runtime_error(stringf(R"(Profile "%o" unrecognized)", profile));
  }
  return std::make_shared<WorkerOptionsImpl>(Private());
}

WorkerOptionsImpl::WorkerOptionsImpl(Private) {
}
WorkerOptionsImpl::~WorkerOptionsImpl() = default;

std::shared_ptr<WorkerSessionImpl> WorkerSessionImpl::create(
    std::shared_ptr<DHWorkerSession> lowlevelSession, std::shared_ptr<Executor> executor) {
  auto result = std::make_shared<WorkerSessionImpl>(Private(), std::move(lowlevelSession),
      std::move(executor));
  result->self_ = result;
  return result;
}

WorkerSessionImpl::WorkerSessionImpl(Private, std::shared_ptr<DHWorkerSession> lowlevelSession,
    std::shared_ptr<Executor> executor) :
    lowlevelSession_(std::move(lowlevelSession)), executor_(std::move(executor)) {}

WorkerSessionImpl::~WorkerSessionImpl() = default;

std::shared_ptr<QueryScopeImpl> WorkerSessionImpl::queryScope() {
  return QueryScopeImpl::create(self_.lock(), lowlevelSession_, executor_);
}
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
