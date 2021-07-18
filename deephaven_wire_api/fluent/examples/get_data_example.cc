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
namespace {
class NubbyCallback final : public Callback<const QueryTable&, const XXXTableData&> {
public:
  ~NubbyCallback() final = default;
  void invoke(const QueryTable &qt, const XXXTableData &td) final;
};
}  // namespace

void GetDataExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  table.observe();

  auto cb = std::make_shared<NubbyCallback>();
  table.getData(std::move(cb));
  std::cerr << "wait here a bit\n";
  std::this_thread::sleep_for(std::chrono::seconds(25));
}

namespace {
void NubbyCallback::invoke(const QueryTable &qt, const XXXTableData &td) {
  std::cerr << "hi it is party time\n";
}
}  // namespace

}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
