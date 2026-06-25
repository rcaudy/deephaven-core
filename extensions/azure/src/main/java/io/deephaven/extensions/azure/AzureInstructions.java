//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.annotations.CopyableStyle;
import io.deephaven.base.log.LogOutput;
import io.deephaven.base.log.LogOutputAppendable;
import org.immutables.value.Value.Check;
import org.immutables.value.Value.Default;
import org.immutables.value.Value.Immutable;
import org.immutables.value.Value.Lazy;

import java.net.URI;
import java.time.Duration;
import java.util.Optional;

/**
 * This class provides instructions intended for reading from and writing to Azure Blob Storage. The default values
 * documented in this class may change in the future. As such, callers may wish to explicitly set the values.
 */
@Immutable
@CopyableStyle
public abstract class AzureInstructions implements LogOutputAppendable {

    private static final int DEFAULT_MAX_CONCURRENT_REQUESTS = 256;
    private static final int DEFAULT_READ_AHEAD_COUNT = 32;
    private static final int DEFAULT_FRAGMENT_SIZE = 1 << 16; // 64 KiB
    private static final int MIN_FRAGMENT_SIZE = 8 << 10; // 8 KiB
    private static final Duration DEFAULT_CONNECTION_TIMEOUT = Duration.ofSeconds(2);
    static final Duration DEFAULT_READ_TIMEOUT = Duration.ofSeconds(2);
    static final Duration DEFAULT_WRITE_TIMEOUT = Duration.ofSeconds(2);
    private static final int DEFAULT_NUM_CONCURRENT_WRITE_BLOCKS = 64;
    private static final int MIN_CONCURRENT_WRITE_BLOCKS = 1;
    private static final Duration MIN_READ_WRITE_TIMEOUT = Duration.ofMillis(1);

    /**
     * Azure block blobs have a maximum of 50,000 blocks. With 10 MiB blocks, the maximum file size is ~488 GiB.
     */
    private static final int DEFAULT_WRITE_BLOCK_SIZE = 10 << 20; // 10 MiB

    /**
     * Azure allows blocks as small as 1 byte, but we enforce a minimum for efficiency.
     */
    static final int MIN_WRITE_BLOCK_SIZE = 1 << 10; // 1 KiB

    static final AzureInstructions DEFAULT = builder().build();

    public static Builder builder() {
        return ImmutableAzureInstructions.builder();
    }

    /**
     * The storage account name. If not provided, it will be inferred from the URI authority (e.g.,
     * {@code account} from {@code abfss://container@account.blob.core.windows.net/path}).
     */
    public abstract Optional<String> accountName();

    /**
     * The endpoint suffix to use when constructing the Azure Blob Storage endpoint. Defaults to
     * {@value AzureBlobConstants#DEFAULT_ENDPOINT_SUFFIX}. Override for sovereign clouds (e.g.,
     * {@code "blob.core.chinacloudapi.cn"}) or local emulators.
     */
    @Default
    public String endpointSuffix() {
        return AzureBlobConstants.DEFAULT_ENDPOINT_SUFFIX;
    }

    /**
     * The endpoint to connect to. Callers connecting to standard Azure Blob Storage do not typically need to set this;
     * it is most useful when connecting to a local emulator such as Azurite.
     */
    public abstract Optional<URI> endpointOverride();

    /**
     * The maximum number of concurrent requests to make to Azure Blob Storage, defaults to
     * {@value #DEFAULT_MAX_CONCURRENT_REQUESTS}.
     */
    @Default
    public int maxConcurrentRequests() {
        return DEFAULT_MAX_CONCURRENT_REQUESTS;
    }

    /**
     * The number of fragments to send asynchronous read requests for while reading the current fragment. Defaults to
     * {@value #DEFAULT_READ_AHEAD_COUNT}.
     */
    @Default
    public int readAheadCount() {
        return DEFAULT_READ_AHEAD_COUNT;
    }

    /**
     * The maximum byte size of each fragment to read from Azure Blob Storage in bytes, defaults to
     * {@value DEFAULT_FRAGMENT_SIZE}, must be larger than {@value MIN_FRAGMENT_SIZE}.
     */
    @Default
    public int fragmentSize() {
        return DEFAULT_FRAGMENT_SIZE;
    }

    /**
     * The amount of time to wait when initially establishing a connection before giving up and timing out, defaults to
     * 2 seconds.
     */
    @Default
    public Duration connectionTimeout() {
        return DEFAULT_CONNECTION_TIMEOUT;
    }

    /**
     * The amount of time to wait when reading a fragment before giving up and timing out, defaults to 2 seconds.
     */
    @Default
    public Duration readTimeout() {
        return DEFAULT_READ_TIMEOUT;
    }

    /**
     * The amount of time to wait when writing a block before giving up and timing out, defaults to 2 seconds.
     */
    @Default
    public Duration writeTimeout() {
        return DEFAULT_WRITE_TIMEOUT;
    }

    /**
     * The credentials to use when reading or writing to Azure Blob Storage. By default, uses
     * {@link AzureCredentials#defaultCredentials()}.
     */
    @Default
    public AzureCredentials credentials() {
        return AzureCredentials.defaultCredentials();
    }

    /**
     * The size of each block (in bytes) to upload when writing to Azure Blob Storage, defaults to
     * {@value #DEFAULT_WRITE_BLOCK_SIZE}. The minimum allowed block size is {@value #MIN_WRITE_BLOCK_SIZE}. Setting a
     * higher value may increase throughput, but may also increase memory usage. Note that the maximum number of blocks
     * allowed for a single blob is 50,000.
     */
    @Default
    public int writeBlockSize() {
        return DEFAULT_WRITE_BLOCK_SIZE;
    }

    /**
     * The maximum number of blocks that can be uploaded concurrently when writing to Azure Blob Storage without
     * blocking. Setting a higher value may increase throughput, but may also increase memory usage. Defaults to
     * {@value #DEFAULT_NUM_CONCURRENT_WRITE_BLOCKS}.
     */
    @Default
    public int numConcurrentWriteBlocks() {
        return DEFAULT_NUM_CONCURRENT_WRITE_BLOCKS;
    }

    @Override
    public LogOutput append(final LogOutput logOutput) {
        return logOutput.append(toString());
    }

    public abstract AzureInstructions withEndpointOverride(final URI endpointOverride);

    abstract AzureInstructions withReadAheadCount(int readAheadCount);

    @Lazy
    AzureInstructions singleUse() {
        final int readAheadCount = Math.min(DEFAULT_READ_AHEAD_COUNT, readAheadCount());
        return withReadAheadCount(readAheadCount);
    }

    public interface Builder {
        Builder accountName(String accountName);

        Builder endpointSuffix(String endpointSuffix);

        Builder endpointOverride(URI endpointOverride);

        Builder maxConcurrentRequests(int maxConcurrentRequests);

        Builder readAheadCount(int readAheadCount);

        Builder fragmentSize(int fragmentSize);

        Builder connectionTimeout(Duration connectionTimeout);

        Builder readTimeout(Duration readTimeout);

        Builder writeTimeout(Duration writeTimeout);

        Builder credentials(AzureCredentials credentials);

        Builder writeBlockSize(int writeBlockSize);

        Builder numConcurrentWriteBlocks(int numConcurrentWriteBlocks);

        default Builder endpointOverride(final String endpointOverride) {
            return endpointOverride(URI.create(endpointOverride));
        }

        AzureInstructions build();
    }

    @Check
    final void boundsCheckMaxConcurrentRequests() {
        if (maxConcurrentRequests() < 1) {
            throw new IllegalArgumentException("maxConcurrentRequests(=" + maxConcurrentRequests() + ") must be >= 1");
        }
    }

    @Check
    final void boundsCheckReadAheadCount() {
        if (readAheadCount() < 0) {
            throw new IllegalArgumentException("readAheadCount(=" + readAheadCount() + ") must be >= 0");
        }
    }

    @Check
    final void boundsCheckMinFragmentSize() {
        if (fragmentSize() < MIN_FRAGMENT_SIZE) {
            throw new IllegalArgumentException("fragmentSize(=" + fragmentSize() + ") must be >= " + MIN_FRAGMENT_SIZE +
                    " bytes");
        }
    }

    @Check
    final void azureSdkCredentials() {
        if (!(credentials() instanceof AzureSdkCredentials)) {
            throw new IllegalArgumentException(
                    "credentials() must be created via provided io.deephaven.extensions.azure.AzureCredentials methods");
        }
    }

    @Check
    final void boundsCheckWriteBlockSize() {
        if (writeBlockSize() < MIN_WRITE_BLOCK_SIZE) {
            throw new IllegalArgumentException(
                    "writeBlockSize(=" + writeBlockSize() + ") must be >= " + MIN_WRITE_BLOCK_SIZE);
        }
    }

    @Check
    final void boundsCheckMinNumConcurrentWriteBlocks() {
        if (numConcurrentWriteBlocks() < MIN_CONCURRENT_WRITE_BLOCKS) {
            throw new IllegalArgumentException(
                    "numConcurrentWriteBlocks(=" + numConcurrentWriteBlocks() + ") must be >= " +
                            MIN_CONCURRENT_WRITE_BLOCKS);
        }
    }

    @Check
    final void boundsCheckReadTimeout() {
        if (MIN_READ_WRITE_TIMEOUT.compareTo(readTimeout()) > 0) {
            throw new IllegalArgumentException(
                    "readTimeout(=" + readTimeout() + ") must be >= " + MIN_READ_WRITE_TIMEOUT);
        }
    }

    @Check
    final void boundsCheckWriteTimeout() {
        if (MIN_READ_WRITE_TIMEOUT.compareTo(writeTimeout()) > 0) {
            throw new IllegalArgumentException(
                    "writeTimeout(=" + writeTimeout() + ") must be >= " + MIN_READ_WRITE_TIMEOUT);
        }
    }

    @Check
    final void boundsCheckMaxNumConcurrentWriteBlocks() {
        if (numConcurrentWriteBlocks() > maxConcurrentRequests()) {
            throw new IllegalArgumentException(
                    "numConcurrentWriteBlocks(=" + numConcurrentWriteBlocks() + ") must be <= " +
                            "maxConcurrentRequests(=" + maxConcurrentRequests() + ")");
        }
    }
}
