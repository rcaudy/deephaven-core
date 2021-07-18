#pragma once

#include <exception>
#include <memory>
#include <vector>
#include <utility/callbacks.h>
#include <boost/optional.hpp>

namespace deephaven {
namespace openAPI {
namespace utility {
namespace internal {
class PromiseStateBase {
public:
  bool valid();

protected:
  void checkValidLocked(bool expected);
  virtual bool validLocked() = 0;

  std::mutex mutex_;
  std::exception_ptr eptr_;
};

template<typename T>
class PromiseState final : public PromiseStateBase {
public:
  // valid means promise fullfilled with either value or error

  const T &value() {
    std::unique_lock<std::mutex> guard(mutex_);
    checkValidLocked(true);
    return *value_;
  }

  // oops. need to invoke all the waiters
  void setValue(T value) {
    std::unique_lock<std::mutex> guard(mutex_);
    checkValidLocked(false);
    value_ = std::move(value);

    std::vector<std::shared_ptr<SFCallback<const T&>>> cbs;
    cbs.swap(callbacks_);
    guard.unlock();

    for (auto &cb : cbs) {
      cb->onSuccess(*value_);
    }
  }

  // oops. need to invoke all the waiters
  void setError(std::exception_ptr ep) {
    std::unique_lock<std::mutex> guard(mutex_);
    checkValidLocked(false);
    eptr_ = std::move(ep);

    std::vector<std::shared_ptr<SFCallback<const T&>>> cbs;
    cbs.swap(callbacks_);
    guard.unlock();

    for (auto &cb : cbs) {
      cb->onFailure(eptr_);
    }
  }

  // Returns true if cb is the first-ever callback waiting for a result from this future.
  // (Can be used to trigger deferred work that eventually sets the promise).
  bool invoke(std::shared_ptr<SFCallback<const T&>> cb) {
    std::unique_lock<std::mutex> guard(mutex_);
    if (!validLocked()) {
      callbacks_.push_back(std::move(cb));
      return callbacks_.size() == 1;
    }
    guard.unlock();

    if (value_.has_value()) {
      cb->onSuccess(value_.value());
    } else {
      cb->onFailure(eptr_);
    }
    return false;
  }

private:
  bool validLocked() final {
    return value_.has_value() || eptr_ != nullptr;
  }

  boost::optional<T> value_;
  std::vector<std::shared_ptr<SFCallback<const T&>>> callbacks_;
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

  bool invoke(std::shared_ptr<SFCallback<const T&>> cb) {
    return state_->invoke(std::move(cb));
  }

private:
  std::shared_ptr<internal::PromiseState<T>> state_;
};
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
