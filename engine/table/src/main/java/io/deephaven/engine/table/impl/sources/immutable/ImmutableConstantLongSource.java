//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit ImmutableConstantCharSource and run "./gradlew replicateSourcesAndChunks" to regenerate
//
// @formatter:off
package io.deephaven.engine.table.impl.sources.immutable;

import java.time.Instant;
import java.time.ZonedDateTime;
import java.time.LocalDate;
import java.time.LocalTime;
import io.deephaven.base.verify.Require;
import java.time.ZoneId;

import io.deephaven.engine.table.ColumnSource;

import io.deephaven.chunk.LongChunk;
import io.deephaven.chunk.WritableLongChunk;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.chunkattributes.RowKeys;
import io.deephaven.engine.table.impl.*;
import io.deephaven.engine.table.impl.select.WhereFilter;
import io.deephaven.engine.table.impl.sources.*;
import io.deephaven.engine.table.impl.util.JobScheduler;
import org.jetbrains.annotations.NotNull;

import java.util.function.Consumer;
import java.util.function.LongConsumer;

import static io.deephaven.engine.rowset.RowSequence.NULL_ROW_KEY;

// region boxing imports
import static io.deephaven.util.QueryConstants.NULL_LONG;
// endregion boxing imports

/**
 * Constant-value immutable {@link io.deephaven.engine.table.ColumnSource} of {@code long}.
 */
public class ImmutableConstantLongSource
        extends AbstractColumnSource<Long>
        implements ImmutableColumnSourceGetDefaults.ForLong, InMemoryColumnSource,
        RowKeyAgnosticChunkSource<Values> , ConvertibleTimeSource {

    private final long value;

    // region constructor
    public ImmutableConstantLongSource(final long value) {
        super(Long.class);
        this.value = value;
    }
    // endregion constructor

    @Override
    public final long getLong(final long rowKey) {
        if (rowKey == NULL_ROW_KEY) {
            return NULL_LONG;
        }
        return value;
    }

    @Override
    public final void fillChunk(
            @NotNull final FillContext context,
            @NotNull final WritableChunk<? super Values> destination,
            @NotNull final RowSequence rowSequence) {
        final int size = rowSequence.intSize();
        destination.setSize(size);
        destination.asWritableLongChunk().fillWithValue(0, size, value);
    }

    @Override
    public final void fillPrevChunk(
            @NotNull final FillContext context,
            @NotNull final WritableChunk<? super Values> destination,
            @NotNull final RowSequence rowSequence) {
        fillChunk(context, destination, rowSequence);
    }

    @Override
    public void fillChunkUnordered(
            @NotNull FillContext context,
            @NotNull WritableChunk<? super Values> dest,
            @NotNull LongChunk<? extends RowKeys> keys) {
        final WritableLongChunk<? super Values> destChunk = dest.asWritableLongChunk();
        for (int ii = 0; ii < keys.size(); ++ii) {
            destChunk.set(ii, keys.get(ii) == RowSequence.NULL_ROW_KEY ? NULL_LONG : value);
        }
        destChunk.setSize(keys.size());
    }

    @Override
    public void fillPrevChunkUnordered(
            @NotNull FillContext context,
            @NotNull WritableChunk<? super Values> dest,
            @NotNull LongChunk<? extends RowKeys> keys) {
        fillChunkUnordered(context, dest, keys);
    }

    @Override
    public boolean providesFillUnordered() {
        return true;
    }

    @Override
    public void estimatePushdownFilterCost(
            final WhereFilter filter,
            final RowSet selection,
            final boolean usePrev,
            final PushdownFilterContext context,
            final JobScheduler jobScheduler,
            final LongConsumer onComplete,
            final Consumer<Exception> onError) {
        // Delegate to the shared code for RowKeyAgnosticChunkSource
        RowKeyAgnosticChunkSource.estimatePushdownFilterCostHelper(
                filter, selection, usePrev, context, jobScheduler, onComplete, onError);
    }

    @Override
    public void pushdownFilter(
            final WhereFilter filter,
            final RowSet selection,
            final boolean usePrev,
            final PushdownFilterContext context,
            final long costCeiling,
            final JobScheduler jobScheduler,
            final Consumer<PushdownResult> onComplete,
            final Consumer<Exception> onError) {
        // Delegate to the shared code for RowKeyAgnosticChunkSource
        RowKeyAgnosticChunkSource.pushdownFilterHelper(this, filter, selection, usePrev, context, costCeiling,
                jobScheduler, onComplete, onError);
    }

    // region reinterpretation
    @Override
    public <ALTERNATE_DATA_TYPE> boolean allowsReinterpret(@NotNull final Class<ALTERNATE_DATA_TYPE> alternateDataType) {
        return alternateDataType == long.class || alternateDataType == Instant.class;
    }

    @SuppressWarnings("unchecked")
    @Override
    protected <ALTERNATE_DATA_TYPE> ColumnSource<ALTERNATE_DATA_TYPE> doReinterpret(@NotNull Class<ALTERNATE_DATA_TYPE> alternateDataType) {
        if (alternateDataType == this.getType()) {
            return (ColumnSource<ALTERNATE_DATA_TYPE>) this;
        } else if (alternateDataType == Instant.class) {
            return (ColumnSource<ALTERNATE_DATA_TYPE>) toInstant();
        }

        throw new IllegalArgumentException("Cannot reinterpret `" + getType().getName() + "` to `" + alternateDataType.getName() + "`");
    }

    @Override
    public boolean supportsTimeConversion() {
        return true;
    }

    @Override
    public ColumnSource<ZonedDateTime> toZonedDateTime(@NotNull final ZoneId zone) {
        return new ImmutableConstantZonedDateTimeSource(Require.neqNull(zone, "zone"), this);
    }

    @Override
    public ColumnSource<LocalDate> toLocalDate(@NotNull final ZoneId zone) {
        return new LongAsLocalDateColumnSource(this, zone);
    }

    @Override
    public ColumnSource<LocalTime> toLocalTime(@NotNull final ZoneId zone) {
        return new LongAsLocalTimeColumnSource(this, zone);
    }

    @Override
    public ColumnSource<Instant> toInstant() {
        return new ImmutableConstantInstantSource(this);
    }

    @Override
    public ColumnSource<Long> toEpochNano() {
        return this;
    }
    // endregion reinterpretation
}
