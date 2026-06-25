//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import io.deephaven.extensions.azure.AzureCredentials;
import io.deephaven.extensions.azure.AzureInstructions;
import org.junit.jupiter.api.Test;

import java.time.Duration;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

class AzureInstructionsRegistryTest {

    @Test
    void addAndRetrieve() {
        final AzureInstructions instructions = AzureInstructions.builder()
                .credentials(AzureCredentials.anonymous())
                .connectionTimeout(Duration.ofSeconds(10))
                .build();
        final Map<String, String> properties = new HashMap<>();
        final Runnable cleanup = AzureInstructionsRegistry.addToProperties(instructions, properties);
        try {
            final Optional<AzureInstructions> retrieved = AzureInstructionsRegistry.getInstructions(properties);
            assertThat(retrieved).isPresent();
            assertThat(retrieved.get()).isSameAs(instructions);
        } finally {
            cleanup.run();
        }
    }

    @Test
    void getInstructionsEmptyProperties() {
        final Optional<AzureInstructions> retrieved =
                AzureInstructionsRegistry.getInstructions(Map.of());
        assertThat(retrieved).isEmpty();
    }

    @Test
    void cleanupRemovesInstructions() {
        final AzureInstructions instructions = AzureInstructions.builder().build();
        final Map<String, String> properties = new HashMap<>();
        final Runnable cleanup = AzureInstructionsRegistry.addToProperties(instructions, properties);
        cleanup.run();
        assertThatThrownBy(() -> AzureInstructionsRegistry.getInstructions(properties))
                .isInstanceOf(IllegalStateException.class)
                .hasMessageContaining("already cleaned up");
    }

    @Test
    void duplicateKeyThrows() {
        final AzureInstructions instructions = AzureInstructions.builder().build();
        final Map<String, String> properties = new HashMap<>();
        final Runnable cleanup = AzureInstructionsRegistry.addToProperties(instructions, properties);
        try {
            assertThatThrownBy(() -> AzureInstructionsRegistry.addToProperties(instructions, properties))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("already exists");
        } finally {
            cleanup.run();
        }
    }

    @Test
    void multipleRegistrations() {
        final AzureInstructions instructions1 = AzureInstructions.builder()
                .credentials(AzureCredentials.anonymous())
                .build();
        final AzureInstructions instructions2 = AzureInstructions.builder()
                .credentials(AzureCredentials.sharedKey("acct", "key"))
                .build();
        final Map<String, String> props1 = new HashMap<>();
        final Map<String, String> props2 = new HashMap<>();
        final Runnable cleanup1 = AzureInstructionsRegistry.addToProperties(instructions1, props1);
        final Runnable cleanup2 = AzureInstructionsRegistry.addToProperties(instructions2, props2);
        try {
            assertThat(AzureInstructionsRegistry.getInstructions(props1).get()).isSameAs(instructions1);
            assertThat(AzureInstructionsRegistry.getInstructions(props2).get()).isSameAs(instructions2);
        } finally {
            cleanup1.run();
            cleanup2.run();
        }
    }
}
