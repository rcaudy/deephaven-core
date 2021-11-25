package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.LongChunk;
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
import io.deephaven.engine.tuple.generated.ObjectLongShortTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Object, Long, and Short.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ObjectReinterpretedDateTimeShortColumnTupleSource extends AbstractTupleSource<ObjectLongShortTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link ObjectReinterpretedDateTimeShortColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<ObjectLongShortTuple, Object, Long, Short> FACTORY = new Factory();

    private final ColumnSource<Object> columnSource1;
    private final ColumnSource<Long> columnSource2;
    private final ColumnSource<Short> columnSource3;

    public ObjectReinterpretedDateTimeShortColumnTupleSource(
            @NotNull final ColumnSource<Object> columnSource1,
            @NotNull final ColumnSource<Long> columnSource2,
            @NotNull final ColumnSource<Short> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final ObjectLongShortTuple createTuple(final long indexKey) {
        return new ObjectLongShortTuple(
                columnSource1.get(indexKey),
                columnSource2.getLong(indexKey),
                columnSource3.getShort(indexKey)
        );
    }

    @Override
    public final ObjectLongShortTuple createPreviousTuple(final long indexKey) {
        return new ObjectLongShortTuple(
                columnSource1.getPrev(indexKey),
                columnSource2.getPrevLong(indexKey),
                columnSource3.getPrevShort(indexKey)
        );
    }

    @Override
    public final ObjectLongShortTuple createTupleFromValues(@NotNull final Object... values) {
        return new ObjectLongShortTuple(
                values[0],
                DateTimeUtils.nanos((DateTime)values[1]),
                TypeUtils.unbox((Short)values[2])
        );
    }

    @Override
    public final ObjectLongShortTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new ObjectLongShortTuple(
                values[0],
                TypeUtils.unbox((Long)values[1]),
                TypeUtils.unbox((Short)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final ObjectLongShortTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) tuple.getFirstElement());
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
    public final Object exportToExternalKey(@NotNull final ObjectLongShortTuple tuple) {
        return new SmartKey(
                tuple.getFirstElement(),
                DateTimeUtils.nanosToTime(tuple.getSecondElement()),
                TypeUtils.box(tuple.getThirdElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final ObjectLongShortTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return tuple.getFirstElement();
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
    public final Object exportElementReinterpreted(@NotNull final ObjectLongShortTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return tuple.getFirstElement();
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
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<ObjectLongShortTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ObjectChunk<Object, Values> chunk1 = chunks[0].asObjectChunk();
        LongChunk<Values> chunk2 = chunks[1].asLongChunk();
        ShortChunk<Values> chunk3 = chunks[2].asShortChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new ObjectLongShortTuple(chunk1.get(ii), chunk2.get(ii), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link ObjectReinterpretedDateTimeShortColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<ObjectLongShortTuple, Object, Long, Short> {

        private Factory() {
        }

        @Override
        public TupleSource<ObjectLongShortTuple> create(
                @NotNull final ColumnSource<Object> columnSource1,
                @NotNull final ColumnSource<Long> columnSource2,
                @NotNull final ColumnSource<Short> columnSource3
        ) {
            return new ObjectReinterpretedDateTimeShortColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
