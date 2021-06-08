/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/filter_example.h"

#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {

void FilterExample::run(const QueryScope &scope) {
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getNumCol("Close");

  auto t1 = table.where(
      "ImportDate == `2017-11-01` && Ticker == `AAPL` && (Close <= 120.0 || isNull(Close))");
  PrintUtils::printTableData(std::cout, t1);

  auto t2 = table.where(importDate == "2017-11-01" && ticker == "AAPL" &&
      (close <= 120.0 || close.isNull()));
  PrintUtils::printTableData(std::cout, t2);

  // TODO(kosak)
  // PrintUtils.PrintTableData(table.Where("2017-11-01" == importDate && Condition.Search("AAPL")));
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
