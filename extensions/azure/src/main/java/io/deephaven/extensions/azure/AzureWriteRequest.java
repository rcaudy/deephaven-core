//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import java.nio.ByteBuffer;

/**
 * Holds a borrowed buffer from the {@link AzureWriteContext} pool for a single block upload.
 */
final class AzureWriteRequest {
    final ByteBuffer buffer;
    private final AzureWriteContext context;

    AzureWriteRequest(final AzureWriteContext context, final int blockSize) throws InterruptedException {
        this.context = context;
        this.buffer = context.take();
        this.buffer.limit(blockSize);
    }

    void releaseBuffer() {
        context.give(buffer);
    }
}
