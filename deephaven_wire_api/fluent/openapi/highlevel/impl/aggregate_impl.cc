#include "highlevel/impl/aggregate_impl.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {

std::shared_ptr<AggregateImpl> AggregateImpl::create(
    std::shared_ptr<AggregateDescriptor> descriptor) {
  return std::make_shared<AggregateImpl>(Private(), std::move(descriptor));
}

AggregateImpl::AggregateImpl(Private, std::shared_ptr<AggregateDescriptor> descriptor) :
    descriptor_(std::move(descriptor)) {}

std::shared_ptr<AggregateComboImpl> AggregateComboImpl::create(
    std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> aggregates) {
  return std::make_shared<AggregateComboImpl>(Private(), std::move(aggregates));
}

AggregateComboImpl::AggregateComboImpl(Private,
    std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> aggregates) :
    aggregates_(std::move(aggregates)) {}
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
