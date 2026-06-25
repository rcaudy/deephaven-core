//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.identity.DefaultAzureCredentialBuilder;
import com.azure.storage.blob.BlobServiceClientBuilder;

enum DefaultAzureCredentialsImpl implements AzureSdkCredentials {
    INSTANCE;

    @Override
    public void apply(final BlobServiceClientBuilder builder, final AzureInstructions instructions) {
        builder.credential(new DefaultAzureCredentialBuilder().build());
    }
}
