#pragma once

#include <future>
#include <memory>
#include <boost/make_unique.hpp>

#include "core/deserializer.h"
#include "core/protocol_base_classes.h"
#include "core/callbacks.h"
#include "utility/executor.h"

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace util {

namespace internal {
template<class T>
class TypedResponseHandler final :
    public deephaven::openAPI::core::SFCallback<deephaven::openAPI::core::remoting::util::Deserializer *> {
protected:
  typedef deephaven::openAPI::core::remoting::util::Deserializer Deserializer;
  typedef deephaven::openAPI::utility::Executor Executor;

  typedef deephaven::openAPI::core::SFCallback<std::shared_ptr<T>> sfCallback_t;

public:
  TypedResponseHandler(std::shared_ptr<sfCallback_t> outer, std::shared_ptr<Executor> executor) :
      outer_(std::move(outer)), executor_(std::move(executor)) {}

  ~TypedResponseHandler() override = default;

  void onSuccess(Deserializer *d) final {
    auto response = T::deserializeObject(d);

    auto outer = outer_;
    auto cb = [outer, response](deephaven::openAPI::utility::Void) mutable {
      outer->onSuccess(std::move(response));
    };
    executor_->invokeCallable(std::move(cb));
  }

  void onFailure(std::exception_ptr ep) final {
    auto outer = outer_;
    auto cb = [outer, ep](deephaven::openAPI::utility::Void) mutable {
      outer->onFailure(std::move(ep));
    };
    executor_->invokeCallable(std::move(cb));
  }

private:
  std::shared_ptr<sfCallback_t> outer_;
  std::shared_ptr<Executor> executor_;
};
}  // namespace internal

template<typename RESPONSE>
std::shared_ptr<internal::TypedResponseHandler<RESPONSE>> createResponseHandler(
    std::shared_ptr<deephaven::openAPI::core::SFCallback<std::shared_ptr<RESPONSE>>> inner,
    std::shared_ptr<deephaven::openAPI::utility::Executor> executor) {
  return std::make_shared<internal::TypedResponseHandler<RESPONSE>>(
      std::move(inner), std::move(executor));
}
}  // namespace util
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
