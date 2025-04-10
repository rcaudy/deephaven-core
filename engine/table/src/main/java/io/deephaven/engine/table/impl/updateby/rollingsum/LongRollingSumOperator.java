//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit CharRollingSumOperator and run "./gradlew replicateUpdateBy" to regenerate
//
// @formatter:off
package io.deephaven.engine.table.impl.updateby.rollingsum;

import io.deephaven.base.ringbuffer.LongRingBuffer;
import io.deephaven.base.verify.Assert;
import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.LongChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.table.impl.MatchPair;
import io.deephaven.engine.table.impl.updateby.UpdateByOperator;
import io.deephaven.engine.table.impl.updateby.internal.BaseLongUpdateByOperator;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import static io.deephaven.util.QueryConstants.*;

public class LongRollingSumOperator extends BaseLongUpdateByOperator {
    private static final int RING_BUFFER_INITIAL_CAPACITY = 512;
    // region extra-fields
    // endregion extra-fields

    protected class Context extends BaseLongUpdateByOperator.Context {
        protected LongChunk<? extends Values> longInfluencerValuesChunk;
        protected LongRingBuffer longWindowValues;

        protected Context(final int chunkSize) {
            super(chunkSize);
            longWindowValues = new LongRingBuffer(RING_BUFFER_INITIAL_CAPACITY, true);
        }

        @Override
        public void close() {
            super.close();
            longWindowValues = null;
        }


        @Override
        public void setValueChunks(@NotNull final Chunk<? extends Values>[] valueChunks) {
            longInfluencerValuesChunk = valueChunks[0].asLongChunk();
        }

        @Override
        public void push(int pos, int count) {
            longWindowValues.ensureRemaining(count);

            for (int ii = 0; ii < count; ii++) {
                long val = longInfluencerValuesChunk.get(pos + ii);
                longWindowValues.addUnsafe(val);

                // increase the running sum
                if (val != NULL_LONG) {
                    if (curVal == NULL_LONG) {
                        curVal = val;
                    } else {
                        curVal += val;
                    }
                } else {
                    nullCount++;
                }
            }
        }

        @Override
        public void pop(int count) {
            Assert.geq(longWindowValues.size(), "longWindowValues.size()", count);

            for (int ii = 0; ii < count; ii++) {
                long val = longWindowValues.removeUnsafe();

                // reduce the running sum
                if (val != NULL_LONG) {
                    curVal -= val;
                } else {
                    nullCount--;
                }
            }
        }

        @Override
        public void writeToOutputChunk(int outIdx) {
            if (longWindowValues.size() == nullCount) {
                outputValues.set(outIdx, NULL_LONG);
            } else {
                outputValues.set(outIdx, curVal);
            }
        }

        @Override
        public void reset() {
            super.reset();
            longWindowValues.clear();
        }
    }

    @NotNull
    @Override
    public UpdateByOperator.Context makeUpdateContext(final int affectedChunkSize, final int influencerChunkSize) {
        return new Context(affectedChunkSize);
    }

    public LongRollingSumOperator(
            @NotNull final MatchPair pair,
            @NotNull final String[] affectingColumns,
            @Nullable final String timestampColumnName,
            final long reverseWindowScaleUnits,
            final long forwardWindowScaleUnits
    // region extra-constructor-args
    // endregion extra-constructor-args
    ) {
        super(pair, affectingColumns, timestampColumnName, reverseWindowScaleUnits, forwardWindowScaleUnits, true);
        // region constructor
        // endregion constructor
    }

    @Override
    public UpdateByOperator copy() {
        return new LongRollingSumOperator(
                pair,
                affectingColumns,
                timestampColumnName,
                reverseWindowScaleUnits,
                forwardWindowScaleUnits
        // region extra-copy-args
        // endregion extra-copy-args
        );
    }
}
