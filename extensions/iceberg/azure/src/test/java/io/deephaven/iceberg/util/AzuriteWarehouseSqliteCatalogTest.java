//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import com.azure.storage.blob.BlobServiceClient;
import com.azure.storage.blob.BlobServiceClientBuilder;
import io.deephaven.engine.testutil.junit4.EngineCleanup;
import io.deephaven.extensions.azure.AzureBlobConstants;
import io.deephaven.extensions.azure.AzureCredentials;
import io.deephaven.extensions.azure.AzureInstructions;
import io.deephaven.extensions.azure.testlib.AzuriteContainer;
import io.deephaven.iceberg.junit5.SqliteCatalogBase;
import io.deephaven.iceberg.sqlite.SqliteHelper;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.TestInfo;

import java.nio.file.Path;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

import org.apache.iceberg.CatalogProperties;
import org.jetbrains.annotations.Nullable;

@Tag("testcontainers")
final class AzuriteWarehouseSqliteCatalogTest extends SqliteCatalogBase {

    private static AzureInstructions azureInstructions;
    private static BlobServiceClient blobServiceClient;

    @BeforeAll
    static void initContainer() {
        AzuriteContainer.init();
        azureInstructions = AzureInstructions.builder()
                .endpointOverride(AzuriteContainer.endpoint())
                .credentials(AzureCredentials.sharedKey(
                        AzuriteContainer.ACCOUNT_NAME, AzuriteContainer.ACCOUNT_KEY))
                .build();
        blobServiceClient = new BlobServiceClientBuilder()
                .connectionString(AzuriteContainer.connectionString())
                .buildClient();
    }

    @Nullable
    @Override
    public Object dataInstructions() {
        return azureInstructions;
    }

    @Override
    protected IcebergCatalogAdapter catalogAdapter(
            final TestInfo testInfo,
            final Path rootDir,
            final Map<String, String> properties) {
        final String methodName = testInfo.getTestMethod().orElseThrow().getName();
        final String catalogName = methodName + "-catalog";
        // Azure container names must be 3-63 characters
        final String rawName = methodName.toLowerCase(Locale.US).replace('_', '-');
        final String containerName = rawName.substring(0, Math.min(rawName.length(), 63));

        // Create the Azure container if it doesn't exist
        try {
            blobServiceClient.createBlobContainer(containerName);
        } catch (final Exception e) {
            // Container may already exist
        }

        final String warehouseLocation = String.format("abfss://%s@%s.blob.core.windows.net/warehouse",
                containerName, AzuriteContainer.ACCOUNT_NAME);
        properties.put(CatalogProperties.WAREHOUSE_LOCATION, warehouseLocation);

        // ADLSFileIO (set by InjectAzureProperties) creates its own Azure client for catalog metadata I/O.
        // It needs shared key credentials and the DFS endpoint to connect to Azurite.
        properties.put("adls.auth.shared-key.account.name", AzuriteContainer.ACCOUNT_NAME);
        properties.put("adls.auth.shared-key.account.key", AzuriteContainer.ACCOUNT_KEY);
        properties.put("adls.connection-string." + AzuriteContainer.ACCOUNT_NAME + ".blob.core.windows.net",
                AzuriteContainer.adlsEndpoint());

        return IcebergToolsAzure.createAdapter(
                BuildCatalogOptions.builder()
                        .name(catalogName)
                        .putAllProperties(properties)
                        .putAllHadoopConfig(Map.of())
                        .build(),
                azureInstructions);
    }
}
