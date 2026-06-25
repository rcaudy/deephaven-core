//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobContainerClient;
import com.azure.storage.blob.models.BlobItem;
import com.azure.storage.blob.models.BlobStorageException;
import com.azure.storage.blob.models.ListBlobsOptions;
import io.deephaven.UncheckedDeephavenException;
import io.deephaven.base.stats.Counter;
import io.deephaven.base.stats.Stats;
import io.deephaven.base.stats.Value;
import io.deephaven.base.verify.Require;
import io.deephaven.engine.readtracker.impl.QueryPerformanceReadTracker;
import io.deephaven.hash.KeyedObjectHashMap;
import io.deephaven.hash.KeyedObjectKey;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.util.channel.Channels;
import io.deephaven.util.channel.CompletableOutputStream;
import io.deephaven.util.channel.SeekableChannelContext;
import io.deephaven.util.channel.SeekableChannelsProvider;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.io.InputStream;
import java.lang.ref.SoftReference;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.channels.SeekableByteChannel;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicReferenceFieldUpdater;
import java.util.stream.Stream;

import static io.deephaven.base.FileUtils.REPEATED_URI_SEPARATOR;
import static io.deephaven.base.FileUtils.REPEATED_URI_SEPARATOR_PATTERN;
import static io.deephaven.base.FileUtils.URI_SEPARATOR;

/**
 * {@link SeekableChannelsProvider} implementation that is used to fetch objects from Azure Blob Storage.
 */
class AzureSeekableChannelProvider implements SeekableChannelsProvider {

    private static final int UNKNOWN_SIZE = -1;

    private static final Logger log = LoggerFactory.getLogger(AzureSeekableChannelProvider.class);

    private final AzureInstructions instructions;

    /**
     * A shared cache for Azure read requests. This cache is shared across all Azure channels created by this provider.
     */
    private final AzureReadRequestCache sharedReadCache;

    @SuppressWarnings("rawtypes")
    private static final AtomicReferenceFieldUpdater<AzureSeekableChannelProvider, SoftReference> FILE_SIZE_CACHE_REF_UPDATER =
            AtomicReferenceFieldUpdater.newUpdater(AzureSeekableChannelProvider.class, SoftReference.class,
                    "fileSizeCacheRef");

    private static final Value FETCH_BLOB_SIZE_DURATION_NANOS =
            Stats.makeItem("AzureSeekableChannelProvider", "fetchBlobSize", Counter.FACTORY).getValue();

    private volatile SoftReference<Map<URI, FileSizeInfo>> fileSizeCacheRef;

    AzureSeekableChannelProvider(@NotNull final AzureInstructions instructions) {
        this.instructions = Objects.requireNonNull(instructions);
        this.sharedReadCache = new AzureReadRequestCache(instructions.fragmentSize());
        this.fileSizeCacheRef = new SoftReference<>(new KeyedObjectHashMap<>(FileSizeInfo.URI_MATCH_KEY));
    }

    @Override
    public boolean exists(@NotNull final URI uri) {
        if (getCachedSize(uri) != UNKNOWN_SIZE) {
            return true;
        }
        final AzureUri azureUri = AzureUri.of(uri);
        try {
            fetchBlobSize(azureUri);
        } catch (final BlobStorageException e) {
            if (e.getStatusCode() == 404) {
                return false;
            }
            throw new UncheckedDeephavenException("Error checking existence of blob " + uri, e);
        } catch (final IOException e) {
            throw new UncheckedDeephavenException("Error checking existence of blob " + uri, e);
        }
        return true;
    }

    @Override
    public SeekableByteChannel getReadChannel(
            @NotNull final SeekableChannelContext channelContext,
            @NotNull final URI uri) {
        final AzureUri azureUri = AzureUri.of(uri);
        // context is unused here, will be set before reading from the channel
        final long cachedSize = getCachedSize(uri);
        if (cachedSize != UNKNOWN_SIZE) {
            return new AzureSeekableByteChannel(azureUri, cachedSize);
        }
        return new AzureSeekableByteChannel(azureUri);
    }

    @Override
    public InputStream getInputStream(final SeekableByteChannel channel, final int sizeHint) {
        // AzureSeekableByteChannel is internally buffered, no need to re-buffer
        return Channels.newInputStreamNoClose(channel);
    }

    @Override
    public SeekableChannelContext makeReadContext() {
        return new AzureReadContext(this, instructions, sharedReadCache);
    }

    @Override
    public SeekableChannelContext makeSingleUseReadContext() {
        return new AzureReadContext(this, instructions.singleUse(), sharedReadCache);
    }

    @Override
    public WriteContext makeWriteContext() {
        return new AzureWriteContext(instructions);
    }

    @Override
    public boolean isCompatibleWith(@NotNull final SeekableChannelContext channelContext) {
        return channelContext instanceof AzureReadContext;
    }

    @Override
    public CompletableOutputStream getOutputStream(
            @NotNull final WriteContext channelContext,
            @NotNull final URI uri,
            final int bufferSizeHint) {
        // bufferSizeHint is unused because azure output stream is buffered internally into blocks
        final AzureUri azureUri = AzureUri.of(uri);
        return new AzureCompletableOutputStream(azureUri,
                AzureBlobClientFactory.getContainerAsyncClient(instructions, azureUri)
                        .getBlobAsyncClient(azureUri.blobPath()),
                instructions, channelContext);
    }

    @Override
    public Stream<URI> list(@NotNull final URI directory) {
        if (log.isDebugEnabled()) {
            log.debug().append("Fetching child URIs for directory: ").append(directory.toString()).endl();
        }
        return createStream(AzureBlobConstants.ABFSS_URI_SCHEME, directory, false);
    }

    @Override
    public Stream<URI> walk(@NotNull final URI directory) {
        if (log.isDebugEnabled()) {
            log.debug().append("Performing recursive traversal from directory: ").append(directory.toString()).endl();
        }
        return createStream(AzureBlobConstants.ABFSS_URI_SCHEME, directory, true);
    }

    /**
     * Create a stream of URIs, the elements of which are the blob entries in the directory.
     *
     * @param resultScheme The scheme to use for URI results
     * @param directory The parent directory to list.
     * @param isRecursive Whether to list the entries recursively.
     */
    Stream<URI> createStream(
            @NotNull final String resultScheme,
            @NotNull final URI directory,
            final boolean isRecursive) {
        final AzureUri azureUri = AzureUri.of(directory);
        final BlobContainerClient containerClient =
                AzureBlobClientFactory.getContainerClient(instructions, azureUri);
        final String prefix = azureUri.blobPath();

        final Stream<BlobItem> blobStream;
        if (isRecursive) {
            blobStream = containerClient.listBlobs(new ListBlobsOptions().setPrefix(prefix), null).stream();
        } else {
            blobStream = containerClient
                    .listBlobsByHierarchy("/", new ListBlobsOptions().setPrefix(prefix), null)
                    .stream()
                    .filter(item -> !Boolean.TRUE.equals(item.isPrefix()));
        }

        return blobStream
                .filter(item -> !item.getName().equals(prefix))
                .map(item -> {
                    String path = "/" + item.getName();
                    if (path.contains(REPEATED_URI_SEPARATOR)) {
                        path = REPEATED_URI_SEPARATOR_PATTERN.matcher(path).replaceAll(URI_SEPARATOR);
                    }
                    final URI resultUri;
                    try {
                        resultUri = new URI(resultScheme, directory.getUserInfo(), directory.getHost(),
                                directory.getPort(), path, null, null);
                    } catch (final URISyntaxException e) {
                        throw new UncheckedDeephavenException(
                                "Failed to create URI for Azure blob: " + item.getName(), e);
                    }
                    if (item.getProperties() != null && item.getProperties().getContentLength() != null) {
                        updateFileSizeCache(resultUri, item.getProperties().getContentLength());
                    }
                    return resultUri;
                });
    }

    /**
     * Fetch the size of the blob at the given Azure URI.
     *
     * @throws BlobStorageException if the blob does not exist (status 404) or other Azure errors
     * @throws IOException if there is an error fetching the blob size
     */
    long fetchBlobSize(@NotNull final AzureUri azureUri) throws IOException {
        final long cachedSize = getCachedSize(azureUri.uri());
        if (cachedSize != UNKNOWN_SIZE) {
            return cachedSize;
        }
        if (log.isDebugEnabled()) {
            log.debug().append("GetProperties: ").append(azureUri.toString()).endl();
        }
        final long start = System.nanoTime();
        try {
            final long size = AzureBlobClientFactory.getContainerClient(instructions, azureUri)
                    .getBlobClient(azureUri.blobPath())
                    .getProperties()
                    .getBlobSize();
            updateFileSizeCache(azureUri.uri(), size);
            return size;
        } catch (final BlobStorageException e) {
            throw e;
        } catch (final Exception e) {
            throw new IOException("Failed to fetch blob properties for " + azureUri, e);
        } finally {
            final long duration = System.nanoTime() - start;
            QueryPerformanceReadTracker.recordMetadataOperation(duration);
            FETCH_BLOB_SIZE_DURATION_NANOS.sample(duration);
        }
    }

    // ---- file size cache ----

    /**
     * Get a strong reference to the file size cache, creating it if necessary.
     */
    private Map<URI, FileSizeInfo> getFileSizeCache() {
        SoftReference<Map<URI, FileSizeInfo>> cacheRef;
        Map<URI, FileSizeInfo> cache;
        while ((cache = (cacheRef = fileSizeCacheRef).get()) == null) {
            if (FILE_SIZE_CACHE_REF_UPDATER.compareAndSet(this, cacheRef,
                    new SoftReference<>(cache = new KeyedObjectHashMap<>(FileSizeInfo.URI_MATCH_KEY)))) {
                return cache;
            }
        }
        return cache;
    }

    /**
     * Get the cached size for the given URI, or {@value UNKNOWN_SIZE} if the size is not cached.
     */
    private long getCachedSize(final URI uri) {
        final Map<URI, FileSizeInfo> fileSizeCache = fileSizeCacheRef.get();
        if (fileSizeCache != null) {
            final FileSizeInfo sizeInfo = fileSizeCache.get(uri);
            if (sizeInfo != null) {
                return sizeInfo.size;
            }
        }
        return UNKNOWN_SIZE;
    }

    /**
     * Cache the file size for the given URI.
     */
    private void updateFileSizeCache(@NotNull final URI uri, final long size) {
        if (size < 0) {
            throw new IllegalArgumentException("Invalid blob size: " + size + " for URI " + uri);
        }
        final Map<URI, FileSizeInfo> fileSizeCache = getFileSizeCache();
        fileSizeCache.compute(uri, (key, existingInfo) -> {
            if (existingInfo == null) {
                return new FileSizeInfo(uri, size);
            } else if (existingInfo.size != size) {
                throw new IllegalStateException("Existing size " + existingInfo.size + " does not match "
                        + " the new size " + size + " for key " + key);
            }
            return existingInfo;
        });
    }

    private static final class FileSizeInfo {
        private final URI uri;
        private final long size;

        FileSizeInfo(@NotNull final URI uri, final long size) {
            this.uri = Require.neqNull(uri, "uri");
            this.size = size;
        }

        private static final KeyedObjectKey<URI, FileSizeInfo> URI_MATCH_KEY = new KeyedObjectKey.Basic<>() {
            @Override
            public URI getKey(@NotNull final FileSizeInfo value) {
                return value.uri;
            }
        };
    }

    @Override
    public void close() {
        sharedReadCache.clear();
    }
}
