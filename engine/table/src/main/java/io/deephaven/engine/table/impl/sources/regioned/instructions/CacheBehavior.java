/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned.instructions;

public enum CacheBehavior {
    /** Use Deephaven's normal caching behavior */
    Default,

    /** Always cache results */
    Always,

    /** Never cache results */
    Never
}
