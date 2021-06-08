/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */

#pragma once

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace util {
class DemoConstants {
public:
  // This is the namespace for our example historical table.
  static constexpr const char historicalNamespace[] = "LearnDeephaven";

  // This is an example historical (aka non-ticking or static) table.
  static constexpr const char historicalTable[] = "EODTrades";

  // This is the namespace for our example intraday table.
  static constexpr const char intradayNamespace[] = "DbInternal";

  // This is an example intraday (aka ticking or dynamic) table.
  static constexpr const char intradayTable[] = "ProcessEventLog";
};
}  // namespace util
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
