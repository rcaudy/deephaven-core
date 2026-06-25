//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import org.jetbrains.annotations.NotNull;

import java.util.Map;

/**
 * A plugin interface for injecting storage-provider-specific properties into the Iceberg catalog property map. Plugin
 * implementations are discovered via {@link java.util.ServiceLoader} and invoked during
 * {@link IcebergTools#injectDeephavenProperties(Map)}.
 *
 * <p>
 * Each implementation may inject properties needed for its respective storage backend (e.g., AWS/S3, Azure Blob
 * Storage) without modifying properties already set by the user.
 */
public interface PropertyInjector {

    /**
     * Creates a new map with provider-specific properties injected. The input map must not be modified.
     *
     * @param inputProperties the input catalog properties
     * @return a new map containing the original properties plus any injected defaults
     */
    Map<String, String> injectProperties(@NotNull Map<String, String> inputProperties);
}
