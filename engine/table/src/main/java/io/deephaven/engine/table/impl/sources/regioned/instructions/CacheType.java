/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned.instructions;

public enum CacheType {

    /** Create caches using soft references */
    Soft,

    /** Create caches using hard references */
    Hard
}
