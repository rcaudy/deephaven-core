/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.parquet.table.region;

import io.deephaven.api.SortColumn;
import io.deephaven.chunk.WritableObjectChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.configuration.Configuration;
import io.deephaven.engine.page.ChunkPage;
import io.deephaven.engine.page.Page;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.impl.chunkattributes.DictionaryKeys;
import io.deephaven.engine.table.impl.locations.TableDataException;
import io.deephaven.engine.table.impl.sort.timsort.ObjectTimsortKernel;
import io.deephaven.engine.table.impl.sources.regioned.ColumnRegionLong;
import io.deephaven.engine.table.impl.sources.regioned.ColumnRegionObject;
import io.deephaven.engine.table.impl.sources.regioned.RegionVisitResult;
import io.deephaven.engine.table.impl.sources.regioned.kernel.ObjectRegionBinarySearchKernel;
import io.deephaven.parquet.table.location.ParquetColumnLocation;
import io.deephaven.parquet.table.pagestore.ColumnChunkPageStore;
import io.deephaven.util.compare.ObjectComparisons;
import org.apache.commons.lang3.mutable.MutableInt;
import org.apache.parquet.column.statistics.BinaryStatistics;
import org.jetbrains.annotations.NotNull;

import java.util.Arrays;
import java.util.function.Supplier;

/**
 * {@link ColumnRegionObject} implementation for regions that support fetching objects from
 * {@link ColumnChunkPageStore column chunk page stores}.
 */
public final class ParquetColumnRegionObject<DATA_TYPE, ATTR extends Values> extends ParquetColumnRegionBase<ATTR>
        implements ColumnRegionObject<DATA_TYPE, ATTR>, ParquetColumnRegion<ATTR>, Page<ATTR> {
    private static final double STANDARD_SORT_FRACTION_THRESHOLD = Configuration.getInstance()
            .getDoubleForClassWithDefault(ParquetColumnRegionObject.class, "sortFractionThreshold", 0.5d);

    private volatile Supplier<ColumnRegionLong<DictionaryKeys>> dictionaryKeysRegionSupplier;
    private volatile Supplier<ColumnRegionObject<DATA_TYPE, ATTR>> dictionaryValuesRegionSupplier;

    private ColumnRegionLong<DictionaryKeys> dictionaryKeysRegion;
    private ColumnRegionObject<DATA_TYPE, ATTR> dictionaryValuesRegion;

    public ParquetColumnRegionObject(
            @NotNull final ColumnChunkPageStore<ATTR> columnChunkPageStore,
            @NotNull final Supplier<ColumnRegionLong<DictionaryKeys>> dictionaryKeysRegionSupplier,
            @NotNull final Supplier<ColumnRegionObject<DATA_TYPE, ATTR>> dictionaryValuesRegionSupplier,
            @NotNull final ParquetColumnLocation<Values> location) {
        super(columnChunkPageStore.mask(), columnChunkPageStore, location);
        this.dictionaryKeysRegionSupplier = dictionaryKeysRegionSupplier;
        this.dictionaryValuesRegionSupplier = dictionaryValuesRegionSupplier;
    }

    public DATA_TYPE getObject(final long rowKey) {
        final ChunkPage<ATTR> page = getChunkPageContaining(rowKey);
        try {
            return page.<DATA_TYPE>asObjectChunk().get(page.getChunkOffset(rowKey));
        } catch (Exception e) {
            throw new TableDataException("Error retrieving object at Object row key " + rowKey + " from a parquet table", e);
        }
    }

    @Override
    public RegionVisitResult supportsDictionaryFormat(@NotNull final RowSet.SearchIterator keysToVisit) {
        if (!columnChunkPageStore.usesDictionaryOnEveryPage()) {
            return RegionVisitResult.FAILED;
        }
        return advanceToNextPage(keysToVisit) ? RegionVisitResult.CONTINUE : RegionVisitResult.COMPLETE;
    }

    @Override
    public ColumnRegionLong<DictionaryKeys> getDictionaryKeysRegion() {
        if (dictionaryKeysRegionSupplier != null) {
            synchronized (this) {
                if (dictionaryKeysRegionSupplier != null) {
                    dictionaryKeysRegion = dictionaryKeysRegionSupplier.get();
                    dictionaryKeysRegionSupplier = null;
                }
            }
        }
        return dictionaryKeysRegion;
    }

    @Override
    public ColumnRegionObject<DATA_TYPE, ATTR> getDictionaryValuesRegion() {
        if (dictionaryValuesRegionSupplier != null) {
            synchronized (this) {
                if (dictionaryValuesRegionSupplier != null) {
                    dictionaryValuesRegion = dictionaryValuesRegionSupplier.get();
                    dictionaryValuesRegionSupplier = null;
                }
            }
        }
        return dictionaryValuesRegion;
    }

    // TODO NATE NOCOMMIT: These are still helpful aren't they?
    public RowSet binSearchMatch(
            final long firstRowKey,
            final long lastRowKey,
            @NotNull final SortColumn sortColumn,
            @NotNull final Object[] keys) {
        return ObjectRegionBinarySearchKernel.binarySearchMatch(this, firstRowKey, lastRowKey, sortColumn, keys);
    }

    public boolean mightContain(@NotNull final Object[] keys) {
        // We don't have statistics, so we need to assume there is something in the range that fits.
        if (!columnChunkPageStore.hasStatistics()) {
            return true;
        }

        final BinaryStatistics stats = columnChunkPageStore.getStatistics();
        if (!stats.hasNonNullValue()) {
            // We don't have min/max data recorded.  We have to assume it might contain the data
            return true;
        }

        final Object[] sortedKeys = Arrays.copyOf(keys, keys.length);
        try (final ObjectTimsortKernel.ObjectSortKernelContext<ATTR> kernel =
                     ObjectTimsortKernel.createContext(sortedKeys.length)) {
            kernel.sort(WritableObjectChunk.writableChunkWrap(sortedKeys));
        }

        int firstNonNullValue = 0;
        if(sortedKeys[firstNonNullValue] == null) {
            // If there were nulls in the region, we can just say 'yes'
            if(stats.getNumNulls() > 0) {
                return true;
            }

            // If there were not, then find the last value to find that is not null
            while(firstNonNullValue < sortedKeys.length && sortedKeys[firstNonNullValue] == null) {
                firstNonNullValue++;
            }

            // Everything was null,  we are done.
            if(firstNonNullValue >= sortedKeys.length) {
                return false;
            }
        }

        final DATA_TYPE minVal = columnChunkPageStore.convertSingleValue(stats.genericGetMin());
        final DATA_TYPE maxVal = columnChunkPageStore.convertSingleValue(stats.genericGetMax());
        // Look through the keys and find anything that fits in the range.
        for (int ii = 0; ii <= firstNonNullValue; ii++) {
            if (ObjectComparisons.geq(sortedKeys[ii], minVal) && ObjectComparisons.leq(sortedKeys[ii], maxVal)) {
                return true;
            }
        }

        // Nothing matches, we can skip this region.
        return false;
    }

    @Override
    public WritableRowSet match(
            final boolean invertMatch,
            final boolean usePrev,
            final boolean caseInsensitive,
            @NotNull final RowSequence rowSequence,
            final Object... sortedKeys) {
        if (!columnChunkPageStore.usesDictionaryOnEveryPage()) {
            return match(invertMatch, usePrev, caseInsensitive, rowSequence, sortedKeys);
        }

        final ColumnRegionObject<?, ATTR> valuesRegion = getDictionaryValuesRegion();
        // TODO NATE NOCOMMIT: this isn't a helpful test
        final long maxRegionSize = valuesRegion.mask();
        if ((maxRegionSize / (double)rowSequence.size()) > STANDARD_SORT_FRACTION_THRESHOLD) {
            return super.match(invertMatch, usePrev, caseInsensitive, rowSequence, sortedKeys);
        }

        final RowSet matchedKeys = getDictionaryValuesRegion().match(
                invertMatch, usePrev, caseInsensitive, rowSequence, sortedKeys);
        final Object[] convertedKeys = new Object[sortedKeys.length];
        MutableInt pos = new MutableInt(0);
        matchedKeys.forAllRowKeys(k -> convertedKeys[pos.getAndIncrement()] = k);

        return getDictionaryKeysRegion().match(invertMatch, usePrev, caseInsensitive, rowSequence, convertedKeys);
    }
}
