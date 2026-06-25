//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import com.google.auto.service.AutoService;
import org.jetbrains.annotations.NotNull;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * {@link PropertyInjector} that injects Deephaven-specific Azure Blob Storage settings into the property map passed to
 * {@link BuildCatalogOptions}. The keys are duplicated from Iceberg's <em>iceberg-azure</em> module to avoid adding an
 * extra dependency on the exact field names.
 */
@AutoService(PropertyInjector.class)
public class InjectAzureProperties implements PropertyInjector {

    /**
     * Duplicated from Iceberg's ADLSFileIO class name.
     */
    private static final String ADLS_FILE_IO_IMPL = "org.apache.iceberg.azure.adlsv2.ADLSFileIO";

    /**
     * Duplicated from CatalogProperties.FILE_IO_IMPL.
     */
    private static final String FILE_IO_IMPL = "io-impl";

    /**
     * Duplicated from CatalogProperties.WAREHOUSE_LOCATION.
     */
    private static final String WAREHOUSE_LOCATION = "warehouse";

    @Override
    public Map<String, String> injectProperties(@NotNull final Map<String, String> inputProperties) {
        final String warehouseLocation = inputProperties.get(WAREHOUSE_LOCATION);
        if (warehouseLocation == null || !isAzureWarehouseLocation(warehouseLocation)) {
            return inputProperties;
        }

        final Map<String, String> updatedProperties = new LinkedHashMap<>(inputProperties);

        // If no FileIO implementation is set and the warehouse location is Azure, default to ADLSFileIO
        updatedProperties.putIfAbsent(FILE_IO_IMPL, ADLS_FILE_IO_IMPL);

        return updatedProperties;
    }

    private static boolean isAzureWarehouseLocation(@NotNull final String warehouseLocation) {
        final String lower = warehouseLocation.toLowerCase();
        return lower.startsWith("abfss://")
                || lower.startsWith("abfs://")
                || lower.startsWith("wasbs://")
                || lower.startsWith("wasb://");
    }
}
