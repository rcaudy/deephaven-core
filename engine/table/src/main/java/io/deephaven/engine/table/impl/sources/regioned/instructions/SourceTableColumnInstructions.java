/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned.instructions;

import io.deephaven.annotations.BuildableStyle;
import org.immutables.value.Value;
import org.jetbrains.annotations.NotNull;


@Value.Immutable
@BuildableStyle
public abstract class SourceTableColumnInstructions {
    public static final SourceTableColumnInstructions DEFAULT = builder().build();

    /**
     * @return the desired caching behavior
     */
    @Value.Default
    public CacheBehavior cacheBehavior() {
        return CacheBehavior.Default;
    }

    @Value.Default
    public CacheType cacheType() {
        return CacheType.Soft;
    }

    public static Builder builder() {
        return ImmutableSourceTableColumnInstructions.builder();
    }

    public interface Builder {
        Builder cacheBehavior(@NotNull CacheBehavior cacheBehavior);

        Builder cacheType(@NotNull CacheType cacheType);

        SourceTableColumnInstructions build();
    }
}
