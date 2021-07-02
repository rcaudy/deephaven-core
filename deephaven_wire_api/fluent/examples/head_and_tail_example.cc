/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/head_and_tail_example.h"

#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {
void HeadAndTailExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");

  auto importDate = table.getStrCol("ImportDate");

  table = table.where(importDate == "2017-11-01");

  std::cout << "==== Head(2) ====\n";
  PrintUtils::printTableData(std::cout, table.head(2));

  std::cout << "==== Tail(2) ====\n";
  PrintUtils::printTableData(std::cout, table.tail(2));
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
