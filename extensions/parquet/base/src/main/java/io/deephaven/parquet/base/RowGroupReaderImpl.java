/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.parquet.base;

import io.deephaven.parquet.base.util.SeekableChannelsProvider;
import org.apache.parquet.format.ColumnChunk;
import org.apache.parquet.format.RowGroup;
import org.apache.parquet.format.Util;
import org.apache.parquet.format.converter.ParquetMetadataConverter;
import org.apache.parquet.hadoop.metadata.BlockMetaData;
import org.apache.parquet.hadoop.metadata.ColumnChunkMetaData;
import org.apache.parquet.internal.column.columnindex.OffsetIndex;
import org.apache.parquet.schema.MessageType;
import org.apache.parquet.schema.Type;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.channels.Channels;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RowGroupReaderImpl implements RowGroupReader {

    private static final int BUFFER_SIZE = 65536;
    private final RowGroup rowGroup;
    private final SeekableChannelsProvider channelsProvider;
    private final MessageType type;
    private final Map<String, List<Type>> schemaMap = new HashMap<>();
    private final Map<String, ColumnChunk> chunkMap = new HashMap<>();
    private final Map<String, ColumnChunkMetaData> metadataMap = new HashMap<>();

    private final Path rootPath;
    private final String version;

    RowGroupReaderImpl(
            @NotNull final BlockMetaData blockMetaData,
            @NotNull final RowGroup rowGroup,
            @NotNull final SeekableChannelsProvider channelsProvider,
            @NotNull final Path rootPath,
            @NotNull final MessageType type,
            @NotNull final MessageType schema,
            @Nullable final String version) {
        this.channelsProvider = channelsProvider;
        this.rowGroup = rowGroup;
        this.rootPath = rootPath;
        this.type = type;

        // TODO: Use BlockMetaData instead of column.getMetaData
        final List<ColumnChunk> columns = rowGroup.columns;
        for (int ii = 0; ii < columns.size(); ii++) {
            final ColumnChunk column = columns.get(ii);
            final List<String> path_in_schema = column.getMeta_data().path_in_schema;
            final String key = path_in_schema.toString();
            final List<Type> nonRequiredFields = new ArrayList<>();
            for (int indexInPath = 0; indexInPath < path_in_schema.size(); indexInPath++) {
                final Type fieldType = schema.getType(path_in_schema.subList(0, indexInPath + 1)
                        .toArray(String[]::new));
                if (fieldType.getRepetition() != Type.Repetition.REQUIRED) {
                    nonRequiredFields.add(fieldType);
                }
            }

            chunkMap.put(key, column);
            schemaMap.put(key, nonRequiredFields);
            metadataMap.put(key, blockMetaData.getColumns().get(ii));
        }
        this.version = version;
    }

    @Override
    public ColumnChunkReaderImpl getColumnChunk(@NotNull final List<String> path) {
        String key = path.toString();
        ColumnChunk columnChunk = chunkMap.get(key);
        List<Type> fieldTypes = schemaMap.get(key);
        if (columnChunk == null) {
            return null;
        }

        OffsetIndex offsetIndex = null;
        if (columnChunk.isSetOffset_index_offset()) {
            try (final SeekableByteChannel readChannel = channelsProvider.getReadChannel(rootPath)) {
                readChannel.position(columnChunk.getOffset_index_offset());
                offsetIndex = ParquetMetadataConverter.fromParquetOffsetIndex(Util.readOffsetIndex(
                        new BufferedInputStream(Channels.newInputStream(readChannel), BUFFER_SIZE)));
            } catch (IOException e) {
                throw new UncheckedIOException(e);
            }
        }
        return new ColumnChunkReaderImpl(columnChunk,
                metadataMap.get(key),
                channelsProvider,
                rootPath,
                type,
                offsetIndex,
                fieldTypes,
                numRows(),
                version);
    }

    @Override
    public long numRows() {
        return rowGroup.num_rows;
    }

    @Override
    public RowGroup getRowGroup() {
        return rowGroup;
    }
}
