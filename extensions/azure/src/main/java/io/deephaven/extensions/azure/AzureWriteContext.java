//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.util.channel.SeekableChannelsProvider;
import org.jetbrains.annotations.NotNull;

import java.nio.ByteBuffer;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.atomic.AtomicIntegerFieldUpdater;

/**
 * Context object used to store buffer pool for Azure write requests.
 */
final class AzureWriteContext implements SeekableChannelsProvider.WriteContext {
    private static final Logger log = LoggerFactory.getLogger(AzureWriteContext.class);

    private final int writeBlockSize;
    private final int numConcurrentWriteBlocks;
    private final ArrayBlockingQueue<ByteBuffer> bufferQueue;
    private volatile int createdCount;

    private static final AtomicIntegerFieldUpdater<AzureWriteContext> CREATED_COUNT_UPDATER =
            AtomicIntegerFieldUpdater.newUpdater(AzureWriteContext.class, "createdCount");

    AzureWriteContext(@NotNull final AzureInstructions instructions) {
        this.writeBlockSize = instructions.writeBlockSize();
        this.numConcurrentWriteBlocks = instructions.numConcurrentWriteBlocks();
        this.bufferQueue = new ArrayBlockingQueue<>(numConcurrentWriteBlocks);
        this.createdCount = 0;
        if (log.isDebugEnabled()) {
            log.debug().append("Creating Azure output stream context").endl();
        }
    }

    ByteBuffer take() throws InterruptedException {
        final ByteBuffer buffer = bufferQueue.poll();
        if (buffer != null) {
            return buffer;
        }
        int current;
        while ((current = createdCount) < numConcurrentWriteBlocks) {
            if (CREATED_COUNT_UPDATER.compareAndSet(this, current, current + 1)) {
                return ByteBuffer.allocate(writeBlockSize);
            }
        }
        return bufferQueue.take();
    }

    void give(@NotNull final ByteBuffer buffer) {
        buffer.clear();
        if (!bufferQueue.offer(buffer)) {
            throw new IllegalStateException("Failed to return buffer to queue, queue size expected to be " +
                    numConcurrentWriteBlocks + ", remaining capacity = " + bufferQueue.remainingCapacity());
        }
    }

    @Override
    public void close() {
        bufferQueue.clear();
    }
}
