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
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);

  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");

  auto t2 = table.where(importDate == "2017-11-01");
  std::cout << "Contains AT\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.contains("AT")));
  std::cout << "Starts With BL\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.startsWith("BL")));
  std::cout << "Ends With J\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.endsWith("J")));
  std::cout << "Matches ^I.*M$\n";
  PrintUtils::printTableData(std::cout, t2.where(ticker.matches("^I.*M$")));
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
