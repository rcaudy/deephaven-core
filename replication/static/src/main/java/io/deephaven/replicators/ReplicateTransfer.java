/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.replicators;

import java.io.IOException;

import static io.deephaven.replication.ReplicatePrimitiveCode.*;

public class ReplicateTransfer {
    private static final String PARQUET_INT_TRANSFER_PATH =
            "extensions/parquet/table/src/main/java/io/deephaven/parquet/table/transfer/IntTransfer.java";

    public static void main(String[] args) throws IOException {

        intToChar(PARQUET_INT_TRANSFER_PATH, null,
                "IntBuffer", "IntStatistics", "int rowCount", "int targetSize", "int ii");
        intToByte(PARQUET_INT_TRANSFER_PATH, null,
                "IntBuffer", "IntStatistics", "int rowCount", "int targetSize", "int ii");
        intToShort(PARQUET_INT_TRANSFER_PATH, null,
                "IntBuffer", "IntStatistics", "int rowCount", "int targetSize", "int ii");
        intToLong(PARQUET_INT_TRANSFER_PATH, null,
                "int rowCount", "int targetSize", "int ii");
        intToDouble(PARQUET_INT_TRANSFER_PATH, null,
                "int rowCount", "int targetSize", "int ii");
        intToFloat(PARQUET_INT_TRANSFER_PATH, null,
                "int rowCount", "int targetSize", "int ii");
    }
}
