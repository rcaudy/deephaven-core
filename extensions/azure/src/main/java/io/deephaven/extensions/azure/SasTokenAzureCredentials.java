//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobServiceClientBuilder;

import java.util.Objects;

final class SasTokenAzureCredentials implements AzureSdkCredentials {

    static SasTokenAzureCredentials of(final String sasToken) {
        return new SasTokenAzureCredentials(Objects.requireNonNull(sasToken, "sasToken"));
    }

    private final String sasToken;

    private SasTokenAzureCredentials(final String sasToken) {
        this.sasToken = sasToken;
    }

    @Override
    public void apply(final BlobServiceClientBuilder builder, final AzureInstructions instructions) {
        builder.sasToken(sasToken);
    }
}
