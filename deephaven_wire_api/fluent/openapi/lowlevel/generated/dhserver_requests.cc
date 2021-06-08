#include "lowlevel/generated/dhserver_requests.h"
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
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/util/deserializer_adapter.h"
#include "lowlevel/util/protocol_container_classes.h"
#include "lowlevel/util/serializer_adapter.h"
#include "utility/utility.h"
namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace generated {
const boost::string_view ServerRequestHash::hash = "4c2f9395991d663dd41df95061e5974a11edddff";
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace primary {
std::shared_ptr<Login> Login::create(std::shared_ptr<std::string> username, std::shared_ptr<std::string> password, std::shared_ptr<std::string> operateAs) {
  return std::make_shared<Login>(Private(), std::move(username), std::move(password), std::move(operateAs));
}
Login::Login(Private, std::shared_ptr<std::string> username, std::shared_ptr<std::string> password, std::shared_ptr<std::string> operateAs)
  : username_(std::move(username)), password_(std::move(password)), operateAs_(std::move(operateAs))
  {
}
Login::~Login() = default;
void Login::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&username_);
  sa.write(&password_);
  sa.write(&operateAs_);
}
std::shared_ptr<Reconnect> Reconnect::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken> token) {
  return std::make_shared<Reconnect>(Private(), std::move(token));
}
Reconnect::Reconnect(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken> token)
  : token_(std::move(token))
  {
}
Reconnect::~Reconnect() = default;
void Reconnect::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&token_);
}
std::shared_ptr<Refresh> Refresh::create() {
  return std::make_shared<Refresh>(Private());
}
Refresh::Refresh(Private)
  
  {
}
Refresh::~Refresh() = default;
void Refresh::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<CreateAuthToken> CreateAuthToken::create(std::shared_ptr<std::string> service) {
  return std::make_shared<CreateAuthToken>(Private(), std::move(service));
}
CreateAuthToken::CreateAuthToken(Private, std::shared_ptr<std::string> service)
  : service_(std::move(service))
  {
}
CreateAuthToken::~CreateAuthToken() = default;
void CreateAuthToken::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&service_);
}
std::shared_ptr<GetAuthConfigValues> GetAuthConfigValues::create() {
  return std::make_shared<GetAuthConfigValues>(Private());
}
GetAuthConfigValues::GetAuthConfigValues(Private)
  
  {
}
GetAuthConfigValues::~GetAuthConfigValues() = default;
void GetAuthConfigValues::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetUserInfo> GetUserInfo::create() {
  return std::make_shared<GetUserInfo>(Private());
}
GetUserInfo::GetUserInfo(Private)
  
  {
}
GetUserInfo::~GetUserInfo() = default;
void GetUserInfo::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetDbServersForType> GetDbServersForType::create(std::shared_ptr<std::string> type) {
  return std::make_shared<GetDbServersForType>(Private(), std::move(type));
}
GetDbServersForType::GetDbServersForType(Private, std::shared_ptr<std::string> type)
  : type_(std::move(type))
  {
}
GetDbServersForType::~GetDbServersForType() = default;
void GetDbServersForType::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&type_);
}
std::shared_ptr<GetDbServers> GetDbServers::create() {
  return std::make_shared<GetDbServers>(Private());
}
GetDbServers::GetDbServers(Private)
  
  {
}
GetDbServers::~GetDbServers() = default;
void GetDbServers::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetAllUsers> GetAllUsers::create() {
  return std::make_shared<GetAllUsers>(Private());
}
GetAllUsers::GetAllUsers(Private)
  
  {
}
GetAllUsers::~GetAllUsers() = default;
void GetAllUsers::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetQueryTypes> GetQueryTypes::create() {
  return std::make_shared<GetQueryTypes>(Private());
}
GetQueryTypes::GetQueryTypes(Private)
  
  {
}
GetQueryTypes::~GetQueryTypes() = default;
void GetQueryTypes::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetTemporaryQueryTypes> GetTemporaryQueryTypes::create() {
  return std::make_shared<GetTemporaryQueryTypes>(Private());
}
GetTemporaryQueryTypes::GetTemporaryQueryTypes(Private)
  
  {
}
GetTemporaryQueryTypes::~GetTemporaryQueryTypes() = default;
void GetTemporaryQueryTypes::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetJvmProfiles> GetJvmProfiles::create() {
  return std::make_shared<GetJvmProfiles>(Private());
}
GetJvmProfiles::GetJvmProfiles(Private)
  
  {
}
GetJvmProfiles::~GetJvmProfiles() = default;
void GetJvmProfiles::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetQueryScriptCode> GetQueryScriptCode::create(int64_t serialId) {
  return std::make_shared<GetQueryScriptCode>(Private(), serialId);
}
GetQueryScriptCode::GetQueryScriptCode(Private, int64_t serialId)
  : serialId_(serialId)
  {
}
GetQueryScriptCode::~GetQueryScriptCode() = default;
void GetQueryScriptCode::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&serialId_);
}
std::shared_ptr<GetScriptPaths> GetScriptPaths::create(int64_t serialId, std::shared_ptr<std::string> owner) {
  return std::make_shared<GetScriptPaths>(Private(), serialId, std::move(owner));
}
GetScriptPaths::GetScriptPaths(Private, int64_t serialId, std::shared_ptr<std::string> owner)
  : serialId_(serialId), owner_(std::move(owner))
  {
}
GetScriptPaths::~GetScriptPaths() = default;
void GetScriptPaths::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&serialId_);
  sa.write(&owner_);
}
std::shared_ptr<GetScriptBody> GetScriptBody::create(std::shared_ptr<std::string> path, std::shared_ptr<std::string> owner, int64_t serialId) {
  return std::make_shared<GetScriptBody>(Private(), std::move(path), std::move(owner), serialId);
}
GetScriptBody::GetScriptBody(Private, std::shared_ptr<std::string> path, std::shared_ptr<std::string> owner, int64_t serialId)
  : path_(std::move(path)), owner_(std::move(owner)), serialId_(serialId)
  {
}
GetScriptBody::~GetScriptBody() = default;
void GetScriptBody::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&path_);
  sa.write(&owner_);
  sa.write(&serialId_);
}
std::shared_ptr<StartWorker> StartWorker::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig> config) {
  return std::make_shared<StartWorker>(Private(), std::move(id), std::move(config));
}
StartWorker::StartWorker(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig> config)
  : id_(std::move(id)), config_(std::move(config))
  {
}
StartWorker::~StartWorker() = default;
void StartWorker::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&id_);
  sa.write(&config_);
}
std::shared_ptr<StopWorker> StopWorker::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id) {
  return std::make_shared<StopWorker>(Private(), std::move(id));
}
StopWorker::StopWorker(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id)
  : id_(std::move(id))
  {
}
StopWorker::~StopWorker() = default;
void StopWorker::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&id_);
}
std::shared_ptr<GetAllGroups> GetAllGroups::create() {
  return std::make_shared<GetAllGroups>(Private());
}
GetAllGroups::GetAllGroups(Private)
  
  {
}
GetAllGroups::~GetAllGroups() = default;
void GetAllGroups::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetQueryConstants> GetQueryConstants::create() {
  return std::make_shared<GetQueryConstants>(Private());
}
GetQueryConstants::GetQueryConstants(Private)
  
  {
}
GetQueryConstants::~GetQueryConstants() = default;
void GetQueryConstants::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetMyGroups> GetMyGroups::create() {
  return std::make_shared<GetMyGroups>(Private());
}
GetMyGroups::GetMyGroups(Private)
  
  {
}
GetMyGroups::~GetMyGroups() = default;
void GetMyGroups::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetBusinessCalendars> GetBusinessCalendars::create() {
  return std::make_shared<GetBusinessCalendars>(Private());
}
GetBusinessCalendars::GetBusinessCalendars(Private)
  
  {
}
GetBusinessCalendars::~GetBusinessCalendars() = default;
void GetBusinessCalendars::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetDefaultCalendar> GetDefaultCalendar::create() {
  return std::make_shared<GetDefaultCalendar>(Private());
}
GetDefaultCalendar::GetDefaultCalendar(Private)
  
  {
}
GetDefaultCalendar::~GetDefaultCalendar() = default;
void GetDefaultCalendar::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetQuerySerialsForDependent> GetQuerySerialsForDependent::create(bool isTemporary) {
  return std::make_shared<GetQuerySerialsForDependent>(Private(), isTemporary);
}
GetQuerySerialsForDependent::GetQuerySerialsForDependent(Private, bool isTemporary)
  : isTemporary_(isTemporary)
  {
}
GetQuerySerialsForDependent::~GetQuerySerialsForDependent() = default;
void GetQuerySerialsForDependent::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&isTemporary_);
}
std::shared_ptr<GetTemporaryQueueNames> GetTemporaryQueueNames::create() {
  return std::make_shared<GetTemporaryQueueNames>(Private());
}
GetTemporaryQueueNames::GetTemporaryQueueNames(Private)
  
  {
}
GetTemporaryQueueNames::~GetTemporaryQueueNames() = default;
void GetTemporaryQueueNames::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<GetServerConfigValues> GetServerConfigValues::create() {
  return std::make_shared<GetServerConfigValues>(Private());
}
GetServerConfigValues::GetServerConfigValues(Private)
  
  {
}
GetServerConfigValues::~GetServerConfigValues() = default;
void GetServerConfigValues::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<RestartQueries> RestartQueries::create(std::shared_ptr<std::vector<int64_t>> serialIds) {
  return std::make_shared<RestartQueries>(Private(), std::move(serialIds));
}
RestartQueries::RestartQueries(Private, std::shared_ptr<std::vector<int64_t>> serialIds)
  : serialIds_(std::move(serialIds))
  {
}
RestartQueries::~RestartQueries() = default;
void RestartQueries::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&serialIds_);
}
std::shared_ptr<StopQueries> StopQueries::create(std::shared_ptr<std::vector<int64_t>> serialIds) {
  return std::make_shared<StopQueries>(Private(), std::move(serialIds));
}
StopQueries::StopQueries(Private, std::shared_ptr<std::vector<int64_t>> serialIds)
  : serialIds_(std::move(serialIds))
  {
}
StopQueries::~StopQueries() = default;
void StopQueries::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&serialIds_);
}
std::shared_ptr<DeleteQueries> DeleteQueries::create(std::shared_ptr<std::vector<int64_t>> serialIds) {
  return std::make_shared<DeleteQueries>(Private(), std::move(serialIds));
}
DeleteQueries::DeleteQueries(Private, std::shared_ptr<std::vector<int64_t>> serialIds)
  : serialIds_(std::move(serialIds))
  {
}
DeleteQueries::~DeleteQueries() = default;
void DeleteQueries::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&serialIds_);
}
std::shared_ptr<GetQuerySelectionPermissions> GetQuerySelectionPermissions::create(std::shared_ptr<std::vector<int64_t>> serialIds) {
  return std::make_shared<GetQuerySelectionPermissions>(Private(), std::move(serialIds));
}
GetQuerySelectionPermissions::GetQuerySelectionPermissions(Private, std::shared_ptr<std::vector<int64_t>> serialIds)
  : serialIds_(std::move(serialIds))
  {
}
GetQuerySelectionPermissions::~GetQuerySelectionPermissions() = default;
void GetQuerySelectionPermissions::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&serialIds_);
}
std::shared_ptr<ModifyQuery> ModifyQuery::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode) {
  return std::make_shared<ModifyQuery>(Private(), std::move(queryConfig), std::move(scriptCode));
}
ModifyQuery::ModifyQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode)
  : queryConfig_(std::move(queryConfig)), scriptCode_(std::move(scriptCode))
  {
}
ModifyQuery::~ModifyQuery() = default;
void ModifyQuery::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&queryConfig_);
  sa.write(&scriptCode_);
}
std::shared_ptr<SaveDraftQuery> SaveDraftQuery::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode) {
  return std::make_shared<SaveDraftQuery>(Private(), std::move(queryConfig), std::move(scriptCode));
}
SaveDraftQuery::SaveDraftQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode)
  : queryConfig_(std::move(queryConfig)), scriptCode_(std::move(scriptCode))
  {
}
SaveDraftQuery::~SaveDraftQuery() = default;
void SaveDraftQuery::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&queryConfig_);
  sa.write(&scriptCode_);
}
std::shared_ptr<GetChallengeNonce> GetChallengeNonce::create() {
  return std::make_shared<GetChallengeNonce>(Private());
}
GetChallengeNonce::GetChallengeNonce(Private)
  
  {
}
GetChallengeNonce::~GetChallengeNonce() = default;
void GetChallengeNonce::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
}
std::shared_ptr<ChallengeResponse> ChallengeResponse::create(std::shared_ptr<std::vector<int8_t>> sigBytes, std::shared_ptr<std::vector<int8_t>> publicBytes, std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs) {
  return std::make_shared<ChallengeResponse>(Private(), std::move(sigBytes), std::move(publicBytes), std::move(username), std::move(operateAs));
}
ChallengeResponse::ChallengeResponse(Private, std::shared_ptr<std::vector<int8_t>> sigBytes, std::shared_ptr<std::vector<int8_t>> publicBytes, std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs)
  : sigBytes_(std::move(sigBytes)), publicBytes_(std::move(publicBytes)), username_(std::move(username)), operateAs_(std::move(operateAs))
  {
}
ChallengeResponse::~ChallengeResponse() = default;
void ChallengeResponse::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&sigBytes_);
  sa.write(&publicBytes_);
  sa.write(&username_);
  sa.write(&operateAs_);
}
std::shared_ptr<ExternalLogin> ExternalLogin::create(std::shared_ptr<std::string> key) {
  return std::make_shared<ExternalLogin>(Private(), std::move(key));
}
ExternalLogin::ExternalLogin(Private, std::shared_ptr<std::string> key)
  : key_(std::move(key))
  {
}
ExternalLogin::~ExternalLogin() = default;
void ExternalLogin::serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *serializer, int32_t callbackId) const {
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  auto tempRequestId = requestId;
  sa.write(&tempRequestId);
  sa.write(&callbackId);
  sa.write(&key_);
}
}  // namespace primary
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
