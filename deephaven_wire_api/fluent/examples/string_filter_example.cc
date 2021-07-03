/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/string_filter_example.h"

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
void StringFilterExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");

  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");

  auto t2 = table.where(importDate == "2017-11-01");
  std::cout << "Contains A\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.contains("A")));
  std::cout << "Starts With BL\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.startsWith("BL")));
  std::cout << "Ends With X\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.endsWith("X")));
  std::cout << "Matches ^I.*M$\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.matches("^I.*M$")));
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
