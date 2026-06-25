//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

class AzureCredentialsTest {

    @Test
    void defaultCredentials() {
        isAzureSdkCredentials(AzureCredentials.defaultCredentials());
    }

    @Test
    void sharedKey() {
        isAzureSdkCredentials(AzureCredentials.sharedKey("accountName", "accountKey"));
    }

    @Test
    void sasToken() {
        isAzureSdkCredentials(AzureCredentials.sasToken("sv=2023-01-03&ss=b&srt=co&sp=rl&se=2030-01-01"));
    }

    @Test
    void connectionString() {
        isAzureSdkCredentials(AzureCredentials.connectionString(
                "DefaultEndpointsProtocol=https;AccountName=test;AccountKey=dGVzdA==;EndpointSuffix=core.windows.net"));
    }

    @Test
    void anonymous() {
        isAzureSdkCredentials(AzureCredentials.anonymous());
    }

    private void isAzureSdkCredentials(AzureCredentials c) {
        assertThat(c).isInstanceOf(AzureSdkCredentials.class);
    }
}
