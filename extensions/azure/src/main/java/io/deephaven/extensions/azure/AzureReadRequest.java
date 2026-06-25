//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobAsyncClient;
import com.azure.storage.blob.models.BlobRange;
import io.deephaven.base.reference.CleanupReference;
import io.deephaven.base.stats.Counter;
import io.deephaven.base.stats.Stats;
import io.deephaven.base.stats.Value;
import io.deephaven.base.verify.Require;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.util.reference.CleanupReferenceProcessor;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.IOException;
import java.lang.ref.SoftReference;
import java.nio.ByteBuffer;
import java.time.Duration;
import java.time.Instant;
import java.util.concurrent.CancellationException;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

/**
 * A request for a single fragment of an Azure blob, which can be used concurrently. Extends {@link SoftReference} and
 * implements {@link CleanupReference} to allow for cancelling the request once all references to the buffer have been
 * released.
 */
final class AzureReadRequest extends SoftReference<ByteBuffer> implements CleanupReference<ByteBuffer> {

    private static final Value READ_DURATION_NANOS =
            Stats.makeItem("AzureReadRequest", "readDurationNanos", Counter.FACTORY).getValue();
    private static final Value READ_SIZE_BYTES =
            Stats.makeItem("AzureReadRequest", "readSizeBytes", Counter.FACTORY).getValue();

    static final class ID {
        private final AzureUri uri;
        private final long fragmentIndex;

        ID(final AzureUri uri, final long fragmentIndex) {
            this.uri = Require.neqNull(uri, "uri");
            this.fragmentIndex = fragmentIndex;
        }

        @Override
        public int hashCode() {
            int result = 31 + Long.hashCode(fragmentIndex);
            result = 31 * result + uri.hashCode();
            return result;
        }

        @Override
        public boolean equals(final Object obj) {
            if (this == obj)
                return true;
            if (obj == null || getClass() != obj.getClass())
                return false;
            final ID other = (ID) obj;
            return fragmentIndex == other.fragmentIndex && uri.equals(other.uri);
        }
    }

    private static final Logger log = LoggerFactory.getLogger(AzureReadRequest.class);

    private final AzureUri azureUri;
    private final ID id;
    private final AzureInstructions instructions;
    private final BlobAsyncClient blobAsyncClient;
    private final long fragmentIndex;
    private final long from;
    private final long to;
    private final Instant createdAt;
    private volatile CompletableFuture<Boolean> consumerFuture;
    private volatile long startNanos;
    private int fillCount;
    private long fillBytes;
    private final AzureReadRequestCache sharedCache;

    @NotNull
    static Acquired createAndAcquire(final long fragmentIndex, @NotNull final AzureReadContext context) {
        final long from = fragmentIndex * context.instructions.fragmentSize();
        final long to = Math.min(from + context.instructions.fragmentSize(), context.size) - 1;
        final long requestLength = to - from + 1;
        final ByteBuffer buffer = ByteBuffer.allocate((int) requestLength);
        final AzureReadRequest request = new AzureReadRequest(fragmentIndex, context, buffer, from, to);
        return request.acquire(buffer);
    }

    private AzureReadRequest(
            final long fragmentIndex,
            @NotNull final AzureReadContext context,
            @NotNull final ByteBuffer buffer,
            final long from,
            final long to) {
        super(buffer, CleanupReferenceProcessor.getDefault().getReferenceQueue());
        this.fragmentIndex = fragmentIndex;
        this.azureUri = context.uri;
        this.instructions = context.instructions;
        this.blobAsyncClient = AzureBlobClientFactory.getContainerAsyncClient(context.instructions, context.uri)
                .getBlobAsyncClient(context.uri.blobPath());
        this.from = from;
        this.to = to;
        sharedCache = context.sharedReadCache;
        createdAt = Instant.now();
        id = new ID(azureUri, fragmentIndex);
    }

    ID getId() {
        return id;
    }

    @Nullable
    Acquired tryAcquire() {
        final ByteBuffer acquiredBuffer = get();
        if (acquiredBuffer == null) {
            return null;
        }
        return acquire(acquiredBuffer);
    }

    private Acquired acquire(final ByteBuffer buffer) {
        return new Acquired(buffer);
    }

    private void sendImpl() {
        if (consumerFuture == null) {
            synchronized (this) {
                if (consumerFuture == null) {
                    if (log.isDebugEnabled()) {
                        log.debug().append("Sending: ").append(requestStr()).endl();
                    }
                    startNanos = System.nanoTime();
                    final long requestLength = to - from + 1;
                    final BlobRange range = new BlobRange(from, requestLength);
                    consumerFuture = blobAsyncClient.downloadStreamWithResponse(range, null, null, false)
                            .flatMapMany(response -> response.getValue())
                            .reduce(get(), (buf, chunk) -> {
                                if (buf == null) {
                                    return null;
                                }
                                final int numBytes = chunk.remaining();
                                buf.duplicate().position(buf.position()).put(chunk);
                                buf.position(buf.position() + numBytes);
                                return buf;
                            })
                            .map(buf -> {
                                if (buf == null) {
                                    return false;
                                }
                                buf.flip();
                                return true;
                            })
                            .defaultIfEmpty(false)
                            .toFuture()
                            .whenComplete((isComplete, throwable) -> {
                                final long durationNanos = System.nanoTime() - startNanos;
                                READ_DURATION_NANOS.sample(durationNanos);
                                READ_SIZE_BYTES.sample(requestLength());
                                if (log.isDebugEnabled()) {
                                    final Instant completedAt = Instant.now();
                                    if (Boolean.TRUE.equals(isComplete)) {
                                        log.debug().append("Send complete: ").append(requestStr()).append(' ')
                                                .append(Duration.between(createdAt, completedAt).toString()).endl();
                                    } else {
                                        log.debug().append("Send error: ").append(requestStr()).append(' ')
                                                .append(Duration.between(createdAt, completedAt).toString()).endl();
                                    }
                                }
                            });
                }
            }
        }
    }

    class Acquired {
        private final ByteBuffer acquiredBuffer;

        private Acquired(final ByteBuffer buffer) {
            this.acquiredBuffer = buffer;
        }

        boolean isDone() {
            return consumerFuture != null && consumerFuture.isDone();
        }

        void send() {
            sendImpl();
        }

        final AzureReadRequest request() {
            return AzureReadRequest.this;
        }

        int fill(final long localPosition, final ByteBuffer dest) throws IOException {
            final int resultOffset = (int) (localPosition - from);
            final int resultLength = Math.min((int) (to - localPosition + 1), dest.remaining());
            final ByteBuffer filledBuffer = getFilledBuffer();
            filledBuffer.limit(resultOffset + resultLength);
            filledBuffer.position(resultOffset);
            try {
                dest.put(filledBuffer);
            } finally {
                filledBuffer.clear();
            }
            ++fillCount;
            fillBytes += resultLength;
            return resultLength;
        }

        private ByteBuffer getFilledBuffer() throws IOException {
            final long readNanos = instructions.readTimeout().plusMillis(100).toNanos();
            final Boolean isComplete;
            try {
                isComplete = consumerFuture.get(readNanos, TimeUnit.NANOSECONDS);
            } catch (final InterruptedException | ExecutionException | TimeoutException | CancellationException e) {
                throw AzureReadContext.handleAzureException(e,
                        String.format("fetching fragment %s", requestStr()), instructions);
            }
            if (!Boolean.TRUE.equals(isComplete)) {
                throw new IllegalStateException(String.format("Failed to complete request %s, probably because the " +
                        "underlying buffer got freed while completing the request", requestStr()));
            }
            final ByteBuffer filledBuffer = acquiredBuffer.asReadOnlyBuffer();
            if (filledBuffer.position() != 0 || filledBuffer.limit() != filledBuffer.capacity()
                    || filledBuffer.limit() != requestLength()) {
                throw new IllegalStateException(String.format(
                        "Expected: pos=0, limit=%d, capacity=%d. Actual: pos=%d, limit=%d, capacity=%d",
                        requestLength(), requestLength(), filledBuffer.position(), filledBuffer.limit(),
                        filledBuffer.capacity()));
            }
            return filledBuffer;
        }
    }

    @Override
    public void cleanup() {
        final boolean didCancel = consumerFuture.cancel(true);
        sharedCache.remove(this);
        if (log.isDebugEnabled()) {
            final String cancelType = didCancel ? "fast" : (fillCount == 0 ? "unused" : "normal");
            log.debug()
                    .append("cancel ").append(cancelType)
                    .append(": ")
                    .append(requestStr())
                    .append(" fillCount=").append(fillCount)
                    .append(" fillBytes=").append(fillBytes).endl();
        }
    }

    private int requestLength() {
        return (int) (to - from + 1);
    }

    String requestStr() {
        return String.format("ix=%d [%d, %d]/%d %s/%s", fragmentIndex, from, to, requestLength(),
                azureUri.container(), azureUri.blobPath());
    }
}
