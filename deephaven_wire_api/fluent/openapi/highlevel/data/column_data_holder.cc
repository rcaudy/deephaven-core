/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "highlevel/data/column_data_holder.h"

#include <memory>
#include <string>
#include "highlevel/data/column_data.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace data {
ColumnDataHolder::ColumnDataHolder(std::string name, bool grouped,
    std::shared_ptr<ColumnData> columnData) : name_(std::move(name)), grouped_(grouped),
    columnData_(std::move(columnData)) {}
ColumnDataHolder::ColumnDataHolder(const ColumnDataHolder &other) = default;
ColumnDataHolder &ColumnDataHolder::operator=(const ColumnDataHolder &other) = default;
ColumnDataHolder::ColumnDataHolder(ColumnDataHolder &&other) noexcept = default;
ColumnDataHolder &ColumnDataHolder::operator=(ColumnDataHolder &&other) noexcept = default;
ColumnDataHolder::~ColumnDataHolder() = default;
}  // namespace data
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
