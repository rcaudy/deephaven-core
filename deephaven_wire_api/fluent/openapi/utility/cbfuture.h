#pragma once

#include <exception>
#include <memory>
#include <utility/callbacks.h>

namespace deephaven {
namespace openAPI {
namespace utility {
template<typename T>
class CBPromise {
public:
  void setError(std::exception_ptr ep);
};

template<typename T>
class CBFuture {
public:
  bool valid();
  const T &value();

  // Returns true if cb is the first-ever callback waiting for a result from this future.
  // (Can be used to trigger deferred work that eventually sets the promise).
  bool invoke(std::shared_ptr<SFCallback<const T&>> cb);
};
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
