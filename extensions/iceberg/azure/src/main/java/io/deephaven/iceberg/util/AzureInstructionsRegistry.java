//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import io.deephaven.extensions.azure.AzureInstructions;

import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

/**
 * A registry that stores {@link AzureInstructions} instances keyed by a UUID that is embedded in catalog properties.
 * This allows {@link AzureInstructionsProviderPlugin} to retrieve the original instructions that were passed to
 * {@link IcebergToolsAzure#createAdapter(BuildCatalogOptions, AzureInstructions)}.
 */
final class AzureInstructionsRegistry {

    private static final String UUID_KEY = AzureInstructionsRegistry.class.getName() + ".__uuid";

    private static final Map<String, AzureInstructions> INSTRUCTIONS_MAP = new ConcurrentHashMap<>();

    /**
     * Stores the given {@link AzureInstructions} in the registry and adds a UUID key to {@code propertiesOut} for later
     * retrieval via {@link #getInstructions(Map)}. It is an error if the UUID key is already present in the properties.
     *
     * @param instructions the instructions to store
     * @param propertiesOut the mutable properties map to add the UUID key to
     * @return a cleanup runnable that removes the instructions from the registry; the caller should arrange for this to
     *         be invoked when the corresponding Catalog is no longer in use
     */
    static Runnable addToProperties(final AzureInstructions instructions, final Map<String, String> propertiesOut) {
        Objects.requireNonNull(instructions);
        final String uuid = UUID.randomUUID().toString();
        putOrThrow(propertiesOut, UUID_KEY, uuid);
        INSTRUCTIONS_MAP.put(uuid, instructions);
        return () -> INSTRUCTIONS_MAP.remove(uuid);
    }

    /**
     * Retrieves the {@link AzureInstructions} stored by a prior {@link #addToProperties(AzureInstructions, Map)} call,
     * if the properties contain the UUID key.
     *
     * @param properties the catalog properties
     * @return the instructions, if present
     * @throws IllegalStateException if the UUID key is present but the instructions have already been cleaned up
     */
    static Optional<AzureInstructions> getInstructions(final Map<String, String> properties) {
        final String uuid = properties.get(UUID_KEY);
        if (uuid == null) {
            return Optional.empty();
        }
        final AzureInstructions instructions = INSTRUCTIONS_MAP.get(uuid);
        if (instructions == null) {
            throw new IllegalStateException(
                    "These AzureInstructions were already cleaned up; please ensure that the returned Runnable from " +
                            "addToProperties is not invoked until the Catalog is no longer in use.");
        }
        return Optional.of(instructions);
    }

    private static <K, V> void putOrThrow(final Map<K, V> map, final K key, final V value) {
        if (map.putIfAbsent(key, value) != null) {
            throw new IllegalArgumentException(String.format("Key '%s' already exists in map", key));
        }
    }

    private AzureInstructionsRegistry() {}
}
