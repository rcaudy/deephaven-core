/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/new_table_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
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
namespace {
std::shared_ptr<std::string> makeShared(const char *s) {
  return std::make_shared<std::string>(s);
}
}  // namespace
void NewTableExample::run(const QueryScope &scope) {
  std::vector<boost::optional<bool>> boolData = { {}, false, true, false, false, true };
  std::vector<int8_t> byteData = { DeephavenConstants::NULL_BYTE, 0, 1, -1, DeephavenConstants::MIN_BYTE, DeephavenConstants::MAX_BYTE };
  std::vector<int16_t> shortData = { DeephavenConstants::NULL_SHORT, 0, 1, -1, DeephavenConstants::MIN_SHORT, DeephavenConstants::MAX_SHORT };
  std::vector<int32_t> intData = { DeephavenConstants::NULL_INT, 0, 1, -1, DeephavenConstants::MIN_INT, DeephavenConstants::MAX_INT };
  std::vector<int64_t> longData = { DeephavenConstants::NULL_LONG, 0L, 1L, -1L, DeephavenConstants::MIN_LONG, DeephavenConstants::MAX_LONG };
  std::vector<float> floatData = { DeephavenConstants::NULL_FLOAT, 0.0f, 1.0f, -1.0f, -3.4e+38f, std::numeric_limits<float>::max() };
  std::vector<double> doubleData = { DeephavenConstants::NULL_DOUBLE, 0.0, 1.0, -1.0, -1.79e+308, std::numeric_limits<double>::max() };
// TODO(kosak)
//  std::vector<hmm> decimalData = { null, 0, 1, -1, decimal.MinValue, decimal.MaxValue };
//  std::vector<hmm2> bigIntData = { null, BigInteger.Zero, BigInteger.One, BigInteger.MinusOne, new BigInteger(decimal.MinValue), new BigInteger(decimal.MaxValue) };
  std::vector<std::shared_ptr<std::string>> stringData = { nullptr,
      // TODO(kosak): decide what to do here
      makeShared(""), makeShared("A really long string"), makeShared("Negative One"), makeShared("AAAAAA"), makeShared("ZZZZZZ") };
  // TODO(kosak)
  std::vector<DBDateTime> dateTimeData =
      {
          {},
          DBDateTime(1970, 1, 1),
          DBDateTime(2019, 12, 31, 23, 59, 59, 999),
          DBDateTime(1900, 1, 1, 0, 0, 0),
          DBDateTime(1966, 3, 1, 12, 34, 56, 123),
          DBDateTime(2021, 1, 20, 12, 0, 0)
      };
//  std::vector<DHDate> dateData = { null, new DHDate(1970, 1, 1), new DHDate(2019, 1, 1), new DHDate(1900, 1, 1), DHDate.MinValue, DHDate.MaxValue };
//  std::vector<DHTime> timeData = { null, new DHTime(0, 0, 0, 0), new DHTime(1, 59, 59, 999999999), new DHTime(1, 0, 0, 0), DHTime.MinValue, DHTime.MaxValue };

  std::vector<ColumnDataHolder> columnDataHolders;
  columnDataHolders.emplace_back("BoolValue", false, BooleanColumnData::create(boolData));
  columnDataHolders.emplace_back("ByteValue", false, ByteColumnData::create(std::move(byteData)));
  columnDataHolders.emplace_back("ShortValue", false, ShortColumnData::create(std::move(shortData)));
  columnDataHolders.emplace_back("IntValue", false, IntColumnData::create(std::move(intData)));
  columnDataHolders.emplace_back("LongValue", false, LongColumnData::create(std::move(longData)));
  columnDataHolders.emplace_back("FloatValue", false, FloatColumnData::create(std::move(floatData)));
  columnDataHolders.emplace_back("DoubleValue", false, DoubleColumnData::create(std::move(doubleData)));
//  columnDataHolders.emplace_back("DecimalValue", false, DecimalColumnData::create(std::move(decimalData)));
//  columnDataHolders.emplace_back("BigIntegerValue", false, BigIntegerColumnData::create(std::move(bigIntData)));
  columnDataHolders.emplace_back("StringValue", false, StringColumnData::create(std::move(stringData)));
  columnDataHolders.emplace_back("DateTimeValue", false, DBDateTimeColumnData::create(std::move(dateTimeData)));
//  columnDataHolders.emplace_back("DateValue", false, DateColumnData::create(std::move(dateData)));
//  columnDataHolders.emplace_back("TimeValue", false, TimeColumnData::create(std::move(timeData)));

  auto temp = scope.tempTable(columnDataHolders);
  PrintUtils::printTableData(std::cout, temp);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
