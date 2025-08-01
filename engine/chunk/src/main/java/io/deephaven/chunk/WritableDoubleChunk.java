//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit WritableCharChunk and run "./gradlew replicateSourcesAndChunks" to regenerate
//
// @formatter:off
package io.deephaven.chunk;

import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.util.pools.MultiChunkPool;

import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;

import java.util.Arrays;
// region FillWithNullValueImports
import static io.deephaven.util.QueryConstants.NULL_DOUBLE;
// endregion FillWithNullValueImports

// region BufferImports
import java.nio.Buffer;
import java.nio.DoubleBuffer;
// endregion BufferImports

import static io.deephaven.chunk.util.pools.ChunkPoolConstants.POOL_WRITABLE_CHUNKS;

/**
 * {@link WritableChunk} implementation for double data.
 */
public class WritableDoubleChunk<ATTR extends Any> extends DoubleChunk<ATTR> implements WritableChunk<ATTR> {

    @SuppressWarnings("rawtypes")
    private static final WritableDoubleChunk[] EMPTY_WRITABLE_DOUBLE_CHUNK_ARRAY = new WritableDoubleChunk[0];

    static <ATTR extends Any> WritableDoubleChunk<ATTR>[] getEmptyChunkArray() {
        // noinspection unchecked
        return EMPTY_WRITABLE_DOUBLE_CHUNK_ARRAY;
    }

    /**
     * Get a {@link WritableDoubleChunk} with {@link #size()} of {@code size} for use by the caller until it is
     * {@link #close() closed}.
     *
     * @param size The {@link #size()} and minimum capacity of the returned chunk
     * @return The chunk
     */
    public static <ATTR extends Any> WritableDoubleChunk<ATTR> makeWritableChunk(int size) {
        if (POOL_WRITABLE_CHUNKS) {
            return MultiChunkPool.forThisThread().takeWritableDoubleChunk(size);
        }
        return new WritableDoubleChunk<>(makeArray(size), 0, size);
    }

    public static <ATTR extends Any> WritableDoubleChunk<ATTR> writableChunkWrap(double[] data) {
        return writableChunkWrap(data, 0, data.length);
    }

    public static <ATTR extends Any> WritableDoubleChunk<ATTR> writableChunkWrap(double[] data, int offset, int size) {
        return new WritableDoubleChunk<>(data, offset, size);
    }

    protected WritableDoubleChunk(double[] data, int offset, int capacity) {
        super(data, offset, capacity);
    }

    public final void set(int index, double value) {
        data[offset + index] = value;
    }

    public final void add(double value) {
        data[offset + size++] = value;
    }

    @Override
    public WritableDoubleChunk<ATTR> slice(int offset, int capacity) {
        ChunkHelpers.checkSliceArgs(size, offset, capacity);
        return new WritableDoubleChunk<>(data, this.offset + offset, capacity);
    }

    // region array
    /**
     * Get the data array backing this WritableDoubleChunk. The first element of this chunk corresponds to
     * {@code array()[arrayOffset()]}.
     * <p>
     * This WritableDoubleChunk must never be {@link #close() closed} while the array <em>may</em> be in use externally,
     * because it must not be returned to any pool for re-use until that re-use is guaranteed to be exclusive.
     *
     * @return The backing data array
     */
    public final double[] array() {
        return data;
    }

    /**
     * Get this WritableDoubleChunk's offset into the backing data array. The first element of this chunk corresponds to
     * {@code array()[arrayOffset()]}.
     *
     * @return The offset into the backing data array
     */
    public final int arrayOffset() {
        return offset;
    }
    // endregion array

    // region FillWithNullValueImpl
    @Override
    public final void fillWithNullValue(final int offset, final int length) {
        fillWithValue(offset, length, NULL_DOUBLE);
    }
    // endregion FillWithNullValueImpl

    // region fillWithBoxedValue
    @Override
    public final void fillWithBoxedValue(int offset, int size, Object value) {
        fillWithValue(offset, size, TypeUtils.unbox((Double) value));
    }
    // endregion fillWithBoxedValue

    public final void fillWithValue(final int offset, final int length, final double value) {
        final int netOffset = this.offset + offset;
        if (length >= SYSTEM_ARRAYFILL_THRESHOLD) {
            Arrays.fill(data, netOffset, netOffset + length, value);
            return;
        }
        for (int ii = 0; ii < length; ++ii) {
            data[netOffset + ii] = value;
        }
    }

    public final void appendTypedChunk(DoubleChunk<? extends ATTR> src, int srcOffset, int length) {
        copyFromTypedChunk(src, srcOffset, size, length);
        size += length;
    }

    @Override
    public final void copyFromChunk(Chunk<? extends ATTR> src, int srcOffset, int destOffset, int length) {
        final DoubleChunk<? extends ATTR> typedSrc = src.asDoubleChunk();
        copyFromTypedChunk(typedSrc, srcOffset, destOffset, length);
    }

    public final void copyFromTypedChunk(DoubleChunk<? extends ATTR> src, int srcOffset, int destOffset, int length) {
        copyFromTypedArray(src.data, src.offset + srcOffset, destOffset, length);
    }

    @Override
    public final void copyFromArray(Object srcArray, int srcOffset, int destOffset, int length) {
        final double[] typedArray = (double[]) srcArray;
        copyFromTypedArray(typedArray, srcOffset, destOffset, length);
    }

    public final void copyFromTypedArray(double[] src, int srcOffset, int destOffset, int length) {
        final int netDestOffset = offset + destOffset;
        if (length >= SYSTEM_ARRAYCOPY_THRESHOLD) {
            // I wonder if this is wasteful because we already know the concrete type of src and data.
            System.arraycopy(src, srcOffset, data, netDestOffset, length);
            return;
        }
        if (ChunkHelpers.canCopyForward(src, srcOffset, data, destOffset, length)) {
            // noinspection ManualArrayCopy
            for (int ii = 0; ii < length; ++ii) {
                data[netDestOffset + ii] = src[srcOffset + ii];
            }
            return;
        }
        // noinspection ManualArrayCopy
        for (int ii = length - 1; ii >= 0; --ii) {
            data[netDestOffset + ii] = src[srcOffset + ii];
        }
    }

    // region CopyFromBuffer
    @Override
    public final void copyFromBuffer(@NotNull final Buffer srcBuffer, final int srcOffset, final int destOffset,
            final int length) {
        final DoubleBuffer doubleSrcBuffer = (DoubleBuffer) srcBuffer;
        copyFromTypedBuffer(doubleSrcBuffer, srcOffset, destOffset, length);
    }

    /**
     * <p>
     * Fill a sub-range of this WritableDoubleChunk with values from a {@link DoubleBuffer}.
     *
     * <p>
     * See {@link #copyFromBuffer(Buffer, int, int, int)} for general documentation.
     *
     * @param srcBuffer The source {@link DoubleBuffer}
     * @param srcOffset The absolute offset into {@code srcBuffer} to start copying from
     * @param destOffset The offset into this chunk to start copying to
     * @param length The number of elements to copy
     */
    public final void copyFromTypedBuffer(@NotNull final DoubleBuffer srcBuffer, final int srcOffset,
            final int destOffset, final int length) {
        if (srcBuffer.hasArray()) {
            copyFromTypedArray(srcBuffer.array(), srcBuffer.arrayOffset() + srcOffset, destOffset, length);
        } else {
            final int initialPosition = srcBuffer.position();
            srcBuffer.position(srcOffset);
            srcBuffer.get(data, offset + destOffset, length);
            srcBuffer.position(initialPosition);
        }
    }
    // endregion CopyFromBuffer

    @Override
    public final void sort() {
        sort(0, size);
    }

    // region sort
    @Override
    public final void sort(int start, int length) {
        Arrays.sort(data, offset + start, offset + start + length);

        // region SortFixup
        // endregion SortFixup
    }
    // endregion sort

    @Override
    public void close() {}

    // region downcast
    public static <ATTR extends Any, ATTR_DERIV extends ATTR> WritableDoubleChunk<ATTR> upcast(
            WritableDoubleChunk<ATTR_DERIV> self) {
        // noinspection unchecked
        return (WritableDoubleChunk<ATTR>) self;
    }
    // endregion downcast
}
