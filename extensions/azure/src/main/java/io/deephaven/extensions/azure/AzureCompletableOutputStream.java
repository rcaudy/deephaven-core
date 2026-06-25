//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobAsyncClient;
import com.azure.storage.blob.specialized.BlockBlobAsyncClient;
import io.deephaven.util.SafeCloseable;
import io.deephaven.util.channel.CompletableOutputStream;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import reactor.core.publisher.Flux;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.CancellationException;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Semaphore;

/**
 * Output stream implementation that writes to Azure Blob Storage using staged block upload.
 *
 * <p>
 * Blocks are staged with unique block IDs and committed in order when the stream is completed. This is analogous to
 * S3's multipart upload.
 */
final class AzureCompletableOutputStream extends CompletableOutputStream {

    private static final int MAX_BLOCK_COUNT = 50000;

    private final AzureUri azureUri;
    private final BlockBlobAsyncClient blockBlobClient;
    private final AzureInstructions instructions;

    private int nextBlockNumber;
    private final Semaphore numBlocksCompleted;
    private final List<String> committedBlockIds;
    private final AzureWriteContext writeContext;

    @Nullable
    private AzureWriteRequest bufferedBlockRequest;

    @Nullable
    private CompletableFuture<Void> handoff;

    private enum State {
        OPEN, DONE, COMPLETED, ABORTED
    }

    private State state;
    private final CompletableFuture<Void> status;

    AzureCompletableOutputStream(
            @NotNull final AzureUri azureUri,
            @NotNull final BlobAsyncClient blobAsyncClient,
            @NotNull final AzureInstructions instructions,
            @NotNull final SafeCloseable channelContext) {
        this.azureUri = azureUri;
        this.blockBlobClient = blobAsyncClient.getBlockBlobAsyncClient();
        this.instructions = instructions;

        this.nextBlockNumber = 0;
        this.numBlocksCompleted = new Semaphore(0);
        this.committedBlockIds = Collections.synchronizedList(new ArrayList<>());

        if (!(channelContext instanceof AzureWriteContext)) {
            throw new IllegalArgumentException("Unsupported channel context " + channelContext);
        }
        this.writeContext = (AzureWriteContext) channelContext;
        this.bufferedBlockRequest = null;

        this.state = State.OPEN;
        this.status = new CompletableFuture<>();
    }

    @Override
    public void write(final int b) throws IOException {
        checkStatus();
        write((dest, destOff, destCount) -> {
            dest.put((byte) b);
            return 1;
        }, 0, 1);
    }

    @Override
    public void write(final byte @NotNull [] b) throws IOException {
        checkStatus();
        write(b, 0, b.length);
    }

    @Override
    public void write(final byte @NotNull [] b, final int off, final int len) throws IOException {
        checkStatus();
        write((dest, currentOffset, remainingLength) -> {
            final int lengthToWrite = Math.min(remainingLength, dest.remaining());
            dest.put(b, currentOffset, lengthToWrite);
            return lengthToWrite;
        }, off, len);
    }

    @FunctionalInterface
    private interface DataWriter {
        int write(ByteBuffer dest, int currentOffset, int remainingLength) throws IOException;
    }

    private void write(@NotNull final DataWriter writer, int off, int len) throws IOException {
        if (state != State.OPEN) {
            throw new IOException("Cannot write to stream for uri " + azureUri + " because stream is in state " +
                    state + " instead of OPEN");
        }
        while (len != 0) {
            final int lengthWritten = writeImpl(writer, off, len);
            off += lengthWritten;
            len -= lengthWritten;
        }
    }

    private int writeImpl(final DataWriter writer, final int off, final int len) throws IOException {
        if (bufferedBlockRequest == null) {
            final AzureWriteRequest request;
            try {
                request = new AzureWriteRequest(writeContext, instructions.writeBlockSize());
            } catch (final InterruptedException e) {
                Thread.currentThread().interrupt();
                throw new IOException("Thread interrupted while creating a write request for block " +
                        nextBlockNumber, e);
            }
            handoff = new CompletableFuture<>();
            forwardExceptionAsCancel(status, handoff);
            handoff.whenComplete((unused, throwable) -> {
                if (throwable != null) {
                    request.releaseBuffer();
                }
            });
            bufferedBlockRequest = request;
        }
        final int lengthWritten = writer.write(bufferedBlockRequest.buffer, off, len);
        if (!bufferedBlockRequest.buffer.hasRemaining()) {
            sendBlockRequest(false);
            bufferedBlockRequest = null;
            handoff = null;
        }
        return lengthWritten;
    }

    @Override
    public void flush() throws IOException {
        checkStatus();
    }

    @Override
    public void done() throws IOException {
        checkStatus();
        if (state == State.DONE) {
            return;
        }
        if (state != State.OPEN) {
            throw new IOException("Cannot mark stream as done for uri " + azureUri +
                    " because stream is in state " + state + " instead of OPEN");
        }
        sendLastRequestIfPresent();
        state = State.DONE;
    }

    @Override
    public void complete() throws IOException {
        checkStatus();
        if (state == State.COMPLETED) {
            return;
        }
        done();
        commitBlockList();
        state = State.COMPLETED;
    }

    @Override
    public void rollback() throws IOException {
        checkStatus();
        if (state == State.COMPLETED || state == State.ABORTED) {
            return;
        }
        // Azure doesn't require explicit abort -- uncommitted blocks expire after 7 days
        failAll(new IOException("Upload rolled back for uri " + azureUri));
        state = State.ABORTED;
    }

    @Override
    public void close() throws IOException {
        checkStatus();
        if (state == State.COMPLETED || state == State.ABORTED) {
            return;
        }
        failAll(new IOException("Upload closed for uri " + azureUri));
        state = State.ABORTED;
    }

    // ---- helpers ----

    /**
     * Generate a block ID. Azure requires all block IDs for a blob to be the same length, so we zero-pad and
     * Base64-encode.
     */
    private static String generateBlockId(final int blockNumber) {
        return Base64.getEncoder().encodeToString(String.format("%06d", blockNumber).getBytes());
    }

    private void sendBlockRequest(final boolean onDone) throws IOException {
        if (nextBlockNumber >= MAX_BLOCK_COUNT) {
            final IOException ex = new IOException("Cannot upload more than " + MAX_BLOCK_COUNT +
                    " blocks for uri " + azureUri + ", please try again with a larger block size");
            failAll(ex);
            throw ex;
        }
        if (!Objects.requireNonNull(handoff).complete(null)) {
            throw statusError();
        }
        final AzureWriteRequest request = Objects.requireNonNull(bufferedBlockRequest);
        request.buffer.flip();
        if (onDone && !request.buffer.hasRemaining()) {
            request.releaseBuffer();
            return;
        }

        final String blockId = generateBlockId(nextBlockNumber);
        final int blockNumber = nextBlockNumber;
        final int blockSize = request.buffer.remaining();

        final CompletableFuture<Void> uploadFuture = blockBlobClient.stageBlock(blockId,
                Flux.just(request.buffer.asReadOnlyBuffer()), blockSize)
                .toFuture();

        uploadFuture.whenComplete((unused, throwable) -> request.releaseBuffer());

        uploadFuture.whenComplete((unused, throwable) -> {
            try {
                if (throwable == null) {
                    committedBlockIds.add(blockId);
                } else {
                    failAll(new IOException("Failed to upload block " + blockNumber + " for uri " + azureUri,
                            throwable));
                }
            } finally {
                numBlocksCompleted.release();
            }
        });
        forwardExceptionAsCancel(status, uploadFuture);
        nextBlockNumber++;
    }

    private static void forwardExceptionAsCancel(final CompletableFuture<?> src, final CompletableFuture<?> dst) {
        src.whenComplete((ignored, ex) -> {
            if (ex != null) {
                dst.cancel(true);
            }
        });
    }

    private void failAll(final Throwable throwable) {
        status.completeExceptionally(throwable);
    }

    private void checkStatus() throws IOException {
        if (status.isCompletedExceptionally()) {
            throw statusError();
        }
    }

    private IOException statusError() {
        try {
            status.join();
        } catch (final CompletionException | CancellationException e) {
            final Throwable cause = e.getCause();
            if (cause instanceof IOException) {
                return (IOException) cause;
            } else {
                return new IOException("Failed to upload to Azure Blob Storage, check cause for more details", cause);
            }
        }
        throw new IllegalStateException();
    }

    private void sendLastRequestIfPresent() throws IOException {
        if (bufferedBlockRequest == null) {
            return;
        }
        sendBlockRequest(true);
        bufferedBlockRequest = null;
        handoff = null;
    }

    private void commitBlockList() throws IOException {
        if (nextBlockNumber == 0) {
            // Nothing was written; create an empty blob
            blockBlobClient.commitBlockList(List.of()).block();
            status.complete(null);
            return;
        }

        final int totalBlockCount = nextBlockNumber;
        try {
            numBlocksCompleted.acquire(totalBlockCount);
        } catch (final InterruptedException e) {
            Thread.currentThread().interrupt();
            final IOException ioe = new IOException("Failed to complete the upload since interrupted while waiting " +
                    "for all blocks to finish", e);
            failAll(ioe);
            throw ioe;
        }

        checkStatus();

        // Sort block IDs to ensure they're committed in order (they encode the block number)
        committedBlockIds.sort(Comparator.naturalOrder());

        try {
            blockBlobClient.commitBlockList(committedBlockIds).block();
        } catch (final Exception e) {
            final IOException ex = new IOException(
                    String.format("Failed to commit block list for uri %s", azureUri), e);
            failAll(ex);
            throw ex;
        }

        status.complete(null);
    }
}
