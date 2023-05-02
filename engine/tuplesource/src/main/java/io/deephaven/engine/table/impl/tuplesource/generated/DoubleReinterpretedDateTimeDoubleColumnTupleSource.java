package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.DoubleChunk;
import io.deephaven.chunk.LongChunk;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.chunk.WritableObjectChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.time.DateTime;
import io.deephaven.time.DateTimeUtils;
import io.deephaven.tuple.generated.DoubleLongDoubleTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Double, Long, and Double.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class DoubleReinterpretedDateTimeDoubleColumnTupleSource extends AbstractTupleSource<DoubleLongDoubleTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link DoubleReinterpretedDateTimeDoubleColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<DoubleLongDoubleTuple, Double, Long, Double> FACTORY = new Factory();

    private final ColumnSource<Double> columnSource1;
    private final ColumnSource<Long> columnSource2;
    private final ColumnSource<Double> columnSource3;

    public DoubleReinterpretedDateTimeDoubleColumnTupleSource(
            @NotNull final ColumnSource<Double> columnSource1,
            @NotNull final ColumnSource<Long> columnSource2,
            @NotNull final ColumnSource<Double> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final DoubleLongDoubleTuple createTuple(final long rowKey) {
        return new DoubleLongDoubleTuple(
                columnSource1.getDouble(rowKey),
                columnSource2.getLong(rowKey),
                columnSource3.getDouble(rowKey)
        );
    }

    @Override
    public final DoubleLongDoubleTuple createPreviousTuple(final long rowKey) {
        return new DoubleLongDoubleTuple(
                columnSource1.getPrevDouble(rowKey),
                columnSource2.getPrevLong(rowKey),
                columnSource3.getPrevDouble(rowKey)
        );
    }

    @Override
    public final DoubleLongDoubleTuple createTupleFromValues(@NotNull final Object... values) {
        return new DoubleLongDoubleTuple(
                TypeUtils.unbox((Double)values[0]),
                DateTimeUtils.epochNanos((DateTime)values[1]),
                TypeUtils.unbox((Double)values[2])
        );
    }

    @Override
    public final DoubleLongDoubleTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new DoubleLongDoubleTuple(
                TypeUtils.unbox((Double)values[0]),
                TypeUtils.unbox((Long)values[1]),
                TypeUtils.unbox((Double)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final DoubleLongDoubleTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationRowKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationRowKey, tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationRowKey, (ELEMENT_TYPE) DateTimeUtils.epochNanosToDateTime(tuple.getSecondElement()));
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationRowKey, tuple.getThirdElement());
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportElement(@NotNull final DoubleLongDoubleTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.epochNanosToDateTime(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final DoubleLongDoubleTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<? extends Values> [] chunks) {
        WritableObjectChunk<DoubleLongDoubleTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        DoubleChunk<? extends Values> chunk1 = chunks[0].asDoubleChunk();
        LongChunk<? extends Values> chunk2 = chunks[1].asLongChunk();
        DoubleChunk<? extends Values> chunk3 = chunks[2].asDoubleChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new DoubleLongDoubleTuple(chunk1.get(ii), chunk2.get(ii), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link DoubleReinterpretedDateTimeDoubleColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<DoubleLongDoubleTuple, Double, Long, Double> {

        private Factory() {
        }

        @Override
        public TupleSource<DoubleLongDoubleTuple> create(
                @NotNull final ColumnSource<Double> columnSource1,
                @NotNull final ColumnSource<Long> columnSource2,
                @NotNull final ColumnSource<Double> columnSource3
        ) {
            return new DoubleReinterpretedDateTimeDoubleColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
