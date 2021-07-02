/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/aggregates_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::Aggregate;
using deephaven::openAPI::highlevel::AggregateCombo;
using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::aggAvg;
using deephaven::openAPI::highlevel::aggSum;
using deephaven::openAPI::highlevel::aggMin;
using deephaven::openAPI::highlevel::aggMax;
using deephaven::openAPI::highlevel::aggCount;
using deephaven::openAPI::highlevel::aggCombo;
using deephaven::openAPI::highlevel::fluent::SortPair;
//using deephaven::openAPI::highlevel::data::BigIntegerColumnData;
using deephaven::openAPI::highlevel::data::BooleanColumnData;
using deephaven::openAPI::highlevel::data::ByteColumnData;
using deephaven::openAPI::highlevel::data::ColumnDataHolder;
using deephaven::openAPI::highlevel::data::DBDateTime;
using deephaven::openAPI::highlevel::data::DBDateTimeColumnData;
//using deephaven::openAPI::highlevel::data::DecimalColumnData;
using deephaven::openAPI::highlevel::data::DeephavenConstants;
using deephaven::openAPI::highlevel::data::DoubleColumnData;
using deephaven::openAPI::highlevel::data::FloatColumnData;
using deephaven::openAPI::highlevel::data::IntColumnData;
using deephaven::openAPI::highlevel::data::LongColumnData;
using deephaven::openAPI::highlevel::data::ShortColumnData;
using deephaven::openAPI::highlevel::data::StringColumnData;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::utility::appendSeparatedList;
using deephaven::openAPI::utility::makeSeparatedList;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace examples {
void AggregatesExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getStrCol("Close");
  table = table.where(importDate == "2017-11-01");

  auto zngaTable = table.where(ticker == "ZNGA");

  PrintUtils::printTableData(std::cout, zngaTable.headBy(5, ticker));
  PrintUtils::printTableData(std::cout, zngaTable.tailBy(5, ticker));

  auto aggTable = zngaTable.view(close)
      .by(AggregateCombo::create({
          Aggregate::avg("AvgClose=Close"),
          Aggregate::sum("SumClose=Close"),
          Aggregate::min("MinClose=Close"),
          Aggregate::max("MaxClose=Close"),
          Aggregate::count("Count")}));
  PrintUtils::printTableData(std::cout, aggTable);

  auto aggTable2 = zngaTable.view(close)
      .by(aggCombo({
          aggAvg(close.as("AvgClose")),
          aggSum(close.as("SumClose")),
          aggMin(close.as("MinClose")),
          aggMax(close.as("MaxClose")),
          aggCount("Count")}));
  PrintUtils::printTableData(std::cout, aggTable2);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
