/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.parquet.table.region;

import io.deephaven.base.verify.Require;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.SharedContext;
import io.deephaven.engine.table.impl.chunkfilter.ChunkFilter;
import io.deephaven.engine.table.impl.chunkfilter.ChunkMatchFilterFactory;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import io.deephaven.engine.table.impl.sources.regioned.GenericColumnRegionBase;
import io.deephaven.parquet.table.location.ParquetColumnLocation;
import io.deephaven.parquet.table.pagestore.ColumnChunkPageStore;
import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.engine.page.ChunkPage;
import io.deephaven.engine.rowset.RowSequence;
import org.jetbrains.annotations.NotNull;

import javax.annotation.OverridingMethodsMustInvokeSuper;

public abstract class ParquetColumnRegionBase<ATTR extends Values>
        extends GenericColumnRegionBase<ATTR>
        implements ParquetColumnRegion<ATTR> {

    final ParquetColumnLocation<Values> location;
    final ColumnChunkPageStore<ATTR> columnChunkPageStore;

    ParquetColumnRegionBase(
            final long pageMask,
            @NotNull final ColumnChunkPageStore<ATTR> columnChunkPageStore,
            @NotNull final ParquetColumnLocation<Values> location) {
        super(pageMask);
        this.location = location;
        this.columnChunkPageStore = Require.neqNull(columnChunkPageStore, "columnChunkPageStore");

        // We are making the following assumptions, so these basic functions are inlined rather than virtual calls.
        Require.eq(columnChunkPageStore.mask(), "columnChunkPageStore.mask()", mask(), "ColumnRegion.mask()");
        Require.eq(columnChunkPageStore.firstRowOffset(), "columnChunkPageStore.firstRowOffset()",
                firstRowOffset(), "ColumnRegion.firstRowOffset()");
    }

    @Override
    public final Chunk<? extends ATTR> getChunk(
            @NotNull final GetContext context,
            @NotNull final RowSequence rowSequence) {
        throwIfInvalidated();
        return columnChunkPageStore.getChunk(context, rowSequence);
    }

    @Override
    public final Chunk<? extends ATTR> getChunk(
            @NotNull final GetContext context,
            final long firstKey,
            final long lastKey) {
        throwIfInvalidated();
        return columnChunkPageStore.getChunk(context, firstKey, lastKey);
    }

    @Override
    public final void fillChunk(
            @NotNull final FillContext context,
            @NotNull final WritableChunk<? super ATTR> destination,
            @NotNull final RowSequence rowSequence) {
        throwIfInvalidated();
        columnChunkPageStore.fillChunk(context, destination, rowSequence);
    }

    @Override
    public final void fillChunkAppend(
            @NotNull final FillContext context,
            @NotNull final WritableChunk<? super ATTR> destination,
            @NotNull final RowSequence.Iterator rowSequenceIterator) {
        throwIfInvalidated();
        columnChunkPageStore.fillChunkAppend(context, destination, rowSequenceIterator);
    }

    @Override
    public final ChunkPage<ATTR> getChunkPageContaining(final long elementIndex) {
        throwIfInvalidated();
        return columnChunkPageStore.getPageContaining(null, elementIndex);
    }

    @Override
    @OverridingMethodsMustInvokeSuper
    public void releaseCachedResources() {
        ParquetColumnRegion.super.releaseCachedResources();
        columnChunkPageStore.releaseCachedResources();
    }

    @Override
    public final FillContext makeFillContext(final int chunkCapacity, final SharedContext sharedContext) {
        throwIfInvalidated();
        return columnChunkPageStore.makeFillContext(chunkCapacity, sharedContext);
    }

    @Override
    public final GetContext makeGetContext(final int chunkCapacity, final SharedContext sharedContext) {
        throwIfInvalidated();
        return columnChunkPageStore.makeGetContext(chunkCapacity, sharedContext);
    }

    @Override
    public ColumnLocation getLocation() {
        return location;
    }

    @Override
    public final boolean supportsMatching() {
        return true;
    }

    @Override
    public WritableRowSet match(
            final boolean invertMatch,
            final boolean usePrev,
            final boolean caseInsensitive,
            @NotNull final RowSequence rowSequence,
            final Object... sortedKeys) {
        // TODO: push down to fill in native type
        try (final RowSet rows = rowSequence.asRowSet()) {
            return ChunkFilter.applyChunkFilter(rows, this, false,
                    ChunkMatchFilterFactory.getChunkFilter(null, caseInsensitive, invertMatch, sortedKeys));
        }
    }
}
