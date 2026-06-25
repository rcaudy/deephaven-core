//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.iceberg.util;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.ServiceLoader;

import static org.assertj.core.api.Assertions.assertThat;

class PropertyInjectorDiscoveryTest {

    @Test
    void serviceLoaderFindsAzureInjector() {
        final List<String> found = new ArrayList<>();
        for (final PropertyInjector injector : ServiceLoader.load(PropertyInjector.class)) {
            found.add(injector.getClass().getName());
        }
        assertThat(found).contains("io.deephaven.iceberg.util.InjectAzureProperties");
    }

    @Test
    void injectDeephavenPropertiesSetsFileIO() {
        final Map<String, String> input = new java.util.HashMap<>();
        input.put("warehouse", "abfss://container@account.blob.core.windows.net/warehouse");
        final Map<String, String> result = IcebergTools.injectDeephavenProperties(input);
        assertThat(result.get("io-impl"))
                .isEqualTo("org.apache.iceberg.azure.adlsv2.ADLSFileIO");
    }
}
