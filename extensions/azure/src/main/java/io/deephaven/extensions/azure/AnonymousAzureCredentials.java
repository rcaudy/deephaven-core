//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobServiceClientBuilder;

enum AnonymousAzureCredentials implements AzureSdkCredentials {
    INSTANCE;

    @Override
    public void apply(final BlobServiceClientBuilder builder, final AzureInstructions instructions) {
        // No credentials configured; anonymous access
    }
}
