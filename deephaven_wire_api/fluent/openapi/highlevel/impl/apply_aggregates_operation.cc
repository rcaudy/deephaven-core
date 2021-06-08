/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include <highlevel/impl/apply_aggregates_operation.h>

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace impl {
const char ApplyAggregatesOperation::Strategy::Default[];
const char ApplyAggregatesOperation::Strategy::Linear[];
const char ApplyAggregatesOperation::Strategy::LinearGroups[];
const char ApplyAggregatesOperation::Strategy::UseExistingGroups[];
const char ApplyAggregatesOperation::Strategy::CreateGroups[];
const char ApplyAggregatesOperation::Strategy::UseExistingGroupsLinearRefresh[];
const char ApplyAggregatesOperation::Strategy::CreateGroupsLinearRefresh[];
const char ApplyAggregatesOperation::Strategy::UseExistingGroupsLinearGroupRefresh[];
const char ApplyAggregatesOperation::Strategy::CreateGroupsLinearGroupRefresh[];

const char ApplyAggregatesOperation::AggType::Count[];
const char ApplyAggregatesOperation::AggType::Min[];
const char ApplyAggregatesOperation::AggType::Max[];
const char ApplyAggregatesOperation::AggType::Sum[];
const char ApplyAggregatesOperation::AggType::AbsSum[];
const char ApplyAggregatesOperation::AggType::Var[];
const char ApplyAggregatesOperation::AggType::Avg[];
const char ApplyAggregatesOperation::AggType::Std[];
const char ApplyAggregatesOperation::AggType::First[];
const char ApplyAggregatesOperation::AggType::Last[];
const char ApplyAggregatesOperation::AggType::Array[];
const char ApplyAggregatesOperation::AggType::Percentile[];
const char ApplyAggregatesOperation::AggType::WeightedAvg[];
const char ApplyAggregatesOperation::AggType::Median[];
}  // namespace impl
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
