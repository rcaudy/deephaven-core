/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include <iostream>
#include <arrow/flight/client.h>
#include <arrow/flight/client_auth.h>
#include "examples/select_example.h"

#include "highlevel/data/column_data.h"
#include "highlevel/data/column_data_holder.h"
#include "highlevel/util/demo_constants.h"
#include "highlevel/util/print_utils.h"
#include "utility/utility.h"

#include <iostream>
#include <arrow/flight/client.h>
#include <arrow/flight/types.h>
#include <arrow/array.h>
#include <arrow/array/array_primitive.h>
#include <arrow/type.h>
#include <arrow/table.h>

using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::QueryTable;
using deephaven::openAPI::highlevel::data::ColumnDataHolder;
using deephaven::openAPI::highlevel::data::DoubleColumnData;
using deephaven::openAPI::highlevel::data::IntColumnData;
using deephaven::openAPI::highlevel::util::DemoConstants;
using deephaven::openAPI::highlevel::util::PrintUtils;
using deephaven::openAPI::utility::streamf;

namespace deephaven {
namespace openAPI {
namespace examples {

namespace {
void test0(const QueryScope &scope);
void test1(const QueryTable &table);
void test2(const QueryTable &table);
void test2a_err(const QueryTable &table);
void test3(const QueryTable &table);
void test4(const QueryTable &table);
void test5(const QueryTable &table);
}  // namespace

void SelectExample::run(const QueryScope &scope) {
  // auto table = scope.fetchTable("demo");
  auto table = scope.emptyTable(10, {"x"}, {"int"});

  // test0(scope);
  test1(table);

//  test2(table);
//  test2a_err(table);
//
//  test3(table);
//  test4(table);
//  test5(table);
  (void)&test0;
  (void)&test2;
  (void)&test2a_err;
  (void)&test3;
  (void)&test4;
  (void)&test5;
}

namespace {
void test0(const QueryScope &scope) {
  std::vector<int> intData = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> doubleData = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  std::vector<ColumnDataHolder> columnDataHolders;
  columnDataHolders.emplace_back("IntValue", false, IntColumnData::create(std::move(intData)));
  columnDataHolders.emplace_back("DoubleValue", false, DoubleColumnData::create(std::move(doubleData)));
  auto t = scope.tempTable(columnDataHolders);
  auto t2 = t.update("Q2 = IntValue * 100");
  PrintUtils::printTableData(std::cout, t2);
  auto t3 = t2.update("Q3 = Q2 + 10");
  PrintUtils::printTableData(std::cout,t3);
  auto q2 = t3.getNumCol("Q2");
  auto t4 = t3.update((q2 + 100).as("Q4"));
  PrintUtils::printTableData(std::cout,t4);
}

namespace {
struct MyAuthHandler : public arrow::flight::ClientAuthHandler {
  arrow::Status Authenticate(arrow::flight::ClientAuthSender *outgoing,
      arrow::flight::ClientAuthReader *incoming) override {
    std::cerr << "I choose to do nothing\n";
    return arrow::Status::OK();
  }

  arrow::Status GetToken(std::string *token) override {
    std::cerr << "I also choose to do nothing\n";
    return arrow::Status::OK();
  }
};
}

int stupido(std::pair<std::string, std::string> pain);

// Simple Where
void test1(const QueryTable &tableQ) {
  auto t2 = tableQ.update("QQQ = i");
  // Symbolically
//  auto importDate = table.getStrCol("ImportDate");
//  auto ticker = table.getStrCol("Ticker");
//  auto volume = table.getNumCol("Volume");
  // if we allowed C++17 we could do something like
  // auto [importDate, ticker, volume] = table.getCol<StrCol, StrCol, NumCol>("ImportDate", "Ticker", "Volume");

//  auto t2 = table.where(importDate == "2017-11-01" && ticker == "IBM")
//      .select(ticker, volume);
//  PrintUtils::printTableData(std::cout, t2);
//  std::cerr << "test1 done\n";

  std::unique_ptr<arrow::flight::FlightClient> fc;
  arrow::flight::Location location;
  // auto z1 = arrow::flight::Location::Parse("grpc://localhost:10000", &location).ok();
  auto z1 = arrow::flight::Location::ForGrpcTcp("localhost", 10000, &location).ok();
  auto z2 = arrow::flight::FlightClient::Connect(location, &fc).ok();
  arrow::flight::FlightCallOptions options;
  auto crazy = t2.getHackStuff();
  streamf(std::cerr, "crazy is %o %o\n", crazy.first, crazy.second);
  options.headers.push_back(std::move(crazy));
//  auto myAuthHandler = std::unique_ptr<MyAuthHandler>(new MyAuthHandler());
//  auto z3 = fc->Authenticate(options, std::move(myAuthHandler)).ok();
  const auto &ticket = t2.hackGetTicket();
  std::unique_ptr<arrow::flight::FlightStreamReader> fsr;
  arrow::flight::Ticket tkt;
  // super sad
  std::cerr << "ticket is " << ticket.ticket() << "\n";
  tkt.ticket = ticket.ticket();

  auto crazy2 = t2.getHackStuff();
  stupido(std::move(crazy2));

  auto z4 = fc->DoGet(options, tkt, &fsr).ok();
  streamf(std::cout, "z4 is %o\n", z4);

  auto feelingLucky = fsr->GetSchema().ValueOrDie()->ToString();
  streamf(std::cout, "feeling lucky is %o\n", feelingLucky);

  (void)z1;
  (void)z2;
  (void)z4;
}

int stupido(std::pair<std::string, std::string> pain) {
  std::cout << "Hello, World!" << std::endl;

  std::unique_ptr<arrow::flight::FlightClient> fc;
  arrow::flight::Location location;
  auto z1 = arrow::flight::Location::Parse("grpc://localhost:10000", &location).ok();
  std::cout << "z1 is " << z1 << std::endl;
  // auto z1 = arrow::flight::Location::ForGrpcTcp("localhost", 10000, &location).ok();
  auto z2 = arrow::flight::FlightClient::Connect(location, &fc).ok();
  std::cout << "z2 is " << z2 << std::endl;
  arrow::flight::FlightCallOptions options;
  // std::pair<std::string, std::string> crazy("deephaven_session_id", "4040572c-69bf-4f9f-8fab-bb2683ee92d2");
  options.headers.push_back(std::move(pain));
  std::unique_ptr<arrow::flight::FlightStreamReader> fsr;
  arrow::flight::Ticket tkt;
  // super sad
  tkt.ticket = "*****";
  tkt.ticket[0] = 'e';
  tkt.ticket[1] = 3;
  tkt.ticket[2] = 0;
  tkt.ticket[3] = 0;
  tkt.ticket[4] = 0;
  auto stat4 = fc->DoGet(options, tkt, &fsr);
  std::cout << "z4 is " << stat4.ok() << std::endl;

  auto schemaRes = fsr->GetSchema();
  auto ok = schemaRes.ok();
  auto schema = schemaRes.ValueOrDie();
  (void)ok;

  std::cout << schema->ToString(true) << std::endl;
  auto temp = schema->field_names();

  std::shared_ptr<arrow::Table> table;
  auto qqq = fsr->ReadAll(&table).ok();
  (void)qqq;

  auto nc = table->num_columns();
  auto nr = table->num_rows();
  (void)nc;
  (void)nr;

  auto col0 = table->column(0);
  const auto &dt = col0->type();
  const auto &dts = dt->ToString();
  std::cout << "numchunks " << col0->num_chunks() << std::endl;
  std::cout << "length " << col0->length() << std::endl;
  auto arr = col0->chunk(0);
  std::cout << "a length" << arr->length() << std::endl;

  auto dc = std::dynamic_pointer_cast<arrow::Int32Array>(arr);
  bool valid = dc != nullptr;
  (void)valid;
  auto jerk = dc->ToString();
  streamf(std::cout, "Welcome to jerky town: %o\n", jerk);

  return 0;
}

// Select a few columns
void test2(const QueryTable &table) {
  auto t1 = table.where("ImportDate == `2017-11-01` && Ticker == `AAPL`")
      .select("Ticker", "Close", "Volume")
      .head(2);
  PrintUtils::printTableData(std::cout,t1);

  // Symbolically
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getNumCol("Close");
  auto volume = table.getNumCol("Volume");
  auto t2 = table.where(importDate == "2017-11-01" && ticker == "AAPL")
      .select(ticker, close, volume)
      .head(2);
  PrintUtils::printTableData(std::cout, t2);
  std::cerr << "test2 done\n";
}

// Simple Where with syntax error
void test2a_err(const QueryTable &table) {
  try {
    // String literal
    auto t1 = table.where(")))))");
    PrintUtils::printTableData(std::cout, t1);
  } catch (const std::exception &e) {
    // Expected
    streamf(std::cerr, "Caught *expected* exception %o\n", e.what());
    std::cerr << "test3 done\n";
    return;
  }
  throw std::runtime_error("Expected a failure, but didn't experience one");
}

// LastBy + Select
void test3(const QueryTable &table) {
  auto t1 = table.where("ImportDate == `2017-11-01` && Ticker == `AAPL`").lastBy("Ticker")
      .select("Ticker", "Close", "Volume");
  PrintUtils::printTableData(std::cout, t1);

  // Symbolically
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getNumCol("Close");
  auto volume = table.getNumCol("Volume");
  auto t2 = table.where(importDate == "2017-11-01" && ticker == "AAPL").lastBy(ticker)
      .select(ticker, close, volume);
  PrintUtils::printTableData(std::cout, t2);
}

// Formula in the where clause
void test4(const QueryTable &table) {
  auto t1 = table.where("ImportDate == `2017-11-01` && Ticker == `AAPL` && Volume % 10 == Volume % 100")
      .select("Ticker", "Volume");
  PrintUtils::printTableData(std::cout, t1);

  // Symbolically
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto volume = table.getNumCol("Volume");
  auto t2 = table.where(importDate == "2017-11-01" && ticker == "AAPL" && volume % 10 == volume % 100)
      .select(ticker, volume);
  PrintUtils::printTableData(std::cout, t2);
}

// New columns
void test5(const QueryTable &table) {
  auto t1 = table.where("ImportDate == `2017-11-01` && Ticker == `AAPL`").select("Volume");
  PrintUtils::printTableData(std::cout, t1);

  // A formula expression
  auto t2 = table.where("ImportDate == `2017-11-01` && Ticker == `AAPL`")
      .select("MV1 = Volume * Close", "MV12 = Volume + 12");
  PrintUtils::printTableData(std::cout, t2);

  // Symbolically
  auto importDate = table.getStrCol("ImportDate");
  auto ticker = table.getStrCol("Ticker");
  auto close = table.getNumCol("Close");
  auto volume = table.getNumCol("Volume");
  auto t3 = table.where(importDate == "2017-11-01" && ticker == "AAPL")
      .select(volume);
  PrintUtils::printTableData(std::cout, t3);

  // A formula in the where clause
  auto t4 = table.where(importDate == "2017-11-01" && ticker == "AAPL" && close == volume + 12)
      .select(volume);
  PrintUtils::printTableData(std::cout, t4);

  // Epression.As("New Column Name")
  auto t5 = table.where(importDate == "2017-11-01" && ticker == "AAPL")
      .select((volume * close).as("MV1"), (volume + 12).as("MV_plus_12"));
  PrintUtils::printTableData(std::cout, t5);
}
}  // namespace

}  // namespace examples
}  // namespace openAPI
}  // namespace deephaven
