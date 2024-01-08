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
 * Column region interface for regions that support fetching primitive floats.
 */
public interface ColumnRegionFloat<ATTR extends Any> extends ColumnRegion<ATTR> {

    /**
     * Get a single float from this region.
     *
     * @param elementIndex Element row key in the table's address space
     * @return The float value at the specified element row key
     */
    float getFloat(long elementIndex);

    /**
     * Get a single float from this region.
     *
     * @param context      A {@link PagingContextHolder} to enable resource caching where suitable, with current
     *                     region index pointing to this region
     * @param elementIndex Element row key in the table's address space
     * @return The float value at the specified element row key
     */
    default float getFloat(@NotNull final FillContext context, final long elementIndex) {
        return getFloat(elementIndex);
    }

    @Override
    @FinalDefault
    default ChunkType getChunkType() {
        return ChunkType.Float;
    }

    static <ATTR extends Any> ColumnRegionFloat<ATTR> createNull(final long pageMask) {
        //noinspection unchecked
        return pageMask == Null.DEFAULT_INSTANCE.mask() ? Null.DEFAULT_INSTANCE : new Null<ATTR>(pageMask);
    }

    final class Null<ATTR extends Any> extends ColumnRegion.Null<ATTR> implements ColumnRegionFloat<ATTR> {
        @SuppressWarnings("rawtypes")
        private static final ColumnRegionFloat DEFAULT_INSTANCE = new ColumnRegionFloat.Null(RegionedColumnSourceBase.PARAMETERS.regionMask);

        private Null(final long pageMask) {
            super(pageMask);
        }

        @Override
        public float getFloat(final long elementIndex) {
            return QueryConstants.NULL_FLOAT;
        }

        @Override
        public WritableRowSet match(
                final boolean invertMatch,
                final boolean usePrev,
                final boolean caseInsensitive,
                @NotNull final RowSequence rowSequence,
                final Object... sortedKeys) {
            final boolean nullMatched = sortedKeys.length > 0
                    && (sortedKeys[0] == null || sortedKeys[0].equals(QueryConstants.NULL_FLOAT_BOXED));
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
            implements ColumnRegionFloat<ATTR>, WithDefaultsForRepeatingValues<ATTR> {

        private final float value;

        public Constant(final long pageMask, final float value) {
            super(pageMask);
            this.value = value;
        }

        @Override
        public float getFloat(final long elementIndex) {
            return value;
        }

        @Override
        public void fillChunkAppend(@NotNull final FillContext context, @NotNull final WritableChunk<? super ATTR> destination, final int length) {
            final int offset = destination.size();
            destination.asWritableFloatChunk().fillWithValue(offset, length, value);
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
            if (value == QueryConstants.NULL_FLOAT && sortedKeys.length > 0
                    && (sortedKeys[0] == null || sortedKeys[0] == QueryConstants.NULL_FLOAT_BOXED)) {
                return true;
            }
            return Arrays.binarySearch(sortedKeys,  value) >= 0;
        }
    }

    final class StaticPageStore<ATTR extends Any>
            extends RegionedPageStore.Static<ATTR, ATTR, ColumnRegionFloat<ATTR>>
            implements ColumnRegionFloat<ATTR> {

        public StaticPageStore(
                @NotNull final Parameters parameters,
                @NotNull final ColumnRegionFloat<ATTR>[] regions,
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
        public float getFloat(final long elementIndex) {
            return lookupRegion(elementIndex).getFloat(elementIndex);
        }

        @Override
        public float getFloat(@NotNull final FillContext context, final long elementIndex) {
            return lookupRegion(elementIndex).getFloat(context, elementIndex);
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
                    final ColumnRegionFloat<ATTR> region = lookupRegion(firstRow);
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
