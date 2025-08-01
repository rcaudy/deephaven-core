//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit ResettableWritableCharChunk and run "./gradlew replicateSourcesAndChunks" to regenerate
//
// @formatter:off
package io.deephaven.chunk;

import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.util.pools.MultiChunkPool;
import io.deephaven.util.type.ArrayTypeUtils;

import static io.deephaven.chunk.util.pools.ChunkPoolConstants.POOL_RESETTABLE_CHUNKS;

/**
 * {@link ResettableWritableChunk} implementation for byte data.
 */
public class ResettableWritableByteChunk<ATTR_BASE extends Any>
        extends WritableByteChunk<ATTR_BASE>
        implements ResettableWritableChunk<ATTR_BASE> {

    public static <ATTR_BASE extends Any> ResettableWritableByteChunk<ATTR_BASE> makeResettableChunk() {
        if (POOL_RESETTABLE_CHUNKS) {
            return MultiChunkPool.forThisThread().takeResettableWritableByteChunk();
        }
        return new ResettableWritableByteChunk<>();
    }

    private ResettableWritableByteChunk(byte[] data, int offset, int capacity) {
        super(data, offset, capacity);
    }

    protected ResettableWritableByteChunk() {
        this(ArrayTypeUtils.EMPTY_BYTE_ARRAY, 0, 0);
    }

    @Override
    public ResettableWritableByteChunk<ATTR_BASE> slice(int offset, int capacity) {
        ChunkHelpers.checkSliceArgs(size, offset, capacity);
        return new ResettableWritableByteChunk<>(data, this.offset + offset, capacity);
    }

    @Override
    public <ATTR extends ATTR_BASE> WritableByteChunk<ATTR> resetFromChunk(WritableChunk<ATTR> other, int offset,
            int capacity) {
        return resetFromTypedChunk(other.asWritableByteChunk(), offset, capacity);
    }

    @Override
    public <ATTR extends ATTR_BASE> WritableByteChunk<ATTR> resetFromArray(Object array, int offset, int capacity) {
        final byte[] typedArray = (byte[]) array;
        return resetFromTypedArray(typedArray, offset, capacity);
    }

    public <ATTR extends ATTR_BASE> WritableByteChunk<ATTR> resetFromArray(Object array) {
        final byte[] typedArray = (byte[]) array;
        return resetFromTypedArray(typedArray, 0, typedArray.length);
    }

    @Override
    public <ATTR extends ATTR_BASE> WritableByteChunk<ATTR> clear() {
        return resetFromArray(ArrayTypeUtils.EMPTY_BYTE_ARRAY, 0, 0);
    }

    public <ATTR extends ATTR_BASE> WritableByteChunk<ATTR> resetFromTypedChunk(WritableByteChunk<ATTR> other,
            int offset, int capacity) {
        ChunkHelpers.checkSliceArgs(other.size, offset, capacity);
        return resetFromTypedArray(other.data, other.offset + offset, capacity);
    }

    public <ATTR extends ATTR_BASE> WritableByteChunk<ATTR> resetFromTypedArray(byte[] data, int offset, int capacity) {
        ChunkHelpers.checkArrayArgs(data.length, offset, capacity);
        this.data = data;
        this.offset = offset;
        this.capacity = capacity;
        this.size = capacity;
        // noinspection unchecked
        return (WritableByteChunk<ATTR>) this;
    }
}
