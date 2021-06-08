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
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);

  auto importDate = table.getStrCol("ImportDate");

  table = table.where(importDate == "2017-11-01");

  std::cout << "==== Head(100) ====\n";
  PrintUtils::printTableData(std::cout, table.head(100));

  std::cout << "==== Tail(100) ====\n";
  PrintUtils::printTableData(std::cout, table.tail(100));
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
