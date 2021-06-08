/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#pragma once

#include <string>

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {

class ApplyAggregatesOperation {
public:
  class Strategy {
  public:
    static constexpr const char Default[] = "DEFAULT";
    static constexpr const char Linear[] = "LINEAR";
    static constexpr const char LinearGroups[] = "LINEAR_GROUPS";
    static constexpr const char UseExistingGroups[] = "USE_EXISTING_GROUPS";
    static constexpr const char CreateGroups[] = "CREATE_GROUPS";
    static constexpr const char UseExistingGroupsLinearRefresh[] = "USE_EXISTING_GROUPS_LINEAR_REFRESH";
    static constexpr const char CreateGroupsLinearRefresh[] = "CREATE_GROUPS_LINEAR_REFRESH";
    static constexpr const char UseExistingGroupsLinearGroupRefresh[] = "USE_EXISTING_GROUPS_LINEAR_GROUP_REFRESH";
    static constexpr const char CreateGroupsLinearGroupRefresh[] = "CREATE_GROUPS_LINEAR_GROUP_REFRESH";
  };

  class AggType {
  public:
    static constexpr const char Count[] = "Count";
    static constexpr const char Min[] = "Min";
    static constexpr const char Max[] = "Max";
    static constexpr const char Sum[] = "Sum";
    static constexpr const char AbsSum[] = "AbsSum";
    static constexpr const char Var[] = "Var";
    static constexpr const char Avg[] = "Avg";
    static constexpr const char Std[] = "Std";
    static constexpr const char First[] = "First";
    static constexpr const char Last[] = "Last";
    static constexpr const char Array[] = "Array";
    static constexpr const char Percentile[] = "Percentile";
    static constexpr const char WeightedAvg[] = "WeightedAvg";
    static constexpr const char Median[] = "Median";
  };
};
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
