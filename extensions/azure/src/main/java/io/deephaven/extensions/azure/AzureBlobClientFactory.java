//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobContainerAsyncClient;
import com.azure.storage.blob.BlobContainerClient;
import com.azure.storage.blob.BlobServiceAsyncClient;
import com.azure.storage.blob.BlobServiceClient;
import com.azure.storage.blob.BlobServiceClientBuilder;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import org.jetbrains.annotations.NotNull;

import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

final class AzureBlobClientFactory {

    private static final Logger log = LoggerFactory.getLogger(AzureBlobClientFactory.class);

    /**
     * Cache of async clients keyed by endpoint + credential identity. We cache at the BlobServiceAsyncClient level
     * because the endpoint encodes the account, and credentials are typically stable per account.
     */
    private static final Map<ClientCacheKey, BlobServiceAsyncClient> asyncClientCache = new ConcurrentHashMap<>();
    private static final Map<ClientCacheKey, BlobServiceClient> syncClientCache = new ConcurrentHashMap<>();

    static BlobServiceAsyncClient getAsyncClient(@NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        final ClientCacheKey key = ClientCacheKey.of(instructions, azureUri);
        return asyncClientCache.computeIfAbsent(key, k -> buildAsyncClient(instructions, azureUri));
    }

    static BlobServiceClient getSyncClient(@NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        final ClientCacheKey key = ClientCacheKey.of(instructions, azureUri);
        return syncClientCache.computeIfAbsent(key, k -> buildSyncClient(instructions, azureUri));
    }

    static BlobContainerAsyncClient getContainerAsyncClient(@NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        return getAsyncClient(instructions, azureUri).getBlobContainerAsyncClient(azureUri.container());
    }

    static BlobContainerClient getContainerClient(@NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        return getSyncClient(instructions, azureUri).getBlobContainerClient(azureUri.container());
    }

    private static BlobServiceAsyncClient buildAsyncClient(
            @NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        if (log.isDebugEnabled()) {
            log.debug().append("Building async Azure client for account: ")
                    .append(azureUri.accountName()).endl();
        }
        return configureBuilder(new BlobServiceClientBuilder(), instructions, azureUri).buildAsyncClient();
    }

    private static BlobServiceClient buildSyncClient(
            @NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        if (log.isDebugEnabled()) {
            log.debug().append("Building sync Azure client for account: ")
                    .append(azureUri.accountName()).endl();
        }
        return configureBuilder(new BlobServiceClientBuilder(), instructions, azureUri).buildClient();
    }

    private static BlobServiceClientBuilder configureBuilder(
            @NotNull final BlobServiceClientBuilder builder,
            @NotNull final AzureInstructions instructions,
            @NotNull final AzureUri azureUri) {
        // Set the endpoint
        if (instructions.endpointOverride().isPresent()) {
            builder.endpoint(instructions.endpointOverride().get().toString());
        } else {
            builder.endpoint(azureUri.endpoint());
        }

        // Apply credentials
        ((AzureSdkCredentials) instructions.credentials()).apply(builder, instructions);

        return builder;
    }

    private static final class ClientCacheKey {
        private final String endpoint;
        private final int credentialIdentityHash;

        static ClientCacheKey of(final AzureInstructions instructions, final AzureUri azureUri) {
            final String endpoint = instructions.endpointOverride()
                    .map(Object::toString)
                    .orElse(azureUri.endpoint());
            return new ClientCacheKey(endpoint, System.identityHashCode(instructions.credentials()));
        }

        private ClientCacheKey(final String endpoint, final int credentialIdentityHash) {
            this.endpoint = endpoint;
            this.credentialIdentityHash = credentialIdentityHash;
        }

        @Override
        public boolean equals(final Object o) {
            if (this == o)
                return true;
            if (o == null || getClass() != o.getClass())
                return false;
            final ClientCacheKey that = (ClientCacheKey) o;
            return credentialIdentityHash == that.credentialIdentityHash
                    && Objects.equals(endpoint, that.endpoint);
        }

        @Override
        public int hashCode() {
            return 31 * endpoint.hashCode() + credentialIdentityHash;
        }
    }
}
