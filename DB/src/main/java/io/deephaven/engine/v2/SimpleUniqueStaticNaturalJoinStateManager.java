package io.deephaven.engine.v2;

import io.deephaven.base.verify.Assert;
import io.deephaven.base.verify.Require;
import io.deephaven.engine.v2.hashing.ToIntFunctor;
import io.deephaven.engine.v2.sources.ColumnSource;
import io.deephaven.engine.v2.sources.LongArraySource;
import io.deephaven.engine.v2.sources.chunk.*;
import io.deephaven.engine.v2.sources.chunk.Attributes.Values;
import io.deephaven.engine.structures.RowSequence;
import io.deephaven.engine.v2.utils.RedirectionIndex;
import io.deephaven.engine.v2.utils.RowSet;
import org.apache.commons.lang3.mutable.MutableInt;
import org.jetbrains.annotations.NotNull;

/**
 * A static natural join manager that only maintains a single array source for the right indices.
 *
 * We do not store the keys, because we know that only one possible value can exist in each slot.
 *
 * This manager is appropriate for non-composite joins with small types (byte, char, short) or where we know that the
 * table has a limited range (e.g., a symbol table).
 */
class SimpleUniqueStaticNaturalJoinStateManager extends StaticNaturalJoinStateManager {
    private final int tableSize;
    private final ToIntFunctor<Values> transform;

    private final LongArraySource rightIndexSource = new LongArraySource();

    SimpleUniqueStaticNaturalJoinStateManager(ColumnSource<?>[] tableKeySources, int tableSize, ToIntFunctor<Values> transform) {
        super(tableKeySources);
        this.tableSize = Require.gtZero(tableSize, "tableSize");
        this.transform = transform;
        rightIndexSource.ensureCapacity(tableSize);
        for (int ii = 0; ii < tableSize; ++ii) {
            rightIndexSource.set(ii, RowSet.NULL_ROW_KEY);
        }
    }

    void setRightSide(RowSet rightRowSet, ColumnSource<?> valueSource) {
        try (final RowSequence.Iterator rsIt = rightRowSet.getRowSequenceIterator();
             final ColumnSource.GetContext getContext = valueSource.makeGetContext((int)Math.min(CHUNK_SIZE, rightRowSet.size()))
        ) {
            while (rsIt.hasMore()) {
                final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(CHUNK_SIZE);

                final Chunk<? extends Values> dataChunk = valueSource.getChunk(getContext, chunkOk);
                final IntChunk<? extends Values> dataChunkAsInt = transform.apply(dataChunk);
                final MutableInt position = new MutableInt(0);

                chunkOk.forEachLong((long keyIndex) -> {
                    final int tableLocation = dataChunkAsInt.get(position.intValue());
                    position.increment();
                    if (tableLocation < 0 || tableLocation >= tableSize) {
                        return true;
                    }
                    final long existingRight = rightIndexSource.getLong(tableLocation);
                    if (existingRight == RowSet.NULL_ROW_KEY) {
                        rightIndexSource.set(tableLocation, keyIndex);
                    } else {
                        rightIndexSource.set(tableLocation, DUPLICATE_RIGHT_VALUE);
                    }
                    return true;
                });
            }
        }
    }

    @Override
    void decorateLeftSide(RowSet leftRowSet, ColumnSource<?> [] valueSources, LongArraySource leftRedirections) {
        if (leftRowSet.isEmpty()) {
            return;
        }

        Assert.eq(valueSources.length, "valueSources.length", 1);
        final ColumnSource<?> valueSource = valueSources[0];

        try (final RowSequence.Iterator rsIt = leftRowSet.getRowSequenceIterator();
             final ColumnSource.GetContext getContext = valueSource.makeGetContext((int)Math.min(CHUNK_SIZE, leftRowSet.size()))
        ) {
            long offset = 0;
            while (rsIt.hasMore()) {
                final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(CHUNK_SIZE);

                final Chunk<? extends Values> dataChunk = valueSource.getChunk(getContext, chunkOk);

                final IntChunk<? extends Values> dataChunkAsInt = transform.apply(dataChunk);
                for (int ii = 0; ii < dataChunkAsInt.size(); ++ii) {
                    final int tableLocation = dataChunkAsInt.get(ii);
                    if (tableLocation < 0 || tableLocation >= tableSize) {
                        continue;
                    }
                    final long existingRight = rightIndexSource.getLong(tableLocation);

                    if (existingRight == DUPLICATE_RIGHT_VALUE) {
                        throw new IllegalStateException("More than one right side mapping for key " + keySourcesForErrorMessages[0].get(leftRowSet.get(offset + ii)));
                    }
                    leftRedirections.set(offset + ii, existingRight);
                }

                offset += chunkOk.size();
            }
        }
    }

    @NotNull
    RedirectionIndex buildRedirectionIndex(QueryTable leftTable, boolean exactMatch, LongArraySource leftRedirections, JoinControl.RedirectionType redirectionType) {
        return buildRedirectionIndex(leftTable, exactMatch, leftRedirections::getLong, redirectionType);
    }
}
