//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import com.google.auto.service.AutoService;
import io.deephaven.extensions.azure.AzureBlobConstants;
import io.deephaven.extensions.azure.AzureCredentials;
import io.deephaven.extensions.azure.AzureInstructions;
import io.deephaven.iceberg.internal.DataInstructionsProviderPlugin;
import org.jetbrains.annotations.NotNull;

import java.util.Map;

/**
 * {@link DataInstructionsProviderPlugin} implementation for producing {@link AzureInstructions}. The produced
 * instructions are created by mapping Iceberg Azure catalog properties to their Deephaven equivalents.
 */
@AutoService(DataInstructionsProviderPlugin.class)
@SuppressWarnings("unused")
public final class AzureInstructionsProviderPlugin implements DataInstructionsProviderPlugin {

    /**
     * Iceberg Azure property key prefixes and keys. These are duplicated from iceberg-azure's AzureProperties to avoid
     * hard compile-time coupling on specific field names.
     */
    private static final String ADLS_CONNECTION_STRING_PREFIX = "adls.connection-string.";
    private static final String ADLS_SAS_TOKEN_PREFIX = "adls.sas-token.";
    private static final String ADLS_SHARED_KEY_ACCOUNT_NAME = "adls.auth.shared-key.account.name";
    private static final String ADLS_SHARED_KEY_ACCOUNT_KEY = "adls.auth.shared-key.account.key";

    @Override
    public AzureInstructions createInstructions(
            @NotNull final String uriScheme,
            @NotNull final Map<String, String> properties) {
        final AzureInstructions registryInstructions =
                AzureInstructionsRegistry.getInstructions(properties).orElse(null);
        if (registryInstructions != null) {
            return registryInstructions;
        }

        if (!AzureBlobConstants.AZURE_SCHEMES.contains(uriScheme) && !hasAzureProperties(properties)) {
            return null;
        }

        final AzureInstructions.Builder builder = AzureInstructions.builder();

        // Check for shared key credentials
        final String accountName = properties.get(ADLS_SHARED_KEY_ACCOUNT_NAME);
        final String accountKey = properties.get(ADLS_SHARED_KEY_ACCOUNT_KEY);
        if (accountName != null && accountKey != null) {
            builder.accountName(accountName);
            builder.credentials(AzureCredentials.sharedKey(accountName, accountKey));
            return builder.build();
        }

        // Check for connection string credentials (keyed by account name)
        for (final Map.Entry<String, String> entry : properties.entrySet()) {
            if (entry.getKey().startsWith(ADLS_CONNECTION_STRING_PREFIX)) {
                builder.credentials(AzureCredentials.connectionString(entry.getValue()));
                return builder.build();
            }
        }

        // Check for SAS token credentials (keyed by account name)
        for (final Map.Entry<String, String> entry : properties.entrySet()) {
            if (entry.getKey().startsWith(ADLS_SAS_TOKEN_PREFIX)) {
                builder.credentials(AzureCredentials.sasToken(entry.getValue()));
                return builder.build();
            }
        }

        // If we have an Azure URI scheme but no explicit credentials, use default credentials
        if (AzureBlobConstants.AZURE_SCHEMES.contains(uriScheme)) {
            builder.credentials(AzureCredentials.defaultCredentials());
            return builder.build();
        }

        return null;
    }

    private static boolean hasAzureProperties(@NotNull final Map<String, String> properties) {
        if (properties.containsKey(ADLS_SHARED_KEY_ACCOUNT_NAME)
                || properties.containsKey(ADLS_SHARED_KEY_ACCOUNT_KEY)) {
            return true;
        }
        for (final String key : properties.keySet()) {
            if (key.startsWith(ADLS_CONNECTION_STRING_PREFIX) || key.startsWith(ADLS_SAS_TOKEN_PREFIX)) {
                return true;
            }
        }
        return false;
    }
}
