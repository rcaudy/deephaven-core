//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit CharChunkChunk and run "./gradlew replicateSourcesAndChunks" to regenerate
//
// @formatter:off
package io.deephaven.chunk;

import io.deephaven.chunk.attributes.Any;

public class DoubleChunkChunk<ATTR extends Any> extends ChunkChunkBase<ATTR> implements ChunkChunk<ATTR> {
    @SuppressWarnings({"unchecked", "rawtypes"})
    private static final DoubleChunkChunk EMPTY = new DoubleChunkChunk<>(new DoubleChunk[0], 0, 0);

    public static <ATTR extends Any> DoubleChunkChunk<ATTR> getEmptyChunk() {
        // noinspection unchecked
        return EMPTY;
    }

    public static <ATTR extends Any> DoubleChunk<ATTR>[] makeArray(int capacity) {
        // noinspection unchecked
        return new DoubleChunk[capacity];
    }

    public static <ATTR extends Any> DoubleChunkChunk<ATTR> chunkWrap(DoubleChunk<ATTR>[] data) {
        return new DoubleChunkChunk<>(data, 0, data.length);
    }

    public static <ATTR extends Any> DoubleChunkChunk<ATTR> chunkWrap(DoubleChunk<ATTR>[] data, int offset, int capacity) {
        return new DoubleChunkChunk<>(data, offset, capacity);
    }

    DoubleChunk<ATTR>[] data;
    /**
     * innerData[i] is a cached copy of data[i].data used for faster two-dimensional access.
     */
    double[][] innerData;
    /**
     * innerOffsets[i] is a cached copy of data[i].offset used for faster two-dimensional access.
     */
    int[] innerOffsets;

    DoubleChunkChunk(DoubleChunk<ATTR>[] data, int offset, int capacity) {
        super(data.length, offset, capacity);
        this.data = data;
        resetInnerCache(data, offset, 0, capacity);
    }

    /**
     * Update cached "inner" data structures.
     */
    final void resetInnerCache(DoubleChunk<ATTR>[] data, int offset, int oldCapacity, int newCapacity) {
        if (innerData == null || innerData.length < newCapacity) {
            innerData = new double[newCapacity][];
            innerOffsets = new int[newCapacity];
        }
        for (int ii = 0; ii < newCapacity; ++ii) {
            resetInnerCacheItem(ii, data[ii + offset]);
        }
        for (int ii = newCapacity; ii < oldCapacity; ++ii) {
            // Be friendly to the garbage collector
            innerData[ii] = null;
            innerOffsets[ii] = 0; // to be nice
        }
    }

    /**
     * Update a specific cached "inner" data structures.
     */
    final void resetInnerCacheItem(int index, DoubleChunk<ATTR> chunk) {
        if (chunk == null) {
            innerData[index] = null;
            innerOffsets[index] = 0;
        } else {
            innerData[index] = chunk.data;
            innerOffsets[index] = chunk.offset;
        }
    }

    public final DoubleChunk<ATTR> get(int index) {
        return data[offset + index];
    }

    public final DoubleChunk<ATTR> getChunk(int index) {
        return get(index);
    }

    public final double get(int j, int i) {
        return innerData[j][innerOffsets[j] + i];
    }

    @Override
    public DoubleChunkChunk<ATTR> slice(int offset, int capacity) {
        ChunkHelpers.checkSliceArgs(size, offset, capacity);
        return new DoubleChunkChunk<>(data, this.offset + offset, capacity);
    }

    // region AsType
    // endregion AsType
}
