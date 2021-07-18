#pragma once

#include <exception>
#include <memory>
#include <utility/callbacks.h>

namespace deephaven {
namespace openAPI {
namespace utility {
namespace internal {
template<typename T>
class PromiseState {
public:
  bool valid();
  const T &value();
  void setError(std::exception_ptr ep);
};
}
template<typename T>
class CBPromise {
public:
  void setError(std::exception_ptr ep) {
    state_->setError(std::move(ep));
  }

private:
  std::shared_ptr<internal::PromiseState<T>> state_;
};

template<typename T>
class CBFuture {
public:
  bool valid() { return state_->valid(); }
  const T &value() { return state_->value(); }

  // Returns true if cb is the first-ever callback waiting for a result from this future.
  // (Can be used to trigger deferred work that eventually sets the promise).
  bool invoke(std::shared_ptr<SFCallback<const T&>> cb);

private:
  std::shared_ptr<internal::PromiseState<T>> state_;
};
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
