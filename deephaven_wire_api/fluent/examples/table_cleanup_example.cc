/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/table_cleanup_example.h"

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
using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace examples {
// This example shows explicit QueryTable cleanup using destructors/RAII. Generally you would not
// need to worry about this, but you may want to destroy some tables more eagerly if you find you
// are using too much resources at the server.
void TableCleanupExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  // This example will dispose each table individually. This might be handy
  // but not necessary as you can depend on the context to clean up
  {
    auto t1 = table.where(importDate == "2017-11-01");
    {
      auto t2 = t1.countBy(ticker);
      PrintUtils::printTableData(std::cout, t2);
    }
    std::cerr << "t2 has been cleaned up.\n";
  }
  std::cerr << "t1 has been cleaned up.\n";
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
