//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import org.jetbrains.annotations.NotNull;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.Objects;

/**
 * Parses Azure Blob Storage URIs into their component parts.
 *
 * <p>
 * Azure URIs have the form: {@code abfss://container@account.blob.core.windows.net/path/to/blob}
 * <ul>
 * <li>Scheme: {@code abfs}, {@code abfss}, {@code wasb}, or {@code wasbs}</li>
 * <li>Container: extracted from the userInfo portion of the authority</li>
 * <li>Account name: extracted from the host, stripping the endpoint suffix</li>
 * <li>Blob path: the path component</li>
 * </ul>
 */
final class AzureUri {

    private final URI uri;
    private final String container;
    private final String accountName;
    private final String blobPath;
    private final String endpointSuffix;

    /**
     * Parse an Azure Blob Storage URI.
     *
     * @param uri the URI to parse
     * @return the parsed AzureUri
     * @throws IllegalArgumentException if the URI is not a valid Azure Blob Storage URI
     */
    static AzureUri of(@NotNull final URI uri) {
        final String scheme = uri.getScheme();
        if (scheme == null || !AzureBlobConstants.AZURE_SCHEMES.contains(scheme)) {
            throw new IllegalArgumentException("Not an Azure Blob Storage URI: " + uri);
        }

        // Container is in the userInfo portion: abfss://container@account.suffix/path
        final String container = uri.getUserInfo();
        if (container == null || container.isEmpty()) {
            throw new IllegalArgumentException("Azure URI missing container in authority (expected " +
                    "container@account.suffix): " + uri);
        }

        // Host is account.suffix, e.g., "myaccount.blob.core.windows.net"
        final String host = uri.getHost();
        if (host == null || host.isEmpty()) {
            throw new IllegalArgumentException("Azure URI missing host: " + uri);
        }

        final int dotIndex = host.indexOf('.');
        if (dotIndex <= 0) {
            throw new IllegalArgumentException("Azure URI host must be in the form 'account.suffix': " + uri);
        }

        final String accountName = host.substring(0, dotIndex);
        final String endpointSuffix = host.substring(dotIndex + 1);

        // Path may have a leading slash; normalize
        String path = uri.getPath();
        if (path != null && path.startsWith("/")) {
            path = path.substring(1);
        }
        if (path == null) {
            path = "";
        }

        return new AzureUri(uri, container, accountName, path, endpointSuffix);
    }

    private AzureUri(
            @NotNull final URI uri,
            @NotNull final String container,
            @NotNull final String accountName,
            @NotNull final String blobPath,
            @NotNull final String endpointSuffix) {
        this.uri = Objects.requireNonNull(uri);
        this.container = Objects.requireNonNull(container);
        this.accountName = Objects.requireNonNull(accountName);
        this.blobPath = Objects.requireNonNull(blobPath);
        this.endpointSuffix = Objects.requireNonNull(endpointSuffix);
    }

    /** The original URI. */
    URI uri() {
        return uri;
    }

    /** The container name. */
    String container() {
        return container;
    }

    /** The storage account name. */
    String accountName() {
        return accountName;
    }

    /** The blob path within the container (no leading slash). */
    String blobPath() {
        return blobPath;
    }

    /** The endpoint suffix (e.g., "blob.core.windows.net" or "dfs.core.windows.net"). */
    String endpointSuffix() {
        return endpointSuffix;
    }

    /**
     * Construct the Azure Blob Storage endpoint URL for this account.
     *
     * @return the endpoint, e.g., "https://myaccount.blob.core.windows.net"
     */
    String endpoint() {
        return "https://" + accountName + "." + endpointSuffix;
    }

    /**
     * Create a new URI with the same authority and a different path and scheme.
     */
    URI withPath(@NotNull final String scheme, @NotNull final String newPath) {
        try {
            return new URI(scheme, container, uri.getHost(), uri.getPort(), "/" + newPath, null, null);
        } catch (final URISyntaxException e) {
            throw new IllegalArgumentException("Failed to create URI with path: " + newPath, e);
        }
    }

    @Override
    public boolean equals(final Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        final AzureUri other = (AzureUri) o;
        return uri.equals(other.uri);
    }

    @Override
    public int hashCode() {
        return uri.hashCode();
    }

    @Override
    public String toString() {
        return uri.toString();
    }
}
