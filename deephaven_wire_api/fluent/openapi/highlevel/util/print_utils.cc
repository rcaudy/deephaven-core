#include "highlevel/util/print_utils.h"

#include <iostream>
#include <future>
#include <queue>
#include "utility/utility.h"

using namespace std;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::streamSeparatedList;
using deephaven::openAPI::utility::stringf;
using deephaven::openAPI::highlevel::data::ColumnData;
using deephaven::openAPI::highlevel::fluent::Column;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace util {
namespace {
void dumpHeaders(std::ostream &s, const std::vector<string> &columns);
void dumpRows(std::ostream &s, int64_t rows,
    const std::vector<std::shared_ptr<ColumnData>> &columnData);
std::vector<std::string> asStrings(const std::vector<Column> &columns);
std::atomic<size_t> nextTableId(0);
}  // namespace

void PrintUtils::printTableData(std::ostream &s, const QueryTable &queryTable) {
  std::string var = stringf("result%o", nextTableId++);
//  streamf(s, "********* Not printing data. Instead binding to variable %o\n", var);
//  queryTable.bindToVariable(var);
  auto columns = queryTable.getColumns();
  printTableData(s, queryTable, columns);
}

void PrintUtils::printTableData(std::ostream &s, const QueryTable &table,
    std::initializer_list<Column> columns) {
  std::vector<Column> colVec(std::make_move_iterator(columns.begin()),
      std::make_move_iterator(columns.end()));
  printTableData(s, table, colVec);
}

void PrintUtils::printTableData(std::ostream &s, const QueryTable &table,
    const std::vector<Column> &columns) {
  auto colsAsStrings = asStrings(columns);
  printTableData(s, table, colsAsStrings);
}

void PrintUtils::printTableData(std::ostream &s, const QueryTable &queryTable,
    const std::vector<std::string> &columns) {
  dumpHeaders(s, columns);
  auto cb = [&s](const TableData &td) {
    dumpRows(s, td.includedRows().count(), td.columnData());
  };
  streamTableData(queryTable, columns, cb, 3);
}

void PrintUtils::showTableUpdate(const QueryTable &table, const XXXTableUpdate &tableUpdate) {
  std::cout << "Delta updates arrived... yay!\n";
}

void PrintUtils::printChunk(std::ostream &s, const std::vector<Column> &columns,
    bool wantHeaders, long rows, const std::vector<std::shared_ptr<ColumnData>> &columnData) {
  if (wantHeaders) {
    dumpHeaders(s, asStrings(columns));
  }
  dumpRows(s, rows, columnData);
}

void PrintUtils::streamTableData(const QueryTable &queryTable,
    const std::vector<std::string> &columns, const std::function<void(const TableData &)> &callback,
    size_t numSimultaneousRequests) {
//  const int64_t chunkSize = 100000;  // 100K
//  auto empty = queryTable.scope().emptyTable(0, {}, {});
//  auto snapshotted = empty.snapshot(queryTable, true, {});
//  auto size = snapshotted.hackGetSizeFromTableDefinition();
//
//  int64_t current = 0;
//  std::queue<std::future<TableData>> queue;
//  while (true) {
//    // If there are rows left to fetch *and* there is room left in the queue, start another fetch
//    // task
//    if (current < size && queue.size() < numSimultaneousRequests) {
//      auto end = std::min(current + chunkSize, size);
//      auto res = SFCallback<TableData>::createForFuture();
//      snapshotted.getTableDataAsync(current, end - 1, columns, std::move(res.first));
//      queue.push(std::move(res.second));
//      current = end;
//      continue;
//    }
//
//    // Otherwise if queue is empty, then we are done
//    if (queue.empty()) {
//      break;
//    }
//
//    // Otherwise, pop a task off the front of the queue, wait for it, and give the results to the
//    // callback.
//    auto tableData = queue.front().get();
//    queue.pop();
//    callback(tableData);
//  }
}

namespace {
void dumpHeaders(std::ostream &s, const std::vector<std::string> &columns) {
  auto renderHeader = [](std::ostream &s2, const std::string &s) {
    s2 << s;
  };
  streamSeparatedList(s, columns.begin(), columns.end(), "\t", renderHeader);
  s << '\n';
}

void dumpRows(std::ostream &s, int64_t rows, const std::vector<std::shared_ptr<ColumnData>> &columnData) {
  int64_t rowIndex;
  auto renderData = [&rowIndex](std::ostream &s2, const std::shared_ptr<ColumnData> &cd) {
    // TODO(kosak): these empty columns don't really make sense to print
    if (cd == nullptr) {
      return;
    }
    cd->streamTo(s2, rowIndex);
  };
  for (rowIndex = 0; rowIndex < rows; ++rowIndex) {
    streamSeparatedList(s, columnData.begin(), columnData.end(), "\t", renderData);
    s << '\n';
  }
}

std::vector<std::string> asStrings(const std::vector<Column> &columns) {
  std::vector<std::string> result;
  result.reserve(columns.size());
  for (const auto &col : columns) {
    result.push_back(col.name());
  }
  return result;
}
}  // namespace
}  // namespace util
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
