package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.ByteChunk;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.LongChunk;
import io.deephaven.engine.chunk.ObjectChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.engine.time.DateTime;
import io.deephaven.engine.time.DateTimeUtils;
import io.deephaven.engine.tuple.generated.LongObjectByteTuple;
import io.deephaven.util.BooleanUtils;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Long, Object, and Byte.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ReinterpretedDateTimeObjectReinterpretedBooleanColumnTupleSource extends AbstractTupleSource<LongObjectByteTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link ReinterpretedDateTimeObjectReinterpretedBooleanColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<LongObjectByteTuple, Long, Object, Byte> FACTORY = new Factory();

    private final ColumnSource<Long> columnSource1;
    private final ColumnSource<Object> columnSource2;
    private final ColumnSource<Byte> columnSource3;

    public ReinterpretedDateTimeObjectReinterpretedBooleanColumnTupleSource(
            @NotNull final ColumnSource<Long> columnSource1,
            @NotNull final ColumnSource<Object> columnSource2,
            @NotNull final ColumnSource<Byte> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final LongObjectByteTuple createTuple(final long rowKey) {
        return new LongObjectByteTuple(
                columnSource1.getLong(rowKey),
                columnSource2.get(rowKey),
                columnSource3.getByte(rowKey)
        );
    }

    @Override
    public final LongObjectByteTuple createPreviousTuple(final long rowKey) {
        return new LongObjectByteTuple(
                columnSource1.getPrevLong(rowKey),
                columnSource2.getPrev(rowKey),
                columnSource3.getPrevByte(rowKey)
        );
    }

    @Override
    public final LongObjectByteTuple createTupleFromValues(@NotNull final Object... values) {
        return new LongObjectByteTuple(
                DateTimeUtils.nanos((DateTime)values[0]),
                values[1],
                BooleanUtils.booleanAsByte((Boolean)values[2])
        );
    }

    @Override
    public final LongObjectByteTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new LongObjectByteTuple(
                TypeUtils.unbox((Long)values[0]),
                values[1],
                TypeUtils.unbox((Byte)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final LongObjectByteTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) DateTimeUtils.nanosToTime(tuple.getFirstElement()));
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) tuple.getSecondElement());
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) BooleanUtils.byteAsBoolean(tuple.getThirdElement()));
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final LongObjectByteTuple tuple) {
        return new SmartKey(
                DateTimeUtils.nanosToTime(tuple.getFirstElement()),
                tuple.getSecondElement(),
                BooleanUtils.byteAsBoolean(tuple.getThirdElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final LongObjectByteTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return DateTimeUtils.nanosToTime(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return tuple.getSecondElement();
        }
        if (elementIndex == 2) {
            return BooleanUtils.byteAsBoolean(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final LongObjectByteTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return tuple.getSecondElement();
        }
        if (elementIndex == 2) {
            return TypeUtils.box(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<LongObjectByteTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        LongChunk<Values> chunk1 = chunks[0].asLongChunk();
        ObjectChunk<Object, Values> chunk2 = chunks[1].asObjectChunk();
        ByteChunk<Values> chunk3 = chunks[2].asByteChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new LongObjectByteTuple(chunk1.get(ii), chunk2.get(ii), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link ReinterpretedDateTimeObjectReinterpretedBooleanColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<LongObjectByteTuple, Long, Object, Byte> {

        private Factory() {
        }

        @Override
        public TupleSource<LongObjectByteTuple> create(
                @NotNull final ColumnSource<Long> columnSource1,
                @NotNull final ColumnSource<Object> columnSource2,
                @NotNull final ColumnSource<Byte> columnSource3
        ) {
            return new ReinterpretedDateTimeObjectReinterpretedBooleanColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
