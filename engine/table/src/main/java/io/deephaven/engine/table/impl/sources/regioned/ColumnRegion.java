/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned;

import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.Releasable;
import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.engine.page.Page;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import io.deephaven.util.annotations.FinalDefault;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public interface ColumnRegion<ATTR extends Any> extends Page<ATTR>, Releasable {

    // TODO NATE NOCOMMIT MAYBE THIS SHOULD BE NULLABLE to better support null regions (and make them singletons again)
    // javadoc why / when nullable
    @Nullable
    ColumnLocation getLocation();

    @Override
    @FinalDefault
    default long firstRowOffset() {
        return 0;
    }

    /**
     * Invalidate the region -- any further reads that cannot be completed consistently and correctly will fail.
     */
    void invalidate();

    /**
     * Check if this region has matching features.
     *
     * @return true if this has matching features
     */
    default boolean supportsMatching() {
        return false;
    }

    // Should this really return a writable row set/
    /**
     * If {@link #supportsMatching()} is {@code true} this method will perform matching in lieu of the standard
     * {@link RegionedColumnSourceBase#match(boolean, boolean, boolean, RowSet, Object...)}.
     *
     * @param invertMatch if the match should be inverted
     * @param usePrev if the match should use the previous value
     * @param caseInsensitive if the match is case insensitive
     * @param rowSequence relevant rows to search
     * @param sortedKeys the keys to search for in sorted order
     * @return an index of matched rows
     */
    default WritableRowSet match(
            boolean invertMatch,
            boolean usePrev,
            boolean caseInsensitive,
            @NotNull RowSequence rowSequence,
            Object... sortedKeys) {
        throw new UnsupportedOperationException("This region does not support matching");
    }

    abstract class Null<ATTR extends Any>
            extends GenericColumnRegionBase<ATTR>
            implements ColumnRegion<ATTR>, WithDefaultsForRepeatingValues<ATTR> {

        Null(final long pageMask) {
            super(pageMask);
        }

        @Override
        public void fillChunkAppend(@NotNull final FillContext context,
                @NotNull final WritableChunk<? super ATTR> destination, final int length) {
            final int offset = destination.size();

            destination.fillWithNullValue(offset, length);
            destination.setSize(offset + length);
        }

        @Override
        public final ColumnLocation getLocation() {
            return null;
        }

        @Override
        public final boolean supportsMatching() {
            return true;
        }

        @Override
        public abstract WritableRowSet match(
                boolean invertMatch,
                boolean usePrev,
                boolean caseInsensitive,
                @NotNull RowSequence rowSequence,
                Object... sortedKeys);
    }
}
