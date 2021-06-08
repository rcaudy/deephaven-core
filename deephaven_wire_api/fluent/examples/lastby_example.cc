/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/lastby_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::utility::appendSeparatedList;
using deephaven::openAPI::utility::makeSeparatedList;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace examples {

void LastByExample::run(const QueryScope &scope) {
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");

  auto lb = table.where(importDate == "2017-11-01").lastBy(ticker);
  PrintUtils::printTableData(std::cout, lb);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
