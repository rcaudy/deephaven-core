//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure.testlib;

import org.testcontainers.containers.GenericContainer;
import org.testcontainers.containers.wait.strategy.Wait;
import org.testcontainers.utility.DockerImageName;

import java.net.URI;

/**
 * Singleton Azurite container for Azure Blob Storage integration tests.
 */
public final class AzuriteContainer {

    public static final String ACCOUNT_NAME = "devstoreaccount1";
    public static final String ACCOUNT_KEY =
            "Eby8vdM02xNOcqFlqUwJPLlmEtlCDXJ1OUzFT50uSRZ6IFsuFq2UVErCz4I6tq/K1SZFPTOtr/KBHBeksoGMGw==";

    private static final int BLOB_PORT = 10000;
    @SuppressWarnings("resource")
    private static final GenericContainer<?> AZURITE =
            new GenericContainer<>(DockerImageName.parse(System.getProperty("testcontainers.azurite.image"))
                    .asCompatibleSubstituteFor("mcr.microsoft.com/azure-storage/azurite"))
                    .withExposedPorts(BLOB_PORT)
                    .waitingFor(Wait.forListeningPort());
    static {
        AZURITE.start();
    }

    public static void init() {
        // no-op, ensures this class is initialized
    }

    public static URI endpoint() {
        return URI.create(String.format("http://%s:%d/%s",
                AZURITE.getHost(), AZURITE.getMappedPort(BLOB_PORT), ACCOUNT_NAME));
    }

    /**
     * Connection string for the Blob Storage endpoint, used by Deephaven's Azure channel provider and
     * {@code BlobServiceClientBuilder}.
     */
    public static String connectionString() {
        return String.format(
                "DefaultEndpointsProtocol=http;AccountName=%s;AccountKey=%s;BlobEndpoint=http://%s:%d/%s;",
                ACCOUNT_NAME, ACCOUNT_KEY,
                AZURITE.getHost(), AZURITE.getMappedPort(BLOB_PORT), ACCOUNT_NAME);
    }

    /**
     * The endpoint URL for Iceberg's {@code ADLSFileIO} via the {@code adls.connection-string.<account>} property
     * (which Iceberg treats as an endpoint URL, not an actual connection string). Azurite routes DFS requests through
     * the Blob endpoint.
     */
    public static String adlsEndpoint() {
        return String.format("http://%s:%d/%s",
                AZURITE.getHost(), AZURITE.getMappedPort(BLOB_PORT), ACCOUNT_NAME);
    }

    private AzuriteContainer() {}
}
