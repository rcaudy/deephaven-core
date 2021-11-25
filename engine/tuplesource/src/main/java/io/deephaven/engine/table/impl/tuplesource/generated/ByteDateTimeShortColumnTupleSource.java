package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.ByteChunk;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.ObjectChunk;
import io.deephaven.engine.chunk.ShortChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.engine.time.DateTime;
import io.deephaven.engine.time.DateTimeUtils;
import io.deephaven.engine.tuple.generated.ByteLongShortTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Byte, DateTime, and Short.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ByteDateTimeShortColumnTupleSource extends AbstractTupleSource<ByteLongShortTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link ByteDateTimeShortColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<ByteLongShortTuple, Byte, DateTime, Short> FACTORY = new Factory();

    private final ColumnSource<Byte> columnSource1;
    private final ColumnSource<DateTime> columnSource2;
    private final ColumnSource<Short> columnSource3;

    public ByteDateTimeShortColumnTupleSource(
            @NotNull final ColumnSource<Byte> columnSource1,
            @NotNull final ColumnSource<DateTime> columnSource2,
            @NotNull final ColumnSource<Short> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final ByteLongShortTuple createTuple(final long indexKey) {
        return new ByteLongShortTuple(
                columnSource1.getByte(indexKey),
                DateTimeUtils.nanos(columnSource2.get(indexKey)),
                columnSource3.getShort(indexKey)
        );
    }

    @Override
    public final ByteLongShortTuple createPreviousTuple(final long indexKey) {
        return new ByteLongShortTuple(
                columnSource1.getPrevByte(indexKey),
                DateTimeUtils.nanos(columnSource2.getPrev(indexKey)),
                columnSource3.getPrevShort(indexKey)
        );
    }

    @Override
    public final ByteLongShortTuple createTupleFromValues(@NotNull final Object... values) {
        return new ByteLongShortTuple(
                TypeUtils.unbox((Byte)values[0]),
                DateTimeUtils.nanos((DateTime)values[1]),
                TypeUtils.unbox((Short)values[2])
        );
    }

    @Override
    public final ByteLongShortTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new ByteLongShortTuple(
                TypeUtils.unbox((Byte)values[0]),
                DateTimeUtils.nanos((DateTime)values[1]),
                TypeUtils.unbox((Short)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final ByteLongShortTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) DateTimeUtils.nanosToTime(tuple.getSecondElement()));
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationIndexKey, tuple.getThirdElement());
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final ByteLongShortTuple tuple) {
        return new SmartKey(
                TypeUtils.box(tuple.getFirstElement()),
                DateTimeUtils.nanosToTime(tuple.getSecondElement()),
                TypeUtils.box(tuple.getThirdElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final ByteLongShortTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToTime(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final ByteLongShortTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToTime(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<ByteLongShortTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ByteChunk<Values> chunk1 = chunks[0].asByteChunk();
        ObjectChunk<DateTime, Values> chunk2 = chunks[1].asObjectChunk();
        ShortChunk<Values> chunk3 = chunks[2].asShortChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new ByteLongShortTuple(chunk1.get(ii), DateTimeUtils.nanos(chunk2.get(ii)), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link ByteDateTimeShortColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<ByteLongShortTuple, Byte, DateTime, Short> {

        private Factory() {
        }

        @Override
        public TupleSource<ByteLongShortTuple> create(
                @NotNull final ColumnSource<Byte> columnSource1,
                @NotNull final ColumnSource<DateTime> columnSource2,
                @NotNull final ColumnSource<Short> columnSource3
        ) {
            return new ByteDateTimeShortColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
