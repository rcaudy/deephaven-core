//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.util.channel.CompletableOutputStream;
import io.deephaven.util.channel.SeekableChannelContext;
import io.deephaven.util.channel.SeekableChannelsProvider;
import io.deephaven.util.channel.SeekableChannelsProviderDelegate;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.net.URI;
import java.nio.channels.SeekableByteChannel;
import java.util.Objects;
import java.util.stream.Stream;

import static io.deephaven.base.FileUtils.convertToURI;
import static io.deephaven.extensions.azure.AzureBlobConstants.ABFSS_URI_SCHEME;
import static io.deephaven.extensions.azure.AzureBlobConstants.ABFS_URI_SCHEME;
import static io.deephaven.extensions.azure.AzureBlobConstants.WASBS_URI_SCHEME;
import static io.deephaven.extensions.azure.AzureBlobConstants.WASB_URI_SCHEME;

/**
 * Multi-scheme dispatcher that routes Azure URI operations to the appropriate scheme-specific provider.
 */
@SuppressWarnings("resource")
final class UniversalAzureProvider extends SeekableChannelsProviderDelegate {

    private final SeekableChannelsProvider abfss;
    private final SeekableChannelsProvider abfs;
    private final SeekableChannelsProvider wasb;
    private final SeekableChannelsProvider wasbs;

    UniversalAzureProvider(
            final AzureSeekableChannelProvider delegate,
            final SeekableChannelsProvider abfss,
            final AzureDelegateProvider abfs,
            final AzureDelegateProvider wasb,
            final AzureDelegateProvider wasbs) {
        super(Objects.requireNonNull(delegate));
        this.abfss = abfss;
        this.abfs = abfs;
        this.wasb = wasb;
        this.wasbs = wasbs;
    }

    private SeekableChannelsProvider of(final String scheme) {
        switch (scheme) {
            case ABFSS_URI_SCHEME:
                if (abfss == null) {
                    break;
                }
                return abfss;
            case ABFS_URI_SCHEME:
                if (abfs == null) {
                    break;
                }
                return abfs;
            case WASB_URI_SCHEME:
                if (wasb == null) {
                    break;
                }
                return wasb;
            case WASBS_URI_SCHEME:
                if (wasbs == null) {
                    break;
                }
                return wasbs;
        }
        throw new IllegalArgumentException("Unexpected scheme: " + scheme);
    }

    @Override
    public boolean exists(@NotNull final URI uri) {
        return of(uri.getScheme()).exists(uri);
    }

    @Override
    public SeekableByteChannel getReadChannel(@NotNull final SeekableChannelContext channelContext,
            @NotNull final URI uri)
            throws IOException {
        return of(uri.getScheme()).getReadChannel(channelContext, uri);
    }

    @Override
    public CompletableOutputStream getOutputStream(
            @NotNull final WriteContext channelContext,
            @NotNull final URI uri,
            final int bufferSizeHint) throws IOException {
        return of(uri.getScheme()).getOutputStream(channelContext, uri, bufferSizeHint);
    }

    @Override
    public Stream<URI> list(@NotNull final URI directory) throws IOException {
        return of(directory.getScheme()).list(directory);
    }

    @Override
    public Stream<URI> walk(@NotNull final URI directory) throws IOException {
        return of(directory.getScheme()).walk(directory);
    }

    @Override
    public SeekableByteChannel getReadChannel(@NotNull final SeekableChannelContext channelContext,
            @NotNull final String uriStr)
            throws IOException {
        final URI uri = convertToURI(uriStr, false);
        // Note: delegating to the URI version instead of the uriStr version
        return of(uri.getScheme()).getReadChannel(channelContext, uri);
    }

    @Override
    public String toString() {
        return "UniversalAzureProvider{" +
                "delegate=" + delegate +
                ",abfss=" + (abfss != null) +
                ",abfs=" + (abfs != null) +
                ",wasb=" + (wasb != null) +
                ",wasbs=" + (wasbs != null) +
                '}';
    }
}
