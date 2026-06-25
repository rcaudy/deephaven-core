//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobServiceClientBuilder;
import com.azure.storage.common.StorageSharedKeyCredential;

import java.util.Objects;

final class SharedKeyAzureCredentials implements AzureSdkCredentials {

    static SharedKeyAzureCredentials of(final String accountName, final String accountKey) {
        return new SharedKeyAzureCredentials(
                Objects.requireNonNull(accountName, "accountName"),
                Objects.requireNonNull(accountKey, "accountKey"));
    }

    private final String accountName;
    private final String accountKey;

    private SharedKeyAzureCredentials(final String accountName, final String accountKey) {
        this.accountName = accountName;
        this.accountKey = accountKey;
    }

    @Override
    public void apply(final BlobServiceClientBuilder builder, final AzureInstructions instructions) {
        builder.credential(new StorageSharedKeyCredential(accountName, accountKey));
    }
}
