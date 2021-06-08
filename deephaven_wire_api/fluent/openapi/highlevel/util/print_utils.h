#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <boost/utility/string_view.hpp>
#include "highlevel/columns.h"
#include "highlevel/openapi.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace util {
class PrintUtils {
  typedef deephaven::openAPI::highlevel::fluent::Column Column;
  typedef deephaven::openAPI::highlevel::data::ColumnData ColumnData;

public:
  static void printTableData(std::ostream &s, const QueryTable &table);
  static void printTableData(std::ostream &s, const QueryTable &table, std::initializer_list<Column> columns);
  static void printTableData(std::ostream &s, const QueryTable &table, const std::vector<Column> &columns);
  static void printTableData(std::ostream &s, const QueryTable &table, const std::vector<std::string> &columns);

  static void printChunk(std::ostream &s, const std::vector<Column> &columns, bool wantHeaders, long rows,
      const std::vector<std::shared_ptr<ColumnData>> &columnData);

  static void streamTableData(const QueryTable &queryTable,
      const std::vector<std::string> &columns, const std::function<void(const TableData &)> &callback,
      size_t numSimultaneousRequests);

  static void showTableUpdate(const QueryTable &table, const XXXTableUpdate &tableUpdate);
};
}  // namespace util
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
