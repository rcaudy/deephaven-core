/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/validation_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::utility::MyOstringStream;
using deephaven::openAPI::utility::separatedList;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace examples {
namespace {
void testWheres(const QueryScope &scope);
void testSelects(const QueryScope &scope);
void testWheresHelper(boost::string_view what, const QueryTable &table,
    const std::vector<std::string> &badWheres,
    const std::vector<std::string> &goodWheres);
void testSelectsHelper(boost::string_view what, const QueryTable &table,
    const std::vector<std::vector<std::string>> &badSelects,
    const std::vector<std::vector<std::string>> &goodSelects);

template<typename T>
std::vector<T> concat(const std::vector<T> &lhs, const std::vector<T> &rhs);
}  // namespace

void ValidationExample::run(const QueryScope &scope) {
  testWheres(scope);
  testSelects(scope);
  // (void)&testSelects;
}

namespace {
void testWheres(const QueryScope &scope) {
  std::vector<std::string> badWheres = {
      "X > 3)", // syntax error
      "S = new String(`hello`)", // new not allowed
      "S = java.util.regex.Pattern.quote(S)", // Pattern.quote not on whitelist
      "X = Math.min(3, 4)" // Math.min not on whitelist
  };
  std::vector<std::string> badWheresWhenDynamic = {
      "X = i", // clients can't use i on dynamic tables
      "X = ii", // clients can't use ii on dynamic tables
  };
  std::vector<std::string> goodWheres = {
      "X = 3",
      "S = `hello`",
      "S.length() = 17", // instance methods of String ok
      "X = min(3, 4)", // "builtin" from GroovyStaticImports
      "X = isNormal(3)", // another builtin from GroovyStaticImports
      "X in 3, 4, 5",
  };

  auto staticTable = scope.emptyTable(10, {}, {})
      .update("X = 12", "S = `hello`");
  // "badWheresWhenDynamic" are ok for static tables
  // testWheresHelper("static table", staticTable, badWheres, concat(goodWheres, badWheresWhenDynamic));

  auto now = std::chrono::system_clock::now();
  auto nowNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
  std::chrono::seconds duration(10);
  auto durationNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

  auto dynamicTable = scope.timeTable(nowNanos, durationNanos)
      .update("X = 12", "S = `hello`")
      .preemptive(100);
  // "badWheresWhenDynamic" are bad for dynamic tables
  testWheresHelper("dynamic table", dynamicTable, concat(badWheres, badWheresWhenDynamic),
      goodWheres);
}

void testWheresHelper(boost::string_view what, const QueryTable &table,
    const std::vector<std::string> &badWheres,
    const std::vector<std::string> &goodWheres) {
  for (const auto &bw : badWheres) {
    try {
      streamf(std::cerr, "hi... trying %o %o\n", what, bw);
      auto t1 = table.where(bw);
      t1.observe();
      // auto t2 = t1.getTableData();
    } catch (const std::exception &e) {
      streamf(std::cerr, "%o: %o: Failed *as expected* with: %o\n", what, bw, e.what());
      continue;
    }

    throw std::runtime_error(stringf("%o: %o: Expected to fail, but succeeded", what, bw));
  }

  for (const auto &gw : goodWheres) {
    table.where(gw).observe();
    streamf(std::cerr, "%o: %o: Succeeded as expected\n", what, gw);
  }
}

void testSelects(const QueryScope &scope) {
  std::vector<std::vector<std::string>> badSelects = {
      { "X = 3)" },
      { "S = `hello`", "T = java.util.regex.Pattern.quote(S)" }, // Pattern.quote not on whitelist
      { "X = Math.min(3, 4)" } // Math.min not on whitelist
  };
  std::vector<std::vector<std::string>> badSelectsWhenDynamic = {
      {"X = i"}, // clients can't use i on dynamic tables
      {"X = ii"} // clients can't use ii on dynamic tables
  };
  std::vector<std::vector<std::string>> goodSelects = {
      {"X = 3"},
      {"S = `hello`", "T = S.length()"}, // instance methods of String ok
      {"X = min(3, 4)"}, // "builtin" from GroovyStaticImports
      {"X = isNormal(3)"}, // another builtin from GroovyStaticImports
  };
  auto staticTable = scope.emptyTable(10, {}, {})
      .update("X = 12", "S = `hello`");
  // "badSelectsWhenDynamic" are ok for static tables
  testSelectsHelper("static table", staticTable, badSelects, concat(goodSelects, badSelectsWhenDynamic));

//  auto now = std::chrono::system_clock::now();
//  auto nowNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
//  std::chrono::seconds duration(10);
//  auto durationNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

  auto now = std::chrono::system_clock::now();
  auto nowNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
  std::chrono::seconds duration(10);
  auto durationNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

  auto dynamicTable = scope.timeTable(nowNanos, durationNanos)
      .update("X = 12", "S = `hello`")
      .preemptive(100);
  // "badSelectsWhenDynamic" are bad for dynamic tables
  testSelectsHelper("dynamic table", dynamicTable, concat(badSelects, badSelectsWhenDynamic), goodSelects);
}

void testSelectsHelper(boost::string_view what, const QueryTable &table,
    const std::vector<std::vector<std::string>> &badSelects,
    const std::vector<std::vector<std::string>> &goodSelects) {
  for (const auto &bs : badSelects) {
    MyOstringStream selection;
    selection << separatedList(bs.begin(), bs.end());
    try {
      table.select(bs).observe();
    }
    catch (const std::exception &e) {
      streamf(std::cerr, "%o: %o: Failed as expected with: %o\n", what,
          separatedList(bs.begin(), bs.end(), " "), selection.str(), e.what());
      continue;
    }
    throw std::runtime_error(stringf("%o: %o: Expected to fail, but succeeded",
        what, selection.str()));
  }

  for (const auto &gs : goodSelects) {
    table.select(gs).observe();
    streamf(std::cerr, "%o: %o: Succeeded as expected\n", what,
        separatedList(gs.begin(), gs.end()));
  }
}

template<typename T>
std::vector<T> concat(const std::vector<T> &lhs, const std::vector<T> &rhs) {
  std::vector<T> result(lhs);
  result.insert(result.end(), rhs.begin(), rhs.end());
  return result;
}
}  // namespace
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
