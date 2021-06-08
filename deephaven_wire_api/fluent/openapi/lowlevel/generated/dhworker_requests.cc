#include "lowlevel/generated/dhworker_requests.h"
#include <array>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/utility/string_view.hpp>
#include "core/protocol_base_classes.h"
#include "core/deserializer.h"
#include "core/serializer.h"
#include "lowlevel/custom/custom_shared_objects.h"
#include "lowlevel/util/deserializer_adapter.h"
#include "lowlevel/util/protocol_container_classes.h"
#include "lowlevel/util/serializer_adapter.h"
#include "utility/utility.h"
#include "lowlevel/generated/shared_objects.h"
namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace generated {
const boost::string_view WorkerRequestHash::hash = "-3ccb6ecf0c0bb63021a4e326ced6aa1f0887dd21";
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace worker {
std::shared_ptr<Register> Register::create(int32_t clientId, std::shared_ptr<std::string> service, double seedTime, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> authToken) {
  return std::make_shared<Register>(Private(), clientId, std::move(service), seedTime, std::move(authToken));
}
Register::Register(Private, int32_t clientId, std::shared_ptr<std::string> service, double seedTime, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> authToken)
  : clientId_(clientId), service_(std::move(service)), seedTime_(seedTime), authToken_(std::move(authToken))
  {
}
Register::~Register() = default;
void Register::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&clientId_);
  sa.write(&service_);
  sa.write(&seedTime_);
  sa.write(&authToken_);
}
std::shared_ptr<GetCatalog> GetCatalog::create(bool systemNamespaces, bool userNamespaces, std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex) {
  return std::make_shared<GetCatalog>(Private(), systemNamespaces, userNamespaces, std::move(namespaceRegex), std::move(tableRegex));
}
GetCatalog::GetCatalog(Private, bool systemNamespaces, bool userNamespaces, std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex)
  : systemNamespaces_(systemNamespaces), userNamespaces_(userNamespaces), namespaceRegex_(std::move(namespaceRegex)), tableRegex_(std::move(tableRegex))
  {
}
GetCatalog::~GetCatalog() = default;
void GetCatalog::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&systemNamespaces_);
  sa.write(&userNamespaces_);
  sa.write(&namespaceRegex_);
  sa.write(&tableRegex_);
}
std::shared_ptr<GetCatalogTable> GetCatalogTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle) {
  return std::make_shared<GetCatalogTable>(Private(), std::move(handle));
}
GetCatalogTable::GetCatalogTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle)
  : handle_(std::move(handle))
  {
}
GetCatalogTable::~GetCatalogTable() = default;
void GetCatalogTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
}
std::shared_ptr<FetchTable> FetchTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> tableName) {
  return std::make_shared<FetchTable>(Private(), std::move(handle), std::move(tableName));
}
FetchTable::FetchTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> tableName)
  : handle_(std::move(handle)), tableName_(std::move(tableName))
  {
}
FetchTable::~FetchTable() = default;
void FetchTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&tableName_);
}
std::shared_ptr<FetchPandasTable> FetchPandasTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name) {
  return std::make_shared<FetchPandasTable>(Private(), std::move(handle), std::move(name));
}
FetchPandasTable::FetchPandasTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name)
  : handle_(std::move(handle)), name_(std::move(name))
  {
}
FetchPandasTable::~FetchPandasTable() = default;
void FetchPandasTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&name_);
}
std::shared_ptr<IntradayTable> IntradayTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName, std::shared_ptr<std::string> internalPartitionValue, bool live) {
  return std::make_shared<IntradayTable>(Private(), std::move(handle), std::move(nameSpace), std::move(tableName), std::move(internalPartitionValue), live);
}
IntradayTable::IntradayTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName, std::shared_ptr<std::string> internalPartitionValue, bool live)
  : handle_(std::move(handle)), nameSpace_(std::move(nameSpace)), tableName_(std::move(tableName)), internalPartitionValue_(std::move(internalPartitionValue)), live_(live)
  {
}
IntradayTable::~IntradayTable() = default;
void IntradayTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&nameSpace_);
  sa.write(&tableName_);
  sa.write(&internalPartitionValue_);
  sa.write(&live_);
}
std::shared_ptr<GetIntradayPartitionsAsTable> GetIntradayPartitionsAsTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> name) {
  return std::make_shared<GetIntradayPartitionsAsTable>(Private(), std::move(handle), std::move(nameSpace), std::move(name));
}
GetIntradayPartitionsAsTable::GetIntradayPartitionsAsTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> name)
  : handle_(std::move(handle)), nameSpace_(std::move(nameSpace)), name_(std::move(name))
  {
}
GetIntradayPartitionsAsTable::~GetIntradayPartitionsAsTable() = default;
void GetIntradayPartitionsAsTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&nameSpace_);
  sa.write(&name_);
}
std::shared_ptr<HistoricalTable> HistoricalTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName) {
  return std::make_shared<HistoricalTable>(Private(), std::move(handle), std::move(nameSpace), std::move(tableName));
}
HistoricalTable::HistoricalTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName)
  : handle_(std::move(handle)), nameSpace_(std::move(nameSpace)), tableName_(std::move(tableName))
  {
}
HistoricalTable::~HistoricalTable() = default;
void HistoricalTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&nameSpace_);
  sa.write(&tableName_);
}
std::shared_ptr<TimeTable> TimeTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t startTimeNanos, int64_t periodNanos) {
  return std::make_shared<TimeTable>(Private(), std::move(handle), startTimeNanos, periodNanos);
}
TimeTable::TimeTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t startTimeNanos, int64_t periodNanos)
  : handle_(std::move(handle)), startTimeNanos_(startTimeNanos), periodNanos_(periodNanos)
  {
}
TimeTable::~TimeTable() = default;
void TimeTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&startTimeNanos_);
  sa.write(&periodNanos_);
}
std::shared_ptr<EmptyTable> EmptyTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t size, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes) {
  return std::make_shared<EmptyTable>(Private(), std::move(handle), size, std::move(columnNames), std::move(columnTypes));
}
EmptyTable::EmptyTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t size, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes)
  : handle_(std::move(handle)), size_(size), columnNames_(std::move(columnNames)), columnTypes_(std::move(columnTypes))
  {
}
EmptyTable::~EmptyTable() = default;
void EmptyTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&size_);
  sa.write(&columnNames_);
  sa.write(&columnTypes_);
}
std::shared_ptr<NewTable> NewTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> columnHolders) {
  return std::make_shared<NewTable>(Private(), std::move(handle), std::move(columnHolders));
}
NewTable::NewTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> columnHolders)
  : handle_(std::move(handle)), columnHolders_(std::move(columnHolders))
  {
}
NewTable::~NewTable() = default;
void NewTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&columnHolders_);
}
std::shared_ptr<MergeTables> MergeTables::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> inputTableHandles, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> keyColumn) {
  return std::make_shared<MergeTables>(Private(), std::move(inputTableHandles), std::move(resultHandle), std::move(keyColumn));
}
MergeTables::MergeTables(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> inputTableHandles, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> keyColumn)
  : inputTableHandles_(std::move(inputTableHandles)), resultHandle_(std::move(resultHandle)), keyColumn_(std::move(keyColumn))
  {
}
MergeTables::~MergeTables() = default;
void MergeTables::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandles_);
  sa.write(&resultHandle_);
  sa.write(&keyColumn_);
}
std::shared_ptr<BindTableToVariable> BindTableToVariable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> scriptHandle) {
  return std::make_shared<BindTableToVariable>(Private(), std::move(handle), std::move(name), std::move(scriptHandle));
}
BindTableToVariable::BindTableToVariable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> scriptHandle)
  : handle_(std::move(handle)), name_(std::move(name)), scriptHandle_(std::move(scriptHandle))
  {
}
BindTableToVariable::~BindTableToVariable() = default;
void BindTableToVariable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&name_);
  sa.write(&scriptHandle_);
}
std::shared_ptr<FetchScriptTable> FetchScriptTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> tableName) {
  return std::make_shared<FetchScriptTable>(Private(), std::move(handle), std::move(script), std::move(tableName));
}
FetchScriptTable::FetchScriptTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> tableName)
  : handle_(std::move(handle)), script_(std::move(script)), tableName_(std::move(tableName))
  {
}
FetchScriptTable::~FetchScriptTable() = default;
void FetchScriptTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&script_);
  sa.write(&tableName_);
}
std::shared_ptr<FetchPandasScriptTable> FetchPandasScriptTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> name) {
  return std::make_shared<FetchPandasScriptTable>(Private(), std::move(handle), std::move(script), std::move(name));
}
FetchPandasScriptTable::FetchPandasScriptTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> name)
  : handle_(std::move(handle)), script_(std::move(script)), name_(std::move(name))
  {
}
FetchPandasScriptTable::~FetchPandasScriptTable() = default;
void FetchPandasScriptTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&script_);
  sa.write(&name_);
}
std::shared_ptr<FetchInputTable> FetchInputTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle) {
  return std::make_shared<FetchInputTable>(Private(), std::move(handle));
}
FetchInputTable::FetchInputTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle)
  : handle_(std::move(handle))
  {
}
FetchInputTable::~FetchInputTable() = default;
void FetchInputTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
}
std::shared_ptr<AddToInputTable> AddToInputTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableRequest> request) {
  return std::make_shared<AddToInputTable>(Private(), std::move(request));
}
AddToInputTable::AddToInputTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableRequest> request)
  : request_(std::move(request))
  {
}
AddToInputTable::~AddToInputTable() = default;
void AddToInputTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&request_);
}
std::shared_ptr<Release> Release::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle) {
  return std::make_shared<Release>(Private(), std::move(handle));
}
Release::Release(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle)
  : handle_(std::move(handle))
  {
}
Release::~Release() = default;
void Release::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
}
std::shared_ptr<Subscribe> Subscribe::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, bool isViewport) {
  return std::make_shared<Subscribe>(Private(), std::move(handle), std::move(columns), isViewport);
}
Subscribe::Subscribe(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, bool isViewport)
  : handle_(std::move(handle)), columns_(std::move(columns)), isViewport_(isViewport)
  {
}
Subscribe::~Subscribe() = default;
void Subscribe::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&columns_);
  sa.write(&isViewport_);
}
std::shared_ptr<UpdateSubscription> UpdateSubscription::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> viewports) {
  return std::make_shared<UpdateSubscription>(Private(), std::move(table), std::move(viewports));
}
UpdateSubscription::UpdateSubscription(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> viewports)
  : table_(std::move(table)), viewports_(std::move(viewports))
  {
}
UpdateSubscription::~UpdateSubscription() = default;
void UpdateSubscription::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&table_);
  sa.write(&viewports_);
}
std::shared_ptr<Unsubscribe> Unsubscribe::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table) {
  return std::make_shared<Unsubscribe>(Private(), std::move(table));
}
Unsubscribe::Unsubscribe(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table)
  : table_(std::move(table))
  {
}
Unsubscribe::~Unsubscribe() = default;
void Unsubscribe::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&table_);
}
std::shared_ptr<ConstructSnapshotQuery> ConstructSnapshotQuery::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns) {
  return std::make_shared<ConstructSnapshotQuery>(Private(), std::move(table), std::move(rows), std::move(columns));
}
ConstructSnapshotQuery::ConstructSnapshotQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns)
  : table_(std::move(table)), rows_(std::move(rows)), columns_(std::move(columns))
  {
}
ConstructSnapshotQuery::~ConstructSnapshotQuery() = default;
void ConstructSnapshotQuery::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&table_);
  sa.write(&rows_);
  sa.write(&columns_);
}
std::shared_ptr<FetchTableMap> FetchTableMap::create(std::shared_ptr<std::string> tableMapName) {
  return std::make_shared<FetchTableMap>(Private(), std::move(tableMapName));
}
FetchTableMap::FetchTableMap(Private, std::shared_ptr<std::string> tableMapName)
  : tableMapName_(std::move(tableMapName))
  {
}
FetchTableMap::~FetchTableMap() = default;
void FetchTableMap::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&tableMapName_);
}
std::shared_ptr<GetTableMapKeys> GetTableMapKeys::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle) {
  return std::make_shared<GetTableMapKeys>(Private(), std::move(handle));
}
GetTableMapKeys::GetTableMapKeys(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle)
  : handle_(std::move(handle))
  {
}
GetTableMapKeys::~GetTableMapKeys() = default;
void GetTableMapKeys::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
}
std::shared_ptr<GetTableMapStringEntry> GetTableMapStringEntry::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::string> key) {
  return std::make_shared<GetTableMapStringEntry>(Private(), std::move(tableMapHandle), std::move(tableHandle), std::move(key));
}
GetTableMapStringEntry::GetTableMapStringEntry(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::string> key)
  : tableMapHandle_(std::move(tableMapHandle)), tableHandle_(std::move(tableHandle)), key_(std::move(key))
  {
}
GetTableMapStringEntry::~GetTableMapStringEntry() = default;
void GetTableMapStringEntry::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&tableMapHandle_);
  sa.write(&tableHandle_);
  sa.write(&key_);
}
std::shared_ptr<GetTableMapStringArrayEntry> GetTableMapStringArrayEntry::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key) {
  return std::make_shared<GetTableMapStringArrayEntry>(Private(), std::move(tableMapHandle), std::move(tableHandle), std::move(key));
}
GetTableMapStringArrayEntry::GetTableMapStringArrayEntry(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key)
  : tableMapHandle_(std::move(tableMapHandle)), tableHandle_(std::move(tableHandle)), key_(std::move(key))
  {
}
GetTableMapStringArrayEntry::~GetTableMapStringArrayEntry() = default;
void GetTableMapStringArrayEntry::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&tableMapHandle_);
  sa.write(&tableHandle_);
  sa.write(&key_);
}
std::shared_ptr<GetMergedTableMap> GetMergedTableMap::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle) {
  return std::make_shared<GetMergedTableMap>(Private(), std::move(tableMapHandle), std::move(tableHandle));
}
GetMergedTableMap::GetMergedTableMap(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle)
  : tableMapHandle_(std::move(tableMapHandle)), tableHandle_(std::move(tableHandle))
  {
}
GetMergedTableMap::~GetMergedTableMap() = default;
void GetMergedTableMap::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&tableMapHandle_);
  sa.write(&tableHandle_);
}
std::shared_ptr<ReleaseTableMap> ReleaseTableMap::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle) {
  return std::make_shared<ReleaseTableMap>(Private(), std::move(tableMapHandle));
}
ReleaseTableMap::ReleaseTableMap(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle)
  : tableMapHandle_(std::move(tableMapHandle))
  {
}
ReleaseTableMap::~ReleaseTableMap() = default;
void ReleaseTableMap::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&tableMapHandle_);
}
std::shared_ptr<ByExternal> ByExternal::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, bool dropKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys) {
  return std::make_shared<ByExternal>(Private(), std::move(tableHandle), dropKeys, std::move(keys));
}
ByExternal::ByExternal(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, bool dropKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys)
  : tableHandle_(std::move(tableHandle)), dropKeys_(dropKeys), keys_(std::move(keys))
  {
}
ByExternal::~ByExternal() = default;
void ByExternal::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&tableHandle_);
  sa.write(&dropKeys_);
  sa.write(&keys_);
}
std::shared_ptr<RequestMetrics> RequestMetrics::create(int32_t clientId, bool enable) {
  return std::make_shared<RequestMetrics>(Private(), clientId, enable);
}
RequestMetrics::RequestMetrics(Private, int32_t clientId, bool enable)
  : clientId_(clientId), enable_(enable)
  {
}
RequestMetrics::~RequestMetrics() = default;
void RequestMetrics::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&clientId_);
  sa.write(&enable_);
}
std::shared_ptr<Join> Join::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor> joinDescriptor, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle) {
  return std::make_shared<Join>(Private(), std::move(joinDescriptor), std::move(resultHandle));
}
Join::Join(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor> joinDescriptor, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle)
  : joinDescriptor_(std::move(joinDescriptor)), resultHandle_(std::move(resultHandle))
  {
}
Join::~Join() = default;
void Join::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&joinDescriptor_);
  sa.write(&resultHandle_);
}
std::shared_ptr<Batch> Batch::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest> request) {
  return std::make_shared<Batch>(Private(), std::move(request));
}
Batch::Batch(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest> request)
  : request_(std::move(request))
  {
}
Batch::~Batch() = default;
void Batch::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&request_);
}
std::shared_ptr<SelectDistinct> SelectDistinct::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames) {
  return std::make_shared<SelectDistinct>(Private(), std::move(handle), std::move(resultHandle), std::move(columnNames));
}
SelectDistinct::SelectDistinct(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames)
  : handle_(std::move(handle)), resultHandle_(std::move(resultHandle)), columnNames_(std::move(columnNames))
  {
}
SelectDistinct::~SelectDistinct() = default;
void SelectDistinct::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&resultHandle_);
  sa.write(&columnNames_);
}
std::shared_ptr<ComboAggregate> ComboAggregate::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor> comboAggregateDescriptor) {
  return std::make_shared<ComboAggregate>(Private(), std::move(inputTableHandle), std::move(resultHandle), std::move(comboAggregateDescriptor));
}
ComboAggregate::ComboAggregate(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor> comboAggregateDescriptor)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), comboAggregateDescriptor_(std::move(comboAggregateDescriptor))
  {
}
ComboAggregate::~ComboAggregate() = default;
void ComboAggregate::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&comboAggregateDescriptor_);
}
std::shared_ptr<Update> Update::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs) {
  return std::make_shared<Update>(Private(), std::move(inputTableHandle), std::move(resultHandle), std::move(columnSpecs));
}
Update::Update(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), columnSpecs_(std::move(columnSpecs))
  {
}
Update::~Update() = default;
void Update::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&columnSpecs_);
}
std::shared_ptr<LazyUpdate> LazyUpdate::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs) {
  return std::make_shared<LazyUpdate>(Private(), std::move(inputTableHandle), std::move(resultHandle), std::move(columnSpecs));
}
LazyUpdate::LazyUpdate(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), columnSpecs_(std::move(columnSpecs))
  {
}
LazyUpdate::~LazyUpdate() = default;
void LazyUpdate::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&columnSpecs_);
}
std::shared_ptr<Select> Select::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs) {
  return std::make_shared<Select>(Private(), std::move(inputTableHandle), std::move(resultHandle), std::move(columnSpecs));
}
Select::Select(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), columnSpecs_(std::move(columnSpecs))
  {
}
Select::~Select() = default;
void Select::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&columnSpecs_);
}
std::shared_ptr<Ungroup> Ungroup::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool nullFill, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToUngroup) {
  return std::make_shared<Ungroup>(Private(), std::move(inputTableHandle), std::move(resultHandle), nullFill, std::move(columnsToUngroup));
}
Ungroup::Ungroup(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool nullFill, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToUngroup)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), nullFill_(nullFill), columnsToUngroup_(std::move(columnsToUngroup))
  {
}
Ungroup::~Ungroup() = default;
void Ungroup::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&nullFill_);
  sa.write(&columnsToUngroup_);
}
std::shared_ptr<HeadBy> HeadBy::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs) {
  return std::make_shared<HeadBy>(Private(), std::move(inputTableHandle), std::move(resultHandle), nRows, std::move(groupByColumnSpecs));
}
HeadBy::HeadBy(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), nRows_(nRows), groupByColumnSpecs_(std::move(groupByColumnSpecs))
  {
}
HeadBy::~HeadBy() = default;
void HeadBy::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&nRows_);
  sa.write(&groupByColumnSpecs_);
}
std::shared_ptr<TailBy> TailBy::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs) {
  return std::make_shared<TailBy>(Private(), std::move(inputTableHandle), std::move(resultHandle), nRows, std::move(groupByColumnSpecs));
}
TailBy::TailBy(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs)
  : inputTableHandle_(std::move(inputTableHandle)), resultHandle_(std::move(resultHandle)), nRows_(nRows), groupByColumnSpecs_(std::move(groupByColumnSpecs))
  {
}
TailBy::~TailBy() = default;
void TailBy::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&inputTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&nRows_);
  sa.write(&groupByColumnSpecs_);
}
std::shared_ptr<Pong> Pong::create() {
  return std::make_shared<Pong>(Private());
}
Pong::Pong(Private)
  
  {
}
Pong::~Pong() = default;
void Pong::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<FetchTotalsTable> FetchTotalsTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> directive, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns) {
  return std::make_shared<FetchTotalsTable>(Private(), std::move(handle), std::move(resultHandle), std::move(directive), std::move(columns));
}
FetchTotalsTable::FetchTotalsTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> directive, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns)
  : handle_(std::move(handle)), resultHandle_(std::move(resultHandle)), directive_(std::move(directive)), columns_(std::move(columns))
  {
}
FetchTotalsTable::~FetchTotalsTable() = default;
void FetchTotalsTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&resultHandle_);
  sa.write(&directive_);
  sa.write(&columns_);
}
std::shared_ptr<FetchTableAttributeAsTable> FetchTableAttributeAsTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> attributeName) {
  return std::make_shared<FetchTableAttributeAsTable>(Private(), std::move(handle), std::move(resultHandle), std::move(attributeName));
}
FetchTableAttributeAsTable::FetchTableAttributeAsTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> attributeName)
  : handle_(std::move(handle)), resultHandle_(std::move(resultHandle)), attributeName_(std::move(attributeName))
  {
}
FetchTableAttributeAsTable::~FetchTableAttributeAsTable() = default;
void FetchTableAttributeAsTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&resultHandle_);
  sa.write(&attributeName_);
}
std::shared_ptr<Rollup> Rollup::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> totalsConfig, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::string> byStrategy, bool includeConstituents) {
  return std::make_shared<Rollup>(Private(), std::move(handle), std::move(resultHandle), std::move(totalsConfig), std::move(columns), std::move(byStrategy), includeConstituents);
}
Rollup::Rollup(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> totalsConfig, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::string> byStrategy, bool includeConstituents)
  : handle_(std::move(handle)), resultHandle_(std::move(resultHandle)), totalsConfig_(std::move(totalsConfig)), columns_(std::move(columns)), byStrategy_(std::move(byStrategy)), includeConstituents_(includeConstituents)
  {
}
Rollup::~Rollup() = default;
void Rollup::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&resultHandle_);
  sa.write(&totalsConfig_);
  sa.write(&columns_);
  sa.write(&byStrategy_);
  sa.write(&includeConstituents_);
}
std::shared_ptr<TreeTable> TreeTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> idColumn, std::shared_ptr<std::string> parentColumn, std::shared_ptr<std::string> byStrategy, bool promoteOrphansToRoot) {
  return std::make_shared<TreeTable>(Private(), std::move(handle), std::move(resultHandle), std::move(idColumn), std::move(parentColumn), std::move(byStrategy), promoteOrphansToRoot);
}
TreeTable::TreeTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> idColumn, std::shared_ptr<std::string> parentColumn, std::shared_ptr<std::string> byStrategy, bool promoteOrphansToRoot)
  : handle_(std::move(handle)), resultHandle_(std::move(resultHandle)), idColumn_(std::move(idColumn)), parentColumn_(std::move(parentColumn)), byStrategy_(std::move(byStrategy)), promoteOrphansToRoot_(promoteOrphansToRoot)
  {
}
TreeTable::~TreeTable() = default;
void TreeTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&resultHandle_);
  sa.write(&idColumn_);
  sa.write(&parentColumn_);
  sa.write(&byStrategy_);
  sa.write(&promoteOrphansToRoot_);
}
std::shared_ptr<Snapshot> Snapshot::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool doInitialSnapshot, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns) {
  return std::make_shared<Snapshot>(Private(), std::move(leftTableHandle), std::move(rightTableHandle), std::move(resultHandle), doInitialSnapshot, std::move(stampColumns));
}
Snapshot::Snapshot(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool doInitialSnapshot, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns)
  : leftTableHandle_(std::move(leftTableHandle)), rightTableHandle_(std::move(rightTableHandle)), resultHandle_(std::move(resultHandle)), doInitialSnapshot_(doInitialSnapshot), stampColumns_(std::move(stampColumns))
  {
}
Snapshot::~Snapshot() = default;
void Snapshot::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&leftTableHandle_);
  sa.write(&rightTableHandle_);
  sa.write(&resultHandle_);
  sa.write(&doInitialSnapshot_);
  sa.write(&stampColumns_);
}
std::shared_ptr<TreeSnapshotQuery> TreeSnapshotQuery::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableRequest> request) {
  return std::make_shared<TreeSnapshotQuery>(Private(), std::move(handle), std::move(request));
}
TreeSnapshotQuery::TreeSnapshotQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableRequest> request)
  : handle_(std::move(handle)), request_(std::move(request))
  {
}
TreeSnapshotQuery::~TreeSnapshotQuery() = default;
void TreeSnapshotQuery::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&request_);
}
std::shared_ptr<FetchFigure> FetchFigure::create(std::shared_ptr<std::string> figureName) {
  return std::make_shared<FetchFigure>(Private(), std::move(figureName));
}
FetchFigure::FetchFigure(Private, std::shared_ptr<std::string> figureName)
  : figureName_(std::move(figureName))
  {
}
FetchFigure::~FetchFigure() = default;
void FetchFigure::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&figureName_);
}
std::shared_ptr<FetchScriptFigure> FetchScriptFigure::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> figureName) {
  return std::make_shared<FetchScriptFigure>(Private(), std::move(script), std::move(figureName));
}
FetchScriptFigure::FetchScriptFigure(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> figureName)
  : script_(std::move(script)), figureName_(std::move(figureName))
  {
}
FetchScriptFigure::~FetchScriptFigure() = default;
void FetchScriptFigure::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&script_);
  sa.write(&figureName_);
}
std::shared_ptr<FinishFigureFetch> FinishFigureFetch::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> handles, std::shared_ptr<std::vector<int32_t>> serverIds) {
  return std::make_shared<FinishFigureFetch>(Private(), std::move(handles), std::move(serverIds));
}
FinishFigureFetch::FinishFigureFetch(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> handles, std::shared_ptr<std::vector<int32_t>> serverIds)
  : handles_(std::move(handles)), serverIds_(std::move(serverIds))
  {
}
FinishFigureFetch::~FinishFigureFetch() = default;
void FinishFigureFetch::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handles_);
  sa.write(&serverIds_);
}
std::shared_ptr<DownsampleTable> DownsampleTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> result, std::shared_ptr<std::string> dateCol, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> valueCols, int32_t pxCount, std::shared_ptr<std::vector<int64_t>> zoomRange) {
  return std::make_shared<DownsampleTable>(Private(), std::move(handle), std::move(result), std::move(dateCol), std::move(valueCols), pxCount, std::move(zoomRange));
}
DownsampleTable::DownsampleTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> result, std::shared_ptr<std::string> dateCol, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> valueCols, int32_t pxCount, std::shared_ptr<std::vector<int64_t>> zoomRange)
  : handle_(std::move(handle)), result_(std::move(result)), dateCol_(std::move(dateCol)), valueCols_(std::move(valueCols)), pxCount_(pxCount), zoomRange_(std::move(zoomRange))
  {
}
DownsampleTable::~DownsampleTable() = default;
void DownsampleTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&result_);
  sa.write(&dateCol_);
  sa.write(&valueCols_);
  sa.write(&pxCount_);
  sa.write(&zoomRange_);
}
std::shared_ptr<GetColumnStatisticsForTable> GetColumnStatisticsForTable::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> columnName) {
  return std::make_shared<GetColumnStatisticsForTable>(Private(), std::move(handle), std::move(columnName));
}
GetColumnStatisticsForTable::GetColumnStatisticsForTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> columnName)
  : handle_(std::move(handle)), columnName_(std::move(columnName))
  {
}
GetColumnStatisticsForTable::~GetColumnStatisticsForTable() = default;
void GetColumnStatisticsForTable::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&columnName_);
}
std::shared_ptr<ExecuteCommand> ExecuteCommand::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle, std::shared_ptr<std::string> code) {
  return std::make_shared<ExecuteCommand>(Private(), std::move(handle), std::move(code));
}
ExecuteCommand::ExecuteCommand(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle, std::shared_ptr<std::string> code)
  : handle_(std::move(handle)), code_(std::move(code))
  {
}
ExecuteCommand::~ExecuteCommand() = default;
void ExecuteCommand::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&code_);
}
std::shared_ptr<CancelCommand> CancelCommand::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle) {
  return std::make_shared<CancelCommand>(Private(), std::move(handle));
}
CancelCommand::CancelCommand(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle)
  : handle_(std::move(handle))
  {
}
CancelCommand::~CancelCommand() = default;
void CancelCommand::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
}
std::shared_ptr<StartConsole> StartConsole::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType config) {
  return std::make_shared<StartConsole>(Private(), std::move(handle), config);
}
StartConsole::StartConsole(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType config)
  : handle_(std::move(handle)), config_(config)
  {
}
StartConsole::~StartConsole() = default;
void StartConsole::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&config_);
}
std::shared_ptr<StopConsole> StopConsole::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle) {
  return std::make_shared<StopConsole>(Private(), std::move(handle));
}
StopConsole::StopConsole(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle)
  : handle_(std::move(handle))
  {
}
StopConsole::~StopConsole() = default;
void StopConsole::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
}
std::shared_ptr<OpenDocument> OpenDocument::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidOpenTextDocumentParams> params) {
  return std::make_shared<OpenDocument>(Private(), std::move(handle), std::move(params));
}
OpenDocument::OpenDocument(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidOpenTextDocumentParams> params)
  : handle_(std::move(handle)), params_(std::move(params))
  {
}
OpenDocument::~OpenDocument() = default;
void OpenDocument::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&params_);
}
std::shared_ptr<ChangeDocument> ChangeDocument::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidChangeTextDocumentParams> params) {
  return std::make_shared<ChangeDocument>(Private(), std::move(handle), std::move(params));
}
ChangeDocument::ChangeDocument(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidChangeTextDocumentParams> params)
  : handle_(std::move(handle)), params_(std::move(params))
  {
}
ChangeDocument::~ChangeDocument() = default;
void ChangeDocument::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&params_);
}
std::shared_ptr<GetCompletionItems> GetCompletionItems::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams> params) {
  return std::make_shared<GetCompletionItems>(Private(), std::move(handle), std::move(params));
}
GetCompletionItems::GetCompletionItems(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams> params)
  : handle_(std::move(handle)), params_(std::move(params))
  {
}
GetCompletionItems::~GetCompletionItems() = default;
void GetCompletionItems::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&params_);
}
std::shared_ptr<CloseDocument> CloseDocument::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidCloseTextDocumentParams> params) {
  return std::make_shared<CloseDocument>(Private(), std::move(handle), std::move(params));
}
CloseDocument::CloseDocument(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidCloseTextDocumentParams> params)
  : handle_(std::move(handle)), params_(std::move(params))
  {
}
CloseDocument::~CloseDocument() = default;
void CloseDocument::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&handle_);
  sa.write(&params_);
}
std::shared_ptr<SubscribeToLogs> SubscribeToLogs::create() {
  return std::make_shared<SubscribeToLogs>(Private());
}
SubscribeToLogs::SubscribeToLogs(Private)
  
  {
}
SubscribeToLogs::~SubscribeToLogs() = default;
void SubscribeToLogs::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<UnsubscribeToLogs> UnsubscribeToLogs::create() {
  return std::make_shared<UnsubscribeToLogs>(Private());
}
UnsubscribeToLogs::UnsubscribeToLogs(Private)
  
  {
}
UnsubscribeToLogs::~UnsubscribeToLogs() = default;
void UnsubscribeToLogs::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<CreateWorkspaceData> CreateWorkspaceData::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data) {
  return std::make_shared<CreateWorkspaceData>(Private(), std::move(data));
}
CreateWorkspaceData::CreateWorkspaceData(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data)
  : data_(std::move(data))
  {
}
CreateWorkspaceData::~CreateWorkspaceData() = default;
void CreateWorkspaceData::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&data_);
}
std::shared_ptr<SaveWorkspaceData> SaveWorkspaceData::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data) {
  return std::make_shared<SaveWorkspaceData>(Private(), std::move(data));
}
SaveWorkspaceData::SaveWorkspaceData(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data)
  : data_(std::move(data))
  {
}
SaveWorkspaceData::~SaveWorkspaceData() = default;
void SaveWorkspaceData::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&data_);
}
}  // namespace worker
}  // namespace shared
}  // namespace web
}  // namespace iris
}  // namespace illumon
}  // namespace com
}  // namespace generated
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
