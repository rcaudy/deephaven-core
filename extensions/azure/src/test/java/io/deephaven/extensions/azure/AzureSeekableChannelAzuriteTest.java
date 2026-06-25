//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import com.azure.storage.blob.BlobContainerClient;
import com.azure.storage.blob.BlobServiceClient;
import com.azure.storage.blob.BlobServiceClientBuilder;
import io.deephaven.extensions.azure.testlib.AzuriteContainer;
import io.deephaven.util.channel.CachedChannelProvider;
import io.deephaven.util.channel.CompletableOutputStream;
import io.deephaven.util.channel.SeekableChannelContext;
import io.deephaven.util.channel.SeekableChannelsProvider;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.URI;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.charset.StandardCharsets;
import java.util.UUID;

import static org.assertj.core.api.Assertions.assertThat;

@Tag("testcontainers")
class AzureSeekableChannelAzuriteTest {

    private BlobServiceClient blobServiceClient;
    private String containerName;
    private AzureInstructions instructions;

    @BeforeAll
    static void initContainer() {
        AzuriteContainer.init();
    }

    @BeforeEach
    void setUp() {
        containerName = "test-" + UUID.randomUUID();
        blobServiceClient = new BlobServiceClientBuilder()
                .connectionString(AzuriteContainer.connectionString())
                .buildClient();
        blobServiceClient.createBlobContainer(containerName);
        instructions = AzureInstructions.builder()
                .endpointOverride(AzuriteContainer.endpoint())
                .credentials(AzureCredentials.sharedKey(
                        AzuriteContainer.ACCOUNT_NAME, AzuriteContainer.ACCOUNT_KEY))
                .build();
    }

    @AfterEach
    void tearDown() {
        blobServiceClient.deleteBlobContainer(containerName);
    }

    private URI blobUri(final String blobName) {
        return URI.create(String.format("abfss://%s@%s.blob.core.windows.net/%s",
                containerName, AzuriteContainer.ACCOUNT_NAME, blobName));
    }

    @Test
    void readSimpleBlob() throws IOException {
        final String content = "Hello, Azure!";
        final BlobContainerClient container = blobServiceClient.getBlobContainerClient(containerName);
        container.getBlobClient("hello.txt")
                .upload(new ByteArrayInputStream(content.getBytes(StandardCharsets.UTF_8)), content.length());

        final URI uri = blobUri("hello.txt");
        try (
                final SeekableChannelsProvider providerImpl = providerImpl();
                final SeekableChannelsProvider provider = CachedChannelProvider.create(providerImpl, 32);
                final SeekableChannelContext context = provider.makeReadContext();
                final SeekableByteChannel readChannel = provider.getReadChannel(context, uri)) {
            final ByteBuffer buffer = readAll(readChannel, 256);
            assertThat(buffer).isEqualTo(ByteBuffer.wrap(content.getBytes(StandardCharsets.UTF_8)));
        }
    }

    @Test
    void readEmptyBlob() throws IOException {
        final BlobContainerClient container = blobServiceClient.getBlobContainerClient(containerName);
        container.getBlobClient("empty.txt")
                .upload(new ByteArrayInputStream(new byte[0]), 0);

        final URI uri = blobUri("empty.txt");
        try (
                final SeekableChannelsProvider providerImpl = providerImpl();
                final SeekableChannelsProvider provider = CachedChannelProvider.create(providerImpl, 32);
                final SeekableChannelContext context = provider.makeReadContext();
                final SeekableByteChannel readChannel = provider.getReadChannel(context, uri)) {
            final ByteBuffer buffer = ByteBuffer.allocate(1);
            assertThat(readChannel.read(buffer)).isEqualTo(-1);
        }
    }

    @Test
    void writeAndReadBack() throws IOException {
        final URI uri = blobUri("roundtrip.txt");
        final String content = "Hello, world!";
        final byte[] contentBytes = content.getBytes(StandardCharsets.UTF_8);
        try (
                final SeekableChannelsProvider providerImpl = providerImpl();
                final SeekableChannelsProvider provider = CachedChannelProvider.create(providerImpl, 32)) {
            // Write
            try (
                    final SeekableChannelsProvider.WriteContext writeContext = provider.makeWriteContext();
                    final CompletableOutputStream outputStream = provider.getOutputStream(writeContext, uri, 0)) {
                final int numBytes = 36 * 1024 * 1024; // 36 MiB -> multiple blocks
                final int numIters = numBytes / contentBytes.length;
                for (int i = 0; i < numIters; ++i) {
                    outputStream.write(contentBytes);
                }
                outputStream.flush();
                outputStream.write(contentBytes);
                outputStream.done();
                outputStream.complete();
            }

            // Read back
            try (
                    final SeekableChannelContext readContext = provider.makeReadContext();
                    final SeekableByteChannel readChannel = provider.getReadChannel(readContext, uri)) {
                final ByteBuffer buffer = ByteBuffer.allocate(contentBytes.length);
                // Read first chunk
                fillBuffer(readChannel, buffer);
                assertThat(buffer).isEqualTo(ByteBuffer.wrap(contentBytes));
            }
        }
    }

    @Test
    void exists() throws IOException {
        final BlobContainerClient container = blobServiceClient.getBlobContainerClient(containerName);
        container.getBlobClient("existing.txt")
                .upload(new ByteArrayInputStream("data".getBytes(StandardCharsets.UTF_8)), 4);

        try (final SeekableChannelsProvider providerImpl = providerImpl()) {
            assertThat(providerImpl.exists(blobUri("existing.txt"))).isTrue();
            assertThat(providerImpl.exists(blobUri("nonexistent.txt"))).isFalse();
        }
    }

    private SeekableChannelsProvider providerImpl() {
        return new AzureSeekableChannelProviderPlugin().createProvider("abfss", instructions);
    }

    private static ByteBuffer readAll(final SeekableByteChannel channel, final int maxBytes) throws IOException {
        final ByteBuffer dst = ByteBuffer.allocate(maxBytes);
        while (dst.remaining() > 0 && channel.read(dst) != -1) {
            // continue
        }
        dst.flip();
        return dst;
    }

    private static void fillBuffer(final SeekableByteChannel channel, final ByteBuffer dst) throws IOException {
        while (dst.remaining() > 0 && channel.read(dst) != -1) {
            // continue
        }
        dst.flip();
    }
}
