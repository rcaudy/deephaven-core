/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once

#include <memory>
#include "lowlevel/generated/shared_objects.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {

class AggregateImpl {
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor AggregateDescriptor;
  struct Private {};

public:
  static std::shared_ptr<AggregateImpl> create(std::shared_ptr<AggregateDescriptor> descriptor);
  AggregateImpl(Private, std::shared_ptr<AggregateDescriptor> descriptor);

  const std::shared_ptr<AggregateDescriptor> &descriptor() const {
    return descriptor_;
  }

private:
  std::shared_ptr<AggregateDescriptor> descriptor_;
};

class AggregateComboImpl {
  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor AggregateDescriptor;
  struct Private {};

public:
  static std::shared_ptr<AggregateComboImpl> create(
      std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> aggregates);
  AggregateComboImpl(Private, std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> aggregates);

  const std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> &aggregates() const {
    return aggregates_;
  }

private:
  std::shared_ptr<std::vector<std::shared_ptr<AggregateDescriptor>>> aggregates_;
};

}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
