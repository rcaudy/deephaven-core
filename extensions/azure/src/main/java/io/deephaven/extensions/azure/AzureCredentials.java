//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

/**
 * Credentials to use when reading from or writing to Azure Blob Storage.
 */
public interface AzureCredentials {

    /**
     * Default credentials provider that uses Azure's {@link com.azure.identity.DefaultAzureCredential}, which tries
     * multiple credential types in order (environment, managed identity, Azure CLI, etc.).
     */
    static AzureCredentials defaultCredentials() {
        return DefaultAzureCredentialsImpl.INSTANCE;
    }

    /**
     * Shared key credentials using a storage account name and account key.
     *
     * @param accountName the storage account name
     * @param accountKey the storage account access key
     */
    static AzureCredentials sharedKey(final String accountName, final String accountKey) {
        return SharedKeyAzureCredentials.of(accountName, accountKey);
    }

    /**
     * SAS token credentials for scoped, time-limited access.
     *
     * @param sasToken the SAS token string
     */
    static AzureCredentials sasToken(final String sasToken) {
        return SasTokenAzureCredentials.of(sasToken);
    }

    /**
     * Connection string credentials. The connection string typically contains the account name, account key, and
     * endpoint information.
     *
     * @param connectionString the Azure Storage connection string
     */
    static AzureCredentials connectionString(final String connectionString) {
        return ConnectionStringAzureCredentials.of(connectionString);
    }

    /**
     * Anonymous credentials for public (anonymous) access. This is useful when the container has been configured to
     * allow anonymous read access.
     */
    static AzureCredentials anonymous() {
        return AnonymousAzureCredentials.INSTANCE;
    }
}
