/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned;

import io.deephaven.base.verify.Assert;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.configuration.Configuration;
import io.deephaven.engine.rowset.*;
import io.deephaven.engine.table.impl.sources.AbstractDeferredGroupingColumnSource;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.util.annotations.TestUseOnly;
import io.deephaven.util.compare.ObjectComparisons;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Partial implementation of {@link RegionedColumnSource} for array-backed and delegating implementations to extend.
 */
public abstract class RegionedColumnSourceBase<DATA_TYPE, ATTR extends Values, REGION_TYPE extends ColumnRegion<ATTR>>
        extends AbstractDeferredGroupingColumnSource<DATA_TYPE>
        implements RegionedPageStore<Values, ATTR, REGION_TYPE>, RegionedColumnSource<DATA_TYPE> {
    public static boolean USE_PARALLEL = Configuration.getInstance().getBooleanForClassWithDefault(
            RegionedColumnSourceBase.class, "useParallelMatchFilter", true);
    public static boolean USE_PUSHDOWN = Configuration.getInstance().getBooleanForClassWithDefault(
            RegionedColumnSourceBase.class, "pushDownMatchFilter", true);

    private static class MatchParams {
        final ColumnRegion<? extends Values> region;
        final RowSequence relevantKeys;
        final long regionFirstkey;

        private MatchParams(ColumnRegion<? extends Values> region, RowSequence relevantKeys, long regionFirstKey) {
            this.region = region;
            this.relevantKeys = relevantKeys;
            this.regionFirstkey = regionFirstKey;
        }
    }

    private volatile boolean groupingEnabled = true;

    static final Parameters PARAMETERS;
    static {
        PARAMETERS =
                new RegionedPageStore.Parameters(Long.MAX_VALUE, MAXIMUM_REGION_COUNT, REGION_CAPACITY_IN_ELEMENTS);
        Assert.eq(PARAMETERS.regionMask, "parameters.regionMask", ROW_KEY_TO_SUB_REGION_ROW_INDEX_MASK,
                "ELEMENT_INDEX_TO_SUB_REGION_ELEMENT_INDEX_MASK");
        Assert.eq(PARAMETERS.regionMaskNumBits, "parameters.regionMaskNumBits", SUB_REGION_ROW_INDEX_ADDRESS_BITS,
                "SUB_REGION_ELEMENT_INDEX_ADDRESS_BITS");
    }

    RegionedColumnSourceBase(@NotNull final Class<DATA_TYPE> type, @Nullable final Class<?> componentType) {
        super(type, componentType);
    }

    RegionedColumnSourceBase(@NotNull final Class<DATA_TYPE> type) {
        this(type, null);
    }

    @Override
    public void invalidateRegion(final int regionIndex) {
        getRegion(regionIndex).invalidate();
    }

    @Override
    public void disableGrouping() {
        groupingEnabled = false;
    }

    @Override
    public final Parameters parameters() {
        return PARAMETERS;
    }

    /**
     * Use the more efficient fill chunk implementation, rather than the default which uses get().
     */
    @Override
    public void fillChunk(@NotNull FillContext context, @NotNull WritableChunk<? super Values> destination,
            @NotNull RowSequence rowSequence) {
        RegionedPageStore.super.fillChunk(context, destination, rowSequence);
    }

    /**
     * We are immutable, so stick with the efficient fill chunk even when getting prev.
     */
    @Override
    public void fillPrevChunk(@NotNull FillContext context,
            @NotNull WritableChunk<? super Values> destination, @NotNull RowSequence rowSequence) {
        fillChunk(context, destination, rowSequence);
    }

    /**
     * <p>
     * Add a pre-constructed region without going through the abstract factory method.
     * <p>
     * <em>This method is for unit testing purposes only!</em>
     *
     * @param region The region to add
     * @return The index assigned to the added region
     */
    @SuppressWarnings("UnusedReturnValue")
    @TestUseOnly
    abstract <OTHER_REGION_TYPE> int addRegionForUnitTests(final OTHER_REGION_TYPE region);

    /**
     * @return the region which represents null for this column source.
     */
    @NotNull
    abstract REGION_TYPE getNullRegion();

    @Override
    public WritableRowSet match(
            final boolean invertMatch,
            final boolean usePrev,
            final boolean caseInsensitive,
            @NotNull final RowSet rowSet,
            final Object... keys) {
        if (!USE_PUSHDOWN) {
            return super.match(invertMatch, usePrev, caseInsensitive, rowSet, keys);
        }

        Arrays.sort(keys, ObjectComparisons::compare);
        WritableRowSet result;
        if (!USE_PARALLEL) {
            result = doSequentialMatch(invertMatch, caseInsensitive, rowSet, keys);
        } else {
            result = doParallelMatch(invertMatch, caseInsensitive, rowSet, keys);
        }

        result.retain(rowSet);
        return result;
    }

    private WritableRowSet doParallelMatch(
            final boolean invertMatch,
            final boolean caseInsensitive,
            @NotNull final RowSet rowSet,
            final Object... keys) {
        // First find all the relevant regions for this set
        final List<MatchParams> relevantRegions = new ArrayList<>();
        try (final RowSequence.Iterator rowSequenceIterator = rowSet.getRowSequenceIterator()) {
            for (int regionIdx = 0; regionIdx < getRegionCount(); regionIdx++) {
                final ColumnRegion<? extends Values> region = getRegion(regionIdx);
                final long firstRegionIndex = region.firstRow(regionIdx);
                final long lastRegionIndex = region.maxRow(regionIdx);
                if (rowSequenceIterator.advance(firstRegionIndex)
                        && rowSequenceIterator.peekNextKey() <= lastRegionIndex) {
                    final RowSequence nextOrderedKeysThrough =
                            rowSequenceIterator.getNextRowSequenceThrough(lastRegionIndex);
                    relevantRegions.add(new MatchParams(region, nextOrderedKeysThrough.asRowSet(), firstRegionIndex));
                }
            }

            // Now filter them all in parallel
            final WritableRowSet result;
            if (relevantRegions.size() == 1) {
                final MatchParams p = relevantRegions.get(0);
                result = matchWithinRegion(p.region,
                        p.relevantKeys,
                        caseInsensitive,
                        invertMatch,
                        keys).copy();
            } else {
                // TODO (deephaven-core#3851): parallelize; use disk backed deferred grouping pool if ported
                final RowSetBuilderRandom resultBuilder = RowSetFactory.builderRandom();
                relevantRegions.stream()
                        .map(p -> matchWithinRegion(p.region,
                                p.relevantKeys,
                                caseInsensitive,
                                invertMatch,
                                keys))
                        .forEach(resultBuilder::addRowSet);
                result = resultBuilder.build();
            }
            return result;
        }
    }

    private WritableRowSet doSequentialMatch(
            final boolean invertMatch,
            final boolean caseInsensitive,
            @NotNull final RowSet startingRowSet,
            final Object... keys) {
        RowSetBuilderSequential resultBuilder = RowSetFactory.builderSequential();
        try (final RowSequence.Iterator okIt = startingRowSet.getRowSequenceIterator()) {
            for (int regionIdx = 0; regionIdx < getRegionCount(); regionIdx++) {
                final ColumnRegion<? extends Values> region = getRegion(regionIdx);
                final long firstRegionIndex = region.firstRow(regionIdx);
                final long lastRegionIndex = region.maxRow(regionIdx);
                if (okIt.advance(firstRegionIndex) && okIt.peekNextKey() <= lastRegionIndex) {
                    final RowSequence relevantRegionRows = okIt.getNextRowSequenceThrough(lastRegionIndex);
                    RowSet regionMatch = matchWithinRegion(region,
                            relevantRegionRows,
                            caseInsensitive,
                            invertMatch,
                            keys);
                    resultBuilder.appendRowSequence(regionMatch);
                }
            }
        }

        return resultBuilder.build();
    }

    private RowSet matchWithinRegion(
            @NotNull final ColumnRegion<? extends Values> region,
            @NotNull final RowSequence rowsToFilter,
            final boolean caseInsensitive,
            final boolean invertMatch,
            @NotNull final Object[] keys) {
        // TODO: ensure keys are sorted before parllelizing
        return region.match(invertMatch, false, caseInsensitive, rowsToFilter, keys);
    }
}
