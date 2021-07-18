#include "highlevel/impl/query_scope_impl.h"

#include "highlevel/impl/query_table_impl.h"
#include "lowlevel/generated/shared_objects.h"
#include "utility/utility.h"

using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle;
using deephaven::openAPI::utility::stringVecToShared;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
std::shared_ptr<QueryScopeImpl> QueryScopeImpl::create(std::shared_ptr<WorkerSessionImpl> session,
    std::shared_ptr<DHWorkerSession> lowLevelSession, std::shared_ptr<Executor> executor) {
  auto result = std::make_shared<QueryScopeImpl>(Private(), std::move(session),
      std::move(lowLevelSession), std::move(executor));
  result->self_ = result;
  return result;
}

QueryScopeImpl::QueryScopeImpl(Private, std::shared_ptr<WorkerSessionImpl> session,
    std::shared_ptr<DHWorkerSession> lowLevelSession, std::shared_ptr<Executor> executor) :
    session_(std::move(session)), lowlevelSession_(std::move(lowLevelSession)),
    executor_(std::move(executor)) {}
QueryScopeImpl::~QueryScopeImpl() = default;

std::shared_ptr<QueryTableImpl> QueryScopeImpl::emptyTable(int64_t size,
    std::vector<std::string> columnNames, std::vector<std::string> columnTypes) {
  auto cb = QueryTableImpl::createEtcCallback(this);
  auto resultTicket = lowlevelSession_->emptyTableAsync(size, std::move(columnNames),
      std::move(columnTypes), cb);
  return QueryTableImpl::createOss(self_.lock(), std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryScopeImpl::fetchTable(std::string tableName) {
  auto cb = QueryTableImpl::createEtcCallback(this);
  auto resultTicket = lowlevelSession_->fetchTableAsync(std::move(tableName), cb);
  return QueryTableImpl::createOss(self_.lock(), std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryScopeImpl::historicalTable(std::string nameSpace,
    std::string tableName) {
  throw std::runtime_error("TODO(kosak): Historical table?");
//  auto itdCallback = QueryTableImpl::createItdCallback(lowlevelSession_->executor());
//  auto spNamespace = std::make_shared<std::string>(std::move(nameSpace));
//  auto spTableName = std::make_shared<std::string>(std::move(tableName));
//  auto resultHandle = lowlevelSession_->historicalTableAsync(std::move(spNamespace),
//      std::move(spTableName), itdCallback);
//  return QueryTableImpl::create(self_.lock(), std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryScopeImpl::tempTable(
    const std::vector<ColumnDataHolder> &columnDataHolders) {
  auto columnHolders = std::make_shared<std::vector<std::shared_ptr<ColumnHolder>>>();
  columnHolders->reserve(columnDataHolders.size());
  for (const auto &cdh : columnDataHolders) {
    auto spName = std::make_shared<std::string>(cdh.name());
    auto spType = std::make_shared<std::string>(cdh.columnData()->internal().getColumnType());
    auto ch = ColumnHolder::create(std::move(spName), std::move(spType),
        cdh.columnData()->internal().getLowLevelColumnData(), cdh.grouped());
    columnHolders->push_back(std::move(ch));
  }
  throw std::runtime_error("SAD100");
//  auto itdCallback = QueryTableImpl::createItdCallback(lowlevelSession_->executor());
//  auto resultHandle = lowlevelSession_->tempTableAsync(std::move(columnHolders), itdCallback);
//  return QueryTableImpl::create(self_.lock(), std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<QueryTableImpl> QueryScopeImpl::timeTable(int64_t startTimeNanos,
    int64_t periodNanos) {
  auto cb = QueryTableImpl::createEtcCallback(this);
  auto resultTicket = lowlevelSession_->timeTableAsync(startTimeNanos, periodNanos, cb);
  return QueryTableImpl::createOss(self_.lock(), std::move(resultTicket), std::move(cb));
}

std::shared_ptr<QueryTableImpl> QueryScopeImpl::catalogTable() {
  throw std::runtime_error("SAD101");
//  auto itdCallback = QueryTableImpl::createItdCallback(lowlevelSession_->executor());
//  auto resultHandle = lowlevelSession_->catalogTableAsync(itdCallback);
//  return QueryTableImpl::create(self_.lock(), std::move(resultHandle), std::move(itdCallback));
}

std::shared_ptr<DatabaseCatalogTableImpl> DatabaseCatalogTableImpl::create(
    std::shared_ptr<catalogTable_t> catalog) {
  return std::make_shared<DatabaseCatalogTableImpl>(Private(), std::move(catalog));
}

DatabaseCatalogTableImpl::DatabaseCatalogTableImpl(Private,
    std::shared_ptr<catalogTable_t> catalog) : catalog_(std::move(catalog)) {}
DatabaseCatalogTableImpl::~DatabaseCatalogTableImpl() = default;
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
