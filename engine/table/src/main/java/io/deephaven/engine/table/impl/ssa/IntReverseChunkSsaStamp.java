//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit IntChunkSsaStamp and run "./gradlew replicateReverseSegmentedSortedArray" to regenerate
//
// @formatter:off


package io.deephaven.engine.table.impl.ssa;

import io.deephaven.chunk.*;
import io.deephaven.engine.rowset.chunkattributes.RowKeys;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.table.impl.util.RowRedirection;
import io.deephaven.engine.rowset.RowSetBuilderRandom;
import io.deephaven.engine.table.impl.util.WritableRowRedirection;

/**
 * Stamp kernel for when the left hand side is a sorted chunk and the right hand side is a ticking SegmentedSortedArray.
 */
public class IntReverseChunkSsaStamp implements ChunkSsaStamp {
    static IntReverseChunkSsaStamp INSTANCE = new IntReverseChunkSsaStamp();

    private IntReverseChunkSsaStamp() {} // use the instance

    @Override
    public void processEntry(Chunk<Values> leftStampValues, Chunk<RowKeys> leftStampKeys, SegmentedSortedArray ssa,
            WritableLongChunk<RowKeys> rightKeysForLeft, boolean disallowExactMatch) {
        processEntry(leftStampValues.asIntChunk(), leftStampKeys, (IntReverseSegmentedSortedArray) ssa, rightKeysForLeft,
                disallowExactMatch);
    }

    private static void processEntry(IntChunk<Values> leftStampValues, Chunk<RowKeys> leftStampKeys,
            IntReverseSegmentedSortedArray ssa, WritableLongChunk<RowKeys> rightKeysForLeft, boolean disallowExactMatch) {
        final int leftSize = leftStampKeys.size();
        final long rightSize = ssa.size();
        if (rightSize == 0) {
            rightKeysForLeft.fillWithValue(0, leftSize, RowSequence.NULL_ROW_KEY);
            rightKeysForLeft.setSize(leftSize);
            return;
        }

        final IntReverseSegmentedSortedArray.Iterator ssaIt = ssa.iterator(disallowExactMatch, true);

        for (int li = 0; li < leftSize;) {
            final int leftValue = leftStampValues.get(li);
            final int comparison = doComparison(leftValue, ssaIt.getValue());
            if (disallowExactMatch ? comparison <= 0 : comparison < 0) {
                rightKeysForLeft.set(li++, RowSequence.NULL_ROW_KEY);
                continue;
            } else if (comparison == 0) {
                rightKeysForLeft.set(li++, ssaIt.getKey());
                continue;
            }

            ssaIt.advanceToLast(leftValue);

            final long redirectionKey = ssaIt.getKey();
            if (!ssaIt.hasNext()) {
                rightKeysForLeft.fillWithValue(li, leftSize - li, redirectionKey);
                return;
            } else {
                rightKeysForLeft.set(li++, redirectionKey);
                final int nextRightValue = ssaIt.nextValue();
                while (li < leftSize && (disallowExactMatch ? leq(leftStampValues.get(li), nextRightValue)
                        : lt(leftStampValues.get(li), nextRightValue))) {
                    rightKeysForLeft.set(li++, redirectionKey);
                }
            }
        }
    }

    @Override
    public void processRemovals(Chunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            Chunk<? extends Values> rightStampChunk, LongChunk<RowKeys> rightKeys,
            WritableLongChunk<RowKeys> priorRedirections, WritableRowRedirection rowRedirection,
            RowSetBuilderRandom modifiedBuilder, boolean disallowExactMatch) {
        processRemovals(leftStampValues.asIntChunk(), leftStampKeys, rightStampChunk.asIntChunk(), rightKeys,
                priorRedirections, rowRedirection, modifiedBuilder, disallowExactMatch);
    }

    private static void processRemovals(IntChunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            IntChunk<? extends Values> rightStampChunk, LongChunk<RowKeys> rightKeys,
            WritableLongChunk<RowKeys> nextRedirections, WritableRowRedirection rowRedirection,
            RowSetBuilderRandom modifiedBuilder, boolean disallowExactMatch) {
        // When removing a row, record the stamp, redirection key, and prior redirection key. Binary search
        // in the left for the removed key to find the smallest value geq the removed right. Update all rows
        // with the removed redirection to the previous key.

        int leftLowIdx = 0;

        for (int ii = 0; ii < rightStampChunk.size(); ++ii) {
            final int rightStampValue = rightStampChunk.get(ii);
            final long rightStampKey = rightKeys.get(ii);
            final long newRightStampKey = nextRedirections.get(ii);

            leftLowIdx = findFirstResponsiveLeft(leftLowIdx, leftStampValues, disallowExactMatch, rightStampValue);

            while (leftLowIdx < leftStampKeys.size()) {
                final long leftKey = leftStampKeys.get(leftLowIdx);
                final long leftRedirectionKey = rowRedirection.get(leftKey);
                if (leftRedirectionKey == rightStampKey) {
                    modifiedBuilder.addKey(leftKey);
                    if (newRightStampKey == RowSequence.NULL_ROW_KEY) {
                        rowRedirection.removeVoid(leftKey);
                    } else {
                        rowRedirection.putVoid(leftKey, newRightStampKey);
                    }
                    leftLowIdx++;
                } else {
                    break;
                }
            }
        }
    }

    @Override
    public void processInsertion(Chunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            Chunk<? extends Values> rightStampChunk, LongChunk<RowKeys> rightKeys, Chunk<Values> nextRightValue,
            WritableRowRedirection rowRedirection, RowSetBuilderRandom modifiedBuilder, boolean endsWithLastValue,
            boolean disallowExactMatch) {
        processInsertion(leftStampValues.asIntChunk(), leftStampKeys, rightStampChunk.asIntChunk(), rightKeys,
                nextRightValue.asIntChunk(), rowRedirection, modifiedBuilder, endsWithLastValue, disallowExactMatch);
    }

    private static void processInsertion(IntChunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            IntChunk<? extends Values> rightStampChunk, LongChunk<RowKeys> rightKeys, IntChunk<Values> nextRightValue,
            WritableRowRedirection rowRedirection, RowSetBuilderRandom modifiedBuilder, boolean endsWithLastValue,
            boolean disallowExactMatch) {
        // We've already filtered out duplicate right stamps by the time we get here, which means that the
        // rightStampChunk
        // contains only values that are the last in any given run; and thus are possible matches.

        // We binary search in the left for the first value >=, everything up until the next extant right value
        // (contained
        // in the nextRightValue chunk) should be re-stamped with our value

        int leftLowIdx = 0;

        for (int ii = 0; ii < rightStampChunk.size(); ++ii) {
            final int rightStampValue = rightStampChunk.get(ii);

            leftLowIdx = findFirstResponsiveLeft(leftLowIdx, leftStampValues, disallowExactMatch, rightStampValue);

            final long rightStampKey = rightKeys.get(ii);

            if (ii == rightStampChunk.size() - 1 && endsWithLastValue) {
                while (leftLowIdx < leftStampKeys.size()) {
                    final long leftKey = leftStampKeys.get(leftLowIdx);
                    rowRedirection.putVoid(leftKey, rightStampKey);
                    modifiedBuilder.addKey(leftKey);
                    leftLowIdx++;
                }
            } else {
                final int nextRight = nextRightValue.get(ii);
                while (leftLowIdx < leftStampKeys.size()) {
                    final int leftValue = leftStampValues.get(leftLowIdx);
                    if (disallowExactMatch ? leq(leftValue, nextRight) : lt(leftValue, nextRight)) {
                        final long leftKey = leftStampKeys.get(leftLowIdx);
                        rowRedirection.putVoid(leftKey, rightStampKey);
                        modifiedBuilder.addKey(leftKey);
                        leftLowIdx++;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    @Override
    public int findModified(int first, Chunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            RowRedirection rowRedirection, Chunk<? extends Values> rightStampChunk,
            LongChunk<RowKeys> rightStampIndices, RowSetBuilderRandom modifiedBuilder, boolean disallowExactMatch) {
        return findModified(first, leftStampValues.asIntChunk(), leftStampKeys, rowRedirection,
                rightStampChunk.asIntChunk(), rightStampIndices, modifiedBuilder, disallowExactMatch);
    }

    private static int findModified(int leftLowIdx, IntChunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            RowRedirection rowRedirection, IntChunk<? extends Values> rightStampChunk,
            LongChunk<RowKeys> rightStampIndices, RowSetBuilderRandom modifiedBuilder, boolean disallowExactMatch) {
        for (int ii = 0; ii < rightStampChunk.size(); ++ii) {
            final int rightStampValue = rightStampChunk.get(ii);

            // now find the lowest left value leq (lt) than rightStampValue
            leftLowIdx = findFirstResponsiveLeft(leftLowIdx, leftStampValues, disallowExactMatch, rightStampValue);

            final long rightStampKey = rightStampIndices.get(ii);
            int checkIdx = leftLowIdx;
            while (checkIdx < leftStampValues.size()
                    && rowRedirection.get(leftStampKeys.get(checkIdx)) == rightStampKey) {
                modifiedBuilder.addKey(leftStampKeys.get(checkIdx));
                checkIdx++;
            }
        }

        return leftLowIdx;
    }

    @Override
    public void applyShift(Chunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            Chunk<? extends Values> rightStampChunk, LongChunk<RowKeys> rightStampKeys, long shiftDelta,
            WritableRowRedirection rowRedirection, boolean disallowExactMatch) {
        applyShift(leftStampValues.asIntChunk(), leftStampKeys, rightStampChunk.asIntChunk(), rightStampKeys,
                shiftDelta, rowRedirection, disallowExactMatch);
    }

    private void applyShift(IntChunk<Values> leftStampValues, LongChunk<RowKeys> leftStampKeys,
            IntChunk<? extends Values> rightStampChunk, LongChunk<RowKeys> rightStampKeys, long shiftDelta,
            WritableRowRedirection rowRedirection, boolean disallowExactMatch) {
        int leftLowIdx = 0;
        for (int ii = 0; ii < rightStampChunk.size(); ++ii) {
            final int rightStampValue = rightStampChunk.get(ii);

            // now find the lowest left value leq (lt) than rightStampValue
            leftLowIdx = findFirstResponsiveLeft(leftLowIdx, leftStampValues, disallowExactMatch, rightStampValue);

            final long rightStampKey = rightStampKeys.get(ii);
            int checkIdx = leftLowIdx;
            while (checkIdx < leftStampValues.size()
                    && rowRedirection.get(leftStampKeys.get(checkIdx)) == rightStampKey) {
                rowRedirection.putVoid(leftStampKeys.get(checkIdx), rightStampKey + shiftDelta);
                checkIdx++;
            }
        }
    }

    private static int findFirstResponsiveLeft(int leftLowIdx, IntChunk<Values> leftStampValues,
            boolean disallowExactMatch, int rightStampValue) {
        int leftHighIdx = leftStampValues.size();

        while (leftLowIdx < leftHighIdx) {
            final int leftMidIdx = (leftHighIdx + leftLowIdx) >>> 1;
            final int leftMidValue = leftStampValues.get(leftMidIdx);

            final int comparison = doComparison(leftMidValue, rightStampValue);
            final boolean moveLow = disallowExactMatch ? comparison <= 0 : comparison < 0;
            if (moveLow) {
                leftLowIdx = leftMidIdx + 1;
            } else {
                leftHighIdx = leftMidIdx;
            }
        }
        return leftLowIdx;
    }

    // region comparison functions
    // note that this is a descending kernel, thus the comparisons here are backwards (e.g., the lt function is in terms of the sort direction, so is implemented by gt)
    private static int doComparison(int lhs, int rhs) {
        return -1 * Integer.compare(lhs, rhs);
    }
    // endregion comparison functions

    private static boolean lt(int lhs, int rhs) {
        return doComparison(lhs, rhs) < 0;
    }

    private static boolean leq(int lhs, int rhs) {
        return doComparison(lhs, rhs) <= 0;
    }
}

