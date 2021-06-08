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
struct WorkerNotificationHash {
  static const boost::string_view hash;
};
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace worker {
class ExportedTableCreationMessage;
class HandleResolved;
class InitialSnapshot;
class IncrementalUpdates;
class TableMapStringKeyAdded;
class TableMapStringArrayKeyAdded;
class ReportMetrics;
class ExportedTableUpdateMessage;
class ExportedTableUpdateMessageError;
class Ping;
class SendLog;
}  // namespace worker
}  // namespace shared
}  // namespace web
}  // namespace iris
}  // namespace illumon
}  // namespace com
class DHWorkerNotificationVisitor {
public:
  virtual ~DHWorkerNotificationVisitor() = default;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableCreationMessage *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HandleResolved *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::InitialSnapshot *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::IncrementalUpdates *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringKeyAdded *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringArrayKeyAdded *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ReportMetrics *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessage *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessageError *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Ping *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::SendLog *item) = 0;
};
class DHWorkerNotification : public deephaven::openAPI::core::remoting::Notification {
public:
  virtual void acceptVisitor(DHWorkerNotificationVisitor *visitor) = 0;
};
std::shared_ptr<DHWorkerNotification> deserializeDHWorkerNotification(deephaven::openAPI::core::remoting::util::Deserializer *d, int32_t notificationId);
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace worker {
class ExportedTableCreationMessage final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 0;
  static std::shared_ptr<ExportedTableCreationMessage> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> tableDef);
  ExportedTableCreationMessage(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> tableDef);
  ExportedTableCreationMessage(const ExportedTableCreationMessage &other) = delete;
  ExportedTableCreationMessage &operator=(const ExportedTableCreationMessage &other) = delete;
  ~ExportedTableCreationMessage() final;
  static std::shared_ptr<ExportedTableCreationMessage> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> &tableDef() const { return tableDef_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition> tableDef_;
};
class HandleResolved final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 1;
  static std::shared_ptr<HandleResolved> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  HandleResolved(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle);
  HandleResolved(const HandleResolved &other) = delete;
  HandleResolved &operator=(const HandleResolved &other) = delete;
  ~HandleResolved() final;
  static std::shared_ptr<HandleResolved> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
};
class InitialSnapshot final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 2;
  static std::shared_ptr<InitialSnapshot> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> snapshot);
  InitialSnapshot(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> snapshot);
  InitialSnapshot(const InitialSnapshot &other) = delete;
  InitialSnapshot &operator=(const InitialSnapshot &other) = delete;
  ~InitialSnapshot() final;
  static std::shared_ptr<InitialSnapshot> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &table() const { return table_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> &snapshot() const { return snapshot_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot> snapshot_;
};
class IncrementalUpdates final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 3;
  static std::shared_ptr<IncrementalUpdates> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> updates);
  IncrementalUpdates(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> updates);
  IncrementalUpdates(const IncrementalUpdates &other) = delete;
  IncrementalUpdates &operator=(const IncrementalUpdates &other) = delete;
  ~IncrementalUpdates() final;
  static std::shared_ptr<IncrementalUpdates> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &table() const { return table_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> &updates() const { return updates_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> table_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates> updates_;
};
class TableMapStringKeyAdded final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 4;
  static std::shared_ptr<TableMapStringKeyAdded> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::string> key);
  TableMapStringKeyAdded(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::string> key);
  TableMapStringKeyAdded(const TableMapStringKeyAdded &other) = delete;
  TableMapStringKeyAdded &operator=(const TableMapStringKeyAdded &other) = delete;
  ~TableMapStringKeyAdded() final;
  static std::shared_ptr<TableMapStringKeyAdded> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::string> &key() const { return key_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle_;
  std::shared_ptr<std::string> key_;
};
class TableMapStringArrayKeyAdded final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 5;
  static std::shared_ptr<TableMapStringArrayKeyAdded> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key);
  TableMapStringArrayKeyAdded(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key);
  TableMapStringArrayKeyAdded(const TableMapStringArrayKeyAdded &other) = delete;
  TableMapStringArrayKeyAdded &operator=(const TableMapStringArrayKeyAdded &other) = delete;
  ~TableMapStringArrayKeyAdded() final;
  static std::shared_ptr<TableMapStringArrayKeyAdded> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &key() const { return key_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> key_;
};
class ReportMetrics final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 6;
  static std::shared_ptr<ReportMetrics> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> metrics);
  ReportMetrics(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> metrics);
  ReportMetrics(const ReportMetrics &other) = delete;
  ReportMetrics &operator=(const ReportMetrics &other) = delete;
  ~ReportMetrics() final;
  static std::shared_ptr<ReportMetrics> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> &metrics() const { return metrics_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> metrics_;
};
class ExportedTableUpdateMessage final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 7;
  static std::shared_ptr<ExportedTableUpdateMessage> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, int64_t size);
  ExportedTableUpdateMessage(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, int64_t size);
  ExportedTableUpdateMessage(const ExportedTableUpdateMessage &other) = delete;
  ExportedTableUpdateMessage &operator=(const ExportedTableUpdateMessage &other) = delete;
  ~ExportedTableUpdateMessage() final;
  static std::shared_ptr<ExportedTableUpdateMessage> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &clientId() const { return clientId_; }
  int64_t size() const { return size_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId_;
  int64_t size_;
};
class ExportedTableUpdateMessageError final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 8;
  static std::shared_ptr<ExportedTableUpdateMessageError> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, std::shared_ptr<std::string> errorMessage);
  ExportedTableUpdateMessageError(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId, std::shared_ptr<std::string> errorMessage);
  ExportedTableUpdateMessageError(const ExportedTableUpdateMessageError &other) = delete;
  ExportedTableUpdateMessageError &operator=(const ExportedTableUpdateMessageError &other) = delete;
  ~ExportedTableUpdateMessageError() final;
  static std::shared_ptr<ExportedTableUpdateMessageError> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &clientId() const { return clientId_; }
  const std::shared_ptr<std::string> &errorMessage() const { return errorMessage_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> clientId_;
  std::shared_ptr<std::string> errorMessage_;
};
class Ping final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 9;
  static std::shared_ptr<Ping> create();
  explicit Ping(Private);
  Ping(const Ping &other) = delete;
  Ping &operator=(const Ping &other) = delete;
  ~Ping() final;
  static std::shared_ptr<Ping> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
private:
};
class SendLog final : public DHWorkerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 10;
  static std::shared_ptr<SendLog> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> log);
  SendLog(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> log);
  SendLog(const SendLog &other) = delete;
  SendLog &operator=(const SendLog &other) = delete;
  ~SendLog() final;
  static std::shared_ptr<SendLog> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHWorkerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> &log() const { return log_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem> log_;
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
