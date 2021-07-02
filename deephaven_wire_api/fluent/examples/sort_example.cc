/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/sort_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::fluent::SortPair;
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
void SortExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");

  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto volume = table.getNumCol("Volume");

  // Limit by date and ticker
  auto table2 = table.where(importDate == "2017-11-01");
  auto table3 = table.where(ticker >= "X");
  PrintUtils::printTableData(std::cout, table3);

  auto table4 = table3.sort({SortPair::descending("Ticker"), SortPair::ascending("Volume")});
  PrintUtils::printTableData(std::cout, table4);

  auto table5 = table3.sort({SortPair::descending(ticker), SortPair::ascending(volume)});
  PrintUtils::printTableData(std::cout, table5);

  // with the sort direction convenience methods on the C# column var
  auto table6 = table3.sort({ticker.descending(), volume.ascending()});
  PrintUtils::printTableData(std::cout, table6);

  std::vector<int32_t> intData0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16};
  std::vector<int32_t> intData1{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7};
  std::vector<int32_t> intData2{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
  std::vector<int32_t> intData3{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1};

  std::vector<ColumnDataHolder> columnDataHolders;
  columnDataHolders.emplace_back("IntValue0", false, IntColumnData::create(std::move(intData0)));
  columnDataHolders.emplace_back("IntValue1", false, IntColumnData::create(std::move(intData1)));
  columnDataHolders.emplace_back("IntValue2", false, IntColumnData::create(std::move(intData2)));
  columnDataHolders.emplace_back("IntValue3", false, IntColumnData::create(std::move(intData3)));

  auto tempTable = scope.tempTable(columnDataHolders);

  auto iv0 = tempTable.getNumCol("IntValue0");
  auto iv1 = tempTable.getNumCol("IntValue1");
  auto iv2 = tempTable.getNumCol("IntValue2");
  auto iv3 = tempTable.getNumCol("IntValue3");
  auto test = tempTable.sort({iv3.descending(), iv2.ascending()});
  PrintUtils::printTableData(std::cout, test);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
