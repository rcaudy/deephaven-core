/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.parquet.table.region;

import io.deephaven.api.SortColumn;
import io.deephaven.chunk.WritableCharChunk;
import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.impl.locations.TableDataException;
import io.deephaven.engine.table.impl.sort.timsort.CharTimsortKernel;
import io.deephaven.engine.table.impl.sources.regioned.ColumnRegionChar;
import io.deephaven.engine.table.impl.sources.regioned.RegionedPageStore;
import io.deephaven.engine.table.impl.sources.regioned.kernel.CharRegionBinarySearchKernel;
import io.deephaven.parquet.table.location.ParquetColumnLocation;
import io.deephaven.parquet.table.pagestore.ColumnChunkPageStore;
import io.deephaven.engine.page.ChunkPage;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.type.ArrayTypeUtils;
import org.apache.parquet.column.statistics.IntStatistics;
import org.jetbrains.annotations.NotNull;

/**
 * {@link ColumnRegionChar} implementation for regions that support fetching primitive chars from
 * {@link ColumnChunkPageStore column chunk page stores}.
 */
public final class ParquetColumnRegionChar<ATTR extends Values> extends ParquetColumnRegionBase<ATTR>
        implements ColumnRegionChar<ATTR>, ParquetColumnRegion<ATTR> {

    public ParquetColumnRegionChar(
            @NotNull final ColumnChunkPageStore<ATTR> columnChunkPageStore,
            @NotNull final ParquetColumnLocation<Values> location) {
        super(columnChunkPageStore.mask(), columnChunkPageStore, location);
    }

    // region getBytes
    // endregion getBytes

    @Override
    public char getChar(final long rowKey) {
        final ChunkPage<ATTR> page = getChunkPageContaining(rowKey);
        try {
            return page.asCharChunk().get(page.getChunkOffset(rowKey));
        } catch (Exception e) {
            throw new TableDataException("Error retrieving char at row key " + rowKey + " from a parquet table", e);
        }
    }

    // TODO NATE NOCOMMIT: these are still useful aren't they?
    public RowSet binSearchMatch(
            long firstRowKey,
            final long lastRowKey,
            @NotNull final SortColumn sortColumn,
            @NotNull final Object[] keys) {
        return CharRegionBinarySearchKernel.binarySearchMatch(this, firstRowKey, lastRowKey, sortColumn, keys);
    }

    public boolean mightContain(@NotNull final Object[] keys) {
        // We don't have statistics, so we need to assume there is something in the range that fits.
        if (!columnChunkPageStore.hasStatistics()) {
            return true;
        }

        final IntStatistics stats = columnChunkPageStore.getStatistics();
        // TODO: make sure this actually does what you think it does.
        if (!stats.hasNonNullValue()) {
            // Statistics are incomplete,  we have to assume the region might have the data.
            return true;
        }

        final char[] typed = ArrayTypeUtils.getUnboxedCharArray(keys);
        try (final CharTimsortKernel.CharSortKernelContext<Any> sortContext =
                     CharTimsortKernel.createContext(typed.length)) {
            sortContext.sort(WritableCharChunk.writableChunkWrap(typed));
        }

        int firstNonNullValue = 0;
        if (typed[firstNonNullValue] == QueryConstants.NULL_CHAR) {
            // If there were nulls in the region, we can just say 'yes'
            if (stats.getNumNulls() > 0) {
                return true;
            }

            // If there were not, then find the last value to find that is not null
            while (firstNonNullValue < typed.length && typed[firstNonNullValue] == QueryConstants.NULL_CHAR) {
                firstNonNullValue++;
            }

            // Everything was null,  we are done.
            if (firstNonNullValue >= typed.length) {
                return false;
            }
        }

        // Look through the keys and find anything that fits in the range.
        for (int ii = firstNonNullValue; ii < typed.length; ii++) {
            if (typed[ii] >= stats.getMin() && typed[ii] <= stats.getMax()) {
                return true;
            }
        }

        // Nothing matches, we can skip this region.
        return false;
    }

    public static final class StaticPageStore<ATTR extends Any>
            extends RegionedPageStore.Static<ATTR, ATTR, ColumnRegionChar<ATTR>>
            implements ColumnRegionChar<ATTR> {

        public StaticPageStore(
                @NotNull final Parameters parameters,
                @NotNull final ColumnRegionChar<ATTR>[] regions,
                @NotNull final ParquetColumnLocation<Values> location) {
            super(parameters, regions, location);
        }

        @Override
        public char getChar(final long elementIndex) {
            return lookupRegion(elementIndex).getChar(elementIndex);
        }

        @Override
        public char getChar(@NotNull final FillContext context, final long elementIndex) {
            return lookupRegion(elementIndex).getChar(context, elementIndex);
        }

        // region StaticRegion.getBytes
        // endregion StaticRegion.getBytes

        @Override
        public void invalidate() {

        }

        @Override
        public WritableRowSet match(
                final boolean invertMatch,
                final boolean usePrev, boolean caseInsensitive,
                @NotNull final RowSequence rowSequence,
                final Object... sortedKeys) {
            // where is the data stored here?
            throw new UnsupportedOperationException("TODO NATE NOCOMMIT");
        }
    }
}
