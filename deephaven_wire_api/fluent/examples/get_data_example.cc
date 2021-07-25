/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/get_data_example.h"

#include "openapi/utility/callbacks.h"
#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::XXXTableData;
using deephaven::openAPI::utility::Callback;

namespace deephaven {
namespace openAPI {
namespace examples {
void GetDataExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  table.observe();
  // Nothing to do here
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
