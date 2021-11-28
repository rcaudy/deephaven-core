package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.CharChunk;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.LongChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.TwoColumnTupleSourceFactory;
import io.deephaven.engine.time.DateTime;
import io.deephaven.engine.time.DateTimeUtils;
import io.deephaven.engine.tuple.generated.CharLongTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Character and Long.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class CharacterReinterpretedDateTimeColumnTupleSource extends AbstractTupleSource<CharLongTuple> {

    /** {@link TwoColumnTupleSourceFactory} instance to create instances of {@link CharacterReinterpretedDateTimeColumnTupleSource}. **/
    public static final TwoColumnTupleSourceFactory<CharLongTuple, Character, Long> FACTORY = new Factory();

    private final ColumnSource<Character> columnSource1;
    private final ColumnSource<Long> columnSource2;

    public CharacterReinterpretedDateTimeColumnTupleSource(
            @NotNull final ColumnSource<Character> columnSource1,
            @NotNull final ColumnSource<Long> columnSource2
    ) {
        super(columnSource1, columnSource2);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
    }

    @Override
    public final CharLongTuple createTuple(final long rowKey) {
        return new CharLongTuple(
                columnSource1.getChar(rowKey),
                columnSource2.getLong(rowKey)
        );
    }

    @Override
    public final CharLongTuple createPreviousTuple(final long rowKey) {
        return new CharLongTuple(
                columnSource1.getPrevChar(rowKey),
                columnSource2.getPrevLong(rowKey)
        );
    }

    @Override
    public final CharLongTuple createTupleFromValues(@NotNull final Object... values) {
        return new CharLongTuple(
                TypeUtils.unbox((Character)values[0]),
                DateTimeUtils.nanos((DateTime)values[1])
        );
    }

    @Override
    public final CharLongTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new CharLongTuple(
                TypeUtils.unbox((Character)values[0]),
                TypeUtils.unbox((Long)values[1])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final CharLongTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, tuple.getFirstElement());
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) DateTimeUtils.nanosToTime(tuple.getSecondElement()));
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final CharLongTuple tuple) {
        return new SmartKey(
                TypeUtils.box(tuple.getFirstElement()),
                DateTimeUtils.nanosToTime(tuple.getSecondElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final CharLongTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToTime(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final CharLongTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return TypeUtils.box(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<CharLongTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        CharChunk<Values> chunk1 = chunks[0].asCharChunk();
        LongChunk<Values> chunk2 = chunks[1].asLongChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new CharLongTuple(chunk1.get(ii), chunk2.get(ii)));
        }
        destination.setSize(chunkSize);
    }

    /** {@link TwoColumnTupleSourceFactory} for instances of {@link CharacterReinterpretedDateTimeColumnTupleSource}. **/
    private static final class Factory implements TwoColumnTupleSourceFactory<CharLongTuple, Character, Long> {

        private Factory() {
        }

        @Override
        public TupleSource<CharLongTuple> create(
                @NotNull final ColumnSource<Character> columnSource1,
                @NotNull final ColumnSource<Long> columnSource2
        ) {
            return new CharacterReinterpretedDateTimeColumnTupleSource(
                    columnSource1,
                    columnSource2
            );
        }
    }
}
