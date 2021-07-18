#include "utility/cbfuture.h"
#include "utility/utility.h"

namespace deephaven {
namespace openAPI {
namespace utility {
namespace internal {
using deephaven::openAPI::utility::stringf;

bool PromiseStateBase::valid() {
  std::unique_lock<std::mutex> guard(mutex_);
  return validLocked();
}

void PromiseStateBase::checkValidLocked(bool expected) {
  bool actual = validLocked();
  if (expected != actual) {
    auto message = stringf("Expected lock state %o, actual lock state %o", expected, actual);
    throw std::runtime_error(message);
  }
}
}  // namespace internal
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
