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
struct WorkerRequestHash {
  static const boost::string_view hash;
};
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace worker {
class Register final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 0;
  static std::shared_ptr<Register> create(int32_t clientId, std::shared_ptr<std::string> service, double seedTime, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> authToken);
  Register(Private, int32_t clientId, std::shared_ptr<std::string> service, double seedTime, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> authToken);
  Register(const Register &other) = delete;
  Register &operator=(const Register &other) = delete;
  ~Register() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ConnectionSuccess correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  int32_t clientId() const { return clientId_; }
  const std::shared_ptr<std::string> &service() const { return service_; }
  double seedTime() const { return seedTime_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> &authToken() const { return authToken_; }
private:
  int32_t clientId_;
  std::shared_ptr<std::string> service_;
  double seedTime_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> authToken_;
};
class GetCatalog final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 1;
  static std::shared_ptr<GetCatalog> create(bool systemNamespaces, bool userNamespaces, std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex);
  GetCatalog(Private, bool systemNamespaces, bool userNamespaces, std::shared_ptr<std::string> namespaceRegex, std::shared_ptr<std::string> tableRegex);
  GetCatalog(const GetCatalog &other) = delete;
  GetCatalog &operator=(const GetCatalog &other) = delete;
  ~GetCatalog() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Catalog correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  bool systemNamespaces() const { return systemNamespaces_; }
  bool userNamespaces() const { return userNamespaces_; }
  const std::shared_ptr<std::string> &namespaceRegex() const { return namespaceRegex_; }
  const std::shared_ptr<std::string> &tableRegex() const { return tableRegex_; }
private:
  bool systemNamespaces_;
  bool userNamespaces_;
  std::shared_ptr<std::string> namespaceRegex_;
  std::shared_ptr<std::string> tableRegex_;
};
class GetCatalogTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 2;
  static std::shared_ptr<GetCatalogTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  GetCatalogTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  GetCatalogTable(const GetCatalogTable &other) = delete;
  GetCatalogTable &operator=(const GetCatalogTable &other) = delete;
  ~GetCatalogTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
};
class FetchTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 3;
  static std::shared_ptr<FetchTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> tableName);
  FetchTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> tableName);
  FetchTable(const FetchTable &other) = delete;
  FetchTable &operator=(const FetchTable &other) = delete;
  ~FetchTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &tableName() const { return tableName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> tableName_;
};
class FetchPandasTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 4;
  static std::shared_ptr<FetchPandasTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name);
  FetchPandasTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name);
  FetchPandasTable(const FetchPandasTable &other) = delete;
  FetchPandasTable &operator=(const FetchPandasTable &other) = delete;
  ~FetchPandasTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> name_;
};
class IntradayTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 5;
  static std::shared_ptr<IntradayTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName, std::shared_ptr<std::string> internalPartitionValue, bool live);
  IntradayTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName, std::shared_ptr<std::string> internalPartitionValue, bool live);
  IntradayTable(const IntradayTable &other) = delete;
  IntradayTable &operator=(const IntradayTable &other) = delete;
  ~IntradayTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &nameSpace() const { return nameSpace_; }
  const std::shared_ptr<std::string> &tableName() const { return tableName_; }
  const std::shared_ptr<std::string> &internalPartitionValue() const { return internalPartitionValue_; }
  bool live() const { return live_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> nameSpace_;
  std::shared_ptr<std::string> tableName_;
  std::shared_ptr<std::string> internalPartitionValue_;
  bool live_;
};
class GetIntradayPartitionsAsTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 6;
  static std::shared_ptr<GetIntradayPartitionsAsTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> name);
  GetIntradayPartitionsAsTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> name);
  GetIntradayPartitionsAsTable(const GetIntradayPartitionsAsTable &other) = delete;
  GetIntradayPartitionsAsTable &operator=(const GetIntradayPartitionsAsTable &other) = delete;
  ~GetIntradayPartitionsAsTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &nameSpace() const { return nameSpace_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> nameSpace_;
  std::shared_ptr<std::string> name_;
};
class HistoricalTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 7;
  static std::shared_ptr<HistoricalTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName);
  HistoricalTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName);
  HistoricalTable(const HistoricalTable &other) = delete;
  HistoricalTable &operator=(const HistoricalTable &other) = delete;
  ~HistoricalTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &nameSpace() const { return nameSpace_; }
  const std::shared_ptr<std::string> &tableName() const { return tableName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> nameSpace_;
  std::shared_ptr<std::string> tableName_;
};
class TimeTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 8;
  static std::shared_ptr<TimeTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t startTimeNanos, int64_t periodNanos);
  TimeTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t startTimeNanos, int64_t periodNanos);
  TimeTable(const TimeTable &other) = delete;
  TimeTable &operator=(const TimeTable &other) = delete;
  ~TimeTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  int64_t startTimeNanos() const { return startTimeNanos_; }
  int64_t periodNanos() const { return periodNanos_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  int64_t startTimeNanos_;
  int64_t periodNanos_;
};
class EmptyTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 9;
  static std::shared_ptr<EmptyTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t size, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes);
  EmptyTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, int64_t size, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes);
  EmptyTable(const EmptyTable &other) = delete;
  EmptyTable &operator=(const EmptyTable &other) = delete;
  ~EmptyTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  int64_t size() const { return size_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnNames() const { return columnNames_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnTypes() const { return columnTypes_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  int64_t size_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes_;
};
class NewTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 10;
  static std::shared_ptr<NewTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> columnHolders);
  NewTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> columnHolders);
  NewTable(const NewTable &other) = delete;
  NewTable &operator=(const NewTable &other) = delete;
  ~NewTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> &columnHolders() const { return columnHolders_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> columnHolders_;
};
class MergeTables final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 11;
  static std::shared_ptr<MergeTables> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> inputTableHandles, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> keyColumn);
  MergeTables(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> inputTableHandles, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> keyColumn);
  MergeTables(const MergeTables &other) = delete;
  MergeTables &operator=(const MergeTables &other) = delete;
  ~MergeTables() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> &inputTableHandles() const { return inputTableHandles_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::string> &keyColumn() const { return keyColumn_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> inputTableHandles_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::string> keyColumn_;
};
class BindTableToVariable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 12;
  static std::shared_ptr<BindTableToVariable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> scriptHandle);
  BindTableToVariable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> scriptHandle);
  BindTableToVariable(const BindTableToVariable &other) = delete;
  BindTableToVariable &operator=(const BindTableToVariable &other) = delete;
  ~BindTableToVariable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &scriptHandle() const { return scriptHandle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> name_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> scriptHandle_;
};
class FetchScriptTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 13;
  static std::shared_ptr<FetchScriptTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> tableName);
  FetchScriptTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> tableName);
  FetchScriptTable(const FetchScriptTable &other) = delete;
  FetchScriptTable &operator=(const FetchScriptTable &other) = delete;
  ~FetchScriptTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &script() const { return script_; }
  const std::shared_ptr<std::string> &tableName() const { return tableName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script_;
  std::shared_ptr<std::string> tableName_;
};
class FetchPandasScriptTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 14;
  static std::shared_ptr<FetchPandasScriptTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> name);
  FetchPandasScriptTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> name);
  FetchPandasScriptTable(const FetchPandasScriptTable &other) = delete;
  FetchPandasScriptTable &operator=(const FetchPandasScriptTable &other) = delete;
  ~FetchPandasScriptTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &script() const { return script_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script_;
  std::shared_ptr<std::string> name_;
};
class FetchInputTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 15;
  static std::shared_ptr<FetchInputTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  FetchInputTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  FetchInputTable(const FetchInputTable &other) = delete;
  FetchInputTable &operator=(const FetchInputTable &other) = delete;
  ~FetchInputTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InputTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
};
class AddToInputTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 16;
  static std::shared_ptr<AddToInputTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableRequest> request);
  AddToInputTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableRequest> request);
  AddToInputTable(const AddToInputTable &other) = delete;
  AddToInputTable &operator=(const AddToInputTable &other) = delete;
  ~AddToInputTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableResponse correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableRequest> &request() const { return request_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::requests::AddToInputTableRequest> request_;
};
class Release final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 17;
  static std::shared_ptr<Release> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  Release(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  Release(const Release &other) = delete;
  Release &operator=(const Release &other) = delete;
  ~Release() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
};
class Subscribe final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 18;
  static std::shared_ptr<Subscribe> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, bool isViewport);
  Subscribe(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, bool isViewport);
  Subscribe(const Subscribe &other) = delete;
  Subscribe &operator=(const Subscribe &other) = delete;
  ~Subscribe() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> &columns() const { return columns_; }
  bool isViewport() const { return isViewport_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns_;
  bool isViewport_;
};
class UpdateSubscription final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 19;
  static std::shared_ptr<UpdateSubscription> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> viewports);
  UpdateSubscription(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> viewports);
  UpdateSubscription(const UpdateSubscription &other) = delete;
  UpdateSubscription &operator=(const UpdateSubscription &other) = delete;
  ~UpdateSubscription() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &table() const { return table_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> &viewports() const { return viewports_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> viewports_;
};
class Unsubscribe final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 20;
  static std::shared_ptr<Unsubscribe> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table);
  Unsubscribe(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table);
  Unsubscribe(const Unsubscribe &other) = delete;
  Unsubscribe &operator=(const Unsubscribe &other) = delete;
  ~Unsubscribe() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &table() const { return table_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table_;
};
class ConstructSnapshotQuery final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 21;
  static std::shared_ptr<ConstructSnapshotQuery> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns);
  ConstructSnapshotQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns);
  ConstructSnapshotQuery(const ConstructSnapshotQuery &other) = delete;
  ConstructSnapshotQuery &operator=(const ConstructSnapshotQuery &other) = delete;
  ~ConstructSnapshotQuery() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &table() const { return table_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &rows() const { return rows_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> &columns() const { return columns_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns_;
};
class FetchTableMap final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 22;
  static std::shared_ptr<FetchTableMap> create(std::shared_ptr<std::string> tableMapName);
  FetchTableMap(Private, std::shared_ptr<std::string> tableMapName);
  FetchTableMap(const FetchTableMap &other) = delete;
  FetchTableMap &operator=(const FetchTableMap &other) = delete;
  ~FetchTableMap() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapDeclaration correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &tableMapName() const { return tableMapName_; }
private:
  std::shared_ptr<std::string> tableMapName_;
};
class GetTableMapKeys final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 23;
  static std::shared_ptr<GetTableMapKeys> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle);
  GetTableMapKeys(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle);
  GetTableMapKeys(const GetTableMapKeys &other) = delete;
  GetTableMapKeys &operator=(const GetTableMapKeys &other) = delete;
  ~GetTableMapKeys() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle_;
};
class GetTableMapStringEntry final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 24;
  static std::shared_ptr<GetTableMapStringEntry> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::string> key);
  GetTableMapStringEntry(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::string> key);
  GetTableMapStringEntry(const GetTableMapStringEntry &other) = delete;
  GetTableMapStringEntry &operator=(const GetTableMapStringEntry &other) = delete;
  ~GetTableMapStringEntry() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &tableMapHandle() const { return tableMapHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &tableHandle() const { return tableHandle_; }
  const std::shared_ptr<std::string> &key() const { return key_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle_;
  std::shared_ptr<std::string> key_;
};
class GetTableMapStringArrayEntry final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 25;
  static std::shared_ptr<GetTableMapStringArrayEntry> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key);
  GetTableMapStringArrayEntry(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key);
  GetTableMapStringArrayEntry(const GetTableMapStringArrayEntry &other) = delete;
  GetTableMapStringArrayEntry &operator=(const GetTableMapStringArrayEntry &other) = delete;
  ~GetTableMapStringArrayEntry() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &tableMapHandle() const { return tableMapHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &tableHandle() const { return tableHandle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &key() const { return key_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key_;
};
class GetMergedTableMap final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 26;
  static std::shared_ptr<GetMergedTableMap> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle);
  GetMergedTableMap(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle);
  GetMergedTableMap(const GetMergedTableMap &other) = delete;
  GetMergedTableMap &operator=(const GetMergedTableMap &other) = delete;
  ~GetMergedTableMap() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &tableMapHandle() const { return tableMapHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &tableHandle() const { return tableHandle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle_;
};
class ReleaseTableMap final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 27;
  static std::shared_ptr<ReleaseTableMap> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle);
  ReleaseTableMap(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle);
  ReleaseTableMap(const ReleaseTableMap &other) = delete;
  ReleaseTableMap &operator=(const ReleaseTableMap &other) = delete;
  ~ReleaseTableMap() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &tableMapHandle() const { return tableMapHandle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> tableMapHandle_;
};
class ByExternal final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 28;
  static std::shared_ptr<ByExternal> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, bool dropKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys);
  ByExternal(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle, bool dropKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys);
  ByExternal(const ByExternal &other) = delete;
  ByExternal &operator=(const ByExternal &other) = delete;
  ~ByExternal() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapDeclaration correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &tableHandle() const { return tableHandle_; }
  bool dropKeys() const { return dropKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &keys() const { return keys_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> tableHandle_;
  bool dropKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys_;
};
class RequestMetrics final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 29;
  static std::shared_ptr<RequestMetrics> create(int32_t clientId, bool enable);
  RequestMetrics(Private, int32_t clientId, bool enable);
  RequestMetrics(const RequestMetrics &other) = delete;
  RequestMetrics &operator=(const RequestMetrics &other) = delete;
  ~RequestMetrics() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  int32_t clientId() const { return clientId_; }
  bool enable() const { return enable_; }
private:
  int32_t clientId_;
  bool enable_;
};
class Join final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 30;
  static std::shared_ptr<Join> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor> joinDescriptor, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle);
  Join(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor> joinDescriptor, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle);
  Join(const Join &other) = delete;
  Join &operator=(const Join &other) = delete;
  ~Join() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor> &joinDescriptor() const { return joinDescriptor_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::JoinDescriptor> joinDescriptor_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
};
class Batch final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 31;
  static std::shared_ptr<Batch> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest> request);
  Batch(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest> request);
  Batch(const Batch &other) = delete;
  Batch &operator=(const Batch &other) = delete;
  ~Batch() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableResponse correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest> &request() const { return request_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::BatchTableRequest> request_;
};
class SelectDistinct final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 32;
  static std::shared_ptr<SelectDistinct> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames);
  SelectDistinct(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames);
  SelectDistinct(const SelectDistinct &other) = delete;
  SelectDistinct &operator=(const SelectDistinct &other) = delete;
  ~SelectDistinct() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnNames() const { return columnNames_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnNames_;
};
class ComboAggregate final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 33;
  static std::shared_ptr<ComboAggregate> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor> comboAggregateDescriptor);
  ComboAggregate(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor> comboAggregateDescriptor);
  ComboAggregate(const ComboAggregate &other) = delete;
  ComboAggregate &operator=(const ComboAggregate &other) = delete;
  ~ComboAggregate() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor> &comboAggregateDescriptor() const { return comboAggregateDescriptor_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::ComboAggregateDescriptor> comboAggregateDescriptor_;
};
class Update final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 34;
  static std::shared_ptr<Update> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs);
  Update(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs);
  Update(const Update &other) = delete;
  Update &operator=(const Update &other) = delete;
  ~Update() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnSpecs() const { return columnSpecs_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs_;
};
class LazyUpdate final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 35;
  static std::shared_ptr<LazyUpdate> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs);
  LazyUpdate(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs);
  LazyUpdate(const LazyUpdate &other) = delete;
  LazyUpdate &operator=(const LazyUpdate &other) = delete;
  ~LazyUpdate() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnSpecs() const { return columnSpecs_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs_;
};
class Select final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 36;
  static std::shared_ptr<Select> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs);
  Select(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs);
  Select(const Select &other) = delete;
  Select &operator=(const Select &other) = delete;
  ~Select() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnSpecs() const { return columnSpecs_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnSpecs_;
};
class Ungroup final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 37;
  static std::shared_ptr<Ungroup> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool nullFill, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToUngroup);
  Ungroup(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool nullFill, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToUngroup);
  Ungroup(const Ungroup &other) = delete;
  Ungroup &operator=(const Ungroup &other) = delete;
  ~Ungroup() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  bool nullFill() const { return nullFill_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnsToUngroup() const { return columnsToUngroup_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  bool nullFill_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToUngroup_;
};
class HeadBy final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 38;
  static std::shared_ptr<HeadBy> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs);
  HeadBy(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs);
  HeadBy(const HeadBy &other) = delete;
  HeadBy &operator=(const HeadBy &other) = delete;
  ~HeadBy() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  int64_t nRows() const { return nRows_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &groupByColumnSpecs() const { return groupByColumnSpecs_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  int64_t nRows_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs_;
};
class TailBy final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 39;
  static std::shared_ptr<TailBy> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs);
  TailBy(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, int64_t nRows, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs);
  TailBy(const TailBy &other) = delete;
  TailBy &operator=(const TailBy &other) = delete;
  ~TailBy() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &inputTableHandle() const { return inputTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  int64_t nRows() const { return nRows_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &groupByColumnSpecs() const { return groupByColumnSpecs_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> inputTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  int64_t nRows_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumnSpecs_;
};
class Pong final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 40;
  static std::shared_ptr<Pong> create();
  explicit Pong(Private);
  Pong(const Pong &other) = delete;
  Pong &operator=(const Pong &other) = delete;
  ~Pong() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class FetchTotalsTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 41;
  static std::shared_ptr<FetchTotalsTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> directive, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns);
  FetchTotalsTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> directive, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns);
  FetchTotalsTable(const FetchTotalsTable &other) = delete;
  FetchTotalsTable &operator=(const FetchTotalsTable &other) = delete;
  ~FetchTotalsTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::string> &directive() const { return directive_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columns() const { return columns_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::string> directive_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns_;
};
class FetchTableAttributeAsTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 42;
  static std::shared_ptr<FetchTableAttributeAsTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> attributeName);
  FetchTableAttributeAsTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> attributeName);
  FetchTableAttributeAsTable(const FetchTableAttributeAsTable &other) = delete;
  FetchTableAttributeAsTable &operator=(const FetchTableAttributeAsTable &other) = delete;
  ~FetchTableAttributeAsTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::string> &attributeName() const { return attributeName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::string> attributeName_;
};
class Rollup final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 43;
  static std::shared_ptr<Rollup> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> totalsConfig, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::string> byStrategy, bool includeConstituents);
  Rollup(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> totalsConfig, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::string> byStrategy, bool includeConstituents);
  Rollup(const Rollup &other) = delete;
  Rollup &operator=(const Rollup &other) = delete;
  ~Rollup() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::string> &totalsConfig() const { return totalsConfig_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columns() const { return columns_; }
  const std::shared_ptr<std::string> &byStrategy() const { return byStrategy_; }
  bool includeConstituents() const { return includeConstituents_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::string> totalsConfig_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns_;
  std::shared_ptr<std::string> byStrategy_;
  bool includeConstituents_;
};
class TreeTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 44;
  static std::shared_ptr<TreeTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> idColumn, std::shared_ptr<std::string> parentColumn, std::shared_ptr<std::string> byStrategy, bool promoteOrphansToRoot);
  TreeTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, std::shared_ptr<std::string> idColumn, std::shared_ptr<std::string> parentColumn, std::shared_ptr<std::string> byStrategy, bool promoteOrphansToRoot);
  TreeTable(const TreeTable &other) = delete;
  TreeTable &operator=(const TreeTable &other) = delete;
  ~TreeTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  const std::shared_ptr<std::string> &idColumn() const { return idColumn_; }
  const std::shared_ptr<std::string> &parentColumn() const { return parentColumn_; }
  const std::shared_ptr<std::string> &byStrategy() const { return byStrategy_; }
  bool promoteOrphansToRoot() const { return promoteOrphansToRoot_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  std::shared_ptr<std::string> idColumn_;
  std::shared_ptr<std::string> parentColumn_;
  std::shared_ptr<std::string> byStrategy_;
  bool promoteOrphansToRoot_;
};
class Snapshot final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 45;
  static std::shared_ptr<Snapshot> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool doInitialSnapshot, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns);
  Snapshot(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle, bool doInitialSnapshot, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns);
  Snapshot(const Snapshot &other) = delete;
  Snapshot &operator=(const Snapshot &other) = delete;
  ~Snapshot() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &leftTableHandle() const { return leftTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &rightTableHandle() const { return rightTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &resultHandle() const { return resultHandle_; }
  bool doInitialSnapshot() const { return doInitialSnapshot_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &stampColumns() const { return stampColumns_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> resultHandle_;
  bool doInitialSnapshot_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> stampColumns_;
};
class TreeSnapshotQuery final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 46;
  static std::shared_ptr<TreeSnapshotQuery> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableRequest> request);
  TreeSnapshotQuery(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableRequest> request);
  TreeSnapshotQuery(const TreeSnapshotQuery &other) = delete;
  TreeSnapshotQuery &operator=(const TreeSnapshotQuery &other) = delete;
  ~TreeSnapshotQuery() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableResult correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableRequest> &request() const { return request_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TreeTableRequest> request_;
};
class FetchFigure final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 47;
  static std::shared_ptr<FetchFigure> create(std::shared_ptr<std::string> figureName);
  FetchFigure(Private, std::shared_ptr<std::string> figureName);
  FetchFigure(const FetchFigure &other) = delete;
  FetchFigure &operator=(const FetchFigure &other) = delete;
  ~FetchFigure() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::FigureDescriptor correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::string> &figureName() const { return figureName_; }
private:
  std::shared_ptr<std::string> figureName_;
};
class FetchScriptFigure final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 48;
  static std::shared_ptr<FetchScriptFigure> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> figureName);
  FetchScriptFigure(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script, std::shared_ptr<std::string> figureName);
  FetchScriptFigure(const FetchScriptFigure &other) = delete;
  FetchScriptFigure &operator=(const FetchScriptFigure &other) = delete;
  ~FetchScriptFigure() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::FigureDescriptor correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &script() const { return script_; }
  const std::shared_ptr<std::string> &figureName() const { return figureName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> script_;
  std::shared_ptr<std::string> figureName_;
};
class FinishFigureFetch final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 49;
  static std::shared_ptr<FinishFigureFetch> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> handles, std::shared_ptr<std::vector<int32_t>> serverIds);
  FinishFigureFetch(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> handles, std::shared_ptr<std::vector<int32_t>> serverIds);
  FinishFigureFetch(const FinishFigureFetch &other) = delete;
  FinishFigureFetch &operator=(const FinishFigureFetch &other) = delete;
  ~FinishFigureFetch() final;
  typedef std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> &handles() const { return handles_; }
  const std::shared_ptr<std::vector<int32_t>> &serverIds() const { return serverIds_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> handles_;
  std::shared_ptr<std::vector<int32_t>> serverIds_;
};
class DownsampleTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 50;
  static std::shared_ptr<DownsampleTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> result, std::shared_ptr<std::string> dateCol, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> valueCols, int32_t pxCount, std::shared_ptr<std::vector<int64_t>> zoomRange);
  DownsampleTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> result, std::shared_ptr<std::string> dateCol, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> valueCols, int32_t pxCount, std::shared_ptr<std::vector<int64_t>> zoomRange);
  DownsampleTable(const DownsampleTable &other) = delete;
  DownsampleTable &operator=(const DownsampleTable &other) = delete;
  ~DownsampleTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &result() const { return result_; }
  const std::shared_ptr<std::string> &dateCol() const { return dateCol_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &valueCols() const { return valueCols_; }
  int32_t pxCount() const { return pxCount_; }
  const std::shared_ptr<std::vector<int64_t>> &zoomRange() const { return zoomRange_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> result_;
  std::shared_ptr<std::string> dateCol_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> valueCols_;
  int32_t pxCount_;
  std::shared_ptr<std::vector<int64_t>> zoomRange_;
};
class GetColumnStatisticsForTable final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 51;
  static std::shared_ptr<GetColumnStatisticsForTable> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> columnName);
  GetColumnStatisticsForTable(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::string> columnName);
  GetColumnStatisticsForTable(const GetColumnStatisticsForTable &other) = delete;
  GetColumnStatisticsForTable &operator=(const GetColumnStatisticsForTable &other) = delete;
  ~GetColumnStatisticsForTable() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnStatistics correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &columnName() const { return columnName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::string> columnName_;
};
class ExecuteCommand final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 52;
  static std::shared_ptr<ExecuteCommand> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle, std::shared_ptr<std::string> code);
  ExecuteCommand(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle, std::shared_ptr<std::string> code);
  ExecuteCommand(const ExecuteCommand &other) = delete;
  ExecuteCommand &operator=(const ExecuteCommand &other) = delete;
  ~ExecuteCommand() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::CommandResult correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &code() const { return code_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle_;
  std::shared_ptr<std::string> code_;
};
class CancelCommand final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 53;
  static std::shared_ptr<CancelCommand> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle);
  CancelCommand(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle);
  CancelCommand(const CancelCommand &other) = delete;
  CancelCommand &operator=(const CancelCommand &other) = delete;
  ~CancelCommand() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ExecutionHandle> handle_;
};
class StartConsole final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 54;
  static std::shared_ptr<StartConsole> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType config);
  StartConsole(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType config);
  StartConsole(const StartConsole &other) = delete;
  StartConsole &operator=(const StartConsole &other) = delete;
  ~StartConsole() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleConnectionResult correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType config() const { return config_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType config_;
};
class StopConsole final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 55;
  static std::shared_ptr<StopConsole> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle);
  StopConsole(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle);
  StopConsole(const StopConsole &other) = delete;
  StopConsole &operator=(const StopConsole &other) = delete;
  ~StopConsole() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
};
class OpenDocument final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 56;
  static std::shared_ptr<OpenDocument> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidOpenTextDocumentParams> params);
  OpenDocument(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidOpenTextDocumentParams> params);
  OpenDocument(const OpenDocument &other) = delete;
  OpenDocument &operator=(const OpenDocument &other) = delete;
  ~OpenDocument() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidOpenTextDocumentParams> &params() const { return params_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidOpenTextDocumentParams> params_;
};
class ChangeDocument final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 57;
  static std::shared_ptr<ChangeDocument> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidChangeTextDocumentParams> params);
  ChangeDocument(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidChangeTextDocumentParams> params);
  ChangeDocument(const ChangeDocument &other) = delete;
  ChangeDocument &operator=(const ChangeDocument &other) = delete;
  ~ChangeDocument() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidChangeTextDocumentParams> &params() const { return params_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidChangeTextDocumentParams> params_;
};
class GetCompletionItems final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 58;
  static std::shared_ptr<GetCompletionItems> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams> params);
  GetCompletionItems(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams> params);
  GetCompletionItems(const GetCompletionItems &other) = delete;
  GetCompletionItems &operator=(const GetCompletionItems &other) = delete;
  ~GetCompletionItems() final;
  typedef std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionItem>> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams> &params() const { return params_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams> params_;
};
class CloseDocument final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 59;
  static std::shared_ptr<CloseDocument> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidCloseTextDocumentParams> params);
  CloseDocument(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidCloseTextDocumentParams> params);
  CloseDocument(const CloseDocument &other) = delete;
  CloseDocument &operator=(const CloseDocument &other) = delete;
  ~CloseDocument() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidCloseTextDocumentParams> &params() const { return params_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DidCloseTextDocumentParams> params_;
};
class SubscribeToLogs final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 60;
  static std::shared_ptr<SubscribeToLogs> create();
  explicit SubscribeToLogs(Private);
  SubscribeToLogs(const SubscribeToLogs &other) = delete;
  SubscribeToLogs &operator=(const SubscribeToLogs &other) = delete;
  ~SubscribeToLogs() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class UnsubscribeToLogs final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 61;
  static std::shared_ptr<UnsubscribeToLogs> create();
  explicit UnsubscribeToLogs(Private);
  UnsubscribeToLogs(const UnsubscribeToLogs &other) = delete;
  UnsubscribeToLogs &operator=(const UnsubscribeToLogs &other) = delete;
  ~UnsubscribeToLogs() final;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
private:
};
class CreateWorkspaceData final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 62;
  static std::shared_ptr<CreateWorkspaceData> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data);
  CreateWorkspaceData(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data);
  CreateWorkspaceData(const CreateWorkspaceData &other) = delete;
  CreateWorkspaceData &operator=(const CreateWorkspaceData &other) = delete;
  ~CreateWorkspaceData() final;
  typedef std::shared_ptr<std::string> correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> &data() const { return data_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data_;
};
class SaveWorkspaceData final : public deephaven::openAPI::core::remoting::Request {
  struct Private {};
public:
  static constexpr int32_t requestId = 63;
  static std::shared_ptr<SaveWorkspaceData> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data);
  SaveWorkspaceData(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data);
  SaveWorkspaceData(const SaveWorkspaceData &other) = delete;
  SaveWorkspaceData &operator=(const SaveWorkspaceData &other) = delete;
  ~SaveWorkspaceData() final;
  typedef deephaven::openAPI::lowlevel::remoting::generated::java::lang::Void correspondingResponseType_t;
  void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s, int32_t callbackId) const final;
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> &data() const { return data_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::WorkspaceData> data_;
};
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
