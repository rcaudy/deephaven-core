/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.parquet.base;

import io.deephaven.util.SafeCloseable;
import org.apache.parquet.column.statistics.Statistics;
import org.jetbrains.annotations.NotNull;
import org.apache.parquet.column.statistics.Statistics;

import java.io.IOException;
import java.nio.IntBuffer;

/**
 * Implementations of this are responsible for encoding pages of data into Parquet file columns
 */
public interface ColumnWriter extends SafeCloseable {
    /**
     * Add a page of data that does not contain null values.
     *
     * @param pageData the raw page data
     * @param valuesCount the count of values in the page.
     * @param statistics the
     * @throws IOException if there is an error writing values.
     */
    void addPageNoNulls(@NotNull Object pageData, int valuesCount, @NotNull Statistics<?> statistics)
            throws IOException;

    /**
     * Add a page of dictionary data to the column.
     *
     * @param dictionaryValues the values in the dictionary
     * @param valuesCount the count of values
     * @throws IOException if there is an error writing dictionary values.
     */
    void addDictionaryPage(@NotNull Object dictionaryValues, int valuesCount) throws IOException;

    /**
     * Add a page of values which may contain null values.
     *
     * @param pageData the raw page data.
     * @param valuesCount the total count of items
     * @throws IOException if there is an error writing values.
     */
    void addPage(@NotNull Object pageData, int valuesCount, Statistics<?> statistics) throws IOException;

    /**
     * Encode a page of vector values.
     *
     * @param pageData the raw flattened page data
     * @param repeatCount an int buffer where each int is the length of a single source vector.
     * @param valuesCount the total number of vectors to encode
     * @throws IOException if there is an error writing values.
     */
    void addVectorPage(
            @NotNull Object pageData,
            @NotNull IntBuffer repeatCount,
            int valuesCount,
            @NotNull Statistics<?> statistics)
            throws IOException;

    /**
     * Reset the statistics for this column. This must be called between each row group.
     */
    void resetStats();

    /**
     * Get the {@link Statistics} object into which to encode min/max/null count information for the footer.
     *
     * @return the statistics object
     */
    @NotNull
    Statistics<?> getStats();
}
