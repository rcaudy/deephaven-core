//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.HashMap;
import java.util.Map;

import static org.assertj.core.api.Assertions.assertThat;

class InjectAzurePropertiesTest {

    private static final String ADLS_FILE_IO = "org.apache.iceberg.azure.adlsv2.ADLSFileIO";

    private final InjectAzureProperties injector = new InjectAzureProperties();

    @ParameterizedTest
    @ValueSource(strings = {"abfss://container@account.blob.core.windows.net/warehouse",
            "abfs://container@account.dfs.core.windows.net/warehouse",
            "wasb://container@account.blob.core.windows.net/warehouse",
            "wasbs://container@account.blob.core.windows.net/warehouse"})
    void injectsFileIOForAzureWarehouse(final String warehouseLocation) {
        final Map<String, String> input = Map.of("warehouse", warehouseLocation);
        final Map<String, String> result = injector.injectProperties(input);
        assertThat(result.get("io-impl")).isEqualTo(ADLS_FILE_IO);
        assertThat(result.get("warehouse")).isEqualTo(warehouseLocation);
    }

    @Test
    void doesNotOverrideExistingFileIO() {
        final Map<String, String> input = Map.of(
                "warehouse", "abfss://container@account.blob.core.windows.net/warehouse",
                "io-impl", "com.custom.MyFileIO");
        final Map<String, String> result = injector.injectProperties(input);
        assertThat(result.get("io-impl")).isEqualTo("com.custom.MyFileIO");
    }

    @Test
    void noOpForNonAzureWarehouse() {
        final Map<String, String> input = Map.of("warehouse", "s3://my-bucket/warehouse");
        final Map<String, String> result = injector.injectProperties(input);
        assertThat(result).isSameAs(input);
    }

    @Test
    void noOpForMissingWarehouse() {
        final Map<String, String> input = Map.of("some.key", "some.value");
        final Map<String, String> result = injector.injectProperties(input);
        assertThat(result).isSameAs(input);
    }

    @Test
    void caseInsensitiveScheme() {
        final Map<String, String> input =
                Map.of("warehouse", "ABFSS://container@account.blob.core.windows.net/warehouse");
        final Map<String, String> result = injector.injectProperties(input);
        assertThat(result.get("io-impl")).isEqualTo(ADLS_FILE_IO);
    }

    @Test
    void preservesAllInputProperties() {
        final Map<String, String> input = new HashMap<>();
        input.put("warehouse", "abfss://container@account.blob.core.windows.net/warehouse");
        input.put("custom.key1", "value1");
        input.put("custom.key2", "value2");
        final Map<String, String> result = injector.injectProperties(input);
        assertThat(result).containsEntry("custom.key1", "value1");
        assertThat(result).containsEntry("custom.key2", "value2");
        assertThat(result).containsEntry("io-impl", ADLS_FILE_IO);
    }
}
