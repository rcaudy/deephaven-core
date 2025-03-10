//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.base.verify.Assert;
import io.deephaven.chunk.LongChunk;
import io.deephaven.chunk.WritableByteChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.chunk.sized.SizedByteChunk;
import io.deephaven.engine.rowset.*;
import io.deephaven.engine.rowset.RowSetFactory;
import io.deephaven.engine.table.impl.sort.ByteSortKernel;
import io.deephaven.engine.table.impl.sources.ObjectArraySource;
import io.deephaven.chunk.ChunkType;
import io.deephaven.chunk.WritableLongChunk;
import io.deephaven.chunk.sized.SizedLongChunk;
import io.deephaven.engine.rowset.chunkattributes.RowKeys;

import java.util.function.Consumer;

/**
 * A tracker for modified cross join hash table slots.
 * <p>
 * After adding an entry, you get back a cookie, which must be passed in on future modification operations for that
 * slot.
 */
class CrossJoinModifiedSlotTracker {
    static final long NULL_COOKIE = 0;

    private static final int START_SLOT_CHUNK_SIZE = 32;
    private static final int CHUNK_SIZE = 4096;

    private int maxSlotChunkCapacity = START_SLOT_CHUNK_SIZE;

    RowSetShiftData leftShifted;
    RowSetShiftData rightShifted;

    WritableRowSet leftAdded;
    WritableRowSet leftRemoved;
    RowSet leftModified;

    boolean hasLeftModifies = false;
    boolean hasRightModifies = false;
    boolean finishedRightProcessing = false;

    private final RightIncrementalChunkedCrossJoinStateManager jsm;

    CrossJoinModifiedSlotTracker(RightIncrementalChunkedCrossJoinStateManager jsm) {
        this.jsm = jsm;
    }

    class SlotState {
        long cookie;
        long slotLocation;
        boolean rightChanged = false;
        boolean finalizedRight = false;
        boolean needsRightShift = false;
        boolean isLeftShifted = false;

        int chunkCapacity = 0;
        final SizedByteChunk<Values> flagChunk = new SizedByteChunk<>();
        final SizedLongChunk<RowKeys> keyChunk = new SizedLongChunk<>();
        RowSetBuilderRandom indexBuilder = RowSetFactory.builderRandom();

        long lastIndex = 0; // if added/removed/modified have been shifted then this is the left-index for the shift
        WritableRowSet rightAdded;
        WritableRowSet rightRemoved;
        WritableRowSet rightModified;
        RowSetShiftData innerShifted;

        TrackingWritableRowSet leftRowSet; // reference, NOT a copy
        TrackingWritableRowSet rightRowSet; // reference, NOT a copy

        private SlotState() {}

        private void clear() {
            if (finalizedRight) {
                rightAdded.close();
                rightRemoved.close();
                rightModified.close();
            }
            keyChunk.close();
            flagChunk.close();
        }

        private SlotState needsRightShift() {
            needsRightShift = true;
            return this;
        }

        private SlotState applyLeftShift() {
            if (isLeftShifted) {
                return this;
            }

            isLeftShifted = true;
            leftShifted.apply(leftRowSet);
            return this;
        }

        private int keySize() {
            final LongChunk<RowKeys> chunk = keyChunk.get();
            if (chunk == null) {
                return 0;
            }
            return chunk.size();
        }

        private void ensureChunkCapacityRemaining() {
            if (chunkCapacity > 0 && keySize() < chunkCapacity) {
                return;
            }

            if (chunkCapacity == 0) {
                chunkCapacity = START_SLOT_CHUNK_SIZE;
            } else if (chunkCapacity >= CHUNK_SIZE) {
                chunkCapacity = chunkCapacity + CHUNK_SIZE;
            } else {
                chunkCapacity = 2 * chunkCapacity;
            }
            maxSlotChunkCapacity = Math.max(maxSlotChunkCapacity, chunkCapacity);
            keyChunk.ensureCapacityPreserve(chunkCapacity);
            flagChunk.ensureCapacityPreserve(chunkCapacity);
        }

        private SlotState appendToChunk(final long key, final byte flag) {
            ensureChunkCapacityRemaining();
            keyChunk.get().add(key);
            flagChunk.get().add(flag);
            return this;
        }

        private SlotState addToBuilder(final long key) {
            indexBuilder.addKey(key);
            return this;
        }

        private void doFinalizeRightState() {
            if (finalizedRight) {
                return;
            }
            finalizedRight = true;

            final WritableLongChunk<RowKeys> keyChunk = this.keyChunk.get();
            final WritableByteChunk<Values> flagChunk = this.flagChunk.get();
            final int keySize = keySize();

            if (keySize > 0) {
                ensureSortKernel();
                sortKernel.sort(flagChunk, keyChunk);
            }

            rightChanged = keySize > 0;

            // finalize right RowSet; transform from right RowSet to downstream offset
            final RowSetBuilderSequential innerAdded = RowSetFactory.builderSequential();
            final RowSetBuilderSequential innerRemoved = RowSetFactory.builderSequential();

            // let's accumulate downstream offsets too
            final RowSetBuilderSequential removedBuilder = RowSetFactory.builderSequential();

            try (final RowSequence.Iterator iter = rightRowSet.getRowSequenceIterator()) {
                final long startRelativePos = iter.getRelativePosition();

                // first we build and translate the removed
                for (int ii = 0; ii < keySize; ++ii) {
                    final long key = keyChunk.get(ii);
                    final byte flag = flagChunk.get(ii);
                    if (flag == FLAG_RM) {
                        innerRemoved.appendKey(key);
                        // translate the removed
                        if (iter.hasMore()) {
                            iter.advance(key);
                        }
                        final long downstreamOffset = iter.getRelativePosition() - startRelativePos;
                        keyChunk.set(ii, downstreamOffset);
                        removedBuilder.appendKey(downstreamOffset);
                    } else if (flag == FLAG_ADD) {
                        innerAdded.appendKey(key);
                    }
                }
            }

            // make our right RowSet be what it needs to be
            final long oldRightSize = rightRowSet.size();
            try (final RowSet added = innerAdded.build();
                    final RowSet removed = innerRemoved.build()) {
                rightRowSet.remove(removed);

                // then we shift
                if (needsRightShift) {
                    rightShifted.apply(rightRowSet);
                }

                if (added.isNonempty()) {
                    rightRowSet.insert(added);
                    jsm.onRightGroupInsertion(rightRowSet, added, slotLocation);
                }

                Assert.eq(oldRightSize + added.size() - removed.size(), "oldRightSize + added.size() - removed.size()",
                        rightRowSet.size(), "rightRowSet.size()");
            }

            // now translate added && modified; accumulate them too
            final RowSetBuilderSequential addedBuilder = RowSetFactory.builderSequential();
            final RowSetBuilderSequential modifiedBuilder = RowSetFactory.builderSequential();

            try (final RowSequence.Iterator iter = rightRowSet.getRowSequenceIterator()) {
                final long startRelativePos = iter.getRelativePosition();

                for (int ii = 0; ii < keySize; ++ii) {
                    final long key = keyChunk.get(ii);
                    final byte flag = flagChunk.get(ii);
                    if (flag == FLAG_RM) {
                        continue;
                    }

                    if (iter.hasMore()) {
                        iter.advance(key);
                    }
                    final long downstreamOffset = iter.getRelativePosition() - startRelativePos;
                    keyChunk.set(ii, downstreamOffset);
                    if (flag == FLAG_ADD) {
                        addedBuilder.appendKey(downstreamOffset);
                    } else if (flag == FLAG_MOD) {
                        modifiedBuilder.appendKey(downstreamOffset);
                    } else {
                        throw new IllegalStateException(
                                "CrossJoinModifiedSlotTracker encountered unexpected flag value: " + flag);
                    }
                }
            }

            // generate downstream updates
            long shiftDelta = 0;
            int preIdx = 0, postIdx = 0;
            long preOff = 0, postOff = 0;
            final RowSetShiftData.Builder shiftBuilder = new RowSetShiftData.Builder();

            while (preIdx < keySize && flagChunk.get(preIdx) != FLAG_RM) {
                ++preIdx;
            }
            while (postIdx < keySize && flagChunk.get(postIdx) != FLAG_ADD) {
                ++postIdx;
            }

            final long newRightSize = rightRowSet.size();
            final long oldRightSizeAdjusted = jsm.leftOuterJoin() ? Math.max(oldRightSize, 1) : oldRightSize;
            final long newRightSizeAdjusted = jsm.leftOuterJoin() ? Math.max(newRightSize, 1) : newRightSize;

            while (postOff < newRightSizeAdjusted && preOff < oldRightSizeAdjusted) {
                final long preNextOff = (preIdx == keySize) ? oldRightSizeAdjusted : keyChunk.get(preIdx);
                final long postNextOff = (postIdx == keySize) ? newRightSizeAdjusted : keyChunk.get(postIdx);

                final long canShift = Math.min(preNextOff - preOff, postNextOff - postOff);
                if (canShift > 0) {
                    shiftBuilder.shiftRange(preOff, preOff + canShift - 1, shiftDelta);
                    preOff += canShift;
                    postOff += canShift;
                }
                if (canShift < 0) {
                    throw new IllegalStateException();
                }

                if (preOff == preNextOff && preIdx < keySize) {
                    ++preOff;
                    --shiftDelta;
                    for (++preIdx; preIdx < keyChunk.size(); ++preIdx) {
                        if (flagChunk.get(preIdx) == FLAG_RM) {
                            break;
                        }
                    }
                }

                if (postOff == postNextOff && postIdx < keySize) {
                    ++postOff;
                    ++shiftDelta;
                    for (++postIdx; postIdx < keyChunk.size(); ++postIdx) {
                        if (flagChunk.get(postIdx) == FLAG_ADD) {
                            break;
                        }
                    }
                }
            }

            if (newRightSize == 0 && oldRightSize > 0 && jsm.leftOuterJoin()) {
                // we need a single result row, that will be all null
                addedBuilder.appendKey(0);
            }

            rightAdded = addedBuilder.build();
            rightRemoved = removedBuilder.build();
            rightModified = modifiedBuilder.build();
            innerShifted = shiftBuilder.build();
            hasRightModifies |= rightModified.isNonempty();

            this.keyChunk.close();
            this.flagChunk.close();
            chunkCapacity = 0;
        }
    }

    private final ObjectArraySource<SlotState> modifiedSlots = new ObjectArraySource<>(SlotState.class);
    private ByteSortKernel<RowKeys, Values> sortKernel;

    private void ensureSortKernel() {
        if (sortKernel == null) {
            sortKernel = ByteSortKernel.makeContext(ChunkType.Long, SortingOrder.Ascending, maxSlotChunkCapacity, true);
        }
    }

    /**
     * the location that we must write to in modified slots; also if we have a pointer that falls outside the range [0,
     * pointer); then we know it is invalid
     */
    private long pointer;
    /** how many slots we have allocated */
    private long allocated;
    /** Each time we clear, we add an offset to our cookies, this prevents us from reading old values */
    private long cookieGeneration = 128;

    private static final byte FLAG_ADD = 0x1;
    private static final byte FLAG_RM = 0x2;
    private static final byte FLAG_MOD = 0x4;

    /**
     * Remove all entries from the tracker.
     *
     * @return Whether all externally-stored cookies should be reset to {@link #NULL_COOKIE}
     **/
    boolean clear() {
        boolean needToResetCookies = false;
        cookieGeneration += pointer;
        if (cookieGeneration > Long.MAX_VALUE / 2) {
            cookieGeneration = 0;
            needToResetCookies = true;
        }
        for (long i = 0; i < pointer; ++i) {
            if (modifiedSlots.get(i) == null) {
                continue;
            }
            modifiedSlots.get(i).clear();
            modifiedSlots.set(i, null);
        }
        maxSlotChunkCapacity = START_SLOT_CHUNK_SIZE;
        pointer = 0;
        if (sortKernel != null) {
            sortKernel.close();
            sortKernel = null;
        }
        leftShifted = null;
        rightShifted = null;

        // leftAdded/leftRemoved/leftModified are used by the downstream update; so we do not free them
        leftAdded = null;
        leftRemoved = null;
        leftModified = null;

        hasLeftModifies = false;
        hasRightModifies = false;
        finishedRightProcessing = false;

        return needToResetCookies;
    }

    /**
     * Is this cookie within our valid range (greater than or equal to our generation, but less than the pointer after
     * adjustment?
     *
     * @param cookie the cookie to check for validity
     *
     * @return true if the cookie is from the current generation, and references a valid slot in our table
     */
    private boolean isValidCookie(long cookie) {
        return cookie >= cookieGeneration && getPointerFromCookie(cookie) < pointer;
    }

    /**
     * Get a cookie to return to the user, given a pointer value.
     *
     * @param pointer the pointer to convert to a cookie
     * @return the cookie to return to the user
     */
    private long getCookieFromPointer(long pointer) {
        return cookieGeneration + pointer;
    }

    /**
     * Given a valid user's cookie, return the corresponding pointer.
     *
     * @param cookie the valid cookie
     * @return the pointer into modifiedSlots
     */
    private long getPointerFromCookie(long cookie) {
        return cookie - cookieGeneration;
    }

    private SlotState getSlotState(final long cookie, final long slot) {
        final SlotState state;
        if (!isValidCookie(cookie)) {
            if (pointer == allocated) {
                allocated += CHUNK_SIZE;
                modifiedSlots.ensureCapacity(allocated);
            }
            state = new SlotState();
            modifiedSlots.set(pointer, state);
            state.slotLocation = slot;
            state.cookie = getCookieFromPointer(pointer++);

            state.leftRowSet = jsm.getLeftRowSet(slot);
            state.rightRowSet = jsm.getRightRowSet(slot);

            if (finishedRightProcessing) {
                state.finalizedRight = true;
                state.rightAdded = RowSetFactory.empty();
                state.rightRemoved = RowSetFactory.empty();
                state.rightModified = RowSetFactory.empty();
                state.innerShifted = RowSetShiftData.EMPTY;
            }
        } else {
            state = modifiedSlots.get(getPointerFromCookie(cookie));
            Assert.eq(state.slotLocation, "state.slotLocation", slot, "slot");
        }
        return state;
    }

    /**
     * Move a main table location.
     *
     * @param newTableLocation the new hash slot
     */
    void moveTableLocation(long cookie, long newTableLocation) {
        if (isValidCookie(cookie)) {
            final long pointer = getPointerFromCookie(cookie);
            final SlotState state = modifiedSlots.get(pointer);
            state.slotLocation = newTableLocation;
        }
    }

    long appendChunkAdd(final long cookie, final long slot, final long key) {
        return getSlotState(cookie, slot).appendToChunk(key, FLAG_ADD).cookie;
    }

    long appendChunkRemove(final long cookie, final long slot, final long key) {
        return getSlotState(cookie, slot).appendToChunk(key, FLAG_RM).cookie;
    }

    long appendChunkModify(final long cookie, final long slot, final long key) {
        return getSlotState(cookie, slot).appendToChunk(key, FLAG_MOD).cookie;
    }

    long addToBuilder(final long cookie, final long slot, final long leftIndex) {
        return getSlotState(cookie, slot).addToBuilder(leftIndex).cookie;
    }

    // Right shifts cannot be applied until after the removes are applied to the slot's right RowSet. So, we ensure that
    // a tracker-slot is allocated for each slot affected by a shift, and apply the shifts later.
    long needsRightShift(final long cookie, final long slot) {
        return getSlotState(cookie, slot).needsRightShift().cookie;
    }

    // Left shifts can actually be applied immediately (removes are already rm'd), but we need to be careful to only
    // shift the leftRowSet once.
    long needsLeftShift(final long cookie, final long slot) {
        return getSlotState(cookie, slot).applyLeftShift().cookie;
    }

    SlotState getFinalSlotState(long cookie) {
        if (!isValidCookie(cookie)) {
            return null;
        }
        ensureSortKernel();

        final SlotState state = modifiedSlots.get(getPointerFromCookie(cookie));
        if (state != null) {
            state.doFinalizeRightState();
        }
        return state;
    }

    void forAllModifiedSlots(Consumer<SlotState> callback) {
        for (int ii = 0; ii < pointer; ++ii) {
            final SlotState slotState = modifiedSlots.get(ii);
            if (slotState != null) {
                slotState.doFinalizeRightState();
                callback.accept(slotState);
            }
        }
    }

    void finalizeRightProcessing() {
        for (int ii = 0; ii < pointer; ++ii) {
            final SlotState slotState = modifiedSlots.get(ii);
            if (slotState != null) {
                slotState.doFinalizeRightState();
            }
        }
        finishedRightProcessing = true;
    }

    void flushLeftRemoves() {
        final RowSetBuilderRandom builder = RowSetFactory.builderRandom();
        for (int jj = 0; jj < pointer; ++jj) {
            final SlotState slotState = modifiedSlots.get(jj);
            if (slotState == null) {
                continue;
            }

            final RowSet leftRemoved = slotState.indexBuilder.build();
            slotState.leftRowSet.remove(leftRemoved);
            slotState.indexBuilder = RowSetFactory.builderRandom();
            long sizePrev = slotState.rightRowSet.sizePrev();
            if (sizePrev > 0) {
                leftRemoved.forAllRowKeys(ii -> {
                    final long prevOffset = ii << jsm.getPrevNumShiftBits();
                    builder.addRange(prevOffset, prevOffset + sizePrev - 1);
                });
            } else if (jsm.leftOuterJoin()) {
                leftRemoved.forAllRowKeys(ii -> {
                    final long prevOffset = ii << jsm.getPrevNumShiftBits();
                    builder.addKey(prevOffset);
                });
            }
        }
        leftRemoved = builder.build();
    }

    void flushLeftAdds() {
        final RowSetBuilderRandom downstreamAdds = RowSetFactory.builderRandom();
        for (int jj = 0; jj < pointer; ++jj) {
            final SlotState slotState = modifiedSlots.get(jj);
            if (slotState == null) {
                continue;
            }

            final RowSet leftAdded = slotState.indexBuilder.build();
            slotState.leftRowSet.insert(leftAdded);
            jsm.updateLeftRowRedirection(leftAdded, slotState.slotLocation);

            slotState.indexBuilder = null;
            long size = slotState.rightRowSet.size();
            if (size > 0) {
                leftAdded.forAllRowKeys(ii -> {
                    final long currOffset = ii << jsm.getNumShiftBits();
                    downstreamAdds.addRange(currOffset, currOffset + size - 1);
                });
            } else if (jsm.leftOuterJoin()) {
                leftAdded.forAllRowKeys(ii -> {
                    final long currOffset = ii << jsm.getNumShiftBits();
                    downstreamAdds.addKey(currOffset);
                });
            }

            final RowSetBuilderRandom modifiedAdds = RowSetFactory.builderRandom();
            final int keySize = slotState.keySize();
            if (keySize > 0) {
                final WritableLongChunk<RowKeys> keyChunk = slotState.keyChunk.get();
                final WritableByteChunk<Values> flagChunk = slotState.flagChunk.get();
                for (int ii = 0; ii < keySize; ++ii) {
                    final long key = keyChunk.get(ii);
                    if (flagChunk.get(ii) != FLAG_ADD) {
                        continue;
                    }
                    // must be a modify
                    final long currOffset = key << jsm.getNumShiftBits();
                    if (size > 0) {
                        downstreamAdds.addRange(currOffset, currOffset + size - 1);
                    } else if (jsm.leftOuterJoin()) {
                        downstreamAdds.addKey(currOffset);
                    }
                    modifiedAdds.addKey(key);
                }
            }

            try (final RowSet moreLeftAdded = modifiedAdds.build()) {
                slotState.leftRowSet.insert(moreLeftAdded);
                jsm.updateLeftRowRedirection(moreLeftAdded, slotState.slotLocation);
            }
        }
        if (leftAdded == null) {
            leftAdded = downstreamAdds.build();
        } else {
            try (final RowSet toInsert = downstreamAdds.build()) {
                leftAdded.insert(toInsert);
            }
        }
    }

    void flushLeftModifies() {
        // Removes accumulate in the slot builder, modifies and adds accumulate in the chunks.
        // We leave the adds to process after left shifts are handled.

        final RowSetBuilderRandom rmBuilder = RowSetFactory.builderRandom();
        final RowSetBuilderRandom modBuilder = RowSetFactory.builderRandom();
        for (int jj = 0; jj < pointer; ++jj) {
            final SlotState slotState = modifiedSlots.get(jj);
            if (slotState == null) {
                continue;
            }
            final RowSet leftRemoved = slotState.indexBuilder.build();
            slotState.leftRowSet.remove(leftRemoved);
            jsm.updateLeftRowRedirection(leftRemoved, RowSequence.NULL_ROW_KEY);
            slotState.indexBuilder = RowSetFactory.builderRandom();
            final long sizePrev = slotState.rightRowSet.sizePrev();
            if (sizePrev > 0) {
                leftRemoved.forAllRowKeys(ii -> {
                    final long prevOffset = ii << jsm.getPrevNumShiftBits();
                    rmBuilder.addRange(prevOffset, prevOffset + sizePrev - 1);
                });
            } else if (jsm.leftOuterJoin()) {
                leftRemoved.forAllRowKeys(ii -> {
                    final long prevOffset = ii << jsm.getPrevNumShiftBits();
                    rmBuilder.addKey(prevOffset);
                });
            }
            final long size = slotState.rightRowSet.size();
            if (sizePrev > 0 && size > 0) {
                final int keySize = slotState.keySize();
                if (keySize > 0) {
                    final WritableLongChunk<RowKeys> keyChunk = slotState.keyChunk.get();
                    final WritableByteChunk<Values> flagChunk = slotState.flagChunk.get();
                    for (int ii = 0; ii < keySize; ++ii) {
                        final long key = keyChunk.get(ii);
                        if (flagChunk.get(ii) == FLAG_MOD) {
                            final long currOffset = key << jsm.getNumShiftBits();
                            modBuilder.addRange(currOffset, currOffset + size - 1);
                        }
                        // must be a modify
                        final long currOffset = key << jsm.getNumShiftBits();
                        modBuilder.addRange(currOffset, currOffset + size - 1);
                    }
                }
            } else if (jsm.leftOuterJoin() && sizePrev == 0 && size == 0) {
                final int keySize = slotState.keySize();
                if (keySize > 0) {
                    final WritableLongChunk<RowKeys> keyChunk = slotState.keyChunk.get();
                    final WritableByteChunk<Values> flagChunk = slotState.flagChunk.get();
                    for (int ii = 0; ii < keySize; ++ii) {
                        final long key = keyChunk.get(ii);
                        if (flagChunk.get(ii) == FLAG_MOD) {
                            final long currOffset = key << jsm.getNumShiftBits();
                            modBuilder.addKey(currOffset);
                        }
                    }
                }
            }
        }
        try (final RowSet toRemove = rmBuilder.build()) {
            leftRemoved.insert(toRemove);
        }
        leftModified = modBuilder.build();
        hasLeftModifies = leftModified.isNonempty();
    }
}
