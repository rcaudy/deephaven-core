package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.CharChunk;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.ShortChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.ThreeColumnTupleSourceFactory;
import io.deephaven.engine.tuple.generated.CharShortCharTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Character, Short, and Character.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class CharacterShortCharacterColumnTupleSource extends AbstractTupleSource<CharShortCharTuple> {

    /** {@link ThreeColumnTupleSourceFactory} instance to create instances of {@link CharacterShortCharacterColumnTupleSource}. **/
    public static final ThreeColumnTupleSourceFactory<CharShortCharTuple, Character, Short, Character> FACTORY = new Factory();

    private final ColumnSource<Character> columnSource1;
    private final ColumnSource<Short> columnSource2;
    private final ColumnSource<Character> columnSource3;

    public CharacterShortCharacterColumnTupleSource(
            @NotNull final ColumnSource<Character> columnSource1,
            @NotNull final ColumnSource<Short> columnSource2,
            @NotNull final ColumnSource<Character> columnSource3
    ) {
        super(columnSource1, columnSource2, columnSource3);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
        this.columnSource3 = columnSource3;
    }

    @Override
    public final CharShortCharTuple createTuple(final long rowKey) {
        return new CharShortCharTuple(
                columnSource1.getChar(rowKey),
                columnSource2.getShort(rowKey),
                columnSource3.getChar(rowKey)
        );
    }

    @Override
    public final CharShortCharTuple createPreviousTuple(final long rowKey) {
        return new CharShortCharTuple(
                columnSource1.getPrevChar(rowKey),
                columnSource2.getPrevShort(rowKey),
                columnSource3.getPrevChar(rowKey)
        );
    }

    @Override
    public final CharShortCharTuple createTupleFromValues(@NotNull final Object... values) {
        return new CharShortCharTuple(
                TypeUtils.unbox((Character)values[0]),
                TypeUtils.unbox((Short)values[1]),
                TypeUtils.unbox((Character)values[2])
        );
    }

    @Override
    public final CharShortCharTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new CharShortCharTuple(
                TypeUtils.unbox((Character)values[0]),
                TypeUtils.unbox((Short)values[1]),
                TypeUtils.unbox((Character)values[2])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final CharShortCharTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, tuple.getFirstElement());
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
    public final Object exportToExternalKey(@NotNull final CharShortCharTuple tuple) {
        return new SmartKey(
                TypeUtils.box(tuple.getFirstElement()),
                TypeUtils.box(tuple.getSecondElement()),
                TypeUtils.box(tuple.getThirdElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final CharShortCharTuple tuple, int elementIndex) {
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
    public final Object exportElementReinterpreted(@NotNull final CharShortCharTuple tuple, int elementIndex) {
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
    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<CharShortCharTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        CharChunk<Values> chunk1 = chunks[0].asCharChunk();
        ShortChunk<Values> chunk2 = chunks[1].asShortChunk();
        CharChunk<Values> chunk3 = chunks[2].asCharChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new CharShortCharTuple(chunk1.get(ii), chunk2.get(ii), chunk3.get(ii)));
        }
        destinationObjectChunk.setSize(chunkSize);
    }

    /** {@link ThreeColumnTupleSourceFactory} for instances of {@link CharacterShortCharacterColumnTupleSource}. **/
    private static final class Factory implements ThreeColumnTupleSourceFactory<CharShortCharTuple, Character, Short, Character> {

        private Factory() {
        }

        @Override
        public TupleSource<CharShortCharTuple> create(
                @NotNull final ColumnSource<Character> columnSource1,
                @NotNull final ColumnSource<Short> columnSource2,
                @NotNull final ColumnSource<Character> columnSource3
        ) {
            return new CharacterShortCharacterColumnTupleSource(
                    columnSource1,
                    columnSource2,
                    columnSource3
            );
        }
    }
}
