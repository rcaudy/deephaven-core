//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import org.junit.jupiter.api.Test;

import java.net.URI;
import java.time.Duration;

import static io.deephaven.extensions.azure.AzureInstructions.DEFAULT_READ_TIMEOUT;
import static io.deephaven.extensions.azure.AzureInstructions.DEFAULT_WRITE_TIMEOUT;
import static org.assertj.core.api.Assertions.failBecauseExceptionWasNotThrown;
import static org.assertj.core.api.AssertionsForClassTypes.assertThat;

class AzureInstructionsTest {

    @Test
    void defaults() {
        final AzureInstructions instructions = AzureInstructions.builder().build();
        assertThat(instructions.accountName().isEmpty()).isTrue();
        assertThat(instructions.endpointSuffix()).isEqualTo("blob.core.windows.net");
        assertThat(instructions.endpointOverride().isEmpty()).isTrue();
        assertThat(instructions.maxConcurrentRequests()).isEqualTo(256);
        assertThat(instructions.readAheadCount()).isEqualTo(32);
        assertThat(instructions.fragmentSize()).isEqualTo(65536);
        assertThat(instructions.connectionTimeout()).isEqualTo(Duration.ofSeconds(2));
        assertThat(instructions.readTimeout()).isEqualTo(Duration.ofSeconds(2));
        assertThat(instructions.writeTimeout()).isEqualTo(Duration.ofSeconds(2));
        assertThat(instructions.credentials()).isEqualTo(AzureCredentials.defaultCredentials());
        assertThat(instructions.writeBlockSize()).isEqualTo(10 << 20);
        assertThat(instructions.numConcurrentWriteBlocks()).isEqualTo(64);
    }

    @Test
    void testSetAccountName() {
        assertThat(AzureInstructions.builder()
                .accountName("myaccount")
                .build()
                .accountName().get())
                .isEqualTo("myaccount");
    }

    @Test
    void testSetEndpointSuffix() {
        assertThat(AzureInstructions.builder()
                .endpointSuffix("blob.core.chinacloudapi.cn")
                .build()
                .endpointSuffix())
                .isEqualTo("blob.core.chinacloudapi.cn");
    }

    @Test
    void testSetEndpointOverride() {
        final URI endpoint = URI.create("http://127.0.0.1:10000/devstoreaccount1");
        assertThat(AzureInstructions.builder()
                .endpointOverride(endpoint)
                .build()
                .endpointOverride().get())
                .isEqualTo(endpoint);
    }

    @Test
    void testSetEndpointOverrideString() {
        assertThat(AzureInstructions.builder()
                .endpointOverride("http://127.0.0.1:10000/devstoreaccount1")
                .build()
                .endpointOverride().get())
                .isEqualTo(URI.create("http://127.0.0.1:10000/devstoreaccount1"));
    }

    @Test
    void testSetMaxConcurrentRequests() {
        assertThat(AzureInstructions.builder()
                .maxConcurrentRequests(100)
                .build()
                .maxConcurrentRequests())
                .isEqualTo(100);
    }

    @Test
    void tooSmallMaxConcurrentRequests() {
        try {
            AzureInstructions.builder()
                    .maxConcurrentRequests(0)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("maxConcurrentRequests");
        }
    }

    @Test
    void negativeMaxConcurrentRequests() {
        try {
            AzureInstructions.builder()
                    .maxConcurrentRequests(-1)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("maxConcurrentRequests");
        }
    }

    @Test
    void minReadAheadCount() {
        assertThat(AzureInstructions.builder()
                .readAheadCount(0)
                .build()
                .readAheadCount())
                .isZero();
    }

    @Test
    void tooSmallReadAheadCount() {
        try {
            AzureInstructions.builder()
                    .readAheadCount(-1)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("readAheadCount");
        }
    }

    @Test
    void minFragmentSize() {
        assertThat(AzureInstructions.builder()
                .fragmentSize(8 * (1 << 10))
                .build()
                .fragmentSize())
                .isEqualTo(8 * (1 << 10));
    }

    @Test
    void tooSmallFragmentSize() {
        try {
            AzureInstructions.builder()
                    .fragmentSize(8 * (1 << 10) - 1)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("fragmentSize");
        }
    }

    @Test
    void testReadTimeout() {
        assertThat(AzureInstructions.builder()
                .readTimeout(Duration.ofSeconds(1))
                .build()
                .readTimeout())
                .isEqualTo(Duration.ofSeconds(1));
    }

    @Test
    void testReadTimeoutNotSet() {
        assertThat(AzureInstructions.builder()
                .build()
                .readTimeout())
                .isEqualTo(DEFAULT_READ_TIMEOUT);
    }

    @Test
    void testReadTimeoutValidate() {
        // 1 milli is allowed
        AzureInstructions.builder()
                .readTimeout(Duration.ofMillis(1))
                .build();

        // Less than 1 milli is not allowed
        try {
            AzureInstructions.builder()
                    .readTimeout(Duration.ofNanos(999_999))
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("readTimeout");
        }
    }

    @Test
    void testWriteTimeout() {
        assertThat(AzureInstructions.builder()
                .writeTimeout(Duration.ofMillis(5))
                .build()
                .writeTimeout())
                .isEqualTo(Duration.ofMillis(5));
    }

    @Test
    void testWriteTimeoutNotSet() {
        assertThat(AzureInstructions.builder()
                .build()
                .writeTimeout())
                .isEqualTo(DEFAULT_WRITE_TIMEOUT);
    }

    @Test
    void testWriteTimeoutValidate() {
        // 1 milli is allowed
        AzureInstructions.builder()
                .writeTimeout(Duration.ofMillis(1))
                .build();

        // Less than 1 milli is not allowed
        try {
            AzureInstructions.builder()
                    .writeTimeout(Duration.ofNanos(999_999))
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("writeTimeout");
        }
    }

    @Test
    void testSetCredentials() {
        assertThat(AzureInstructions.builder()
                .credentials(AzureCredentials.anonymous())
                .build()
                .credentials())
                .isEqualTo(AzureCredentials.anonymous());
    }

    @Test
    void badCredentials() {
        try {
            AzureInstructions.builder()
                    .credentials(new AzureCredentials() {})
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("credentials");
        }
    }

    @Test
    void testSetWriteBlockSize() {
        assertThat(AzureInstructions.builder()
                .writeBlockSize(1 << 20)
                .build()
                .writeBlockSize())
                .isEqualTo(1 << 20);
    }

    @Test
    void tooSmallWriteBlockSize() {
        try {
            AzureInstructions.builder()
                    .writeBlockSize(AzureInstructions.MIN_WRITE_BLOCK_SIZE - 1)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("writeBlockSize");
        }
    }

    @Test
    void minWriteBlockSize() {
        assertThat(AzureInstructions.builder()
                .writeBlockSize(AzureInstructions.MIN_WRITE_BLOCK_SIZE)
                .build()
                .writeBlockSize())
                .isEqualTo(AzureInstructions.MIN_WRITE_BLOCK_SIZE);
    }

    @Test
    void tooSmallNumConcurrentWriteBlocks() {
        try {
            AzureInstructions.builder()
                    .numConcurrentWriteBlocks(0)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("numConcurrentWriteBlocks");
        }
    }

    @Test
    void tooLargeNumConcurrentWriteBlocks() {
        try {
            AzureInstructions.builder()
                    .numConcurrentWriteBlocks(1001)
                    .maxConcurrentRequests(1000)
                    .build();
            failBecauseExceptionWasNotThrown(IllegalArgumentException.class);
        } catch (IllegalArgumentException e) {
            assertThat(e).hasMessageContaining("numConcurrentWriteBlocks");
        }
    }

    @Test
    void testConnectionTimeout() {
        assertThat(AzureInstructions.builder()
                .connectionTimeout(Duration.ofSeconds(5))
                .build()
                .connectionTimeout())
                .isEqualTo(Duration.ofSeconds(5));
    }
}
