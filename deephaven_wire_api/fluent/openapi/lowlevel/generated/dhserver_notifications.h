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
struct ServerNotificationHash {
  static const boost::string_view hash;
};
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace primary {
class QueryAdded;
class QueryModified;
class QueryRemoved;
class ConsoleDeath;
class Ids6976;
}  // namespace primary
}  // namespace shared
}  // namespace web
}  // namespace iris
}  // namespace illumon
}  // namespace com
class DHServerNotificationVisitor {
public:
  virtual ~DHServerNotificationVisitor() = default;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryAdded *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryModified *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryRemoved *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::ConsoleDeath *item) = 0;
  virtual void visit(const deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::Ids6976 *item) = 0;
};
class DHServerNotification : public deephaven::openAPI::core::remoting::Notification {
public:
  virtual void acceptVisitor(DHServerNotificationVisitor *visitor) = 0;
};
std::shared_ptr<DHServerNotification> deserializeDHServerNotification(deephaven::openAPI::core::remoting::util::Deserializer *d, int32_t notificationId);
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace primary {
class QueryAdded final : public DHServerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 0;
  static std::shared_ptr<QueryAdded> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config);
  QueryAdded(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config);
  QueryAdded(const QueryAdded &other) = delete;
  QueryAdded &operator=(const QueryAdded &other) = delete;
  ~QueryAdded() final;
  static std::shared_ptr<QueryAdded> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHServerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> &config() const { return config_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config_;
};
class QueryModified final : public DHServerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 1;
  static std::shared_ptr<QueryModified> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config);
  QueryModified(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config);
  QueryModified(const QueryModified &other) = delete;
  QueryModified &operator=(const QueryModified &other) = delete;
  ~QueryModified() final;
  static std::shared_ptr<QueryModified> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHServerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> &config() const { return config_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config_;
};
class QueryRemoved final : public DHServerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 2;
  static std::shared_ptr<QueryRemoved> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config);
  QueryRemoved(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config);
  QueryRemoved(const QueryRemoved &other) = delete;
  QueryRemoved &operator=(const QueryRemoved &other) = delete;
  ~QueryRemoved() final;
  static std::shared_ptr<QueryRemoved> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHServerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> &config() const { return config_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config_;
};
class ConsoleDeath final : public DHServerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 3;
  static std::shared_ptr<ConsoleDeath> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id);
  ConsoleDeath(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id);
  ConsoleDeath(const ConsoleDeath &other) = delete;
  ConsoleDeath &operator=(const ConsoleDeath &other) = delete;
  ~ConsoleDeath() final;
  static std::shared_ptr<ConsoleDeath> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHServerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> &id() const { return id_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id_;
};
class Ids6976 final : public DHServerNotification {
  struct Private {};
public:
  static constexpr int32_t notificationId = 4;
  static std::shared_ptr<Ids6976> create(std::shared_ptr<std::vector<char16_t>> bugMitigation1, std::shared_ptr<std::vector<int8_t>> bugMitigation2);
  Ids6976(Private, std::shared_ptr<std::vector<char16_t>> bugMitigation1, std::shared_ptr<std::vector<int8_t>> bugMitigation2);
  Ids6976(const Ids6976 &other) = delete;
  Ids6976 &operator=(const Ids6976 &other) = delete;
  ~Ids6976() final;
  static std::shared_ptr<Ids6976> deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(DHServerNotificationVisitor *visitor) final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<char16_t>> &bugMitigation1() const { return bugMitigation1_; }
  const std::shared_ptr<std::vector<int8_t>> &bugMitigation2() const { return bugMitigation2_; }
private:
  std::shared_ptr<std::vector<char16_t>> bugMitigation1_;
  std::shared_ptr<std::vector<int8_t>> bugMitigation2_;
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
