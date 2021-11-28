package io.deephaven.engine.table.impl.tuplesource.generated;

import io.deephaven.datastructures.util.SmartKey;
import io.deephaven.engine.chunk.Attributes.Values;
import io.deephaven.engine.chunk.Chunk;
import io.deephaven.engine.chunk.LongChunk;
import io.deephaven.engine.chunk.ObjectChunk;
import io.deephaven.engine.chunk.WritableChunk;
import io.deephaven.engine.chunk.WritableObjectChunk;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.TupleSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.table.impl.tuplesource.AbstractTupleSource;
import io.deephaven.engine.table.impl.tuplesource.TwoColumnTupleSourceFactory;
import io.deephaven.engine.time.DateTime;
import io.deephaven.engine.time.DateTimeUtils;
import io.deephaven.engine.tuple.generated.LongLongTuple;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;


/**
 * <p>{@link TupleSource} that produces key column values from {@link ColumnSource} types Long and DateTime.
 * <p>Generated by io.deephaven.replicators.TupleSourceCodeGenerator.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class ReinterpretedDateTimeDateTimeColumnTupleSource extends AbstractTupleSource<LongLongTuple> {

    /** {@link TwoColumnTupleSourceFactory} instance to create instances of {@link ReinterpretedDateTimeDateTimeColumnTupleSource}. **/
    public static final TwoColumnTupleSourceFactory<LongLongTuple, Long, DateTime> FACTORY = new Factory();

    private final ColumnSource<Long> columnSource1;
    private final ColumnSource<DateTime> columnSource2;

    public ReinterpretedDateTimeDateTimeColumnTupleSource(
            @NotNull final ColumnSource<Long> columnSource1,
            @NotNull final ColumnSource<DateTime> columnSource2
    ) {
        super(columnSource1, columnSource2);
        this.columnSource1 = columnSource1;
        this.columnSource2 = columnSource2;
    }

    @Override
    public final LongLongTuple createTuple(final long rowKey) {
        return new LongLongTuple(
                columnSource1.getLong(rowKey),
                DateTimeUtils.nanos(columnSource2.get(rowKey))
        );
    }

    @Override
    public final LongLongTuple createPreviousTuple(final long rowKey) {
        return new LongLongTuple(
                columnSource1.getPrevLong(rowKey),
                DateTimeUtils.nanos(columnSource2.getPrev(rowKey))
        );
    }

    @Override
    public final LongLongTuple createTupleFromValues(@NotNull final Object... values) {
        return new LongLongTuple(
                DateTimeUtils.nanos((DateTime)values[0]),
                DateTimeUtils.nanos((DateTime)values[1])
        );
    }

    @Override
    public final LongLongTuple createTupleFromReinterpretedValues(@NotNull final Object... values) {
        return new LongLongTuple(
                TypeUtils.unbox((Long)values[0]),
                DateTimeUtils.nanos((DateTime)values[1])
        );
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <ELEMENT_TYPE> void exportElement(@NotNull final LongLongTuple tuple, final int elementIndex, @NotNull final WritableColumnSource<ELEMENT_TYPE> writableSource, final long destinationIndexKey) {
        if (elementIndex == 0) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) DateTimeUtils.nanosToTime(tuple.getFirstElement()));
            return;
        }
        if (elementIndex == 1) {
            writableSource.set(destinationIndexKey, (ELEMENT_TYPE) DateTimeUtils.nanosToTime(tuple.getSecondElement()));
            return;
        }
        throw new IndexOutOfBoundsException("Invalid element index " + elementIndex + " for export");
    }

    @Override
    public final Object exportToExternalKey(@NotNull final LongLongTuple tuple) {
        return new SmartKey(
                DateTimeUtils.nanosToTime(tuple.getFirstElement()),
                DateTimeUtils.nanosToTime(tuple.getSecondElement())
        );
    }

    @Override
    public final Object exportElement(@NotNull final LongLongTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return DateTimeUtils.nanosToTime(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToTime(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    @Override
    public final Object exportElementReinterpreted(@NotNull final LongLongTuple tuple, int elementIndex) {
        if (elementIndex == 0) {
            return TypeUtils.box(tuple.getFirstElement());
        }
        if (elementIndex == 1) {
            return DateTimeUtils.nanosToTime(tuple.getSecondElement());
        }
        throw new IllegalArgumentException("Bad elementIndex for 2 element tuple: " + elementIndex);
    }

    protected void convertChunks(@NotNull WritableChunk<? super Values> destination, int chunkSize, Chunk<Values> [] chunks) {
        WritableObjectChunk<LongLongTuple, ? super Values> destinationObjectChunk = destination.asWritableObjectChunk();
        LongChunk<Values> chunk1 = chunks[0].asLongChunk();
        ObjectChunk<DateTime, Values> chunk2 = chunks[1].asObjectChunk();
        for (int ii = 0; ii < chunkSize; ++ii) {
            destinationObjectChunk.set(ii, new LongLongTuple(chunk1.get(ii), DateTimeUtils.nanos(chunk2.get(ii))));
        }
        destination.setSize(chunkSize);
    }

    /** {@link TwoColumnTupleSourceFactory} for instances of {@link ReinterpretedDateTimeDateTimeColumnTupleSource}. **/
    private static final class Factory implements TwoColumnTupleSourceFactory<LongLongTuple, Long, DateTime> {

        private Factory() {
        }

        @Override
        public TupleSource<LongLongTuple> create(
                @NotNull final ColumnSource<Long> columnSource1,
                @NotNull final ColumnSource<DateTime> columnSource2
        ) {
            return new ReinterpretedDateTimeDateTimeColumnTupleSource(
                    columnSource1,
                    columnSource2
            );
        }
    }
}
