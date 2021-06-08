#include "lowlevel/generated/dhserver_notifications.h"
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
const boost::string_view ServerNotificationHash::hash = "4c2f9395991d663dd41df95061e5974a11edddff";
std::shared_ptr<DHServerNotification> deserializeDHServerNotification(deephaven::openAPI::core::remoting::util::Deserializer *d, int32_t notificationId) {
  switch (notificationId) {
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryAdded::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryAdded::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryModified::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryModified::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryRemoved::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::QueryRemoved::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::ConsoleDeath::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::ConsoleDeath::deserializeNotification(d);
    }
    case deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::Ids6976::notificationId: {
      return deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::primary::Ids6976::deserializeNotification(d);
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
namespace primary {
std::shared_ptr<QueryAdded> QueryAdded::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config) {
  return std::make_shared<QueryAdded>(Private(), std::move(config));
}
QueryAdded::QueryAdded(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config)
  : config_(std::move(config))
  {
}
QueryAdded::~QueryAdded() = default;
std::shared_ptr<QueryAdded> QueryAdded::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&config);
  return QueryAdded::create(std::move(config));
}
std::shared_ptr<QueryModified> QueryModified::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config) {
  return std::make_shared<QueryModified>(Private(), std::move(config));
}
QueryModified::QueryModified(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config)
  : config_(std::move(config))
  {
}
QueryModified::~QueryModified() = default;
std::shared_ptr<QueryModified> QueryModified::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&config);
  return QueryModified::create(std::move(config));
}
std::shared_ptr<QueryRemoved> QueryRemoved::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config) {
  return std::make_shared<QueryRemoved>(Private(), std::move(config));
}
QueryRemoved::QueryRemoved(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config)
  : config_(std::move(config))
  {
}
QueryRemoved::~QueryRemoved() = default;
std::shared_ptr<QueryRemoved> QueryRemoved::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::QueryConfig> config;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&config);
  return QueryRemoved::create(std::move(config));
}
std::shared_ptr<ConsoleDeath> ConsoleDeath::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id) {
  return std::make_shared<ConsoleDeath>(Private(), std::move(id));
}
ConsoleDeath::ConsoleDeath(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id)
  : id_(std::move(id))
  {
}
ConsoleDeath::~ConsoleDeath() = default;
std::shared_ptr<ConsoleDeath> ConsoleDeath::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId> id;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&id);
  return ConsoleDeath::create(std::move(id));
}
std::shared_ptr<Ids6976> Ids6976::create(std::shared_ptr<std::vector<char16_t>> bugMitigation1, std::shared_ptr<std::vector<int8_t>> bugMitigation2) {
  return std::make_shared<Ids6976>(Private(), std::move(bugMitigation1), std::move(bugMitigation2));
}
Ids6976::Ids6976(Private, std::shared_ptr<std::vector<char16_t>> bugMitigation1, std::shared_ptr<std::vector<int8_t>> bugMitigation2)
  : bugMitigation1_(std::move(bugMitigation1)), bugMitigation2_(std::move(bugMitigation2))
  {
}
Ids6976::~Ids6976() = default;
std::shared_ptr<Ids6976> Ids6976::deserializeNotification(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  std::shared_ptr<std::vector<char16_t>> bugMitigation1;
  std::shared_ptr<std::vector<int8_t>> bugMitigation2;
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  da.read(&bugMitigation1);
  da.read(&bugMitigation2);
  return Ids6976::create(std::move(bugMitigation1), std::move(bugMitigation2));
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
