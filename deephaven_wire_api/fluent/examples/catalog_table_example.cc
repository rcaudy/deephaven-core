/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/catalog_table_example.h"

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
void CatalogTableExample::run(const QueryScope &scope) {
  auto table = scope.catalogTable();
  PrintUtils::printTableData(std::cout, table);
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
