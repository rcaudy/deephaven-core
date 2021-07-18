/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/snapshot_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::data::ColumnDataHolder;
using deephaven::openAPI::highlevel::data::DoubleColumnData;
using deephaven::openAPI::highlevel::data::IntColumnData;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::utility::appendSeparatedList;
using deephaven::openAPI::utility::makeSeparatedList;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace examples {
void SnapshotExample::run(const QueryScope &scope) {
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  table = table.where(importDate == "2017-11-01");

  auto aaplQuery = table.where(ticker == "AAPL");

  // sample once (no time table)
  auto fz = aaplQuery.freeze();
  PrintUtils::printChunk(std::cout, fz.getColumns(), true, 3, fz.getTableData().columnData());

  // create a time table query
  auto timeTable = scope.timeTable(std::chrono::system_clock::now(), std::chrono::seconds(1));
  PrintUtils::printTableData(std::cout,timeTable);

  // sample the appl query using the time table
  auto samplingTable = timeTable.snapshot(aaplQuery).preemptive(100);

  auto callback = QueryTable::updateCallback_t::createFromCallable(&PrintUtils::showTableUpdate);

  // samplingTable.addTableUpdateHandler(callback);
  samplingTable.subscribeAll();

  std::string line;
  std::cout << "Hit enter to unregister callback...";
  std::getline(std::cin, line);

  // samplingTable.removeTableUpdateHandler(callback);

  std::cout << "Hit enter to unsubscribe...";
  std::getline(std::cin, line);
  samplingTable.unsubscribe();

  std::cout << "Hit enter to quit...";
  std::getline(std::cin, line);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven

