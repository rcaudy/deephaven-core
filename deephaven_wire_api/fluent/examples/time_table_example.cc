/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/time_table_example.h"

#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::PrintUtils;

namespace deephaven {
namespace openAPI {
namespace examples {
void TimeTableExample::run(const QueryScope &scope) {
  auto tt = scope.timeTable(std::chrono::system_clock::now(), std::chrono::seconds(5))
      .updateView("Blah=`jojojo`", "Moo=`kosak`")
      .tail(10)
      .preemptive(100);
  tt.getColumns();
  auto callback = QueryTable::updateCallback_t::createFromCallable(&PrintUtils::showTableUpdate);
  tt.addTableUpdateHandler(callback);

  tt.subscribeAll("Blah");

  PrintUtils::printTableData(std::cout, tt);

  std::string line;
  std::cout << "Hit enter to stop subscribe and quit...";
  std::getline(std::cin, line);

  tt.unsubscribe();
}
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
