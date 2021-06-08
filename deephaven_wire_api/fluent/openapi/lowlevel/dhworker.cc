#include "lowlevel/dhworker.h"
#include "lowlevel/generated/dhworker_notifications.h"
#include "lowlevel/generated/dhworker_requests.h"
#include "lowlevel/generated/shared_objects.h"
#include "utility/executor.h"

using deephaven::openAPI::core::remoting::util::Deserializer;
using deephaven::openAPI::core::remoting::Notification;
using deephaven::openAPI::core::remoting::Server;
using deephaven::openAPI::lowlevel::remoting::generated::DHWorkerNotificationVisitor;
using deephaven::openAPI::lowlevel::remoting::generated::deserializeDHWorkerNotification;
using deephaven::openAPI::lowlevel::remoting::generated::dynamicDeserializerNames;
using deephaven::openAPI::lowlevel::remoting::generated::dynamicDeserializerMethods;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ConnectionSuccess;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableCreationMessage;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::HandleResolved;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::InitialSnapshot;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::IncrementalUpdates;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringKeyAdded;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::TableMapStringArrayKeyAdded;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Register;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ReportMetrics;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessage;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableUpdateMessageError;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::ExportedTableCreationMessage;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::Ping;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::worker::SendLog;
using deephaven::openAPI::lowlevel::remoting::generated::WorkerRequestHash;
using deephaven::openAPI::lowlevel::remoting::generated::WorkerSharedHash;
using deephaven::openAPI::core::remoting::Notification;
using deephaven::openAPI::core::remoting::Server;
using deephaven::openAPI::utility::Executor;
using deephaven::openAPI::utility::streamf;
using deephaven::openAPI::utility::stringf;


namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {

std::shared_ptr<DHWorker> DHWorker::createFromUrl(const boost::string_view url, int32_t clientId,
    std::shared_ptr<Executor> executor) {
  auto urlToUse = stringf("%o?checksum=%o%o", url,
      WorkerRequestHash::hash, WorkerSharedHash::hash);

  static_assert(dynamicDeserializerNames.size() == dynamicDeserializerMethods.size(),
      "programming error");
  return std::make_shared<DHWorker>(Private(), nullptr,
      nullptr,
      clientId, std::move(executor));
}

std::shared_ptr<DHWorker> DHWorker::createFromHandshake(std::string metadataHeader,
    std::string sessionToken) {
  streamf(std::cout, "IT'S A PARTY %o and %o\n", metadataHeader, sessionToken);
  return nullptr;
}

DHWorker::DHWorker(Private, std::shared_ptr<Server> server,
    std::shared_ptr<internal::WorkerNotificationHandler> notificationHandler, int32_t clientId,
    std::shared_ptr<Executor> executor) :
    server_(std::move(server)), notificationHandler_(std::move(notificationHandler)),
    clientId_(clientId), executor_(std::move(executor)) {}
DHWorker::~DHWorker() = default;

void DHWorker::registerClientAsync(int32_t clientId, std::shared_ptr<std::string> serviceId,
    int64_t seedTime, std::shared_ptr<ConnectToken> connectToken,
    std::shared_ptr<SFCallback<std::shared_ptr<ConnectionSuccess>>> callback) {
  auto req = Register::create(clientId, std::move(serviceId), seedTime, std::move(connectToken));
  invoke(std::move(req), std::move(callback));
}

void DHWorker::addListener(std::shared_ptr<DHWorkerAPIListener> listener) {
  // notificationHandler_->addListener(std::move(listener));
}

void DHWorker::removeListener(const std::shared_ptr<DHWorkerAPIListener> &listener) {
  // notificationHandler_->removeListener(listener);
}
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
