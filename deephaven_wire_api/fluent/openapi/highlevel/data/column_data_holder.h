/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once

#include <memory>
#include <string>
#include "highlevel/data/column_data.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace data {
class ColumnDataHolder {
public:
  ColumnDataHolder(std::string name, bool grouped, std::shared_ptr<ColumnData> columnData);
  ColumnDataHolder(const ColumnDataHolder &other);
  ColumnDataHolder &operator=(const ColumnDataHolder &other);

  ColumnDataHolder(ColumnDataHolder &&other) noexcept;
  ColumnDataHolder &operator=(ColumnDataHolder &&other) noexcept;
  ~ColumnDataHolder();

  const std::string &name() const { return name_; }
  bool grouped() const { return grouped_; }
  const std::shared_ptr<ColumnData> &columnData() const { return columnData_; }

private:
  // The column name.
  std::string name_;
  bool grouped_ = false;
  std::shared_ptr<ColumnData> columnData_;
};
}  // namespace data
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
