/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once
#include <cstdint>
#include <limits>
#include <string>
#include <boost/utility/string_view.hpp>
#include "lowlevel/generated/shared_objects.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace data {
class DeephavenConstants {
public:
  static constexpr const char16_t NULL_CHAR = std::numeric_limits<char16_t>::max() - 1;
  static constexpr const char16_t MIN_CHAR = std::numeric_limits<char16_t>::min();
  static constexpr const char16_t MAX_CHAR = std::numeric_limits<char16_t>::max();

  static constexpr const double NULL_DOUBLE = -std::numeric_limits<double>::max();
  static constexpr const float NULL_FLOAT = -std::numeric_limits<float>::max();

  static constexpr const int8_t NULL_BYTE = std::numeric_limits<int8_t>::min();
  static constexpr const int8_t MIN_BYTE = std::numeric_limits<int8_t>::min() + 1;
  static constexpr const int8_t MAX_BYTE = std::numeric_limits<int8_t>::max();

  static constexpr const int16_t NULL_SHORT = std::numeric_limits<int16_t>::min();
  static constexpr const int16_t MIN_SHORT = std::numeric_limits<int16_t>::min() + 1;
  static constexpr const int16_t MAX_SHORT = std::numeric_limits<int16_t>::max();

  static constexpr const int32_t NULL_INT = std::numeric_limits<int32_t>::min();
  static constexpr const int32_t MIN_INT = std::numeric_limits<int32_t>::min() + 1;
  static constexpr const int32_t MAX_INT = std::numeric_limits<int32_t>::max();

  static constexpr const int64_t NULL_LONG = std::numeric_limits<int64_t>::min();
  static constexpr const int64_t MIN_LONG = std::numeric_limits<int64_t>::min() + 1;
  static constexpr const int64_t MAX_LONG = std::numeric_limits<int64_t>::max();
};
}  // namespace data
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
