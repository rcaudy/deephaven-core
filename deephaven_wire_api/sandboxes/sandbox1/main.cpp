#include <iostream>
#include <arrow/flight/client.h>
#include <arrow/flight/types.h>
#include <arrow/array.h>
#include <arrow/array/array_primitive.h>
#include <arrow/type.h>
#include <arrow/table.h>

int main() {
  std::cout << "Hello, World!" << std::endl;


  std::unique_ptr<arrow::flight::FlightClient> fc;
  arrow::flight::Location location;
  auto z1 = arrow::flight::Location::Parse("grpc://localhost:10000", &location).ok();
  std::cout << "z1 is " << z1 << std::endl;
  // auto z1 = arrow::flight::Location::ForGrpcTcp("localhost", 10000, &location).ok();
  auto z2 = arrow::flight::FlightClient::Connect(location, &fc).ok();
  std::cout << "z2 is " << z2 << std::endl;
  arrow::flight::FlightCallOptions options;
  std::pair<std::string, std::string> crazy("deephaven_session_id", "4040572c-69bf-4f9f-8fab-bb2683ee92d2");
  options.headers.push_back(std::move(crazy));
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

  std::cout << schema->ToString(true) << std::endl;
  auto temp = schema->field_names();

  std::shared_ptr<arrow::Table> table;
  auto qqq = fsr->ReadAll(&table).ok();

  auto nc = table->num_columns();
  auto nr = table->num_rows();

  auto col0 = table->column(0);
  const auto &dt = col0->type();
  const auto &dts = dt->ToString();
  std::cout << "numchunks " << col0->num_chunks() << std::endl;
  std::cout << "length " << col0->length() << std::endl;
  auto arr = col0->chunk(0);
  std::cout << "a length" << arr->length() << std::endl;

  auto dc = std::dynamic_pointer_cast<arrow::Int32Array>(arr);
  bool valid = dc != nullptr;
  auto jerk = dc->ToString();

  return 0;
}
