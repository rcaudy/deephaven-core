/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/ungroup_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {
void UngroupExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");

  table = table.where(importDate == "2017-11-01");

  auto byTable = table.where(ticker == "AAPL").view("Ticker", "Close").by("Ticker");
  PrintUtils::printTableData(std::cout, byTable);

  auto ungrouped = byTable.ungroup("Close");
  PrintUtils::printTableData(std::cout, ungrouped);

  auto ungrouped2 = byTable.ungroup();
  PrintUtils::printTableData(std::cout, ungrouped2);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
