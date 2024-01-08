/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
/*
 * ---------------------------------------------------------------------------------------------------------------------
 * AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY - for any changes edit ParquetColumnRegionChar and regenerate
 * ---------------------------------------------------------------------------------------------------------------------
 */
package io.deephaven.parquet.table.region;

import io.deephaven.chunk.WritableByteChunk;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSequenceFactory;

import io.deephaven.api.SortColumn;
import io.deephaven.chunk.WritableByteChunk;
import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.impl.locations.TableDataException;
import io.deephaven.engine.table.impl.sort.timsort.ByteTimsortKernel;
import io.deephaven.engine.table.impl.sources.regioned.ColumnRegionByte;
import io.deephaven.engine.table.impl.sources.regioned.RegionedPageStore;
import io.deephaven.engine.table.impl.sources.regioned.kernel.ByteRegionBinarySearchKernel;
import io.deephaven.parquet.table.location.ParquetColumnLocation;
import io.deephaven.parquet.table.pagestore.ColumnChunkPageStore;
import io.deephaven.engine.page.ChunkPage;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.type.ArrayTypeUtils;
import org.apache.parquet.column.statistics.IntStatistics;
import org.jetbrains.annotations.NotNull;

/**
 * {@link ColumnRegionByte} implementation for regions that support fetching primitive bytes from
 * {@link ColumnChunkPageStore column chunk page stores}.
 */
public final class ParquetColumnRegionByte<ATTR extends Values> extends ParquetColumnRegionBase<ATTR>
        implements ColumnRegionByte<ATTR>, ParquetColumnRegion<ATTR> {

    public ParquetColumnRegionByte(
            @NotNull final ColumnChunkPageStore<ATTR> columnChunkPageStore,
            @NotNull final ParquetColumnLocation<Values> location) {
        super(columnChunkPageStore.mask(), columnChunkPageStore, location);
    }

    // region getBytes
    public byte[] getBytes(
            final long firstRowKey,
            @NotNull final byte[] destination,
            final int destinationOffset,
            final int length
    ) {
        final WritableChunk<ATTR> byteChunk = WritableByteChunk.writableChunkWrap(destination, destinationOffset, length);
        try (RowSequence rowSequence = RowSequenceFactory.forRange(firstRowKey, firstRowKey + length - 1)) {
            fillChunk(DEFAULT_FILL_INSTANCE, byteChunk, rowSequence);
        }
        return destination;
    }
    // endregion getBytes

    @Override
    public byte getByte(final long rowKey) {
        final ChunkPage<ATTR> page = getChunkPageContaining(rowKey);
        try {
            return page.asByteChunk().get(page.getChunkOffset(rowKey));
        } catch (Exception e) {
            throw new TableDataException("Error retrieving byte at row key " + rowKey + " from a parquet table", e);
        }
    }

    // TODO NATE NOCOMMIT: these are still useful aren't they?
    public RowSet binSearchMatch(
            long firstRowKey,
            final long lastRowKey,
            @NotNull final SortColumn sortColumn,
            @NotNull final Object[] keys) {
        return ByteRegionBinarySearchKernel.binarySearchMatch(this, firstRowKey, lastRowKey, sortColumn, keys);
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

        final byte[] typed = ArrayTypeUtils.getUnboxedByteArray(keys);
        try (final ByteTimsortKernel.ByteSortKernelContext<Any> sortContext =
                     ByteTimsortKernel.createContext(typed.length)) {
            sortContext.sort(WritableByteChunk.writableChunkWrap(typed));
        }

        int firstNonNullValue = 0;
        if (typed[firstNonNullValue] == QueryConstants.NULL_BYTE) {
            // If there were nulls in the region, we can just say 'yes'
            if (stats.getNumNulls() > 0) {
                return true;
            }

            // If there were not, then find the last value to find that is not null
            while (firstNonNullValue < typed.length && typed[firstNonNullValue] == QueryConstants.NULL_BYTE) {
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
            extends RegionedPageStore.Static<ATTR, ATTR, ColumnRegionByte<ATTR>>
            implements ColumnRegionByte<ATTR> {

        public StaticPageStore(
                @NotNull final Parameters parameters,
                @NotNull final ColumnRegionByte<ATTR>[] regions,
                @NotNull final ParquetColumnLocation<Values> location) {
            super(parameters, regions, location);
        }

        @Override
        public byte getByte(final long elementIndex) {
            return lookupRegion(elementIndex).getByte(elementIndex);
        }

        @Override
        public byte getByte(@NotNull final FillContext context, final long elementIndex) {
            return lookupRegion(elementIndex).getByte(context, elementIndex);
        }

        // region StaticRegion.getBytes
        @Override
        public byte[] getBytes(long firstElementIndex, @NotNull byte[] destination, int destinationOffset, int length) {
            return lookupRegion(firstElementIndex).getBytes(firstElementIndex, destination, destinationOffset, length);
        }
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
