#pragma once
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
struct ServerRequestHash {
  static const boost::string_view hash;
};
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace primary {
class Login final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 0;
  static std::shared_ptr<Login> create(std::shared_ptr<std::string> username, std::shared_ptr<std::string> password, std::shared_ptr<std::string> operateAs);
  Login(Private, std::shared_ptr<std::string> username, std::shared_ptr<std::string> password, std::shared_ptr<std::string> operateAs);
  Login(const Login &other) = delete;
  Login &operator=(const Login &other) = delete;
  ~Login() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &username() const { return username_; }
  const std::shared_ptr<std::string> &password() const { return password_; }
  const std::shared_ptr<std::string> &operateAs() const { return operateAs_; }
private:
  std::shared_ptr<std::string> username_;
  std::shared_ptr<std::string> password_;
  std::shared_ptr<std::string> operateAs_;
};
class Reconnect final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 1;
  static std::shared_ptr<Reconnect> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken> token);
  Reconnect(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken> token);
  Reconnect(const Reconnect &other) = delete;
  Reconnect &operator=(const Reconnect &other) = delete;
  ~Reconnect() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken> &token() const { return token_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken> token_;
};
class Refresh final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 2;
  static std::shared_ptr<Refresh> create();
  explicit Refresh(Private);
  Refresh(const Refresh &other) = delete;
  Refresh &operator=(const Refresh &other) = delete;
  ~Refresh() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class CreateAuthToken final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 3;
  static std::shared_ptr<CreateAuthToken> create(std::shared_ptr<std::string> service);
  CreateAuthToken(Private, std::shared_ptr<std::string> service);
  CreateAuthToken(const CreateAuthToken &other) = delete;
  CreateAuthToken &operator=(const CreateAuthToken &other) = delete;
  ~CreateAuthToken() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &service() const { return service_; }
private:
  std::shared_ptr<std::string> service_;
};
class GetAuthConfigValues final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 4;
  static std::shared_ptr<GetAuthConfigValues> create();
  explicit GetAuthConfigValues(Private);
  GetAuthConfigValues(const GetAuthConfigValues &other) = delete;
  GetAuthConfigValues &operator=(const GetAuthConfigValues &other) = delete;
  ~GetAuthConfigValues() final;
  typedef std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetUserInfo final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 5;
  static std::shared_ptr<GetUserInfo> create();
  explicit GetUserInfo(Private);
  GetUserInfo(const GetUserInfo &other) = delete;
  GetUserInfo &operator=(const GetUserInfo &other) = delete;
  ~GetUserInfo() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::UserInfo correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetDbServersForType final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 6;
  static std::shared_ptr<GetDbServersForType> create(std::shared_ptr<std::string> type);
  GetDbServersForType(Private, std::shared_ptr<std::string> type);
  GetDbServersForType(const GetDbServersForType &other) = delete;
  GetDbServersForType &operator=(const GetDbServersForType &other) = delete;
  ~GetDbServersForType() final;
  typedef std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleServerAddress>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &type() const { return type_; }
private:
  std::shared_ptr<std::string> type_;
};
class GetDbServers final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 7;
  static std::shared_ptr<GetDbServers> create();
  explicit GetDbServers(Private);
  GetDbServers(const GetDbServers &other) = delete;
  GetDbServers &operator=(const GetDbServers &other) = delete;
  ~GetDbServers() final;
  typedef std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleServerAddress>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetAllUsers final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 8;
  static std::shared_ptr<GetAllUsers> create();
  explicit GetAllUsers(Private);
  GetAllUsers(const GetAllUsers &other) = delete;
  GetAllUsers &operator=(const GetAllUsers &other) = delete;
  ~GetAllUsers() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetQueryTypes final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 9;
  static std::shared_ptr<GetQueryTypes> create();
  explicit GetQueryTypes(Private);
  GetQueryTypes(const GetQueryTypes &other) = delete;
  GetQueryTypes &operator=(const GetQueryTypes &other) = delete;
  ~GetQueryTypes() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetTemporaryQueryTypes final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 10;
  static std::shared_ptr<GetTemporaryQueryTypes> create();
  explicit GetTemporaryQueryTypes(Private);
  GetTemporaryQueryTypes(const GetTemporaryQueryTypes &other) = delete;
  GetTemporaryQueryTypes &operator=(const GetTemporaryQueryTypes &other) = delete;
  ~GetTemporaryQueryTypes() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetJvmProfiles final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 11;
  static std::shared_ptr<GetJvmProfiles> create();
  explicit GetJvmProfiles(Private);
  GetJvmProfiles(const GetJvmProfiles &other) = delete;
  GetJvmProfiles &operator=(const GetJvmProfiles &other) = delete;
  ~GetJvmProfiles() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetQueryScriptCode final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 12;
  static std::shared_ptr<GetQueryScriptCode> create(int64_t serialId);
  GetQueryScriptCode(Private, int64_t serialId);
  GetQueryScriptCode(const GetQueryScriptCode &other) = delete;
  GetQueryScriptCode &operator=(const GetQueryScriptCode &other) = delete;
  ~GetQueryScriptCode() final;
  typedef std::shared_ptr<std::string> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  int64_t serialId() const { return serialId_; }
private:
  int64_t serialId_;
};
class GetScriptPaths final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 13;
  static std::shared_ptr<GetScriptPaths> create(int64_t serialId, std::shared_ptr<std::string> owner);
  GetScriptPaths(Private, int64_t serialId, std::shared_ptr<std::string> owner);
  GetScriptPaths(const GetScriptPaths &other) = delete;
  GetScriptPaths &operator=(const GetScriptPaths &other) = delete;
  ~GetScriptPaths() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  int64_t serialId() const { return serialId_; }
  const std::shared_ptr<std::string> &owner() const { return owner_; }
private:
  int64_t serialId_;
  std::shared_ptr<std::string> owner_;
};
class GetScriptBody final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 14;
  static std::shared_ptr<GetScriptBody> create(std::shared_ptr<std::string> path, std::shared_ptr<std::string> owner, int64_t serialId);
  GetScriptBody(Private, std::shared_ptr<std::string> path, std::shared_ptr<std::string> owner, int64_t serialId);
  GetScriptBody(const GetScriptBody &other) = delete;
  GetScriptBody &operator=(const GetScriptBody &other) = delete;
  ~GetScriptBody() final;
  typedef std::shared_ptr<std::string> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &path() const { return path_; }
  const std::shared_ptr<std::string> &owner() const { return owner_; }
  int64_t serialId() const { return serialId_; }
private:
  std::shared_ptr<std::string> path_;
  std::shared_ptr<std::string> owner_;
  int64_t serialId_;
};
class StartWorker final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 15;
  static std::shared_ptr<StartWorker> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig> config);
  StartWorker(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig> config);
  StartWorker(const StartWorker &other) = delete;
  StartWorker &operator=(const StartWorker &other) = delete;
  ~StartWorker() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleAddress correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> &id() const { return id_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig> &config() const { return config_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConfig> config_;
};
class StopWorker final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 16;
  static std::shared_ptr<StopWorker> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id);
  StopWorker(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id);
  StopWorker(const StopWorker &other) = delete;
  StopWorker &operator=(const StopWorker &other) = delete;
  ~StopWorker() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> &id() const { return id_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id_;
};
class GetAllGroups final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 17;
  static std::shared_ptr<GetAllGroups> create();
  explicit GetAllGroups(Private);
  GetAllGroups(const GetAllGroups &other) = delete;
  GetAllGroups &operator=(const GetAllGroups &other) = delete;
  ~GetAllGroups() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetQueryConstants final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 18;
  static std::shared_ptr<GetQueryConstants> create();
  explicit GetQueryConstants(Private);
  GetQueryConstants(const GetQueryConstants &other) = delete;
  GetQueryConstants &operator=(const GetQueryConstants &other) = delete;
  ~GetQueryConstants() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConstants correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetMyGroups final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 19;
  static std::shared_ptr<GetMyGroups> create();
  explicit GetMyGroups(Private);
  GetMyGroups(const GetMyGroups &other) = delete;
  GetMyGroups &operator=(const GetMyGroups &other) = delete;
  ~GetMyGroups() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetBusinessCalendars final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 20;
  static std::shared_ptr<GetBusinessCalendars> create();
  explicit GetBusinessCalendars(Private);
  GetBusinessCalendars(const GetBusinessCalendars &other) = delete;
  GetBusinessCalendars &operator=(const GetBusinessCalendars &other) = delete;
  ~GetBusinessCalendars() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetDefaultCalendar final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 21;
  static std::shared_ptr<GetDefaultCalendar> create();
  explicit GetDefaultCalendar(Private);
  GetDefaultCalendar(const GetDefaultCalendar &other) = delete;
  GetDefaultCalendar &operator=(const GetDefaultCalendar &other) = delete;
  ~GetDefaultCalendar() final;
  typedef std::shared_ptr<std::string> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetQuerySerialsForDependent final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 22;
  static std::shared_ptr<GetQuerySerialsForDependent> create(bool isTemporary);
  GetQuerySerialsForDependent(Private, bool isTemporary);
  GetQuerySerialsForDependent(const GetQuerySerialsForDependent &other) = delete;
  GetQuerySerialsForDependent &operator=(const GetQuerySerialsForDependent &other) = delete;
  ~GetQuerySerialsForDependent() final;
  typedef std::vector<int64_t> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  bool isTemporary() const { return isTemporary_; }
private:
  bool isTemporary_;
};
class GetTemporaryQueueNames final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 23;
  static std::shared_ptr<GetTemporaryQueueNames> create();
  explicit GetTemporaryQueueNames(Private);
  GetTemporaryQueueNames(const GetTemporaryQueueNames &other) = delete;
  GetTemporaryQueueNames &operator=(const GetTemporaryQueueNames &other) = delete;
  ~GetTemporaryQueueNames() final;
  typedef std::vector<std::shared_ptr<std::string>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class GetServerConfigValues final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 24;
  static std::shared_ptr<GetServerConfigValues> create();
  explicit GetServerConfigValues(Private);
  GetServerConfigValues(const GetServerConfigValues &other) = delete;
  GetServerConfigValues &operator=(const GetServerConfigValues &other) = delete;
  ~GetServerConfigValues() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ServerConfigValues correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class RestartQueries final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 25;
  static std::shared_ptr<RestartQueries> create(std::shared_ptr<std::vector<int64_t>> serialIds);
  RestartQueries(Private, std::shared_ptr<std::vector<int64_t>> serialIds);
  RestartQueries(const RestartQueries &other) = delete;
  RestartQueries &operator=(const RestartQueries &other) = delete;
  ~RestartQueries() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<int64_t>> &serialIds() const { return serialIds_; }
private:
  std::shared_ptr<std::vector<int64_t>> serialIds_;
};
class StopQueries final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 26;
  static std::shared_ptr<StopQueries> create(std::shared_ptr<std::vector<int64_t>> serialIds);
  StopQueries(Private, std::shared_ptr<std::vector<int64_t>> serialIds);
  StopQueries(const StopQueries &other) = delete;
  StopQueries &operator=(const StopQueries &other) = delete;
  ~StopQueries() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<int64_t>> &serialIds() const { return serialIds_; }
private:
  std::shared_ptr<std::vector<int64_t>> serialIds_;
};
class DeleteQueries final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 27;
  static std::shared_ptr<DeleteQueries> create(std::shared_ptr<std::vector<int64_t>> serialIds);
  DeleteQueries(Private, std::shared_ptr<std::vector<int64_t>> serialIds);
  DeleteQueries(const DeleteQueries &other) = delete;
  DeleteQueries &operator=(const DeleteQueries &other) = delete;
  ~DeleteQueries() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<int64_t>> &serialIds() const { return serialIds_; }
private:
  std::shared_ptr<std::vector<int64_t>> serialIds_;
};
class GetQuerySelectionPermissions final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 28;
  static std::shared_ptr<GetQuerySelectionPermissions> create(std::shared_ptr<std::vector<int64_t>> serialIds);
  GetQuerySelectionPermissions(Private, std::shared_ptr<std::vector<int64_t>> serialIds);
  GetQuerySelectionPermissions(const GetQuerySelectionPermissions &other) = delete;
  GetQuerySelectionPermissions &operator=(const GetQuerySelectionPermissions &other) = delete;
  ~GetQuerySelectionPermissions() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QuerySelectionPermissions correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<int64_t>> &serialIds() const { return serialIds_; }
private:
  std::shared_ptr<std::vector<int64_t>> serialIds_;
};
class ModifyQuery final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 29;
  static std::shared_ptr<ModifyQuery> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode);
  ModifyQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode);
  ModifyQuery(const ModifyQuery &other) = delete;
  ModifyQuery &operator=(const ModifyQuery &other) = delete;
  ~ModifyQuery() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> &queryConfig() const { return queryConfig_; }
  const std::shared_ptr<std::string> &scriptCode() const { return scriptCode_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig_;
  std::shared_ptr<std::string> scriptCode_;
};
class SaveDraftQuery final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 30;
  static std::shared_ptr<SaveDraftQuery> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode);
  SaveDraftQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig, std::shared_ptr<std::string> scriptCode);
  SaveDraftQuery(const SaveDraftQuery &other) = delete;
  SaveDraftQuery &operator=(const SaveDraftQuery &other) = delete;
  ~SaveDraftQuery() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Long correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> &queryConfig() const { return queryConfig_; }
  const std::shared_ptr<std::string> &scriptCode() const { return scriptCode_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> queryConfig_;
  std::shared_ptr<std::string> scriptCode_;
};
class GetChallengeNonce final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 31;
  static std::shared_ptr<GetChallengeNonce> create();
  explicit GetChallengeNonce(Private);
  GetChallengeNonce(const GetChallengeNonce &other) = delete;
  GetChallengeNonce &operator=(const GetChallengeNonce &other) = delete;
  ~GetChallengeNonce() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ChallengeResponseData correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class ChallengeResponse final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 32;
  static std::shared_ptr<ChallengeResponse> create(std::shared_ptr<std::vector<int8_t>> sigBytes, std::shared_ptr<std::vector<int8_t>> publicBytes, std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs);
  ChallengeResponse(Private, std::shared_ptr<std::vector<int8_t>> sigBytes, std::shared_ptr<std::vector<int8_t>> publicBytes, std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs);
  ChallengeResponse(const ChallengeResponse &other) = delete;
  ChallengeResponse &operator=(const ChallengeResponse &other) = delete;
  ~ChallengeResponse() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<int8_t>> &sigBytes() const { return sigBytes_; }
  const std::shared_ptr<std::vector<int8_t>> &publicBytes() const { return publicBytes_; }
  const std::shared_ptr<std::string> &username() const { return username_; }
  const std::shared_ptr<std::string> &operateAs() const { return operateAs_; }
private:
  std::shared_ptr<std::vector<int8_t>> sigBytes_;
  std::shared_ptr<std::vector<int8_t>> publicBytes_;
  std::shared_ptr<std::string> username_;
  std::shared_ptr<std::string> operateAs_;
};
class ExternalLogin final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 33;
  static std::shared_ptr<ExternalLogin> create(std::shared_ptr<std::string> key);
  ExternalLogin(Private, std::shared_ptr<std::string> key);
  ExternalLogin(const ExternalLogin &other) = delete;
  ExternalLogin &operator=(const ExternalLogin &other) = delete;
  ~ExternalLogin() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RefreshToken correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &key() const { return key_; }
private:
  std::shared_ptr<std::string> key_;
};
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
