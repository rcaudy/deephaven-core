#pragma once

#include "highlevel/openapi.h"

namespace deephaven {
namespace openAPI {
namespace examples {
class GetDataExample {
  typedef deephaven::openAPI::highlevel::QueryScope QueryScope;
public:
  static void run(const QueryScope &scope);
};
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
