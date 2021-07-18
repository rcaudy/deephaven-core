#pragma once

#include <future>
#include <memory>
#include <utility>

namespace deephaven {
namespace openAPI {
namespace utility {
// For simple callbacks.
template<typename... Args>
class Callback {
public:
  template<typename Callable>
  static std::shared_ptr<Callback> createFromCallable(Callable &&callable);

  virtual ~Callback() = default;
  virtual void invoke(Args... args) = 0;
};

// Non-templated base class for SFCallbacks that implements the "failure" side.
class FailureCallback {
public:
  virtual ~FailureCallback() = default;
  virtual void onFailure(std::exception_ptr ep) = 0;
};

namespace internal {
// We do this so that in the special case where there is only one arg, there is an extra static
// method called createForFuture()
template<bool, typename ...Args>
class SFCallbackBase;
} // namespace internal

// Success-or-failure callbacks. The callee is required to eventually invoke either onSuccess or
// onFailure exactly once.
template<typename... Args>
class SFCallback : public internal::SFCallbackBase<sizeof...(Args), Args...> {
public:
  template<typename Callable>
  static std::shared_ptr<SFCallback> createFromCallable(Callable &&callable);

  static std::pair<std::shared_ptr<SFCallback<Args...>>, std::future<std::tuple<Args...>>> createForFutureTuple();

  ~SFCallback() override = default;
  virtual void onSuccess(Args... item) = 0;
};

namespace internal {
template<typename T>
class SFCallbackBase<true, T> : public FailureCallback {
public:
  static std::pair<std::shared_ptr<SFCallback<T>>, std::future<T>> createForFuture();
};

template<typename... Args>
class SFCallbackBase<false, Args...> : public FailureCallback {
};
} // namespace internal


// This helps us make a Callback<T> that can hold some kind of invokeable item (function object or
// lambda or std::function).
namespace internal {
template<typename Callable, typename... Args>
class CallbackCallable final : public Callback<Args...> {
public:
  explicit CallbackCallable(Callable &&callable) : callable_(std::forward<Callable>(callable)) {}

  void invoke(Args... args) final {
    callable_(std::forward<Args>(args)...);
  }

private:
  Callable callable_;
};

// This helper class helps us make a SFCallback<T> that can hold some kind of invokeable item
// (function object or lambda or std::function). It works with the method 'createFromCallable'.
// The invokeable item needs to have an operator() that can take either something compatible with T
// or a std::exception_ptr. So, there can be two overloaded operator() methods, or you can have
// something like boost::variant<T, std::exception_ptr>().
template<typename Callable, typename... Args>
class SFCallbackCallable final : public SFCallback<Args...> {

public:
  explicit SFCallbackCallable(Callable &&callable) : callable_(std::forward<Callable>(callable)) {}

  void onSuccess(Args... item) final {
    callable_(std::forward<Args>(item)...);
  }

  void onFailure(std::exception_ptr ep) final {
    callable_(std::move(ep));
  }

private:
  Callable callable_;
};

// This helps us make a SFCallback<T> that holds a promise. It works with the method 'createForFuture'
template<typename T>
class SFCallbackFutureable final : public SFCallback<T> {
public:
  explicit SFCallbackFutureable(std::promise<T> promise) : promise_(std::move(promise)) {}

  void onSuccess(T item) final {
    promise_.set_value(std::move(item));
  }

  void onFailure(std::exception_ptr ep) final {
    promise_.set_exception(std::move(ep));
  }

private:
  std::promise<T> promise_;
};
}  // namespace internal

template<typename... Args>
template<typename Callable>
std::shared_ptr<Callback<Args...>> Callback<Args...>::createFromCallable(Callable &&callable) {
  return std::make_shared<internal::CallbackCallable<Callable, Args...>>(std::forward<Callable>(callable));
}

template<typename... Args>
template<typename Callable>
std::shared_ptr<SFCallback<Args...>> SFCallback<Args...>::createFromCallable(Callable &&callable) {
  return std::make_shared<internal::SFCallbackCallable<Callable, Args...>>(std::forward<Callable>(callable));
}

// Returns a pair whose first item is a SFCallback<T> which satisfies a promise, and whose second
// item is a std::future<T> which is the future corresponding to that promise.
template<typename... Args>
std::pair<std::shared_ptr<SFCallback<Args...>>, std::future<std::tuple<Args...>>> SFCallback<Args...>::createForFutureTuple() {
  std::promise<std::tuple<Args...>> promise;
  auto fut = promise.get_future();
  auto cb = std::make_shared<internal::SFCallbackFutureable<std::tuple<Args...>>>(std::move(promise));
  return std::make_pair(std::move(cb), std::move(fut));
}
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
