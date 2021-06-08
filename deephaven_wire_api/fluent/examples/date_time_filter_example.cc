/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/date_time_filter_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/columns.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::data::ColumnDataHolder;
using deephaven::openAPI::highlevel::data::DBDateTime;
using deephaven::openAPI::highlevel::data::DBDateTimeColumnData;
using deephaven::openAPI::highlevel::data::StringColumnData;
using deephaven::openAPI::highlevel::fluent::DateTimeCol;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {
namespace {
std::shared_ptr<std::string> makeShared(const char *s) {
  return std::make_shared<std::string>(s);
}
}  // namespace

void DateTimeFilterExample::run(const QueryScope &scope) {
  std::vector<std::shared_ptr<std::string>> labels = {
      makeShared("RowA"),
      makeShared("RowB"),
      makeShared("RowC"),
      makeShared("RowD")
  };
  std::vector<DBDateTime> dateTimeData1 = {
      {},
      DBDateTime(1970, 1, 1),
      DBDateTime(2019, 12, 31, 23, 59, 59, 999999999),
      DBDateTime(1983, 3, 1, 12, 15, 0),
  };
  std::vector<DBDateTime> dateTimeData2 = {
      {},
      DBDateTime(1983, 3, 1, 12, 15, 0),
      DBDateTime(2019, 12, 31, 23, 59, 59, 999999999),
      DBDateTime(1970, 1, 1)
  };

  auto table = scope.tempTable({
      ColumnDataHolder("Label", false, StringColumnData::create(labels)),
      ColumnDataHolder("DateTimeValue1", false, DBDateTimeColumnData::create(dateTimeData1)),
      ColumnDataHolder("DateTimeValue2", false, DBDateTimeColumnData::create(dateTimeData2))
  });
  auto dateTime1 = table.getDateTimeCol("DateTimeValue1");
  auto dateTime2 = table.getDateTimeCol("DateTimeValue2");

  std::cout << "All Rows:\n";
  PrintUtils::printTableData(std::cout, table);

  std::cout << "Rows where dateTime1 < dateTime2:\n";
  PrintUtils::printTableData(std::cout, table.where(dateTime1 < dateTime2));

  // string literal for time in UTC
  std::cout << "Rows where dateTime1 < 2017-08-25T09:30:00.123456789 UTC:\n";
  PrintUtils::printTableData(std::cout, table.where(dateTime1 < "2017-08-25T09:30:00.123456789 UTC"));
  // string literal for variable in UTC
  DBDateTime dateVar(2017, 8, 25, 9, 30, 00, 1234567890);
  std::cout << "Rows where dateTime1 < " << dateVar << ":\n";
  PrintUtils::printTableData(std::cout, table.where(dateTime1 < dateVar));
  // string literal for time in NY
  std::cout << "Rows where dateTime1 < 2017-08-25T09:30:00.123456789 NY:\n";

  PrintUtils::printTableData(std::cout, table.where(dateTime1 < "2017-08-25T09:30:00.123456789 NY"));

  // DBDateTime doesn't carry a time zone, so we don't (yet) have a way to specify a variable that holds
  // a date in a given time zone

  // null
  std::cout << "Rows where isNull(dateTime1):\n";
  PrintUtils::printTableData(std::cout, table.where(dateTime1.isNull()));

  // not null
  std::cout << "Rows where !isNull(dateTime1):\n";
  PrintUtils::printTableData(std::cout, table.where(!dateTime1.isNull()));
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
