//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobServiceClientBuilder;

import java.util.Objects;

final class ConnectionStringAzureCredentials implements AzureSdkCredentials {

    static ConnectionStringAzureCredentials of(final String connectionString) {
        return new ConnectionStringAzureCredentials(
                Objects.requireNonNull(connectionString, "connectionString"));
    }

    private final String connectionString;

    private ConnectionStringAzureCredentials(final String connectionString) {
        this.connectionString = connectionString;
    }

    @Override
    public void apply(final BlobServiceClientBuilder builder, final AzureInstructions instructions) {
        builder.connectionString(connectionString);
    }
}
