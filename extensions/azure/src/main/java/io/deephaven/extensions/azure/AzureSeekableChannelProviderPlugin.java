//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.google.auto.service.AutoService;
import io.deephaven.util.channel.SeekableChannelsProvider;
import io.deephaven.util.channel.SeekableChannelsProviderPlugin;
import io.deephaven.util.channel.SeekableChannelsProviderPluginBase;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Set;

/**
 * {@link SeekableChannelsProviderPlugin} implementation used for reading from and writing to URIs with Azure Blob
 * Storage schemes: {@value AzureBlobConstants#ABFS_URI_SCHEME}, {@value AzureBlobConstants#ABFSS_URI_SCHEME},
 * {@value AzureBlobConstants#WASB_URI_SCHEME}, or {@value AzureBlobConstants#WASBS_URI_SCHEME}.
 */
@AutoService(SeekableChannelsProviderPlugin.class)
public final class AzureSeekableChannelProviderPlugin extends SeekableChannelsProviderPluginBase {

    @Override
    public boolean isCompatible(@NotNull final String uriScheme, @Nullable final Object config) {
        return AzureBlobConstants.AZURE_SCHEMES.contains(uriScheme);
    }

    @Override
    protected SeekableChannelsProvider createProviderImpl(
            @NotNull final String uriScheme,
            @Nullable final Object config) {
        final AzureSeekableChannelProvider impl = new AzureSeekableChannelProvider(normalizeInstructions(config));
        switch (uriScheme) {
            case AzureBlobConstants.ABFSS_URI_SCHEME:
                return impl;
            case AzureBlobConstants.ABFS_URI_SCHEME:
                return new AzureDelegateProvider(AzureBlobConstants.ABFS_URI_SCHEME, impl);
            case AzureBlobConstants.WASB_URI_SCHEME:
                return new AzureDelegateProvider(AzureBlobConstants.WASB_URI_SCHEME, impl);
            case AzureBlobConstants.WASBS_URI_SCHEME:
                return new AzureDelegateProvider(AzureBlobConstants.WASBS_URI_SCHEME, impl);
            default:
                throw new IllegalStateException("Unexpected uriScheme: " + uriScheme);
        }
    }

    @Override
    protected SeekableChannelsProvider createProviderImpl(
            @NotNull final Set<String> uriSchemes,
            @Nullable final Object config) {
        return createUniversalAzureProvider(uriSchemes, config);
    }

    static SeekableChannelsProvider createUniversalAzureProvider(
            @NotNull final Set<String> uriSchemes,
            @Nullable final Object config) {
        final AzureSeekableChannelProvider impl = new AzureSeekableChannelProvider(normalizeInstructions(config));
        return createUniversalAzureProviderHelper(uriSchemes, impl);
    }

    private static SeekableChannelsProvider createUniversalAzureProviderHelper(
            @NotNull final Set<String> uriSchemes,
            @NotNull final AzureSeekableChannelProvider impl) {
        final AzureSeekableChannelProvider abfss = uriSchemes.contains(AzureBlobConstants.ABFSS_URI_SCHEME)
                ? impl
                : null;
        final AzureDelegateProvider abfs = uriSchemes.contains(AzureBlobConstants.ABFS_URI_SCHEME)
                ? new AzureDelegateProvider(AzureBlobConstants.ABFS_URI_SCHEME, impl)
                : null;
        final AzureDelegateProvider wasb = uriSchemes.contains(AzureBlobConstants.WASB_URI_SCHEME)
                ? new AzureDelegateProvider(AzureBlobConstants.WASB_URI_SCHEME, impl)
                : null;
        final AzureDelegateProvider wasbs = uriSchemes.contains(AzureBlobConstants.WASBS_URI_SCHEME)
                ? new AzureDelegateProvider(AzureBlobConstants.WASBS_URI_SCHEME, impl)
                : null;
        return new UniversalAzureProvider(impl, abfss, abfs, wasb, wasbs);
    }

    /**
     * Get the AzureInstructions from the config object, or use the default if the config is null.
     */
    private static AzureInstructions normalizeInstructions(@Nullable final Object config) {
        if (config != null && !(config instanceof AzureInstructions)) {
            throw new IllegalArgumentException(
                    "Only AzureInstructions are valid when reading files from Azure, provided " +
                            "config instance of class " + config.getClass().getName());
        }
        return config == null ? AzureInstructions.DEFAULT : (AzureInstructions) config;
    }
}
