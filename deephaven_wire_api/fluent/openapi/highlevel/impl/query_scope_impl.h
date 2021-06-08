#pragma once

#include <memory>
#include <boost/utility/string_view.hpp>
#include "highlevel/data/column_data_holder.h"
#include "lowlevel/dhworker_session.h"
#include "lowlevel/generated/shared_objects.h"
#include "utility/executor.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
class WorkerSessionImpl;
class QueryTableImpl;

class QueryScopeImpl {
  struct Private {};
  typedef deephaven::openAPI::highlevel::data::ColumnDataHolder ColumnDataHolder;
  typedef deephaven::openAPI::lowlevel::remoting::DHWorkerSession DHWorkerSession;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest BatchTableRequest;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableResponse BatchTableResponse;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition InitialTableDefinition;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle TableHandle;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Catalog Catalog;
  typedef deephaven::openAPI::utility::Executor Executor;

  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

public:
  static std::shared_ptr<QueryScopeImpl> create(std::shared_ptr<WorkerSessionImpl> session,
      std::shared_ptr<DHWorkerSession> lowLevelSession, std::shared_ptr<Executor> executor);

  QueryScopeImpl(Private, std::shared_ptr<WorkerSessionImpl> session,
      std::shared_ptr<DHWorkerSession> lowLevelSession, std::shared_ptr<Executor> executor);
  ~QueryScopeImpl();

  std::shared_ptr<QueryTableImpl> emptyTable(size_t size, std::vector<std::string> columnNames,
      std::vector<std::string> columnTypes);
  std::shared_ptr<QueryTableImpl> historicalTable(std::string nameSpace, std::string tableName);
  std::shared_ptr<QueryTableImpl> tempTable(const std::vector<ColumnDataHolder> &columnDataHolders);
  std::shared_ptr<QueryTableImpl> timeTable(int64_t startTimeNanos, int64_t periodNanos);
  std::shared_ptr<QueryTableImpl> catalogTable();

  const std::shared_ptr<DHWorkerSession> &lowLevelSession() const {
    return lowlevelSession_;
  }

private:
  std::shared_ptr<WorkerSessionImpl> session_;
  std::shared_ptr<DHWorkerSession> lowlevelSession_;
  std::shared_ptr<Executor> executor_;
  std::weak_ptr<QueryScopeImpl> self_;
};

class DatabaseCatalogTableImpl {
  struct Private {};
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table catalogTable_t;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Catalog Catalog;

public:
  static std::shared_ptr<DatabaseCatalogTableImpl> create(std::shared_ptr<catalogTable_t> catalog);

  DatabaseCatalogTableImpl(Private, std::shared_ptr<catalogTable_t> catalog);
  ~DatabaseCatalogTableImpl();

  const std::shared_ptr<catalogTable_t> &catalog() const { return catalog_; }

private:
  std::shared_ptr<catalogTable_t> catalog_;
};
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
