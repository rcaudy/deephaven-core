//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.net.URI;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

class AzureUriTest {

    @Test
    void abfssScheme() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfss://mycontainer@myaccount.blob.core.windows.net/path/to/blob"));
        assertThat(parsed.container()).isEqualTo("mycontainer");
        assertThat(parsed.accountName()).isEqualTo("myaccount");
        assertThat(parsed.blobPath()).isEqualTo("path/to/blob");
        assertThat(parsed.endpointSuffix()).isEqualTo("blob.core.windows.net");
        assertThat(parsed.endpoint()).isEqualTo("https://myaccount.blob.core.windows.net");
    }

    @Test
    void abfsScheme() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfs://mycontainer@myaccount.dfs.core.windows.net/path/to/blob"));
        assertThat(parsed.container()).isEqualTo("mycontainer");
        assertThat(parsed.accountName()).isEqualTo("myaccount");
        assertThat(parsed.endpointSuffix()).isEqualTo("dfs.core.windows.net");
    }

    @Test
    void wasbScheme() {
        final AzureUri parsed =
                AzureUri.of(URI.create("wasb://mycontainer@myaccount.blob.core.windows.net/path/to/blob"));
        assertThat(parsed.container()).isEqualTo("mycontainer");
        assertThat(parsed.accountName()).isEqualTo("myaccount");
    }

    @Test
    void wasbsScheme() {
        final AzureUri parsed =
                AzureUri.of(URI.create("wasbs://mycontainer@myaccount.blob.core.windows.net/path/to/blob"));
        assertThat(parsed.container()).isEqualTo("mycontainer");
        assertThat(parsed.accountName()).isEqualTo("myaccount");
    }

    @Test
    void emptyPath() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfss://mycontainer@myaccount.blob.core.windows.net/"));
        assertThat(parsed.blobPath()).isEmpty();
    }

    @Test
    void noPath() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfss://mycontainer@myaccount.blob.core.windows.net"));
        assertThat(parsed.blobPath()).isEmpty();
    }

    @Test
    void deepPath() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfss://container@account.blob.core.windows.net/a/b/c/d/file.parquet"));
        assertThat(parsed.blobPath()).isEqualTo("a/b/c/d/file.parquet");
    }

    @Test
    void sovereignCloud() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfss://container@account.blob.core.chinacloudapi.cn/path"));
        assertThat(parsed.accountName()).isEqualTo("account");
        assertThat(parsed.endpointSuffix()).isEqualTo("blob.core.chinacloudapi.cn");
        assertThat(parsed.endpoint()).isEqualTo("https://account.blob.core.chinacloudapi.cn");
    }

    @Test
    void withPath() {
        final AzureUri parsed =
                AzureUri.of(URI.create("abfss://container@account.blob.core.windows.net/original"));
        final URI newUri = parsed.withPath("abfss", "new/path/file.parquet");
        assertThat(newUri.getScheme()).isEqualTo("abfss");
        assertThat(newUri.getUserInfo()).isEqualTo("container");
        assertThat(newUri.getHost()).isEqualTo("account.blob.core.windows.net");
        assertThat(newUri.getPath()).isEqualTo("/new/path/file.parquet");
    }

    @ParameterizedTest
    @ValueSource(strings = {"s3://bucket/key", "http://example.com", "file:///tmp/file"})
    void invalidScheme(final String uriStr) {
        assertThatThrownBy(() -> AzureUri.of(URI.create(uriStr)))
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessageContaining("Not an Azure Blob Storage URI");
    }

    @Test
    void missingContainer() {
        assertThatThrownBy(() -> AzureUri.of(URI.create("abfss://account.blob.core.windows.net/path")))
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessageContaining("missing container");
    }

    @Test
    void hostWithoutDot() {
        assertThatThrownBy(() -> AzureUri.of(URI.create("abfss://container@localhost/path")))
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessageContaining("account.suffix");
    }

    @Test
    void equality() {
        final URI uri = URI.create("abfss://container@account.blob.core.windows.net/path");
        final AzureUri a = AzureUri.of(uri);
        final AzureUri b = AzureUri.of(uri);
        assertThat(a).isEqualTo(b);
        assertThat(a.hashCode()).isEqualTo(b.hashCode());
    }

    @Test
    void toStringContainsUri() {
        final URI uri = URI.create("abfss://container@account.blob.core.windows.net/path");
        assertThat(AzureUri.of(uri).toString()).isEqualTo(uri.toString());
    }
}
