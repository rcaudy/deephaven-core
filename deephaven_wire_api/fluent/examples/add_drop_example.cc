/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "examples/add_drop_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::highlevel::fluent::NumericExpression;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::highlevel::QueryScope;

namespace deephaven {
namespace openAPI {
namespace examples {
namespace {
void test0(const QueryScope &scope);
void test1(const QueryScope &scope);
void test2(const QueryScope &scope);
void test3(const QueryScope &scope);
}  // namespace

void AddDropExample::run(const QueryScope &scope) {
  (void)&test0;
  (void)&test1;
  test2(scope);
  (void)&test3;
}

namespace {
void test0(const QueryScope &scope) {
  auto et1 = scope.emptyTable(10, {"x"}, {"qint"});
  streamf(std::cerr, "et1 done\n");
  auto et2 = scope.emptyTable(10, {"x"}, {"int"});
  streamf(std::cerr, "et2 done\n");

  std::cerr << "observing et2 first\n";
  et2.observe();
  std::cerr << "observing et1 next\n";
  et1.observe();
  streamf(std::cerr, "everyone has been observed\n");
}

void test1(const QueryScope &scope) {
  auto et = scope.emptyTable(10, {"x"}, {"int"});
  streamf(std::cerr, "et done\n");

  streamf(std::cerr, "beginning to observe\n");
  et.observe();
  streamf(std::cerr, "done observing et\n");

  auto head5 = et.head(5);
  std::cerr << "observing head5\n";
  head5.observe();
}

void test2(const QueryScope &scope) {
  auto et = scope.emptyTable(10, {"x"}, {"int"});
  et.observe();
  // et.bindToVariable("etvar");
  streamf(std::cerr, "et done\n");

  auto t2 = et.updateView(NumericExpression(3).as("MyVal"));
  auto t3 = t2.updateView("Zamboni = ii");
  t3.bindToVariable("jjj");
}

void test3(const QueryScope &scope) {
}

}  // namespace
}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
