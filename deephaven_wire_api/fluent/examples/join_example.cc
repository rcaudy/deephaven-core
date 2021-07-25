/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/join_example.h"

#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {

void JoinExample::run(const QueryScope &scope) {
  auto table = scope.fetchTable("demo");
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto volume = table.getNumCol("Volume");

  table = table.where(importDate == "2017-11-01");
  auto lastClose = table.lastBy(ticker);
  auto adv = table.view(ticker, volume).avgBy(ticker);

  // do a join on a resolved RHS
//  auto joined = lastClose.naturalJoin(adv,
//      { ticker },
//      { volume.as("ADV") });
//  PrintUtils::printTableData(std::cout, joined);
}

}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
