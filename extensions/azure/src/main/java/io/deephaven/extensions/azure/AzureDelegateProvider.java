//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.util.channel.CompletableOutputStream;
import io.deephaven.util.channel.SeekableChannelContext;
import io.deephaven.util.channel.SeekableChannelsProviderDelegate;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.channels.SeekableByteChannel;
import java.util.Objects;
import java.util.stream.Stream;

import static io.deephaven.extensions.azure.AzureBlobConstants.ABFSS_URI_SCHEME;

/**
 * Delegate provider that translates non-canonical Azure URI schemes (abfs, wasb, wasbs) to the canonical abfss scheme
 * before delegating to the underlying {@link AzureSeekableChannelProvider}.
 */
final class AzureDelegateProvider extends SeekableChannelsProviderDelegate {
    private final String scheme;

    AzureDelegateProvider(final String scheme, final AzureSeekableChannelProvider delegate) {
        super(delegate);
        if (ABFSS_URI_SCHEME.equals(scheme)) {
            throw new IllegalArgumentException(
                    String.format("Should not be delegating, use %s directly", AzureSeekableChannelProvider.class));
        }
        this.scheme = Objects.requireNonNull(scheme);
    }

    @Override
    public boolean exists(@NotNull final URI uri) {
        return delegate.exists(toAbfssUri(uri));
    }

    @Override
    public SeekableByteChannel getReadChannel(@NotNull final SeekableChannelContext channelContext,
            @NotNull final URI uri)
            throws IOException {
        return delegate.getReadChannel(channelContext, toAbfssUri(uri));
    }

    @Override
    public CompletableOutputStream getOutputStream(
            @NotNull final WriteContext channelContext,
            @NotNull final URI uri,
            final int bufferSizeHint) throws IOException {
        return delegate.getOutputStream(channelContext, toAbfssUri(uri), bufferSizeHint);
    }

    @Override
    public Stream<URI> list(@NotNull final URI directory) {
        return ((AzureSeekableChannelProvider) delegate).createStream(scheme, toAbfssUri(directory), false);
    }

    @Override
    public Stream<URI> walk(@NotNull final URI directory) {
        return ((AzureSeekableChannelProvider) delegate).createStream(scheme, toAbfssUri(directory), true);
    }

    @Override
    public String toString() {
        return "AzureDelegateProvider{" +
                "scheme='" + scheme + '\'' +
                ", delegate=" + delegate +
                '}';
    }

    private URI toAbfssUri(@NotNull final URI uri) {
        if (!scheme.equals(uri.getScheme())) {
            throw new IllegalArgumentException(
                    String.format("Expected uri scheme `%s`, got `%s`", scheme, uri.getScheme()));
        }
        try {
            return new URI(ABFSS_URI_SCHEME, uri.getUserInfo(), uri.getHost(), uri.getPort(), uri.getPath(),
                    uri.getQuery(), uri.getFragment());
        } catch (final URISyntaxException e) {
            throw new IllegalArgumentException("Failed to convert URI " + uri + " to abfss URI", e);
        }
    }
}
