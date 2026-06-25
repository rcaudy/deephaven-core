//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.base.verify.Assert;
import io.deephaven.util.channel.CachedChannelProvider;
import io.deephaven.util.channel.SeekableChannelContext;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.ClosedChannelException;
import java.nio.channels.NonWritableChannelException;
import java.nio.channels.SeekableByteChannel;
import java.util.Objects;

import static io.deephaven.extensions.azure.AzureReadContext.UNINITIALIZED_SIZE;

/**
 * {@link SeekableByteChannel} implementation for reading blobs from Azure Blob Storage with read-ahead caching.
 */
final class AzureSeekableByteChannel implements SeekableByteChannel, CachedChannelProvider.ContextHolder {

    private static final long CLOSED_SENTINEL = -1;
    private static final int INIT_POSITION = 0;

    private final AzureUri uri;
    private AzureReadContext context;
    private long position;
    private long size;

    AzureSeekableByteChannel(final AzureUri uri) {
        this(uri, UNINITIALIZED_SIZE);
    }

    AzureSeekableByteChannel(final AzureUri uri, final long size) {
        this.uri = Objects.requireNonNull(uri);
        this.size = size;
        this.position = INIT_POSITION;
    }

    @Override
    public void setContext(@Nullable final SeekableChannelContext channelContext) {
        if (channelContext != null && !(channelContext instanceof AzureReadContext)) {
            throw new IllegalArgumentException("Unsupported channel context " + channelContext);
        }
        this.context = (AzureReadContext) channelContext;
        if (this.context != null) {
            this.context.setURI(uri);
            if (size != UNINITIALIZED_SIZE) {
                context.verifyOrSetSize(size);
            }
        }
    }

    private void prepareRead() throws IOException {
        checkClosed(position);
        Assert.neqNull(context, "channelContext");
        if (size == UNINITIALIZED_SIZE) {
            size = context.size();
        }
    }

    @Override
    public int read(@NotNull final ByteBuffer destination) throws IOException {
        prepareRead();
        if (position >= size) {
            return -1;
        }
        final int filled = context.fill(position, destination);
        position += filled;
        return filled;
    }

    @Override
    public int write(final ByteBuffer src) {
        throw new NonWritableChannelException();
    }

    @Override
    public long position() throws ClosedChannelException {
        checkClosed(position);
        return position;
    }

    @Override
    public SeekableByteChannel position(final long newPosition) throws ClosedChannelException {
        checkClosed(position);
        if (newPosition < 0) {
            throw new IllegalArgumentException("newPosition cannot be < 0, provided newPosition=" + newPosition);
        }
        position = newPosition;
        return this;
    }

    @Override
    public long size() throws IOException {
        prepareRead();
        return size;
    }

    @Override
    public SeekableByteChannel truncate(final long size) {
        throw new NonWritableChannelException();
    }

    @Override
    public boolean isOpen() {
        return position != CLOSED_SENTINEL;
    }

    @Override
    public void close() {
        position = CLOSED_SENTINEL;
    }

    private static void checkClosed(final long position) throws ClosedChannelException {
        if (position == CLOSED_SENTINEL) {
            throw new ClosedChannelException();
        }
    }
}
