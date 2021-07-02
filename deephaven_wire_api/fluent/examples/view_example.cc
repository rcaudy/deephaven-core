/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/view_example.h"

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
using deephaven::openAPI::utility::streamf;

namespace deephaven {
namespace openAPI {
namespace examples {
void ViewExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  // literal strings
  auto t1 = table.lastBy("Ticker").view("Ticker", "Close", "Volume");
  PrintUtils::printTableData(std::cout, t1);

  // Symbolically
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getNumCol("Close");
  auto volume = table.getNumCol("Volume");
  auto t2 = table.lastBy(ticker).view(ticker, close, volume);
  PrintUtils::printTableData(std::cout, t2);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
