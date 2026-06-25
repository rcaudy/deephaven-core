//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import io.deephaven.extensions.azure.AzureInstructions;
import io.deephaven.util.reference.CleanupReferenceProcessor;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.HashMap;
import java.util.Map;

/**
 * Tools for accessing tables in the Iceberg table format from Azure Blob Storage.
 */
public final class IcebergToolsAzure {

    /**
     * Create an Iceberg catalog adapter.
     *
     * @param name the name of the catalog; if omitted, the catalog URI will be used to generate a name
     * @param properties a map containing the Iceberg catalog properties to use
     * @param hadoopConfig a map containing Hadoop configuration properties to use
     * @param instructions the Azure instructions
     * @return the Iceberg catalog adapter
     *
     * @deprecated Use {@link #createAdapter(BuildCatalogOptions, AzureInstructions)} instead with appropriate options.
     * @see #createAdapter(BuildCatalogOptions, AzureInstructions)
     */
    @Deprecated(forRemoval = true)
    public static IcebergCatalogAdapter createAdapter(
            @Nullable final String name,
            @NotNull final Map<String, String> properties,
            @NotNull final Map<String, String> hadoopConfig,
            @NotNull final AzureInstructions instructions) {
        final BuildCatalogOptions.Builder optionsBuilder = BuildCatalogOptions.builder()
                .putAllProperties(properties)
                .putAllHadoopConfig(hadoopConfig)
                .enablePropertyInjection(true);
        if (name != null) {
            optionsBuilder.name(name);
        }
        return createAdapter(optionsBuilder.build(), instructions);
    }

    /**
     * Create an Iceberg catalog adapter with Azure Blob Storage instructions.
     *
     * <p>
     * This is the preferred way to configure an Iceberg catalog adapter when the caller is responsible for providing
     * Azure connectivity details. The {@code instructions} will automatically be used as special instructions if
     * {@link IcebergReadInstructions#dataInstructions()} is not explicitly set. The caller is still responsible for
     * providing any other properties necessary to configure their {@link org.apache.iceberg.catalog.Catalog}
     * implementation.
     *
     * @param options the options to build the catalog
     * @param instructions the Azure instructions
     * @return the Iceberg catalog adapter
     */
    public static IcebergCatalogAdapter createAdapter(
            @NotNull final BuildCatalogOptions options,
            @NotNull final AzureInstructions instructions) {
        if (!options.enablePropertyInjection()) {
            throw new IllegalArgumentException(
                    "Property injection must be enabled to use Azure instructions, please" +
                            " enable or use IcebergTools#createAdapter");
        }
        final Map<String, String> newProperties = new HashMap<>(options.properties());
        final Runnable cleanup = AzureInstructionsRegistry.addToProperties(instructions, newProperties);
        final IcebergCatalogAdapter adapter = IcebergTools.createAdapter(options.withProperties(newProperties));
        // When the Catalog becomes phantom reachable, we can invoke the AzureInstructionsRegistry cleanup.
        // Note: it would be incorrect to register the cleanup against the adapter since the Catalog can outlive the
        // adapter (and the AzureInstructionsRegistry properties are needed by the Catalog).
        CleanupReferenceProcessor.getDefault().registerPhantom(adapter.catalog(), cleanup);
        return adapter;
    }
}
