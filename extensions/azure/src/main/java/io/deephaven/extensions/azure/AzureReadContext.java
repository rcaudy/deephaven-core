//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.engine.readtracker.impl.QueryPerformanceReadTracker;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.util.channel.BaseSeekableChannelContext;
import io.deephaven.util.channel.SeekableChannelContext;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Objects;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeoutException;

/**
 * Context object used to store read-ahead buffers for efficiently reading from Azure Blob Storage.
 */
final class AzureReadContext extends BaseSeekableChannelContext implements SeekableChannelContext {
    private static final Logger log = LoggerFactory.getLogger(AzureReadContext.class);
    static final long UNINITIALIZED_SIZE = -1;
    private static final long UNINITIALIZED_NUM_FRAGMENTS = -1;

    private final AzureSeekableChannelProvider provider;
    final AzureInstructions instructions;
    AzureUri uri;
    final AzureReadRequestCache sharedReadCache;
    long size;
    private long numFragments;

    AzureReadContext(
            @NotNull final AzureSeekableChannelProvider provider,
            @NotNull final AzureInstructions instructions,
            @NotNull final AzureReadRequestCache sharedReadCache) {
        this.provider = Objects.requireNonNull(provider);
        this.instructions = Objects.requireNonNull(instructions);
        this.sharedReadCache = sharedReadCache;
        if (sharedReadCache.getFragmentSize() != instructions.fragmentSize()) {
            throw new IllegalArgumentException("Fragment size mismatch between shared cache and instructions, "
                    + sharedReadCache.getFragmentSize() + " != " + instructions.fragmentSize());
        }
        uri = null;
        size = UNINITIALIZED_SIZE;
        numFragments = UNINITIALIZED_NUM_FRAGMENTS;
    }

    void setURI(@NotNull final AzureUri uri) {
        if (!uri.equals(this.uri)) {
            reset();
        }
        this.uri = uri;
    }

    void verifyOrSetSize(final long size) {
        if (this.size == UNINITIALIZED_SIZE) {
            setSize(size);
        } else if (this.size != size) {
            throw new IllegalStateException(
                    String.format("Inconsistent size. expected=%d, actual=%d, ctx=%s", size, this.size, ctxStr()));
        }
    }

    long size() throws IOException {
        ensureSize();
        return size;
    }

    int fill(final long position, final ByteBuffer dest) throws IOException {
        final int destRemaining = dest.remaining();
        if (destRemaining == 0) {
            return 0;
        }
        ensureSize();
        final long firstFragmentIx = fragmentIndex(position);
        final long readAhead;
        {
            final long lastFragmentIx = fragmentIndex(position + destRemaining - 1);
            final int impliedReadAhead = (int) (lastFragmentIx - firstFragmentIx);
            final int desiredReadAhead = instructions.readAheadCount();
            final long totalRemainingFragments = numFragments - firstFragmentIx - 1;
            readAhead = Math.min(Math.max(impliedReadAhead, desiredReadAhead), totalRemainingFragments);
        }
        final long startNanos = System.nanoTime();
        int filled;
        {
            final AzureReadRequest.Acquired acquiredRequest = getOrCreateRequest(firstFragmentIx);
            for (int i = 0; i < readAhead; ++i) {
                getOrCreateRequest(firstFragmentIx + i + 1);
            }
            filled = acquiredRequest.fill(position, dest);
        }
        for (int i = 0; dest.hasRemaining(); ++i) {
            final AzureReadRequest.Acquired readAheadRequest =
                    sharedReadCache.getRequest(uri, firstFragmentIx + i + 1);
            if (readAheadRequest == null || !readAheadRequest.isDone()) {
                break;
            }
            filled += readAheadRequest.fill(position + filled, dest);
        }
        final long durationNanos = System.nanoTime() - startNanos;
        QueryPerformanceReadTracker.recordRead(durationNanos, filled);
        return filled;
    }

    private void reset() {
        uri = null;
        size = UNINITIALIZED_SIZE;
        numFragments = UNINITIALIZED_NUM_FRAGMENTS;
    }

    @Override
    public void close() {
        super.close();
    }

    @NotNull
    private AzureReadRequest.Acquired getOrCreateRequest(final long fragmentIndex) {
        final AzureReadRequest.Acquired cachedRequest =
                sharedReadCache.getOrCreateRequest(uri, fragmentIndex, this);
        cachedRequest.send();
        return cachedRequest;
    }

    private long fragmentIndex(final long pos) {
        return pos / instructions.fragmentSize();
    }

    private String ctxStr() {
        if (uri != null) {
            return String.format("ctx=%d %s/%s", System.identityHashCode(AzureReadContext.this),
                    uri.container(), uri.blobPath());
        } else {
            return String.format("ctx=%d", System.identityHashCode(AzureReadContext.this));
        }
    }

    static IOException handleAzureException(
            final Exception e,
            final String operationDescription,
            final AzureInstructions instructions) {
        if (e instanceof InterruptedException) {
            Thread.currentThread().interrupt();
            return new IOException(String.format("Thread interrupted while %s", operationDescription), e);
        }
        if (e instanceof ExecutionException) {
            return new IOException(String.format("Execution exception occurred while %s", operationDescription), e);
        }
        if (e instanceof TimeoutException) {
            return new IOException(String.format(
                    "Operation timeout while %s after waiting for duration %s", operationDescription,
                    instructions.readTimeout()), e);
        }
        if (e instanceof CancellationException) {
            return new IOException(String.format("Cancelled an operation while %s", operationDescription), e);
        }
        return new IOException(String.format("Exception caught while %s", operationDescription), e);
    }

    private void ensureSize() throws IOException {
        if (size != UNINITIALIZED_SIZE) {
            return;
        }
        setSize(provider.fetchBlobSize(uri));
    }

    private void setSize(final long size) {
        this.size = size;
        this.numFragments = (size + instructions.fragmentSize() - 1) / instructions.fragmentSize();
    }
}
