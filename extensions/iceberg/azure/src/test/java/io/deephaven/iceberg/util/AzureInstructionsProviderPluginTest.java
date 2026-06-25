//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import io.deephaven.extensions.azure.AzureCredentials;
import io.deephaven.extensions.azure.AzureInstructions;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;

import static org.assertj.core.api.Assertions.assertThat;

class AzureInstructionsProviderPluginTest {

    private final AzureInstructionsProviderPlugin plugin = new AzureInstructionsProviderPlugin();

    @Test
    void registryTakesPrecedence() {
        final AzureInstructions registered = AzureInstructions.builder()
                .credentials(AzureCredentials.anonymous())
                .build();
        final Map<String, String> properties = new HashMap<>();
        // Put shared key properties that would normally produce different instructions
        properties.put("adls.auth.shared-key.account.name", "acct");
        properties.put("adls.auth.shared-key.account.key", "key");
        final Runnable cleanup = AzureInstructionsRegistry.addToProperties(registered, properties);
        try {
            final AzureInstructions result = plugin.createInstructions("abfss", properties);
            assertThat(result).isSameAs(registered);
        } finally {
            cleanup.run();
        }
    }

    @Test
    void sharedKeyFromProperties() {
        final Map<String, String> properties = Map.of(
                "adls.auth.shared-key.account.name", "myaccount",
                "adls.auth.shared-key.account.key", "mykey");
        final AzureInstructions result = plugin.createInstructions("abfss", properties);
        assertThat(result).isNotNull();
        assertThat(result.accountName()).hasValue("myaccount");
    }

    @Test
    void connectionStringFromProperties() {
        final Map<String, String> properties = Map.of(
                "adls.connection-string.myaccount",
                "DefaultEndpointsProtocol=https;AccountName=myaccount;AccountKey=a2V5;EndpointSuffix=core.windows.net");
        final AzureInstructions result = plugin.createInstructions("abfss", properties);
        assertThat(result).isNotNull();
    }

    @Test
    void sasTokenFromProperties() {
        final Map<String, String> properties = Map.of(
                "adls.sas-token.myaccount", "sv=2023-01-03&ss=b&srt=co&sp=rl");
        final AzureInstructions result = plugin.createInstructions("abfss", properties);
        assertThat(result).isNotNull();
    }

    @Test
    void azureSchemeWithNoCredentialProperties() {
        final AzureInstructions result = plugin.createInstructions("abfss", Map.of());
        assertThat(result).isNotNull();
        assertThat(result.credentials()).isEqualTo(AzureCredentials.defaultCredentials());
    }

    @Test
    void nonAzureSchemeNoProperties() {
        final AzureInstructions result = plugin.createInstructions("s3", Map.of());
        assertThat(result).isNull();
    }

    @Test
    void nonAzureSchemeWithAzureProperties() {
        final Map<String, String> properties = Map.of(
                "adls.auth.shared-key.account.name", "myaccount",
                "adls.auth.shared-key.account.key", "mykey");
        final AzureInstructions result = plugin.createInstructions("s3", properties);
        assertThat(result).isNotNull();
        assertThat(result.accountName()).hasValue("myaccount");
    }
}
