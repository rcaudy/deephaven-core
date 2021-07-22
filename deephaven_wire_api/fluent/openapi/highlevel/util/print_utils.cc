#include "highlevel/util/print_utils.h"

#include <iostream>
#include <future>
#include <queue>
#include "utility/utility.h"

using namespace std;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::highlevel::data::ColumnData;
using deephaven::openAPI::highlevel::fluent::Column;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace util {
namespace {
std::atomic<size_t> nextTableId(0);
}  // namespace

void PrintUtils::printTableData(std::ostream &s, const QueryTable &queryTable, bool wantHeaders) {
  std::string var = stringf("result%o", nextTableId++);
//  streamf(s, "********* Not printing data. Instead binding to variable %o\n", var);
//  queryTable.bindToVariable(var);
  // auto columns = queryTable.getColumns();
  // printTableData(s, queryTable, columns);
  std::cerr << "DOING NOTHING\n";
}

void PrintUtils::showTableUpdate(const QueryTable &table, const XXXTableUpdate &tableUpdate) {
  std::cout << "Delta updates arrived... yay!\n";
}
}  // namespace util
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
