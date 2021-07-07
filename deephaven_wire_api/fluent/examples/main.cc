/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include <future>
#include <memory>
#include <queue>
#include <regex>
#include <utility>

#include "examples/add_drop_example.h"
#include "examples/aggregates_example.h"
#include "examples/catalog_example.h"
#include "examples/catalog_table_example.h"
#include "examples/date_time_filter_example.h"
#include "examples/drop_columns_example.h"
#include "examples/get_data_example.h"
#include "examples/head_and_tail_example.h"
#include "examples/filter_example.h"
#include "examples/join_example.h"
#include "examples/lastby_example.h"
#include "examples/merge_tables_example.h"
#include "examples/new_table_example.h"
#include "examples/select_example.h"
#include "examples/snapshot_example.h"
#include "examples/sort_example.h"
#include "examples/string_filter_example.h"
#include "examples/table_cleanup_example.h"
#include "examples/table_snapshot_example.h"
#include "examples/time_table_example.h"
#include "examples/ungroup_example.h"
#include "examples/validation_example.h"
#include "examples/view_example.h"
#include "highlevel/openapi.h"
#include "highlevel/columns.h"
#include "highlevel/util/print_utils.h"
#include "lowlevel/dhserver.h"
#include "lowlevel/dhworker.h"
#include "lowlevel/dhworker_session.h"
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/generated/dhserver_requests.h"
#include "lowlevel/generated/dhworker_requests.h"
#include "utility/utility.h"

using deephaven::openAPI::examples::AddDropExample;
using deephaven::openAPI::examples::AggregatesExample;
using deephaven::openAPI::examples::CatalogExample;
using deephaven::openAPI::examples::CatalogTableExample;
using deephaven::openAPI::examples::DateTimeFilterExample;
using deephaven::openAPI::examples::DropColumnsExample;
using deephaven::openAPI::examples::FilterExample;
using deephaven::openAPI::examples::GetDataExample;
using deephaven::openAPI::examples::HeadAndTailExample;
using deephaven::openAPI::examples::JoinExample;
using deephaven::openAPI::examples::LastByExample;
using deephaven::openAPI::examples::MergeTablesExample;
using deephaven::openAPI::examples::NewTableExample;
using deephaven::openAPI::examples::SelectExample;
using deephaven::openAPI::examples::SnapshotExample;
using deephaven::openAPI::examples::SortExample;
using deephaven::openAPI::examples::StringFilterExample;
using deephaven::openAPI::examples::TableCleanupExample;
using deephaven::openAPI::examples::TableSnapshotExample;
using deephaven::openAPI::examples::TimeTableExample;
using deephaven::openAPI::examples::UngroupExample;
using deephaven::openAPI::examples::ValidationExample;
using deephaven::openAPI::examples::ViewExample;
using deephaven::openAPI::highlevel::OpenApi;
using deephaven::openAPI::highlevel::QueryScope;
using deephaven::openAPI::highlevel::WorkerOptions;
using deephaven::openAPI::lowlevel::remoting::DHServer;
using deephaven::openAPI::lowlevel::remoting::DHWorker;
using deephaven::openAPI::lowlevel::remoting::DHWorkerSession;
using deephaven::openAPI::utility::streamf;

namespace {
class Program {
public:
  Program(std::string host, std::string username, std::string password, std::string operateAs);
  Program(const Program &) = delete;
  Program &operator=(const Program &) = delete;
  ~Program();

  void run(boost::string_view exampleName);

private:
  std::string host_;
  std::string username_;
  std::string password_;
  std::string operateAs_;

  typedef void(*fp_t)(const QueryScope &);
  std::map<boost::string_view, fp_t> examples_;
};
}  // namespace

int main(int argc, char **argv) {
  if (argc != 5 && argc != 6) {
    std::cerr << "Program arguments: exampleName server username password [operateAs]";
    exit(1);
  }
  auto argIdx = 1;
  auto exampleName = argv[argIdx++];
  auto host = argv[argIdx++];
  auto username = argv[argIdx++];
  auto password = argv[argIdx++];
  auto operateAs = argIdx < argc ? argv[argIdx++] : username;

  try {
    Program p(host, username, password, operateAs);
    p.run(exampleName);
    std::cerr << "Program exited normally\n";
    return 0;
  } catch (const std::exception &e) {
    streamf(std::cerr, "Caught exception: %o\n", e.what());
    return 1;
  }
}

namespace {
Program::Program(std::string host, std::string username, std::string password,
    std::string operateAs) : host_(std::move(host)), username_(std::move(username)),
    password_(std::move(password)), operateAs_(std::move(operateAs)) {
  examples_ = std::map<boost::string_view, fp_t> {
      { "adddrop", AddDropExample::run },
      { "validate", ValidationExample::run },
      { "lastby", LastByExample::run },
      { "filter", FilterExample::run },
      { "cleanup", TableCleanupExample::run },
      { "sort", SortExample::run },
      { "snapshot", SnapshotExample::run },
      { "select", SelectExample::run },
      { "view", ViewExample::run },
      { "join", JoinExample::run },
      { "ht", HeadAndTailExample::run },
      { "tt", TimeTableExample::run },
      { "tablesnapshot", TableSnapshotExample::run },
      { "nt", NewTableExample::run },
      { "agg", AggregatesExample::run },
      { "ungroup", UngroupExample::run },
      { "merge", MergeTablesExample::run },
      { "drop", DropColumnsExample::run },
      { "catalog", CatalogExample::run },
      { "cattable", CatalogTableExample::run },
      { "strfilter", StringFilterExample::run },
      { "dtfilter", DateTimeFilterExample::run },
      { "getdata", GetDataExample::run },
  };
}

Program::~Program() = default;

void Program::run(boost::string_view exampleName) {
  // Optimistically assume wildcard
  auto beginp = examples_.begin();
  auto endp = examples_.end();
  if (exampleName != "*") {
    // Named example, not wildcard
    beginp = examples_.find(exampleName);
    if (beginp == examples_.end()) {
      streamf(std::cerr, "No example found with the name %o\n", exampleName);
      return;
    }
    endp = std::next(beginp);
  }
  std::cerr << "Connecting to server\n";
  auto client = OpenApi::connectOss(host_);
  client.login(username_, password_, operateAs_);

  std::cerr << "Starting worker...\n";
  auto workerOptions = WorkerOptions::create("Default");
//  workerOptions.addJvmArg("-ea");
//  workerOptions.addJvmArg("-agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=7172");

  auto workerSession = client.startWorker(workerOptions);
  std::cerr << "Worker started.\n";
  for (auto ep = beginp; ep != endp; ++ep) {
    streamf(std::cerr, "Running example %o\n", ep->first);
    try {
      ep->second(workerSession.queryScope());
    } catch (const std::exception &e) {
      streamf(std::cerr, "Example %o failed with the following exception: %o\n", ep->first,
          e.what());
    }
  }
}
}  // namespace


#if 0
public void OnError(IWorkerSession arg1, Exception ex)
  {
    Console.WriteLine("Worker error: " + ex);
  }

public void OnPing(IWorkerSession obj)
  {
    Console.WriteLine("Worker ping");
  }

public void OnLogMessage(IWorkerSession arg1, LogMessage logMessage)
  {
    Console.WriteLine("Worker log message: " + logMessage);
  }

public void OnClosed(IWorkerSession arg1, ushort code, string msg)
  {
    Console.WriteLine($"Worker closed: {msg} ({code})");
  }

public void OnOpen(IWorkerSession obj)
  {
    Console.WriteLine("Worker open");
  }

  void IOpenApiListener.OnPersistentQueryAdded(IOpenApiClient openApiClient, IPersistentQueryConfig persistentQueryConfig)
  {
    Console.WriteLine("PQ added: " + persistentQueryConfig.Name);
  }

  void IOpenApiListener.OnPersistentQueryModified(IOpenApiClient openApiClient, IPersistentQueryConfig persistentQueryConfig)
  {
    Console.WriteLine("PQ modified: " + persistentQueryConfig.Name);
  }

  void IOpenApiListener.OnPersistentQueryRemoved(IOpenApiClient openApiClient, IPersistentQueryConfig persistentQueryConfig)
  {
    Console.WriteLine("PQ removed: " + persistentQueryConfig.Name);
  }

  void IOpenApiListener.OnClosed(IOpenApiClient openApiClient, ushort code, string message)
  {
    Console.WriteLine("Client closed: {0} ({1})", message, code);
  }

  void IOpenApiListener.OnError(IOpenApiClient openApiClient, Exception ex)
  {
    Console.WriteLine("Client error: " + ex);
  }

  void IOpenApiListener.OnOpen(IOpenApiClient openApiClient)
  {
    Console.WriteLine("Client connected");
  }

  void IOpenApiListener.OnAuthTokenRefresh(IOpenApiClient openApiClient, RefreshToken refreshToken)
  {
    Console.WriteLine("Auth token refresh: " + refreshToken);
  }

  void IOpenApiListener.OnAuthTokenError(IOpenApiClient openApiClient, string error)
  {
    Console.WriteLine("Auth token error: " + error);
  }
}
#endif
