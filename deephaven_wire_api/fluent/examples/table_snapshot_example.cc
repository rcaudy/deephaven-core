/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/table_snapshot_example.h"

#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {
// TODO(kosak): What was this example meant to demonstrate?
void TableSnapshotExample::run(const QueryScope &scope) {
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getNumCol("Close");
  auto eodTimestamp = table.getStrCol("EODTimestamp");

  auto t2 = table.where(importDate == "2017-11-01").where(ticker == "AAPL" && close <= 120.0);
  PrintUtils::printTableData(std::cout, t2, {ticker, close});
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
