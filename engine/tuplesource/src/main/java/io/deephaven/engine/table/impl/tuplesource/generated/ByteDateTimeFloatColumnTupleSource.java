package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.chunk.ByteChunk;
import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.FloatChunk;
import io.deephaven.chunk.ObjectChunk;
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
import io.deephaven.tuple.generated.ByteLongFloatTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Byte, DateTime, and Float.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ByteDateTimeFloatColumnTupleSource extends AbstractTupleSource<ByteLongFloatTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link ByteDateTimeFloatColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<ByteLongFloatTuple, Byte, DateTime, Float> FACTORY = new Factory();

    private final ColumnSource<Byte> columnSource1;
    private final ColumnSource<DateTime> columnSource2;
    private final ColumnSource<Float> columnSource3;

    public ByteDateTimeFloatColumnTupleSource(
            @NotNull final ColumnSource<Byte> columnSource1,
            @NotNull final ColumnSource<DateTime> columnSource2,
            @NotNull final ColumnSource<Float> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final ByteLongFloatTuple createTuple(final long rowKey) {
        return new ByteLongFloatTuple(
                columnSource1.getByte(rowKey),
                DateTimeUtils.nanos(columnSource2.get(rowKey)),
                columnSource3.getFloat(rowKey)
        );
    }

    @Override
    public final ByteLongFloatTuple createPreviousTuple(final long rowKey) {
        return new ByteLongFloatTuple(
                columnSource1.getPrevByte(rowKey),
                DateTimeUtils.nanos(columnSource2.getPrev(rowKey)),
                columnSource3.getPrevFloat(rowKey)
        );
    }

    @Override
    public final ByteLongFloatTuple createTupleFromValues(@NotNull final Object... values) {
        return new ByteLongFloatTuple(
                TypeUtils.unbox((Byte)values[0]),
                DateTimeUtils.nanos((DateTime)values[1]),
                TypeUtils.unbox((Float)values[2])
        );
    }

    @Override
    public final ByteLongFloatTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new ByteLongFloatTuple(
                TypeUtils.unbox((Byte)values[0]),
                DateTimeUtils.nanos((DateTime)values[1]),
                TypeUtils.unbox((Float)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final ByteLongFloatTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationRowKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationRowKey, tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationRowKey, (ELEMENT_TYPE) DateTimeUtils.nanosToDateTime(tuple.getSecondElement()));
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationRowKey, tuple.getThirdElement());
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportElement(@NotNull final ByteLongFloatTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToDateTime(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final ByteLongFloatTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToDateTime(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<? extends Values> [] chunks) {
        WritableObjectChunk<ByteLongFloatTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ByteChunk<? extends Values> chunk1 = chunks[0].asByteChunk();
        ObjectChunk<DateTime, ? extends Values> chunk2 = chunks[1].asObjectChunk();
        FloatChunk<? extends Values> chunk3 = chunks[2].asFloatChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new ByteLongFloatTuple(chunk1.get(ii), DateTimeUtils.nanos(chunk2.get(ii)), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link ByteDateTimeFloatColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<ByteLongFloatTuple, Byte, DateTime, Float> {

        private Factory() {
        }

        @Override
        public TupleSource<ByteLongFloatTuple> create(
                @NotNull final ColumnSource<Byte> columnSource1,
                @NotNull final ColumnSource<DateTime> columnSource2,
                @NotNull final ColumnSource<Float> columnSource3
        ) {
            return new ByteDateTimeFloatColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
