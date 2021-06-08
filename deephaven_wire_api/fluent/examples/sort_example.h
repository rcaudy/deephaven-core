/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once

#include "highlevel/openapi.h"

namespace deephaven {
namespace openAPI {
namespace examples {
class SortExample {
  typedef deephaven::openAPI::highlevel::QueryScope QueryScope;
public:
  static void run(const QueryScope &scope);
};
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
