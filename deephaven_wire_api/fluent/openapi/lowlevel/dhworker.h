#pragma once

#include <future>
#include <memory>
#include "core/callbacks.h"
#include "core/server.h"
#include "lowlevel/generated/shared_objects.h"
#include "lowlevel/util/server_callbacks.h"
#include "utility/executor.h"

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {

class DHWorkerAPIListener;

namespace internal {
class WorkerNotificationHandler;
}  // namespace internal

class DHWorker {
  struct Private {};
  typedef deephaven::openAPI::core::remoting::Server Server;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken ConnectToken;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ConnectionSuccess ConnectionSuccess;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition InitialTableDefinition;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle TableHandle;
  typedef deephaven::openAPI::utility::Executor Executor;

  template<typename T>
  using SFCallback = deephaven::openAPI::core::SFCallback<T>;

public:
  static std::shared_ptr<DHWorker> createFromUrl(boost::string_view url, int32_t clientId,
      std::shared_ptr<Executor> executor);
  static std::shared_ptr<DHWorker> createFromHandshake(std::string metadataHeader,
      std::string sessionToken);

  DHWorker(Private, std::shared_ptr<Server> server,
      std::shared_ptr<internal::WorkerNotificationHandler> handler, int32_t clientId,
      std::shared_ptr<Executor> executor);
  DHWorker(const DHWorker &other) = delete;
  DHWorker &operator=(const DHWorker &other) = delete;
  ~DHWorker();

  void registerClientAsync(int32_t clientId, std::shared_ptr<std::string> serverId, int64_t seedTime,
      std::shared_ptr<ConnectToken> connectToken,
      std::shared_ptr<SFCallback<std::shared_ptr<ConnectionSuccess>>> callback);

  void addListener(std::shared_ptr<DHWorkerAPIListener> listener);
  void removeListener(const std::shared_ptr<DHWorkerAPIListener> &listener);

  template<typename REQUEST>
  void invoke(std::shared_ptr<REQUEST> request,
      std::shared_ptr<SFCallback<std::shared_ptr<typename REQUEST::correspondingResponseType_t>>> callback);

  // const std::shared_ptr<Server> &server() const { return server_; }

private:
  std::shared_ptr<Server> server_;
  std::shared_ptr<internal::WorkerNotificationHandler> notificationHandler_;
  const int32_t clientId_;
  std::shared_ptr<Executor> executor_;
};

class DHWorkerAPIListener {
protected:
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition InitialTableDefinition;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle TableHandle;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSnapshot TableSnapshot;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::DeltaUpdates DeltaUpdates;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle TableMapHandle;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog MetricsLog;
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LogItem LogItem;

public:
  virtual ~DHWorkerAPIListener() = default;

  virtual void onExportedTableCreationMessage(const std::shared_ptr<InitialTableDefinition> &itd) = 0;
  virtual void onHandleResolved(const std::shared_ptr<TableHandle> &th) = 0;
  virtual void onInitialSnapshot(const std::shared_ptr<TableHandle> &th,
      const std::shared_ptr<TableSnapshot> &snapshot) = 0;
  virtual void onIncrementalUpdates(const std::shared_ptr<TableHandle> &th,
      const std::shared_ptr<DeltaUpdates> &du) = 0;
  virtual void onTableMapStringKeyAdded(const std::shared_ptr<TableMapHandle> &tmh,
      const std::shared_ptr<std::string> &key) = 0;
  virtual void onTableMapStringArrayKeyAdded(const std::shared_ptr<TableMapHandle> &tmh,
      const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &key) = 0;
  virtual void onReportMetrics(const std::shared_ptr<std::vector<std::shared_ptr<MetricsLog>>> &metrics) = 0;
  virtual void onExportedTableUpdateMessage(const std::shared_ptr<TableHandle> &th, int64_t size) = 0;
  virtual void onExportedTableUpdateMessageError(const std::shared_ptr<TableHandle> &th,
      const std::shared_ptr<std::string> &errorMessage) = 0;
  virtual void onPing() = 0 ;
  virtual void onSendLog(const std::shared_ptr<LogItem> &logItem) = 0 ;
};

// TODO(kosak): name?
class DHWorkerAPIListenerDefault : public DHWorkerAPIListener {
public:
  ~DHWorkerAPIListenerDefault() override = default;
  void onExportedTableCreationMessage(const std::shared_ptr<InitialTableDefinition> &itd) override {}
  void onHandleResolved(const std::shared_ptr<TableHandle> &th) override {}
  void onInitialSnapshot(const std::shared_ptr<TableHandle> &th,
      const std::shared_ptr<TableSnapshot> &snapshot) override {}
  void onIncrementalUpdates(const std::shared_ptr<TableHandle> &th,
      const std::shared_ptr<DeltaUpdates> &du) override {}
  void onTableMapStringKeyAdded(const std::shared_ptr<TableMapHandle> &tmh,
      const std::shared_ptr<std::string> &key) override {}
  void onTableMapStringArrayKeyAdded(const std::shared_ptr<TableMapHandle> &tmh,
      const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &key) override {}
  void onReportMetrics(const std::shared_ptr<std::vector<std::shared_ptr<MetricsLog>>> &metrics) override {}
  void onExportedTableUpdateMessage(const std::shared_ptr<TableHandle> &th, int64_t size) override {}
  void onExportedTableUpdateMessageError(const std::shared_ptr<TableHandle> &th,
      const std::shared_ptr<std::string> &errorMessage) override {}
  void onPing() override {}
  void onSendLog(const std::shared_ptr<LogItem> &logItem) override {}
};

template<typename REQUEST>
void DHWorker::invoke(std::shared_ptr<REQUEST> request,
    std::shared_ptr<SFCallback<std::shared_ptr<typename REQUEST::correspondingResponseType_t>>> callback) {
  using deephaven::openAPI::lowlevel::remoting::util::createResponseHandler;
  auto responseHandler = createResponseHandler(std::move(callback), executor_);
  throw std::runtime_error("SAD002");
  // TODO(kosak)
  // server_->invoke(std::move(request), std::move(responseHandler));
}

}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
