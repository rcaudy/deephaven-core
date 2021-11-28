package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.DoubleChunk;
import io.deephaven.engine.chunk.ObjectChunk;
import io.deephaven.engine.chunk.ShortChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.engine.tuple.generated.ObjectDoubleShortTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Object, Double, and Short.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ObjectDoubleShortColumnTupleSource extends AbstractTupleSource<ObjectDoubleShortTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link ObjectDoubleShortColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<ObjectDoubleShortTuple, Object, Double, Short> FACTORY = new Factory();

    private final ColumnSource<Object> columnSource1;
    private final ColumnSource<Double> columnSource2;
    private final ColumnSource<Short> columnSource3;

    public ObjectDoubleShortColumnTupleSource(
            @NotNull final ColumnSource<Object> columnSource1,
            @NotNull final ColumnSource<Double> columnSource2,
            @NotNull final ColumnSource<Short> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final ObjectDoubleShortTuple createTuple(final long rowKey) {
        return new ObjectDoubleShortTuple(
                columnSource1.get(rowKey),
                columnSource2.getDouble(rowKey),
                columnSource3.getShort(rowKey)
        );
    }

    @Override
    public final ObjectDoubleShortTuple createPreviousTuple(final long rowKey) {
        return new ObjectDoubleShortTuple(
                columnSource1.getPrev(rowKey),
                columnSource2.getPrevDouble(rowKey),
                columnSource3.getPrevShort(rowKey)
        );
    }

    @Override
    public final ObjectDoubleShortTuple createTupleFromValues(@NotNull final Object... values) {
        return new ObjectDoubleShortTuple(
                values[0],
                TypeUtils.unbox((Double)values[1]),
                TypeUtils.unbox((Short)values[2])
        );
    }

    @Override
    public final ObjectDoubleShortTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new ObjectDoubleShortTuple(
                values[0],
                TypeUtils.unbox((Double)values[1]),
                TypeUtils.unbox((Short)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final ObjectDoubleShortTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, tuple.getSecondElement());
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationIndexKey, tuple.getThirdElement());
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final ObjectDoubleShortTuple tuple) {
        return new SmartKey(
                tuple.getFirstElement(),
                TypeUtils.box(tuple.getSecondElement()),
                TypeUtils.box(tuple.getThirdElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final ObjectDoubleShortTuple tuple, int elementIndex) {
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
    public final Object exportElementReinterpreted(@NotNull final ObjectDoubleShortTuple tuple, int elementIndex) {
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
        WritableObjectChunk<ObjectDoubleShortTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ObjectChunk<Object, Values> chunk1 = chunks[0].asObjectChunk();
        DoubleChunk<Values> chunk2 = chunks[1].asDoubleChunk();
        ShortChunk<Values> chunk3 = chunks[2].asShortChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new ObjectDoubleShortTuple(chunk1.get(ii), chunk2.get(ii), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link ObjectDoubleShortColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<ObjectDoubleShortTuple, Object, Double, Short> {

        private Factory() {
        }

        @Override
        public TupleSource<ObjectDoubleShortTuple> create(
                @NotNull final ColumnSource<Object> columnSource1,
                @NotNull final ColumnSource<Double> columnSource2,
                @NotNull final ColumnSource<Short> columnSource3
        ) {
            return new ObjectDoubleShortColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
