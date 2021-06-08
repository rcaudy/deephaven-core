/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once
#include <cstdint>
#include <ostream>
#include <string>
#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>
#include "highlevel/data/deephaven_constants.h"
#include "lowlevel/generated/shared_objects.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace data {
class DBDateTime {
public:
  // Converts nanos-since-UTC-epoch to DBDateTime. Deephaven null value sentinel is turned into
  // DBDateTime(0).
  static DBDateTime fromNanos(long nanos) {
    if (nanos == DeephavenConstants::NULL_LONG) {
      return DBDateTime(0);
    }
    return DBDateTime(nanos);
  }

  DBDateTime() = default;
  explicit DBDateTime(int64_t nanos) : nanos_(nanos) {}
  DBDateTime(int year, int month, int day);
  DBDateTime(int year, int month, int day, int hour, int minute, int second);
  DBDateTime(int year, int month, int day, int hour, int minute, int second, long nanos);

  int64_t nanos() const { return nanos_; }

  void appendIrisRepresentation(std::string *result) const;
  void appendIrisRepresentation(std::ostream &result) const;

private:
  int64_t nanos_ = 0;

  friend std::ostream &operator<<(std::ostream &s, const DBDateTime &o) {
    o.appendIrisRepresentation(s);
    return s;
  }
};
}  // namespace data
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
