/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/catalog_example.h"

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
void CatalogExample::run(const QueryScope &scope) {
  auto catalog = scope.getDatabaseCatalog(true, true, nullptr, nullptr);
  std::cout << "Catalog of all tables:\n";
  for (const auto &catalogTable : catalog.tables())
  {
    std::cout << catalogTable.nameSpace() << '.' << catalogTable.tableName() << std::endl;
  }

  catalog = scope.getDatabaseCatalog(true, true, "^F.*", ".*");
  std::cout << "Catalog of all tables in namespaces starting with \"F\":\n";
  for (const auto &catalogTable : catalog.tables())
  {
    std::cout << catalogTable.nameSpace() << '.' << catalogTable.tableName() << std::endl;
  }
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
