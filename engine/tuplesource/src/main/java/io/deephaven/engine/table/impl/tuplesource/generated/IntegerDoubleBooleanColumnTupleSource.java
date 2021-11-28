package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.DoubleChunk;
import io.deephaven.engine.chunk.IntChunk;
import io.deephaven.engine.chunk.ObjectChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.engine.tuple.generated.IntDoubleByteTuple;
import io.deephaven.util.BooleanUtils;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Integer, Double, and Boolean.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class IntegerDoubleBooleanColumnTupleSource extends AbstractTupleSource<IntDoubleByteTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link IntegerDoubleBooleanColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<IntDoubleByteTuple, Integer, Double, Boolean> FACTORY = new Factory();

    private final ColumnSource<Integer> columnSource1;
    private final ColumnSource<Double> columnSource2;
    private final ColumnSource<Boolean> columnSource3;

    public IntegerDoubleBooleanColumnTupleSource(
            @NotNull final ColumnSource<Integer> columnSource1,
            @NotNull final ColumnSource<Double> columnSource2,
            @NotNull final ColumnSource<Boolean> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final IntDoubleByteTuple createTuple(final long rowKey) {
        return new IntDoubleByteTuple(
                columnSource1.getInt(rowKey),
                columnSource2.getDouble(rowKey),
                BooleanUtils.booleanAsByte(columnSource3.getBoolean(rowKey))
        );
    }

    @Override
    public final IntDoubleByteTuple createPreviousTuple(final long rowKey) {
        return new IntDoubleByteTuple(
                columnSource1.getPrevInt(rowKey),
                columnSource2.getPrevDouble(rowKey),
                BooleanUtils.booleanAsByte(columnSource3.getPrevBoolean(rowKey))
        );
    }

    @Override
    public final IntDoubleByteTuple createTupleFromValues(@NotNull final Object... values) {
        return new IntDoubleByteTuple(
                TypeUtils.unbox((Integer)values[0]),
                TypeUtils.unbox((Double)values[1]),
                BooleanUtils.booleanAsByte((Boolean)values[2])
        );
    }

    @Override
    public final IntDoubleByteTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new IntDoubleByteTuple(
                TypeUtils.unbox((Integer)values[0]),
                TypeUtils.unbox((Double)values[1]),
                BooleanUtils.booleanAsByte((Boolean)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final IntDoubleByteTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, tuple.getSecondElement());
            return;
        }
        if (elementIndex == 2) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) BooleanUtils.byteAsBoolean(tuple.getThirdElement()));
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final IntDoubleByteTuple tuple) {
        return new SmartKey(
                TypeUtils.box(tuple.getFirstElement()),
                TypeUtils.box(tuple.getSecondElement()),
                BooleanUtils.byteAsBoolean(tuple.getThirdElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final IntDoubleByteTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return BooleanUtils.byteAsBoolean(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final IntDoubleByteTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        if (elementIndex == 2) {
            return BooleanUtils.byteAsBoolean(tuple.getThirdElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 3 element tuple: " + elementIndex);
    }

    @Override
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<IntDoubleByteTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        IntChunk<Values> chunk1 = chunks[0].asIntChunk();
        DoubleChunk<Values> chunk2 = chunks[1].asDoubleChunk();
        ObjectChunk<Boolean, Values> chunk3 = chunks[2].asObjectChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new IntDoubleByteTuple(chunk1.get(ii), chunk2.get(ii), BooleanUtils.booleanAsByte(chunk3.get(ii))));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link IntegerDoubleBooleanColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<IntDoubleByteTuple, Integer, Double, Boolean> {

        private Factory() {
        }

        @Override
        public TupleSource<IntDoubleByteTuple> create(
                @NotNull final ColumnSource<Integer> columnSource1,
                @NotNull final ColumnSource<Double> columnSource2,
                @NotNull final ColumnSource<Boolean> columnSource3
        ) {
            return new IntegerDoubleBooleanColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
