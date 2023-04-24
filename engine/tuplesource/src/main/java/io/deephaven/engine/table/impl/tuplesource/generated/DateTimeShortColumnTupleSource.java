package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.ObjectChunk;
import io.deephaven.chunk.ShortChunk;
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
import io.deephaven.tuple.generated.LongShortTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types DateTime and Short.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class DateTimeShortColumnTupleSource extends AbstractTupleSource<LongShortTuple> {

    /** {@link TwoColumnTupleSourceFactory} instance to create instances of {@link DateTimeShortColumnTupleSource}. **/
    public static final TwoColumnTupleSourceFactory<LongShortTuple, DateTime, Short> FACTORY = new Factory();

    private final ColumnSource<DateTime> columnSource1;
    private final ColumnSource<Short> columnSource2;

    public DateTimeShortColumnTupleSource(
            @NotNull final ColumnSource<DateTime> columnSource1,
            @NotNull final ColumnSource<Short> columnSource2
    ) {
        super(columnSource1, columnSource2);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
    }

    @Override
    public final LongShortTuple createTuple(final long rowKey) {
        return new LongShortTuple(
                DateTimeUtils.nanos(columnSource1.get(rowKey)),
                columnSource2.getShort(rowKey)
        );
    }

    @Override
    public final LongShortTuple createPreviousTuple(final long rowKey) {
        return new LongShortTuple(
                DateTimeUtils.nanos(columnSource1.getPrev(rowKey)),
                columnSource2.getPrevShort(rowKey)
        );
    }

    @Override
    public final LongShortTuple createTupleFromValues(@NotNull final Object... values) {
        return new LongShortTuple(
                DateTimeUtils.nanos((DateTime)values[0]),
                TypeUtils.unbox((Short)values[1])
        );
    }

    @Override
    public final LongShortTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new LongShortTuple(
                DateTimeUtils.nanos((DateTime)values[0]),
                TypeUtils.unbox((Short)values[1])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final LongShortTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationRowKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationRowKey, (ELEMENT_TYPE) DateTimeUtils.nanosToDateTime(tuple.getFirstElement()));
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationRowKey, tuple.getSecondElement());
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportElement(@NotNull final LongShortTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return DateTimeUtils.nanosToDateTime(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final LongShortTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return DateTimeUtils.nanosToDateTime(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<? extends Values> [] chunks) {
        WritableObjectChunk<LongShortTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ObjectChunk<DateTime, ? extends Values> chunk1 = chunks[0].asObjectChunk();
        ShortChunk<? extends Values> chunk2 = chunks[1].asShortChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new LongShortTuple(DateTimeUtils.nanos(chunk1.get(ii)), chunk2.get(ii)));
        }
        destination.setSize(chunkSize);
    }

    /** {@link TwoColumnTupleSourceFactory} for instances of {@link DateTimeShortColumnTupleSource}. **/
    private static final class Factory implements TwoColumnTupleSourceFactory<LongShortTuple, DateTime, Short> {

        private Factory() {
        }

        @Override
        public TupleSource<LongShortTuple> create(
                @NotNull final ColumnSource<DateTime> columnSource1,
                @NotNull final ColumnSource<Short> columnSource2
        ) {
            return new DateTimeShortColumnTupleSource(
                    columnSource1,
                    columnSource2
            );
        }
    }
}
