package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.ObjectChunk;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.chunk.WritableObjectChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.TwoColumnTupleSourceFactory;
import io.deephaven.time.DateTime;
import io.deephaven.time.DateTimeUtils;
import io.deephaven.tuple.generated.LongByteTuple;
import io.deephaven.util.BooleanUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types DateTime and Boolean.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class DateTimeBooleanColumnTupleSource extends AbstractTupleSource<LongByteTuple> {

    /** {@link TwoColumnTupleSourceFactory} instance to create instances of {@link DateTimeBooleanColumnTupleSource}. **/
    public static final TwoColumnTupleSourceFactory<LongByteTuple, DateTime, Boolean> FACTORY = new Factory();

    private final ColumnSource<DateTime> columnSource1;
    private final ColumnSource<Boolean> columnSource2;

    public DateTimeBooleanColumnTupleSource(
            @NotNull final ColumnSource<DateTime> columnSource1,
            @NotNull final ColumnSource<Boolean> columnSource2
    ) {
        super(columnSource1, columnSource2);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
    }

    @Override
    public final LongByteTuple createTuple(final long rowKey) {
        return new LongByteTuple(
                DateTimeUtils.epochNanos(columnSource1.get(rowKey)),
                BooleanUtils.booleanAsByte(columnSource2.getBoolean(rowKey))
        );
    }

    @Override
    public final LongByteTuple createPreviousTuple(final long rowKey) {
        return new LongByteTuple(
                DateTimeUtils.epochNanos(columnSource1.getPrev(rowKey)),
                BooleanUtils.booleanAsByte(columnSource2.getPrevBoolean(rowKey))
        );
    }

    @Override
    public final LongByteTuple createTupleFromValues(@NotNull final Object... values) {
        return new LongByteTuple(
                DateTimeUtils.epochNanos((DateTime)values[0]),
                BooleanUtils.booleanAsByte((Boolean)values[1])
        );
    }

    @Override
    public final LongByteTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new LongByteTuple(
                DateTimeUtils.epochNanos((DateTime)values[0]),
                BooleanUtils.booleanAsByte((Boolean)values[1])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final LongByteTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationRowKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationRowKey, (ELEMENT_TYPE) DateTimeUtils.epochNanosToDateTime(tuple.getFirstElement()));
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationRowKey, (ELEMENT_TYPE) BooleanUtils.byteAsBoolean(tuple.getSecondElement()));
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportElement(@NotNull final LongByteTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return DateTimeUtils.epochNanosToDateTime(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return BooleanUtils.byteAsBoolean(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final LongByteTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return DateTimeUtils.epochNanosToDateTime(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return BooleanUtils.byteAsBoolean(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<? extends Values> [] chunks) {
        WritableObjectChunk<LongByteTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ObjectChunk<DateTime, ? extends Values> chunk1 = chunks[0].asObjectChunk();
        ObjectChunk<Boolean, ? extends Values> chunk2 = chunks[1].asObjectChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new LongByteTuple(DateTimeUtils.epochNanos(chunk1.get(ii)), BooleanUtils.booleanAsByte(chunk2.get(ii))));
        }
        destination.setSize(chunkSize);
    }

    /** {@link TwoColumnTupleSourceFactory} for instances of {@link DateTimeBooleanColumnTupleSource}. **/
    private static final class Factory implements TwoColumnTupleSourceFactory<LongByteTuple, DateTime, Boolean> {

        private Factory() {
        }

        @Override
        public TupleSource<LongByteTuple> create(
                @NotNull final ColumnSource<DateTime> columnSource1,
                @NotNull final ColumnSource<Boolean> columnSource2
        ) {
            return new DateTimeBooleanColumnTupleSource(
                    columnSource1,
                    columnSource2
            );
        }
    }
}
