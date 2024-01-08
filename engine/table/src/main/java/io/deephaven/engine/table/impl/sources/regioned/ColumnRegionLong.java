/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
/*
 * ---------------------------------------------------------------------------------------------------------------------
 * AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY - for any changes edit ColumnRegionChar and regenerate
 * ---------------------------------------------------------------------------------------------------------------------
 */
package io.deephaven.engine.table.impl.sources.regioned;

import io.deephaven.chunk.ChunkType;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.engine.page.PagingContextHolder;
import io.deephaven.chunk.attributes.Any;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.RowSetFactory;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.SafeCloseable;
import io.deephaven.util.annotations.FinalDefault;
import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

/**
 * Column region interface for regions that support fetching primitive longs.
 */
public interface ColumnRegionLong<ATTR extends Any> extends ColumnRegion<ATTR> {

    /**
     * Get a single long from this region.
     *
     * @param elementIndex Element row key in the table's address space
     * @return The long value at the specified element row key
     */
    long getLong(long elementIndex);

    /**
     * Get a single long from this region.
     *
     * @param context      A {@link PagingContextHolder} to enable resource caching where suitable, with current
     *                     region index pointing to this region
     * @param elementIndex Element row key in the table's address space
     * @return The long value at the specified element row key
     */
    default long getLong(@NotNull final FillContext context, final long elementIndex) {
        return getLong(elementIndex);
    }

    @Override
    @FinalDefault
    default ChunkType getChunkType() {
        return ChunkType.Long;
    }

    static <ATTR extends Any> ColumnRegionLong<ATTR> createNull(final long pageMask) {
        //noinspection unchecked
        return pageMask == Null.DEFAULT_INSTANCE.mask() ? Null.DEFAULT_INSTANCE : new Null<ATTR>(pageMask);
    }

    final class Null<ATTR extends Any> extends ColumnRegion.Null<ATTR> implements ColumnRegionLong<ATTR> {
        @SuppressWarnings("rawtypes")
        private static final ColumnRegionLong DEFAULT_INSTANCE = new ColumnRegionLong.Null(RegionedColumnSourceBase.PARAMETERS.regionMask);

        private Null(final long pageMask) {
            super(pageMask);
        }

        @Override
        public long getLong(final long elementIndex) {
            return QueryConstants.NULL_LONG;
        }

        @Override
        public WritableRowSet match(
                final boolean invertMatch,
                final boolean usePrev,
                final boolean caseInsensitive,
                @NotNull final RowSequence rowSequence,
                final Object... sortedKeys) {
            final boolean nullMatched = sortedKeys.length > 0
                    && (sortedKeys[0] == null || sortedKeys[0].equals(QueryConstants.NULL_LONG_BOXED));
            if (nullMatched && !invertMatch || !nullMatched && invertMatch) {
                try (final RowSet rowSet = rowSequence.asRowSet()) {
                    return rowSet.copy();
                }
            }
            return RowSetFactory.empty();
        }
    }

    final class Constant<ATTR extends Any>
            extends GenericColumnRegionBase<ATTR>
            implements ColumnRegionLong<ATTR>, WithDefaultsForRepeatingValues<ATTR> {

        private final long value;

        public Constant(final long pageMask, final long value) {
            super(pageMask);
            this.value = value;
        }

        @Override
        public long getLong(final long elementIndex) {
            return value;
        }

        @Override
        public void fillChunkAppend(@NotNull final FillContext context, @NotNull final WritableChunk<? super ATTR> destination, final int length) {
            final int offset = destination.size();
            destination.asWritableLongChunk().fillWithValue(offset, length, value);
            destination.setSize(offset + length);
        }

        @Override
        public ColumnLocation getLocation() {
            return null;
        }

        @Override
        public boolean supportsMatching() {
            return true;
        }

        @Override
        public WritableRowSet match(
                final boolean invertMatch,
                final boolean usePrev,
                final boolean caseInsensitive,
                @NotNull final RowSequence rowSequence,
                final Object... sortedKeys) {
            boolean valueMatches = arrayContainsValue(sortedKeys);
            if (valueMatches && !invertMatch || !valueMatches && invertMatch) {
                try (final RowSet rowSet = rowSequence.asRowSet()) {
                    return rowSet.copy();
                }
            }

            return RowSetFactory.empty();
        }

        private boolean arrayContainsValue(final Object[] sortedKeys) {
            if (value == QueryConstants.NULL_LONG && sortedKeys.length > 0
                    && (sortedKeys[0] == null || sortedKeys[0] == QueryConstants.NULL_LONG_BOXED)) {
                return true;
            }
            return Arrays.binarySearch(sortedKeys,  value) >= 0;
        }
    }

    final class StaticPageStore<ATTR extends Any>
            extends RegionedPageStore.Static<ATTR, ATTR, ColumnRegionLong<ATTR>>
            implements ColumnRegionLong<ATTR> {

        public StaticPageStore(
                @NotNull final Parameters parameters,
                @NotNull final ColumnRegionLong<ATTR>[] regions,
                @NotNull final ColumnLocation location) {
            super(parameters, regions, location);
        }

        @Override
        public void invalidate() {
            for(int ii = 0; ii < getRegionCount(); ii++) {
                getRegion(ii).invalidate();
            }
        }

        @Override
        public long getLong(final long elementIndex) {
            return lookupRegion(elementIndex).getLong(elementIndex);
        }

        @Override
        public long getLong(@NotNull final FillContext context, final long elementIndex) {
            return lookupRegion(elementIndex).getLong(context, elementIndex);
        }

        @Override
        public WritableRowSet match(
                final boolean invertMatch,
                final boolean usePrev, boolean caseInsensitive,
                @NotNull final RowSequence rowSequence,
                final Object... sortedKeys) {
            // TODO NATE NOCOMMIT: should this parallelize matching?

            WritableRowSet dest = null;
            try (final RowSequence.Iterator rowIter = rowSequence.getRowSequenceIterator()) {
                while (rowIter.hasMore()) {
                    final long firstRow = rowIter.peekNextKey();
                    final ColumnRegionLong<ATTR> region = lookupRegion(firstRow);
                    final long lastRow = region.maxRow(firstRow);
                    final WritableRowSet result = region.match(
                            invertMatch, usePrev, caseInsensitive, rowIter.getNextRowSequenceThrough(lastRow), sortedKeys);
                    if (dest == null) {
                        dest = result;
                    } else {
                        try (final SafeCloseable ignored = result) {
                            dest.insert(result);
                        }
                    }
                }
            }
            return dest == null ? RowSetFactory.empty() : dest;
        }
    }
}
