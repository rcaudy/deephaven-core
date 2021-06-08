/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/drop_columns_example.h"

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
void DropColumnsExample::run(const QueryScope &scope) {
  auto table = scope.historicalTable(DemoConstants::historicalNamespace,
      DemoConstants::historicalTable);
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");

  table = table.where(importDate == "2017-11-01").head(100);

  table = table.dropColumns("Open", "Volume");
  // TODO(kosak): bug: colum names got sorted in printutils header.
  PrintUtils::printTableData(std::cout, table);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
