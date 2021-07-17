#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include "callbacks.h"
#include "utility/utility.h"

namespace deephaven {
namespace openAPI {
namespace utility {
class Executor {
  typedef deephaven::openAPI::utility::Void Void;
  struct Private {};

  template<typename T>
  using Callback = deephaven::openAPI::core::Callback<T>;

public:
  static std::shared_ptr<Executor> create();

  explicit Executor(Private);
  ~Executor();

  typedef Callback<Void> callback_t;

  void invoke(std::shared_ptr<callback_t> f);

  template<typename Callable>
  void invokeCallable(Callable &&callable) {
    invoke(callback_t::createFromCallable(std::forward<Callable>(callable)));
  }

private:
  static void threadStart(std::shared_ptr<Executor> self);
  [[noreturn]]
  void runForever();

  std::mutex mutex_;
  std::condition_variable condvar_;
  std::deque<std::shared_ptr<callback_t>> todo_;
};
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
