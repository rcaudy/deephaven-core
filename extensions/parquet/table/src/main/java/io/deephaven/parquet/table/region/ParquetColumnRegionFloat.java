/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
/*
 * ---------------------------------------------------------------------------------------------------------------------
 * AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY - for any changes edit ParquetColumnRegionChar and regenerate
 * ---------------------------------------------------------------------------------------------------------------------
 */
package io.deephaven.parquet.table.region;

import io.deephaven.api.SortColumn;
import io.deephaven.chunk.WritableFloatChunk;
import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.impl.locations.TableDataException;
import io.deephaven.engine.table.impl.sort.timsort.FloatTimsortKernel;
import io.deephaven.engine.table.impl.sources.regioned.ColumnRegionFloat;
import io.deephaven.engine.table.impl.sources.regioned.RegionedPageStore;
import io.deephaven.engine.table.impl.sources.regioned.kernel.FloatRegionBinarySearchKernel;
import io.deephaven.parquet.table.location.ParquetColumnLocation;
import io.deephaven.parquet.table.pagestore.ColumnChunkPageStore;
import io.deephaven.engine.page.ChunkPage;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.type.ArrayTypeUtils;
import org.apache.parquet.column.statistics.FloatStatistics;
import org.jetbrains.annotations.NotNull;

/**
 * {@link ColumnRegionFloat} implementation for regions that support fetching primitive floats from
 * {@link ColumnChunkPageStore column chunk page stores}.
 */
public final class ParquetColumnRegionFloat<ATTR extends Values> extends ParquetColumnRegionBase<ATTR>
        implements ColumnRegionFloat<ATTR>, ParquetColumnRegion<ATTR> {

    public ParquetColumnRegionFloat(
            @NotNull final ColumnChunkPageStore<ATTR> columnChunkPageStore,
            @NotNull final ParquetColumnLocation<Values> location) {
        super(columnChunkPageStore.mask(), columnChunkPageStore, location);
    }

    // region getBytes
    // endregion getBytes

    @Override
    public float getFloat(final long rowKey) {
        final ChunkPage<ATTR> page = getChunkPageContaining(rowKey);
        try {
            return page.asFloatChunk().get(page.getChunkOffset(rowKey));
        } catch (Exception e) {
            throw new TableDataException("Error retrieving float at row key " + rowKey + " from a parquet table", e);
        }
    }

    // TODO NATE NOCOMMIT: these are still useful aren't they?
    public RowSet binSearchMatch(
            long firstRowKey,
            final long lastRowKey,
            @NotNull final SortColumn sortColumn,
            @NotNull final Object[] keys) {
        return FloatRegionBinarySearchKernel.binarySearchMatch(this, firstRowKey, lastRowKey, sortColumn, keys);
    }

    public boolean mightContain(@NotNull final Object[] keys) {
        // We don't have statistics, so we need to assume there is something in the range that fits.
        if (!columnChunkPageStore.hasStatistics()) {
            return true;
        }

        final FloatStatistics stats = columnChunkPageStore.getStatistics();
        // TODO: make sure this actually does what you think it does.
        if (!stats.hasNonNullValue()) {
            // Statistics are incomplete,  we have to assume the region might have the data.
            return true;
        }

        final float[] typed = ArrayTypeUtils.getUnboxedFloatArray(keys);
        try (final FloatTimsortKernel.FloatSortKernelContext<Any> sortContext =
                     FloatTimsortKernel.createContext(typed.length)) {
            sortContext.sort(WritableFloatChunk.writableChunkWrap(typed));
        }

        int firstNonNullValue = 0;
        if (typed[firstNonNullValue] == QueryConstants.NULL_FLOAT) {
            // If there were nulls in the region, we can just say 'yes'
            if (stats.getNumNulls() > 0) {
                return true;
            }

            // If there were not, then find the last value to find that is not null
            while (firstNonNullValue < typed.length && typed[firstNonNullValue] == QueryConstants.NULL_FLOAT) {
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
            extends RegionedPageStore.Static<ATTR, ATTR, ColumnRegionFloat<ATTR>>
            implements ColumnRegionFloat<ATTR> {

        public StaticPageStore(
                @NotNull final Parameters parameters,
                @NotNull final ColumnRegionFloat<ATTR>[] regions,
                @NotNull final ParquetColumnLocation<Values> location) {
            super(parameters, regions, location);
        }

        @Override
        public float getFloat(final long elementIndex) {
            return lookupRegion(elementIndex).getFloat(elementIndex);
        }

        @Override
        public float getFloat(@NotNull final FillContext context, final long elementIndex) {
            return lookupRegion(elementIndex).getFloat(context, elementIndex);
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
