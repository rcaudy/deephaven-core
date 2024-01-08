/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned;

import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.ChunkSource;
import io.deephaven.engine.table.GetContextMaker;
import io.deephaven.engine.table.SharedContext;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.engine.page.Page;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.table.impl.chunkfilter.ChunkFilter;
import io.deephaven.engine.table.impl.chunkfilter.ChunkMatchFilterFactory;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.annotation.OverridingMethodsMustInvokeSuper;

public class ColumnRegionReferencingImpl<ATTR extends Any, REFERENCED_COLUMN_REGION extends ColumnRegion<ATTR>>
        implements ColumnRegionReferencing<ATTR, REFERENCED_COLUMN_REGION>, Page.WithDefaults<ATTR> {

    private final REFERENCED_COLUMN_REGION referencedColumnRegion;
    @NotNull
    private final Converter<ATTR> converter;

    public ColumnRegionReferencingImpl(
            @NotNull final REFERENCED_COLUMN_REGION referencedColumnRegion,
            @NotNull final Converter<ATTR> converter) {
        this.referencedColumnRegion = referencedColumnRegion;
        this.converter = converter;
    }

    @Override
    public void invalidate() {
        referencedColumnRegion.invalidate();
    }

    @NotNull
    @Override
    public REFERENCED_COLUMN_REGION getReferencedRegion() {
        return referencedColumnRegion;
    }

    @Override
    public long mask() {
        return getReferencedRegion().mask();
    }

    @Override
    public void fillChunkAppend(@NotNull ChunkSource.FillContext context,
            @NotNull WritableChunk<? super ATTR> destination, @NotNull RowSequence rowSequence) {
        converter.convertRegion(destination,
                referencedColumnRegion.getChunk(FillContext.nativeGetContext(context), rowSequence), rowSequence);
    }

    @Override
    public ChunkSource.FillContext makeFillContext(
            final int chunkCapacity, @Nullable final SharedContext sharedContext) {
        return new FillContext(referencedColumnRegion, chunkCapacity, sharedContext);
    }

    @Override
    @OverridingMethodsMustInvokeSuper
    public void releaseCachedResources() {
        ColumnRegionReferencing.super.releaseCachedResources();
        referencedColumnRegion.releaseCachedResources();
    }

    @Override
    public ColumnLocation getLocation() {
        return referencedColumnRegion.getLocation();
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
        final Object[] nativeKeys = converter.convertArray(sortedKeys);
        try (final RowSet rows = rowSequence.asRowSet()) {
            // TODO NATE NOCOMMIT: getNativeType? or pushdown?
            // noinspection unchecked
            return ChunkFilter.applyChunkFilter(rows, (ChunkSource<? extends Values>) referencedColumnRegion, false,
                    ChunkMatchFilterFactory.getChunkFilter(
                            null, caseInsensitive, invertMatch, nativeKeys));
            // referencedColumnRegion.getNativeType(), caseInsensitive, invertMatch, nativeKeys));
        }
    }

    static class FillContext<ATTR extends Any> implements ChunkSource.FillContext {
        private final ChunkSource.GetContext nativeGetContext;

        FillContext(
                @NotNull final GetContextMaker getContextMaker,
                int chunkCapacity,
                @Nullable final SharedContext sharedContext) {
            this.nativeGetContext = getContextMaker.makeGetContext(chunkCapacity, sharedContext);
        }

        static ChunkSource.GetContext nativeGetContext(@NotNull final ChunkSource.FillContext context) {
            return ((FillContext<?>) context).nativeGetContext;
        }

        @Override
        public void close() {
            nativeGetContext.close();
        }
    }
}
