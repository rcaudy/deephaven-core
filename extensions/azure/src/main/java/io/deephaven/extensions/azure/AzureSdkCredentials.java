//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobServiceClientBuilder;
import io.deephaven.util.annotations.InternalUseOnly;

/**
 * Internal interface for Azure credentials that know how to configure a {@link BlobServiceClientBuilder}.
 */
@InternalUseOnly
interface AzureSdkCredentials extends AzureCredentials {

    /**
     * Apply this credential to the given builder.
     *
     * @param builder the builder to configure
     * @param instructions the instructions providing any additional context (e.g., account name for endpoint
     *        resolution)
     */
    void apply(BlobServiceClientBuilder builder, AzureInstructions instructions);
}
