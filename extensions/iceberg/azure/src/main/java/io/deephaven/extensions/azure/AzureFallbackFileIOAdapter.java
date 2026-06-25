//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.google.auto.service.AutoService;
import io.deephaven.iceberg.util.FileIOAdapter;
import io.deephaven.iceberg.util.FileIOAdapterBase;
import io.deephaven.util.channel.SeekableChannelsProvider;
import org.apache.iceberg.io.FileIO;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import static io.deephaven.extensions.azure.AzureBlobConstants.AZURE_SCHEMES;

/**
 * {@link FileIOAdapter} implementation used for reading/writing files to Azure Blob Storage. This adapter creates its
 * own Azure client rather than reusing any client from the FileIO.
 */
@AutoService(FileIOAdapter.class)
public final class AzureFallbackFileIOAdapter extends FileIOAdapterBase {

    @Override
    public boolean isCompatible(
            @NotNull final String uriScheme,
            @NotNull final FileIO io) {
        return isCompatible(uriScheme, io.getClass());
    }

    @Override
    public boolean isCompatible(
            @NotNull final String uriScheme,
            @NotNull final Class<?> ioClass) {
        return AZURE_SCHEMES.contains(uriScheme);
    }

    @Override
    protected SeekableChannelsProvider createProviderImpl(
            @NotNull final String uriScheme,
            @NotNull final FileIO io,
            @Nullable final Object specialInstructions) {
        if (!isCompatible(uriScheme, io)) {
            throw new IllegalArgumentException("Arguments not compatible, provided uri scheme " + uriScheme +
                    ", io " + io.getClass().getName() + ", special instructions " + specialInstructions);
        }
        // Create a universal provider which can read/write to all Azure URIs (abfss, abfs, wasb, wasbs), so if
        // different data files have different Azure URI schemes, we can still read/write them using the same provider.
        return AzureSeekableChannelProviderPlugin.createUniversalAzureProvider(AZURE_SCHEMES, specialInstructions);
    }
}
