package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.ByteChunk;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.ObjectChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.engine.tuple.generated.ObjectByteObjectTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Object, Byte, and Object.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ObjectByteObjectColumnTupleSource extends AbstractTupleSource<ObjectByteObjectTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link ObjectByteObjectColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<ObjectByteObjectTuple, Object, Byte, Object> FACTORY = new Factory();

    private final ColumnSource<Object> columnSource1;
    private final ColumnSource<Byte> columnSource2;
    private final ColumnSource<Object> columnSource3;

    public ObjectByteObjectColumnTupleSource(
            @NotNull final ColumnSource<Object> columnSource1,
            @NotNull final ColumnSource<Byte> columnSource2,
            @NotNull final ColumnSource<Object> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final ObjectByteObjectTuple createTuple(final long rowKey) {
        return new ObjectByteObjectTuple(
                columnSource1.get(rowKey),
                columnSource2.getByte(rowKey),
                columnSource3.get(rowKey)
        );
    }

    @Override
    public final ObjectByteObjectTuple createPreviousTuple(final long rowKey) {
        return new ObjectByteObjectTuple(
                columnSource1.getPrev(rowKey),
                columnSource2.getPrevByte(rowKey),
                columnSource3.getPrev(rowKey)
        );
    }

    @Override
    public final ObjectByteObjectTuple createTupleFromValues(@NotNull final Object... values) {
        return new ObjectByteObjectTuple(
                values[0],
                TypeUtils.unbox((Byte)values[1]),
                values[2]
        );
    }

    @Override
    public final ObjectByteObjectTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new ObjectByteObjectTuple(
                values[0],
                TypeUtils.unbox((Byte)values[1]),
                values[2]
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final ObjectByteObjectTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, tuple.getSecondElement());
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) tuple.getThirdElement());
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final ObjectByteObjectTuple tuple) {
        return new SmartKey(
                tuple.getFirstElement(),
                TypeUtils.box(tuple.getSecondElement()),
                tuple.getThirdElement()
        );
    }

    @Override
    public final Object exportElement(@NotNull final ObjectByteObjectTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return tuple.getFirstElement();
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return tuple.getThirdElement();
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final ObjectByteObjectTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return tuple.getFirstElement();
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return tuple.getThirdElement();
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<ObjectByteObjectTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        ObjectChunk<Object, Values> chunk1 = chunks[0].asObjectChunk();
        ByteChunk<Values> chunk2 = chunks[1].asByteChunk();
        ObjectChunk<Object, Values> chunk3 = chunks[2].asObjectChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new ObjectByteObjectTuple(chunk1.get(ii), chunk2.get(ii), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link ObjectByteObjectColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<ObjectByteObjectTuple, Object, Byte, Object> {

        private Factory() {
        }

        @Override
        public TupleSource<ObjectByteObjectTuple> create(
                @NotNull final ColumnSource<Object> columnSource1,
                @NotNull final ColumnSource<Byte> columnSource2,
                @NotNull final ColumnSource<Object> columnSource3
        ) {
            return new ObjectByteObjectColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
