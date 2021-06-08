/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/merge_tables_example.h"

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
void MergeTablesExample::run(const QueryScope &scope) {
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");

  table = table.where(importDate == "2017-11-01");

  // Run a merge by fetching two tables and them merging them
  auto aaplTable = table.where(ticker == "AAPL").tail(10);
  auto zngaTable = table.where(ticker == "ZNGA").tail(10);

  auto merged = aaplTable.merge({zngaTable});
  PrintUtils::printTableData(std::cout, merged);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
