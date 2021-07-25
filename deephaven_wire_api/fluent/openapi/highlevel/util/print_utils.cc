#include "highlevel/util/print_utils.h"

#include <iostream>
#include <future>
#include <queue>
#include <arrow/array.h>
#include <arrow/scalar.h>
#include <arrow/flight/client.h>
#include <arrow/flight/types.h>
#include "utility/utility.h"

using namespace std;
using deephaven::openAPI::utility::separatedList;
using deephaven::openAPI::utility::SFCallback;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;
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

  const auto *server = queryTable.scope().lowLevelSession()->server().get();

  arrow::flight::FlightCallOptions options;
  options.headers.push_back(server->makeBlessing());
  std::unique_ptr<arrow::flight::FlightStreamReader> fsr;
  arrow::flight::Ticket tkt;
  tkt.ticket = queryTable.hackGetTicket().ticket();

  auto doGetRes = server->flightClient()->DoGet(options, tkt, &fsr);
  if (!doGetRes.ok()) {
    auto message = stringf("Doget failed with status %o", doGetRes.ToString());
    throw std::runtime_error(message);
  }

  auto schemaHolder = fsr->GetSchema();
  if (!schemaHolder.ok()) {
    auto message = stringf("GetSchema failed with status %o", schemaHolder.status().ToString());
    throw std::runtime_error(message);
  }

  if (wantHeaders) {
    auto cols = queryTable.getColumns();
    auto streamName = [](std::ostream &s, const Column &c) {
      s << c.name();
    };
    s << separatedList(cols.begin(), cols.end(), "\t", streamName) << '\n';
  }

  std::cerr << "READING DATA HERE FOR FUN\n";
  while (true) {
    arrow::flight::FlightStreamChunk chunk;
    auto stat = fsr->Next(&chunk);
    std::cerr << "stat is " << stat << "\n";
    if (!stat.ok()) {
      auto message = stringf("FlightStreamReader::Next() failed, status %o", stat.ToString());
      throw std::runtime_error(message);
    }
    if (chunk.data == nullptr) {
      std::cerr << "THE STREAM ENDS\n";
      break;
    }
    std::cerr << "GOT A CHUNK\n";
    const auto *data = chunk.data.get();
    const auto &columns = chunk.data->columns();
    std::cerr << "THERE MANY ROWS: " << data->num_rows() << "\n";
    for (int64_t rowNum = 0; rowNum < data->num_rows(); ++rowNum) {
      streamf(s, "This is row %o\n", rowNum);
      auto streamArrayCell = [rowNum](std::ostream &s, const std::shared_ptr<arrow::Array> &a) {
        // This is going to be rather inefficient
        auto rsc = a->GetScalar(rowNum);
        const auto &vsc = *rsc.ValueOrDie();
        s << vsc.ToString();
      };
      s << separatedList(columns.begin(), columns.end(), "\t", streamArrayCell) << '\n';
    }
  }
//  streamf(s, "********* Not printing data. Instead binding to variable %o\n", var);
//  queryTable.bindToVariable(var);
  // auto columns = queryTable.getColumns();
  // printTableData(s, queryTable, columns);
}

void PrintUtils::showTableUpdate(const QueryTable &table, const XXXTableUpdate &tableUpdate) {
  std::cout << "Delta updates arrived... yay!\n";
}
}  // namespace util
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
