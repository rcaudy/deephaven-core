/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned;

import io.deephaven.base.verify.Require;
import io.deephaven.chunk.attributes.Any;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.table.SharedContext;
import io.deephaven.chunk.*;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import org.jetbrains.annotations.NotNull;

import javax.annotation.OverridingMethodsMustInvokeSuper;
import java.util.function.Supplier;

/**
 * Base deferred region implementation.
 */
public abstract class DeferredColumnRegionBase<ATTR extends Any, REGION_TYPE extends ColumnRegion<ATTR>>
        extends GenericColumnRegionBase<ATTR>
        implements DeferredColumnRegion<ATTR, REGION_TYPE> {

    private Supplier<REGION_TYPE> resultRegionFactory;

    private volatile REGION_TYPE resultRegion;

    DeferredColumnRegionBase(final long pageMask, @NotNull final Supplier<REGION_TYPE> resultRegionFactory) {
        super(pageMask);
        this.resultRegionFactory = Require.neqNull(resultRegionFactory, "resultRegionFactory");
    }

    @Override
    public void invalidate() {
        super.invalidate();
        synchronized (this) {
            if (resultRegion != null) {
                resultRegion.invalidate();
            }
        }
    }

    @Override
    public final REGION_TYPE getResultRegion() {
        if (resultRegion == null) {
            synchronized (this) {
                if (resultRegion == null) {
                    resultRegion = Require.neqNull(resultRegionFactory.get(), "resultRegionFactory.get()");
                    resultRegionFactory = null;
                }
            }
        }
        return resultRegion;
    }

    /**
     * Get the result region if it has already been supplied (because of a call to {@link #getResultRegion()}).
     *
     * @return The result region
     */
    private REGION_TYPE getResultRegionIfSupplied() {
        return resultRegion;
    }

    @Override
    @OverridingMethodsMustInvokeSuper
    public void releaseCachedResources() {
        DeferredColumnRegion.super.releaseCachedResources();
        final REGION_TYPE localResultRegion = getResultRegionIfSupplied();
        if (localResultRegion != null) {
            localResultRegion.releaseCachedResources();
        }
    }

    @Override
    public ChunkType getChunkType() {
        return getResultRegion().getChunkType();
    }

    @Override
    public void fillChunk(
            @NotNull final FillContext context,
            @NotNull final WritableChunk<? super ATTR> destination,
            @NotNull final RowSequence rowSequence) {
        getResultRegion().fillChunk(context, destination, rowSequence);
    }

    @Override
    public void fillChunkAppend(
            @NotNull final FillContext context,
            @NotNull final WritableChunk<? super ATTR> destination,
            @NotNull final RowSequence.Iterator rowSequenceIterator) {
        getResultRegion().fillChunkAppend(context, destination, rowSequenceIterator);
    }

    @Override
    public Chunk<? extends ATTR> getChunk(@NotNull final GetContext context, @NotNull final RowSequence rowSequence) {
        return getResultRegion().getChunk(context, rowSequence);
    }

    @Override
    public Chunk<? extends ATTR> getChunk(@NotNull final GetContext context, final long firstKey, final long lastKey) {
        return getResultRegion().getChunk(context, firstKey, lastKey);
    }

    @Override
    public FillContext makeFillContext(final int chunkCapacity, final SharedContext sharedContext) {
        return getResultRegion().makeFillContext(chunkCapacity, sharedContext);
    }

    @Override
    public GetContext makeGetContext(final int chunkCapacity, final SharedContext sharedContext) {
        return getResultRegion().makeGetContext(chunkCapacity, sharedContext);
    }

    @Override
    public ColumnLocation getLocation() {
        return getResultRegion().getLocation();
    }

    @Override
    public boolean supportsMatching() {
        return getResultRegion().supportsMatching();
    }

    @Override
    public WritableRowSet match(
            final boolean invertMatch,
            final boolean usePrev,
            final boolean caseInsensitive,
            @NotNull final RowSequence rowSequence,
            final Object... sortedKeys) {
        return getResultRegion().match(invertMatch, usePrev, caseInsensitive, rowSequence, sortedKeys);
    }
}
