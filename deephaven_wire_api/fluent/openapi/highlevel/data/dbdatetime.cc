/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include "highlevel/data/dbdatetime.h"

#include <cstdint>
#include <string>
#include <ctime>
#include "highlevel/data/deephaven_constants.h"
#include "lowlevel/generated/shared_objects.h"
#include "utility/utility.h"

using deephaven::openAPI::utility::MyOstringStream;
using deephaven::openAPI::utility::streamf;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace data {
DBDateTime::DBDateTime(int year, int month, int day) : DBDateTime(year, month, day, 0, 0, 0, 0) {}
DBDateTime::DBDateTime(int year, int month, int day, int hour, int minute, int second) :
  DBDateTime(year, month, day, hour, minute, second, 0) {}
DBDateTime::DBDateTime(int year, int month, int day, int hour, int minute, int second,
    long nanos) {
  struct tm tm = {};
  tm.tm_year = year;
  tm.tm_mon = month;
  tm.tm_mday = day;
  tm.tm_hour = hour;
  tm.tm_min = minute;
  tm.tm_sec = second;
  tm.tm_isdst = 0;
  time_t time = mktime(&tm);
  nanos_ = static_cast<long>(time) + nanos;
}

void DBDateTime::streamIrisRepresentation(std::ostream &s) const {
  size_t oneBillion = 1000000000;
  time_t timeSecs = nanos_ / oneBillion;
  auto nanos = nanos_ % oneBillion;
  struct tm tm;
  gmtime_r(&timeSecs, &tm);
  char dateBuffer[32];  // ample
  char nanosBuffer[32];  // ample
  strftime(dateBuffer, sizeof(dateBuffer), "%FT%T", &tm);
  snprintf(nanosBuffer, sizeof(nanosBuffer), "%09zd", nanos);
  s << dateBuffer << '.' << nanosBuffer << " UTC";
}
}  // namespace data
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
