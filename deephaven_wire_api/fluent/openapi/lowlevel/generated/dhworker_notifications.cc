#include "lowlevel/generated/dhworker_notifications.h"
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
const boost::string_view WorkerNotificationHash::hash = "-3ccb6ecf0c0bb63021a4e326ced6aa1f0887dd21";
std::shared_ptr<DHWorkerNotification> deserializeDHWorkerNotification(deephaven::openAPI::core::remoting::util::Deserializer *d, int32_t notificationId) {
  switch (notificationId) {
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableCreationMessage::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableCreationMessage::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HandleResolved::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HandleResolved::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::InitialSnapshot::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::InitialSnapshot::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::IncrementalUpdates::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::IncrementalUpdates::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringKeyAdded::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringKeyAdded::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringArrayKeyAdded::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringArrayKeyAdded::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ReportMetrics::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ReportMetrics::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessage::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessage::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessageError::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessageError::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Ping::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Ping::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::SendLog::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::SendLog::deserializeNotification(d);
    }
    default: {
      throw std::runtime_error(deephaven::openAPI::utility::stringf("Unexpected notificationId %o", notificationId));
    }
  }
}
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace worker {
std::shared_ptr<ExportedTableCreationMessage> ExportedTableCreationMessage::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> tableDef) {
  return std::make_shared<ExportedTableCreationMessage>(Private(), std::move(tableDef));
}
ExportedTableCreationMessage::ExportedTableCreationMessage(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> tableDef)
  : tableDef_(std::move(tableDef))
  {
}
ExportedTableCreationMessage::~ExportedTableCreationMessage() = default;
std::shared_ptr<ExportedTableCreationMessage> ExportedTableCreationMessage::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> tableDef;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&tableDef);
  return ExportedTableCreationMessage::create(std::move(tableDef));
}
std::shared_ptr<HandleResolved> HandleResolved::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle) {
  return std::make_shared<HandleResolved>(Private(), std::move(handle));
}
HandleResolved::HandleResolved(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle)
  : handle_(std::move(handle))
  {
}
HandleResolved::~HandleResolved() = default;
std::shared_ptr<HandleResolved> HandleResolved::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&handle);
  return HandleResolved::create(std::move(handle));
}
std::shared_ptr<InitialSnapshot> InitialSnapshot::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> snapshot) {
  return std::make_shared<InitialSnapshot>(Private(), std::move(table), std::move(snapshot));
}
InitialSnapshot::InitialSnapshot(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> snapshot)
  : table_(std::move(table)), snapshot_(std::move(snapshot))
  {
}
InitialSnapshot::~InitialSnapshot() = default;
std::shared_ptr<InitialSnapshot> InitialSnapshot::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> snapshot;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&table);
  da.read(&snapshot);
  return InitialSnapshot::create(std::move(table), std::move(snapshot));
}
std::shared_ptr<IncrementalUpdates> IncrementalUpdates::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> updates) {
  return std::make_shared<IncrementalUpdates>(Private(), std::move(table), std::move(updates));
}
IncrementalUpdates::IncrementalUpdates(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> updates)
  : table_(std::move(table)), updates_(std::move(updates))
  {
}
IncrementalUpdates::~IncrementalUpdates() = default;
std::shared_ptr<IncrementalUpdates> IncrementalUpdates::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> updates;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&table);
  da.read(&updates);
  return IncrementalUpdates::create(std::move(table), std::move(updates));
}
std::shared_ptr<TableMapStringKeyAdded> TableMapStringKeyAdded::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::string> key) {
  return std::make_shared<TableMapStringKeyAdded>(Private(), std::move(handle), std::move(key));
}
TableMapStringKeyAdded::TableMapStringKeyAdded(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::string> key)
  : handle_(std::move(handle)), key_(std::move(key))
  {
}
TableMapStringKeyAdded::~TableMapStringKeyAdded() = default;
std::shared_ptr<TableMapStringKeyAdded> TableMapStringKeyAdded::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle;
  std::shared_ptr<std::string> key;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&handle);
  da.read(&key);
  return TableMapStringKeyAdded::create(std::move(handle), std::move(key));
}
std::shared_ptr<TableMapStringArrayKeyAdded> TableMapStringArrayKeyAdded::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key) {
  return std::make_shared<TableMapStringArrayKeyAdded>(Private(), std::move(handle), std::move(key));
}
TableMapStringArrayKeyAdded::TableMapStringArrayKeyAdded(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key)
  : handle_(std::move(handle)), key_(std::move(key))
  {
}
TableMapStringArrayKeyAdded::~TableMapStringArrayKeyAdded() = default;
std::shared_ptr<TableMapStringArrayKeyAdded> TableMapStringArrayKeyAdded::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&handle);
  da.read(&key);
  return TableMapStringArrayKeyAdded::create(std::move(handle), std::move(key));
}
std::shared_ptr<ReportMetrics> ReportMetrics::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> metrics) {
  return std::make_shared<ReportMetrics>(Private(), std::move(metrics));
}
ReportMetrics::ReportMetrics(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> metrics)
  : metrics_(std::move(metrics))
  {
}
ReportMetrics::~ReportMetrics() = default;
std::shared_ptr<ReportMetrics> ReportMetrics::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> metrics;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&metrics);
  return ReportMetrics::create(std::move(metrics));
}
std::shared_ptr<ExportedTableUpdateMessage> ExportedTableUpdateMessage::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, int64_t size) {
  return std::make_shared<ExportedTableUpdateMessage>(Private(), std::move(clientId), size);
}
ExportedTableUpdateMessage::ExportedTableUpdateMessage(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, int64_t size)
  : clientId_(std::move(clientId)), size_(size)
  {
}
ExportedTableUpdateMessage::~ExportedTableUpdateMessage() = default;
std::shared_ptr<ExportedTableUpdateMessage> ExportedTableUpdateMessage::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId;
  int64_t size;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&clientId);
  da.read(&size);
  return ExportedTableUpdateMessage::create(std::move(clientId), size);
}
std::shared_ptr<ExportedTableUpdateMessageError> ExportedTableUpdateMessageError::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, std::shared_ptr<std::string> errorMessage) {
  return std::make_shared<ExportedTableUpdateMessageError>(Private(), std::move(clientId), std::move(errorMessage));
}
ExportedTableUpdateMessageError::ExportedTableUpdateMessageError(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, std::shared_ptr<std::string> errorMessage)
  : clientId_(std::move(clientId)), errorMessage_(std::move(errorMessage))
  {
}
ExportedTableUpdateMessageError::~ExportedTableUpdateMessageError() = default;
std::shared_ptr<ExportedTableUpdateMessageError> ExportedTableUpdateMessageError::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId;
  std::shared_ptr<std::string> errorMessage;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&clientId);
  da.read(&errorMessage);
  return ExportedTableUpdateMessageError::create(std::move(clientId), std::move(errorMessage));
}
std::shared_ptr<Ping> Ping::create() {
  return std::make_shared<Ping>(Private());
}
Ping::Ping(Private)
  
  {
}
Ping::~Ping() = default;
std::shared_ptr<Ping> Ping::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  return Ping::create();
}
std::shared_ptr<SendLog> SendLog::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> log) {
  return std::make_shared<SendLog>(Private(), std::move(log));
}
SendLog::SendLog(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> log)
  : log_(std::move(log))
  {
}
SendLog::~SendLog() = default;
std::shared_ptr<SendLog> SendLog::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> log;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&log);
  return SendLog::create(std::move(log));
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
