//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.util;

import io.deephaven.base.ClassUtil;
import io.deephaven.base.Pair;
import io.deephaven.base.clock.Clock;
import io.deephaven.base.verify.Require;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.exceptions.ArgumentException;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.RowSetFactory;
import io.deephaven.engine.table.*;
import io.deephaven.engine.table.impl.InMemoryTable;
import io.deephaven.engine.table.impl.perf.QueryPerformanceRecorder;
import io.deephaven.engine.table.impl.sources.NullValueColumnSource;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.time.DateTimeUtils;
import io.deephaven.engine.table.impl.QueryTable;
import io.deephaven.engine.table.impl.TimeTable;
import io.deephaven.engine.table.impl.replay.Replayer;
import io.deephaven.engine.table.impl.replay.ReplayerInterface;
import io.deephaven.engine.table.impl.sources.ArrayBackedColumnSource;
import io.deephaven.engine.table.impl.sources.ReinterpretUtils;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.chunk.*;
import io.deephaven.engine.table.impl.util.*;
import io.deephaven.io.logger.Logger;
import io.deephaven.io.util.NullOutputStream;
import io.deephaven.util.annotations.ScriptApi;
import io.deephaven.util.type.ArrayTypeUtils;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.security.DigestOutputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.time.Instant;
import java.time.ZoneId;
import java.util.*;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.stream.Collector;
import java.util.stream.Collectors;

import static io.deephaven.engine.table.impl.TableDefaults.ZERO_LENGTH_TABLE_ARRAY;

/**
 * Tools for working with tables. This includes methods to examine tables, combine them, convert them to and from CSV
 * files, and create and manipulate columns.
 */
@SuppressWarnings("unused")
public class TableTools {

    private static final Logger staticLog_ = LoggerFactory.getLogger(TableTools.class);

    // Public so it can be used from user scripts
    @SuppressWarnings("WeakerAccess")
    public static final String NULL_STRING = "(null)";

    private static <T> BinaryOperator<T> throwingMerger() {
        return (u, v) -> {
            throw new IllegalStateException(String.format("Duplicate key %s", u));
        };
    }

    private static <T, K, U> Collector<T, ?, LinkedHashMap<K, U>> toLinkedMap(
            Function<? super T, ? extends K> keyMapper,
            Function<? super T, ? extends U> valueMapper) {
        return Collectors.toMap(keyMapper, valueMapper, throwingMerger(), LinkedHashMap::new);
    }

    private static final Collector<ColumnHolder<?>, ?, LinkedHashMap<String, ColumnSource<?>>> COLUMN_HOLDER_LINKEDMAP_COLLECTOR =
            toLinkedMap(ColumnHolder::getName, ColumnHolder::getColumnSource);

    /////////// Utilities To Display Tables /////////////////
    // region Show Utilities

    /**
     * Prints the first few rows of a table to standard output.
     *
     * @param source a Deephaven table object
     * @param columns varargs of column names to display
     */
    public static void show(Table source, String... columns) {
        show(source, 10, DateTimeUtils.timeZone(), System.out, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, and also prints the details of the row keys and row
     * positions that provided the values.
     *
     * @param source a Deephaven table object
     * @param columns varargs of column names to display
     */
    public static void showWithRowSet(Table source, String... columns) {
        showWithRowSet(source, 10, DateTimeUtils.timeZone(), System.out, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, with commas between values.
     *
     * @param source a Deephaven table object
     * @param columns varargs of column names to display
     */
    public static void showCommaDelimited(Table source, String... columns) {
        show(source, 10, DateTimeUtils.timeZone(), ",", System.out, false, columns);
    }

    /**
     * Prints the first few rows of a table to standard output.
     *
     * @param source a Deephaven table object
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param columns varargs of column names to display
     */
    public static void show(Table source, ZoneId timeZone, String... columns) {
        show(source, 10, timeZone, System.out, columns);
    }

    /**
     * Prints the first few rows of a table to standard output.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param columns varargs of column names to display
     */
    public static void show(Table source, long maxRowCount, String... columns) {
        show(source, maxRowCount, DateTimeUtils.timeZone(), System.out, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, and also prints the details of the row keys and row
     * positions that provided the values.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param columns varargs of column names to display
     */
    public static void showWithRowSet(Table source, long maxRowCount, String... columns) {
        showWithRowSet(source, maxRowCount, DateTimeUtils.timeZone(), System.out, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, with commas between values.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param columns varargs of column names to display
     */
    public static void showCommaDelimited(Table source, long maxRowCount, String... columns) {
        show(source, maxRowCount, DateTimeUtils.timeZone(), ",", System.out, false, columns);
    }

    /**
     * Prints the first few rows of a table to standard output.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param columns varargs of column names to display
     */
    public static void show(Table source, long maxRowCount, ZoneId timeZone,
            String... columns) {
        show(source, maxRowCount, timeZone, System.out, columns);
    }

    /**
     * Prints the first few rows of a table to standard output.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param out a PrintStream destination to which to print the data
     * @param columns varargs of column names to display
     */
    public static void show(Table source, long maxRowCount, ZoneId timeZone, PrintStream out,
            String... columns) {
        show(source, maxRowCount, timeZone, "|", out, false, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, and also prints the details of the row keys and row
     * positions that provided the values.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param out a PrintStream destination to which to print the data
     * @param columns varargs of column names to display
     */
    public static void showWithRowSet(Table source, long maxRowCount, ZoneId timeZone,
            PrintStream out,
            String... columns) {
        show(source, maxRowCount, timeZone, "|", out, true, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, and also prints the details of the row keys and row
     * positions that provided the values.
     *
     * @param source a Deephaven table object
     * @param firstRow the firstRow to display
     * @param lastRow the lastRow (exclusive) to display
     * @param out a PrintStream destination to which to print the data
     * @param columns varargs of column names to display
     */
    public static void showWithRowSet(Table source, long firstRow, long lastRow, PrintStream out, String... columns) {
        TableShowTools.showInternal(source, firstRow, lastRow, DateTimeUtils.timeZone(), "|", out,
                true, columns);
    }

    /**
     * Prints the first few rows of a table to standard output.
     *
     * @param source a Deephaven table object
     * @param maxRowCount the number of rows to return
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param delimiter a String value to use between printed values
     * @param out a PrintStream destination to which to print the data
     * @param showRowSet a boolean indicating whether to also print rowSet details
     * @param columns varargs of column names to display
     */
    public static void show(final Table source, final long maxRowCount, final ZoneId timeZone,
            final String delimiter, final PrintStream out, final boolean showRowSet, String... columns) {
        TableShowTools.showInternal(source, 0, maxRowCount, timeZone, delimiter, out, showRowSet, columns);
    }

    /**
     * Prints the first few rows of a table to standard output, and also prints the details of the row keys and row
     * positions that provided the values.
     *
     * @param source a Deephaven table object
     * @param firstRow the firstRow to display
     * @param lastRow the lastRow (exclusive) to display
     * @param columns varargs of column names to display
     */
    public static void showWithRowSet(final Table source, final long firstRow, final long lastRow,
            final String... columns) {
        TableShowTools.showInternal(source, firstRow, lastRow, DateTimeUtils.timeZone(), "|",
                System.out, true, columns);
    }

    /**
     * Returns the first few rows of a table as a pipe-delimited string.
     *
     * @param t a Deephaven table object
     * @param columns varargs of columns to include in the result
     * @return a String
     */
    public static String string(Table t, String... columns) {
        return string(t, 10, DateTimeUtils.timeZone(), columns);
    }

    /**
     * Returns the first few rows of a table as a pipe-delimited string.
     *
     * @param t a Deephaven table object
     * @param size the number of rows to return
     * @param columns varargs of columns to include in the result
     * @return a String
     */
    public static String string(Table t, int size, String... columns) {
        return string(t, size, DateTimeUtils.timeZone(), columns);
    }

    /**
     * Returns the first few rows of a table as a pipe-delimited string.
     *
     * @param t a Deephaven table object
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param columns varargs of columns to include in the result
     * @return a String
     */
    public static String string(Table t, ZoneId timeZone, String... columns) {
        return string(t, 10, timeZone, columns);
    }

    /**
     * Returns the first few rows of a table as a pipe-delimited string.
     *
     * @param table a Deephaven table object
     * @param size the number of rows to return
     * @param timeZone a time zone constant relative to which date time data should be adjusted
     * @param columns varargs of columns to include in the result
     * @return a String
     */
    public static String string(
            @NotNull final Table table,
            final int size,
            final ZoneId timeZone,
            @NotNull final String... columns) {
        try (final ByteArrayOutputStream bytes = new ByteArrayOutputStream();
                final PrintStream printStream = new PrintStream(bytes, false, StandardCharsets.UTF_8)) {
            TableTools.show(table, size, timeZone, printStream, columns);
            printStream.flush();
            return bytes.toString(StandardCharsets.UTF_8);
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }

    /**
     * Returns a printout of a table formatted as HTML. Limit use to small tables to avoid running out of memory.
     *
     * @param source a Deephaven table object
     * @return a String of the table printout formatted as HTML
     */
    public static String html(Table source) {
        return HtmlTable.html(source);
    }
    // endregion

    // region Diff Utilities

    /**
     * Computes the difference of two tables for use in verification.
     *
     * @param actualResult first Deephaven table object to compare
     * @param expectedResult second Deephaven table object to compare
     * @param maxDiffLines stop comparing after this many differences are found
     * @return String report of the detected differences
     */
    public static String diff(Table actualResult, Table expectedResult, long maxDiffLines) {
        return diff(actualResult, expectedResult, maxDiffLines, EnumSet.noneOf(TableDiff.DiffItems.class));
    }

    /**
     * Computes the difference of two tables for use in verification.
     *
     * @param actualResult first Deephaven table object to compare
     * @param expectedResult second Deephaven table object to compare
     * @param maxDiffLines stop comparing after this many differences are found
     * @param itemsToSkip EnumSet of checks not to perform, such as checking column order, or exact match of double
     *        values
     * @return String report of the detected differences
     */
    public static String diff(Table actualResult, Table expectedResult, long maxDiffLines,
            EnumSet<TableDiff.DiffItems> itemsToSkip) {
        return TableDiff.diffInternal(actualResult, expectedResult, maxDiffLines, itemsToSkip).getFirst();
    }

    /**
     * Computes the difference of two tables for use in verification.
     *
     * @param actualResult first Deephaven table object to compare
     * @param expectedResult second Deephaven table object to compare
     * @param maxDiffLines stop comparing after this many differences are found
     * @param itemsToSkip EnumSet of checks not to perform, such as checking column order, or exact match of double
     *        values
     * @return a pair of String report of the detected differences, and the first different row (0 if there are no
     *         different data values)
     */
    public static Pair<String, Long> diffPair(Table actualResult, Table expectedResult, long maxDiffLines,
            EnumSet<TableDiff.DiffItems> itemsToSkip) {
        return TableDiff.diffInternal(actualResult, expectedResult, maxDiffLines, itemsToSkip);
    }
    // endregion

    public static String nullToNullString(Object obj) {
        return obj == null ? NULL_STRING : obj.toString();
    }

    /////////// Utilities for Creating Columns ///////////

    /**
     * Creates an in-memory column of the specified type for a collection of values.
     *
     * @param clazz the class to use for the new column
     * @param values a collection of values to populate the new column
     * @param <T> the type to use for the new column
     * @return a Deephaven ColumnSource object
     */
    public static <T> ColumnSource<T> colSource(Class<T> clazz, Collection<T> values) {
        WritableColumnSource<T> result = ArrayBackedColumnSource.getMemoryColumnSource(values.size(), clazz);
        int resultIndex = 0;
        for (T value : values) {
            result.set(resultIndex++, value);
        }
        return result;
    }

    /**
     * Creates an in-memory column of the specified type for a collection of values
     *
     * @param values a collection of values to populate the new column
     * @param <T> the type to use for the new column
     * @return a Deephaven ColumnSource object
     */
    @SuppressWarnings("unchecked")
    public static <T> ColumnSource<T> objColSource(T... values) {
        WritableColumnSource<T> result = (WritableColumnSource<T>) ArrayBackedColumnSource
                .getMemoryColumnSource(values.length, values.getClass().getComponentType());
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type long for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Long> colSource(long... values) {
        WritableColumnSource<Long> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, long.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type int for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Integer> colSource(int... values) {
        WritableColumnSource<Integer> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, int.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type short for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Short> colSource(short... values) {
        WritableColumnSource<Short> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, short.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type byte for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Byte> colSource(byte... values) {
        WritableColumnSource<Byte> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, byte.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type char for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Character> colSource(char... values) {
        WritableColumnSource<Character> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, char.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type double for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Double> colSource(double... values) {
        WritableColumnSource<Double> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, double.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Creates an in-memory column of type float for a collection of values.
     *
     * @param values a collection of values to populate the new column
     * @return a Deephaven ColumnSource object
     */
    public static ColumnSource<Float> colSource(float... values) {
        WritableColumnSource<Float> result =
                ArrayBackedColumnSource.getMemoryColumnSource(values.length, float.class);
        for (int i = 0; i < values.length; i++) {
            result.set(i, values[i]);
        }
        return result;
    }

    /**
     * Returns a ColumnHolder that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @param <T> the type of the column
     * @return a Deephaven ColumnHolder object
     */
    public static <T> ColumnHolder<T> col(String name, T... data) {
        if (data.getClass().getComponentType() == Long.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) longCol(name, ArrayTypeUtils.getUnboxedArray((Long[]) data));
        } else if (data.getClass().getComponentType() == Integer.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) intCol(name, ArrayTypeUtils.getUnboxedArray((Integer[]) data));
        } else if (data.getClass().getComponentType() == Short.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) shortCol(name, ArrayTypeUtils.getUnboxedArray((Short[]) data));
        } else if (data.getClass().getComponentType() == Byte.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) byteCol(name, ArrayTypeUtils.getUnboxedArray((Byte[]) data));
        } else if (data.getClass().getComponentType() == Character.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) charCol(name, ArrayTypeUtils.getUnboxedArray((Character[]) data));
        } else if (data.getClass().getComponentType() == Double.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) doubleCol(name, ArrayTypeUtils.getUnboxedArray((Double[]) data));
        } else if (data.getClass().getComponentType() == Float.class) {
            // noinspection unchecked
            return (ColumnHolder<T>) floatCol(name, ArrayTypeUtils.getUnboxedArray((Float[]) data));
        }
        // noinspection unchecked
        return new ColumnHolder<T>(name, (Class<T>) data.getClass().getComponentType(),
                data.getClass().getComponentType().getComponentType(), false, data);
    }

    /**
     * Returns a ColumnHolder of type String that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<String> stringCol(String name, String... data) {
        // NB: IntelliJ says that we do not need to cast data, but javac warns about this statement otherwise
        // noinspection RedundantCast
        return new ColumnHolder<>(name, String.class, null, false, (String[]) data);
    }

    /**
     * Returns a ColumnHolder of type Instant that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Instant> instantCol(String name, Instant... data) {
        // NB: IntelliJ says that we do not need to cast data, but javac warns about this statement otherwise
        // noinspection RedundantCast
        return new ColumnHolder<>(name, Instant.class, null, false, (Instant[]) data);
    }

    /**
     * Returns a ColumnHolder of type Boolean that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Boolean> booleanCol(String name, Boolean... data) {
        // NB: IntelliJ says that we do not need to cast data, but javac warns about this statement otherwise
        // noinspection RedundantCast
        return new ColumnHolder<>(name, Boolean.class, null, false, (Boolean[]) data);
    }

    /**
     * Returns a ColumnHolder of type long that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Long> longCol(String name, long... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /**
     * Returns a ColumnHolder of type int that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Integer> intCol(String name, int... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /**
     * Returns a ColumnHolder of type short that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Short> shortCol(String name, short... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /**
     * Returns a ColumnHolder of type byte that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Byte> byteCol(String name, byte... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /**
     * Returns a ColumnHolder of type char that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Character> charCol(String name, char... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /**
     * Returns a ColumnHolder of type double that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Double> doubleCol(String name, double... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /**
     * Returns a ColumnHolder of type float that can be used when creating in-memory tables.
     *
     * @param name name of the column
     * @param data a list of values for the column
     * @return a Deephaven ColumnHolder object
     */
    public static ColumnHolder<Float> floatCol(String name, float... data) {
        return new ColumnHolder<>(name, false, data);
    }

    /////////// Utilities For Creating Tables /////////////////

    /**
     * Returns a new, empty Deephaven Table.
     *
     * @param size the number of rows to allocate space for
     * @return a Deephaven Table with no columns.
     */
    public static Table emptyTable(long size) {
        return new QueryTable(RowSetFactory.flat(size).toTracking(), Collections.emptyMap()) {
            {
                setFlat();
            }

            @Override
            public String getDescription() {
                return "emptyTable(" + size + ")";
            }
        };
    }

    @SuppressWarnings("SameParameterValue")
    private static <MT extends Map<KT, VT>, KT, VT> MT newMapFromLists(Class<MT> mapClass, List<KT> keys,
            List<VT> values) {
        Require.eq(keys.size(), "keys.size()", values.size(), "values.size()");
        MT result;
        try {
            result = mapClass.newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            throw new RuntimeException(e);
        }
        for (int i = 0; i < keys.size(); ++i) {
            result.put(keys.get(i), values.get(i));
        }
        return result;
    }

    /**
     * Creates a new Table.
     *
     * @param size the number of rows to allocate
     * @param names a List of column names
     * @param columnSources a List of the ColumnSource(s)
     * @return a Deephaven Table
     */
    public static Table newTable(long size, List<String> names, List<ColumnSource<?>> columnSources) {
        // noinspection unchecked
        return newTable(size, newMapFromLists(LinkedHashMap.class, names, columnSources));
    }

    /**
     * Creates a new Table.
     *
     * @param size the number of rows to allocate
     * @param columns a Map of column names and ColumnSources
     * @return a Deephaven Table
     */
    public static Table newTable(long size, Map<String, ColumnSource<?>> columns) {
        for (final Map.Entry<String, ColumnSource<?>> entry : columns.entrySet()) {
            final String columnName = entry.getKey();
            if (entry.getValue() == null) {
                throw new ArgumentException("Column source for " + columnName + " is null");
            }
        }
        return new QueryTable(RowSetFactory.flat(size).toTracking(), columns) {
            {
                setFlat();
            }
        };
    }

    /**
     * Creates a new Table.
     *
     * @param definition the TableDefinition (column names and properties) to use for the new table
     * @return an empty Deephaven Table
     */
    public static Table newTable(TableDefinition definition) {
        Map<String, ColumnSource<?>> columns = new LinkedHashMap<>();
        for (ColumnDefinition<?> columnDefinition : definition.getColumns()) {
            columns.put(columnDefinition.getName(), NullValueColumnSource.getInstance(
                    columnDefinition.getDataType(), columnDefinition.getComponentType()));
        }
        return new QueryTable(definition, RowSetFactory.empty().toTracking(), columns) {
            {
                setFlat();
            }
        };
    }

    /**
     * Creates a new Table.
     *
     * @param columnHolders a list of ColumnHolders from which to create the table
     * @return a Deephaven Table
     */
    public static Table newTable(ColumnHolder<?>... columnHolders) {
        checkSizes(columnHolders);
        WritableRowSet rowSet = getRowSet(columnHolders);
        Map<String, ColumnSource<?>> columns = Arrays.stream(columnHolders).collect(COLUMN_HOLDER_LINKEDMAP_COLLECTOR);
        QueryTable queryTable = new QueryTable(rowSet.toTracking(), columns);
        queryTable.setFlat();
        return queryTable;
    }

    public static Table newTable(TableDefinition definition, ColumnHolder<?>... columnHolders) {
        return newTable(definition, null, columnHolders);
    }

    public static Table newTable(TableDefinition definition, @Nullable Map<String, Object> attributes,
            ColumnHolder<?>... columnHolders) {
        checkSizes(columnHolders);
        final WritableRowSet rowSet = getRowSet(columnHolders);
        final LinkedHashMap<String, ColumnSource<?>> columns =
                Arrays.stream(columnHolders).collect(COLUMN_HOLDER_LINKEDMAP_COLLECTOR);
        final QueryTable queryTable = new QueryTable(definition, rowSet.toTracking(), columns, null, attributes);
        queryTable.setFlat();
        return queryTable;
    }

    /**
     * Creates a metadata {@link Table} representing the columns in {@code definition}. Will include the following
     * columns:
     * <dl>
     * <dt>Name</dt>
     * <dd>{@link ColumnDefinition#getName()}</dd>
     * <dt>DataType</dt>
     * <dd>From {@link ColumnDefinition#getDataType()}, result of {@link Class#getCanonicalName()} if non-{@code null},
     * else {@link Class#getName()}</dd>
     * <dt>ColumnType</dt>
     * <dd>{@code ColumnDefinition#getColumnType()}</dd>
     * <dt>IsPartitioning</dt>
     * <dd>{@link ColumnDefinition#isPartitioning()}</dd>
     * </dl>
     *
     * @param definition the definition
     * @return the metadata Table
     */
    public static Table metaTable(TableDefinition definition) {
        List<String> columnNames = new ArrayList<>();
        List<String> columnDataTypes = new ArrayList<>();
        List<String> columnTypes = new ArrayList<>();
        List<Boolean> columnPartitioning = new ArrayList<>();
        for (ColumnDefinition<?> cDef : definition.getColumns()) {
            columnNames.add(cDef.getName());
            final Class<?> dataType = cDef.getDataType();
            final String dataTypeName = dataType.getCanonicalName();
            columnDataTypes.add(dataTypeName == null ? dataType.getName() : dataTypeName);
            columnTypes.add(cDef.getColumnType().name());
            columnPartitioning.add(cDef.isPartitioning());
        }
        final String[] resultColumnNames = {"Name", "DataType", "ColumnType", "IsPartitioning"};
        final Object[] resultValues = {
                columnNames.toArray(String[]::new),
                columnDataTypes.toArray(String[]::new),
                columnTypes.toArray(String[]::new),
                columnPartitioning.toArray(new Boolean[0]),
        };
        return new InMemoryTable(resultColumnNames, resultValues);
    }

    private static void checkSizes(ColumnHolder<?>[] columnHolders) {
        final int[] sizes = Arrays.stream(columnHolders).mapToInt(ColumnHolder::size).toArray();
        if (Arrays.stream(sizes).anyMatch(size -> size != sizes[0])) {
            throw new IllegalArgumentException(
                    "All columns must have the same number of rows, but sizes are: " + Arrays.toString(sizes));
        }
    }

    private static WritableRowSet getRowSet(ColumnHolder<?>[] columnHolders) {
        return columnHolders.length == 0 ? RowSetFactory.empty()
                : RowSetFactory.flat(columnHolders[0].size());
    }

    // region Time tables

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param period time interval between new row additions.
     * @return time table
     */
    public static Table timeTable(String period) {
        return timeTable(period, (ReplayerInterface) null);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param period time interval between new row additions
     * @param replayer data replayer
     * @return time table
     */
    public static Table timeTable(String period, ReplayerInterface replayer) {
        final long periodValue = DateTimeUtils.parseDurationNanos(period);
        return timeTable(periodValue, replayer);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param period time interval between new row additions
     * @return time table
     */
    public static Table timeTable(Instant startTime, String period) {
        final long periodValue = DateTimeUtils.parseDurationNanos(period);
        return timeTable(startTime, periodValue);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param period time interval between new row additions
     * @param replayer data replayer
     * @return time table
     */
    public static Table timeTable(Instant startTime, String period, ReplayerInterface replayer) {
        final long periodValue = DateTimeUtils.parseDurationNanos(period);
        return timeTable(startTime, periodValue, replayer);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param period time interval between new row additions
     * @return time table
     */
    public static Table timeTable(String startTime, String period) {
        return timeTable(DateTimeUtils.parseInstant(startTime), period);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param period time interval between new row additions
     * @param replayer data replayer
     * @return time table
     */
    public static Table timeTable(String startTime, String period, ReplayerInterface replayer) {
        return timeTable(DateTimeUtils.parseInstant(startTime), period, replayer);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @return time table
     */
    public static Table timeTable(long periodNanos) {
        return timeTable(periodNanos, null);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @param replayer data replayer
     * @return time table
     */
    public static Table timeTable(long periodNanos, ReplayerInterface replayer) {
        return new TimeTable(ExecutionContext.getContext().getUpdateGraph(), Replayer.getClock(replayer),
                null, periodNanos, false);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @return time table
     */
    public static Table timeTable(Instant startTime, long periodNanos) {
        return new TimeTable(ExecutionContext.getContext().getUpdateGraph(), DateTimeUtils.currentClock(),
                startTime, periodNanos, false);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @param replayer data replayer
     * @return time table
     */
    public static Table timeTable(Instant startTime, long periodNanos, ReplayerInterface replayer) {
        return new TimeTable(ExecutionContext.getContext().getUpdateGraph(), Replayer.getClock(replayer),
                startTime, periodNanos, false);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @return time table
     */
    public static Table timeTable(String startTime, long periodNanos) {
        return timeTable(DateTimeUtils.parseInstant(startTime), periodNanos);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param startTime start time for adding new rows
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @param replayer data replayer
     * @return time table
     */
    public static Table timeTable(String startTime, long periodNanos, ReplayerInterface replayer) {
        return timeTable(DateTimeUtils.parseInstant(startTime), periodNanos, replayer);
    }

    /**
     * Creates a table that adds a new row on a regular interval.
     *
     * @param clock the clock
     * @param startTime start time for adding new rows
     * @param periodNanos time interval between new row additions in nanoseconds.
     * @return time table
     */
    public static Table timeTable(Clock clock, Instant startTime, long periodNanos) {
        return new TimeTable(ExecutionContext.getContext().getUpdateGraph(), clock, startTime, periodNanos, false);
    }

    /**
     * Creates a new time table builder.
     *
     * @return a time table builder
     */
    public static TimeTable.Builder timeTableBuilder() {
        return TimeTable.newBuilder();
    }

    // endregion time tables

    /////////// Utilities For Merging Tables /////////////////

    /**
     * Concatenates multiple Deephaven Tables into a single Table.
     *
     * <p>
     * The resultant table will have rows from the same table together, in the order they are specified as inputs.
     * </p>
     *
     * <p>
     * When ticking tables grow, they may run out of the 'pre-allocated' space for newly added rows. When more key-
     * space is needed, tables in higher key-space are shifted to yet higher key-space to make room for new rows. Shifts
     * are handled efficiently, but some downstream operations generate a linear O(n) amount of work per shifted row.
     * When possible, one should favor ordering the constituent tables first by static/non-ticking sources followed by
     * tables that are expected to grow at slower rates, and finally by tables that grow without bound.
     * </p>
     *
     * @param theList a List of Tables to be concatenated
     * @return a Deephaven table object
     */
    public static Table merge(List<Table> theList) {
        return merge(theList.toArray(ZERO_LENGTH_TABLE_ARRAY));
    }

    /**
     * Concatenates multiple Deephaven Tables into a single Table.
     *
     * <p>
     * The resultant table will have rows from the same table together, in the order they are specified as inputs.
     * </p>
     *
     * <p>
     * When ticking tables grow, they may run out of the 'pre-allocated' space for newly added rows. When more key-
     * space is needed, tables in higher key-space are shifted to yet higher key-space to make room for new rows. Shifts
     * are handled efficiently, but some downstream operations generate a linear O(n) amount of work per shifted row.
     * When possible, one should favor ordering the constituent tables first by static/non-ticking sources followed by
     * tables that are expected to grow at slower rates, and finally by tables that grow without bound.
     * </p>
     *
     * @param tables a Collection of Tables to be concatenated
     * @return a Deephaven table object
     */
    public static Table merge(Collection<Table> tables) {
        return merge(tables.toArray(ZERO_LENGTH_TABLE_ARRAY));
    }

    /**
     * Concatenates multiple Deephaven Tables into a single Table.
     *
     * <p>
     * The resultant table will have rows from the same table together, in the order they are specified as inputs.
     * </p>
     *
     * <p>
     * When ticking tables grow, they may run out of the 'pre-allocated' space for newly added rows. When more key-
     * space is needed, tables in higher key-space are shifted to yet higher key-space to make room for new rows. Shifts
     * are handled efficiently, but some downstream operations generate a linear O(n) amount of work per shifted row.
     * When possible, one should favor ordering the constituent tables first by static/non-ticking sources followed by
     * tables that are expected to grow at slower rates, and finally by tables that grow without bound.
     * </p>
     *
     * @param tables a list of Tables to be concatenated
     * @return a Deephaven table object
     */
    public static Table merge(Table... tables) {
        return QueryPerformanceRecorder.withNugget("merge", () -> {
            // TODO (deephaven/deephaven-core/issues/257): When we have a new Table proxy implementation, we should
            // reintroduce remote merge for proxies.
            // If all of the tables are proxies, then we should ship this request over rather than trying to do it
            // locally.
            // Table proxyMerge = io.deephaven.engine.util.TableTools.mergeByProxy(tables);
            // if (proxyMerge != null) {
            // return proxyMerge;
            // }

            final List<Table> tablesToMerge = TableToolsMergeHelper
                    .getTablesToMerge(Arrays.stream(tables), tables.length);
            if (tablesToMerge == null || tablesToMerge.isEmpty()) {
                throw new IllegalArgumentException("No non-null tables provided to merge");
            }
            return PartitionedTableFactory.ofTables(tablesToMerge.toArray(ZERO_LENGTH_TABLE_ARRAY)).merge();
        });
    }

    /**
     * Concatenates multiple sorted Deephaven Tables into a single Table sorted by the specified key column.
     * <p>
     * The input tables must each individually be sorted by keyColumn, otherwise results are undefined.
     *
     * @param tables sorted Tables to be concatenated
     * @param keyColumn the column to use when sorting the concatenated results
     * @return a Deephaven table object
     */
    public static Table mergeSorted(@SuppressWarnings("SameParameterValue") String keyColumn, Table... tables) {
        return mergeSorted(keyColumn, Arrays.asList(tables));
    }

    /**
     * Concatenates multiple sorted Deephaven Tables into a single Table sorted by the specified key column.
     * <p>
     * The input tables must each individually be sorted by keyColumn, otherwise results are undefined.
     *
     * @param tables a Collection of sorted Tables to be concatenated
     * @param keyColumn the column to use when sorting the concatenated results
     * @return a Deephaven table object
     */
    public static Table mergeSorted(String keyColumn, Collection<Table> tables) {
        return MergeSortedHelper.mergeSortedHelper(keyColumn, tables);
    }

    /////////// Other Utilities /////////////////

    /**
     * Produce a new table with all the columns of this table, in the same order, but with {@code double} and
     * {@code float} columns rounded to {@code long}s.
     *
     * @return The new {@code Table}, with all {@code double} and {@code float} columns rounded to {@code long}s.
     */
    @ScriptApi
    public static Table roundDecimalColumns(Table table) {
        final List<ColumnDefinition<?>> columnDefinitions = table.getDefinition().getColumns();
        Set<String> columnsToRound = new HashSet<>(columnDefinitions.size());
        for (ColumnDefinition<?> columnDefinition : columnDefinitions) {
            Class<?> type = columnDefinition.getDataType();
            if (type.equals(double.class) || type.equals(float.class)) {
                columnsToRound.add(columnDefinition.getName());
            }
        }
        return roundDecimalColumns(table, columnsToRound.toArray(String[]::new));
    }

    /**
     * Produce a new table with all the columns of this table, in the same order, but with all {@code double} and
     * {@code float} columns rounded to {@code long}s, except for the specified {@code columnsNotToRound}.
     *
     * @param columnsNotToRound The names of the {@code double} and {@code float} columns <i>not</i> to round to
     *        {@code long}s
     * @return The new {@code Table}, with columns modified as explained above
     */
    @ScriptApi
    public static Table roundDecimalColumnsExcept(Table table, String... columnsNotToRound) {
        Set<String> columnsNotToRoundSet = new HashSet<>(columnsNotToRound.length * 2);
        Collections.addAll(columnsNotToRoundSet, columnsNotToRound);

        final List<ColumnDefinition<?>> columnDefinitions = table.getDefinition().getColumns();
        Set<String> columnsToRound = new HashSet<>(columnDefinitions.size());
        for (ColumnDefinition<?> columnDefinition : columnDefinitions) {
            Class<?> type = columnDefinition.getDataType();
            String colName = columnDefinition.getName();
            if ((type.equals(double.class) || type.equals(float.class)) && !columnsNotToRoundSet.contains(colName)) {
                columnsToRound.add(colName);
            }
        }
        return roundDecimalColumns(table, columnsToRound.toArray(String[]::new));
    }

    /**
     * Produce a new table with all the columns of this table, in the same order, but with {@code double} and
     * {@code float} columns rounded to {@code long}s.
     *
     * @param columns The names of the {@code double} and {@code float} columns to round.
     * @return The new {@code Table}, with the specified columns rounded to {@code long}s.
     * @throws java.lang.IllegalArgumentException If {@code columns} is null, or if one of the specified {@code columns}
     *         is neither a {@code double} column nor a {@code float} column.
     */
    @ScriptApi
    public static Table roundDecimalColumns(Table table, String... columns) {
        if (columns == null) {
            throw new IllegalArgumentException("columns cannot be null");
        }
        List<String> updateDescriptions = new LinkedList<>();
        for (String colName : columns) {
            Class<?> colType = table.getDefinition().getColumn(colName).getDataType();
            if (!(colType.equals(double.class) || colType.equals(float.class)))
                throw new IllegalArgumentException("Column \"" + colName + "\" is not a decimal column!");
            updateDescriptions.add(colName + "=round(" + colName + ')');
        }
        return table.updateView(updateDescriptions.toArray(String[]::new));
    }

    /**
     * <p>
     * Compute the SHA256 hash of the input table.
     * </p>
     * <p>
     * The hash is computed using every value in each row, using toString for unrecognized objects. The hash also
     * includes the input table definition column names and types.
     * </p>
     *
     * @param source The table to fingerprint
     * @return The SHA256 hash of the table data and {@link TableDefinition}
     * @throws IOException If an error occurs during the hashing.
     */
    public static byte[] computeFingerprint(Table source) throws IOException {
        final MessageDigest md;
        try {
            md = MessageDigest.getInstance("SHA-256");
        } catch (NoSuchAlgorithmException e) {
            throw new IllegalStateException(
                    "Runtime does not suport SHA-256 hashing required for resultsTable fingerprints.", e);
        }

        final DataOutputStream osw = new DataOutputStream(new DigestOutputStream(new NullOutputStream(), md));

        for (final ColumnSource<?> col : source.getColumnSources()) {
            processColumnForFingerprint(source.getRowSet(), col, osw);
        }

        // Now add in the Table definition
        final TableDefinition def = source.getDefinition();
        for (final ColumnDefinition<?> cd : def.getColumns()) {
            osw.writeChars(cd.getName());
            osw.writeChars(cd.getDataType().getName());
        }

        return md.digest();
    }

    /**
     * <p>
     * Compute the SHA256 hash of the input table and return it in base64 string format.
     * </p>
     *
     * @param source The table to fingerprint
     * @return The SHA256 hash of the table data and {@link TableDefinition}
     * @throws IOException If an error occurs during the hashing.
     */
    public static String base64Fingerprint(Table source) throws IOException {
        return Base64.getEncoder().encodeToString(computeFingerprint(source));
    }

    private static void processColumnForFingerprint(RowSequence ok, ColumnSource<?> col, DataOutputStream outputStream)
            throws IOException {
        if (col.getType() == Instant.class) {
            // noinspection unchecked
            col = ReinterpretUtils.instantToLongSource((ColumnSource<Instant>) col);
        }

        final int chunkSize = 1 << 16;

        final ChunkType chunkType = col.getChunkType();
        switch (chunkType) {
            case Char:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final CharChunk<? extends Values> valuesChunk = col.getChunk(getContext, chunkOk).asCharChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeChar(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Byte:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final ByteChunk<? extends Values> valuesChunk = col.getChunk(getContext, chunkOk).asByteChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeByte(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Short:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final ShortChunk<? extends Values> valuesChunk =
                                col.getChunk(getContext, chunkOk).asShortChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeShort(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Int:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final IntChunk<? extends Values> valuesChunk = col.getChunk(getContext, chunkOk).asIntChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeInt(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Long:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final LongChunk<? extends Values> valuesChunk = col.getChunk(getContext, chunkOk).asLongChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeLong(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Float:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final FloatChunk<? extends Values> valuesChunk =
                                col.getChunk(getContext, chunkOk).asFloatChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeFloat(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Double:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final DoubleChunk<? extends Values> valuesChunk =
                                col.getChunk(getContext, chunkOk).asDoubleChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeDouble(valuesChunk.get(ii));
                        }
                    }
                }
                break;
            case Object:
                try (final ColumnSource.GetContext getContext = col.makeGetContext(chunkSize);
                        final RowSequence.Iterator rsIt = ok.getRowSequenceIterator()) {
                    while (rsIt.hasMore()) {
                        final RowSequence chunkOk = rsIt.getNextRowSequenceWithLength(chunkSize);
                        final ObjectChunk<?, ? extends Values> valuesChunk =
                                col.getChunk(getContext, chunkOk).asObjectChunk();
                        for (int ii = 0; ii < valuesChunk.size(); ++ii) {
                            outputStream.writeChars(Objects.toString(valuesChunk.get(ii).toString()));
                        }
                    }
                }
                break;
            default:
            case Boolean:
                throw new UnsupportedOperationException();
        }
    }

    public static String nullTypeAsString(final Class<?> dataType) {
        if (dataType == int.class) {
            return "NULL_INT";
        }
        if (dataType == long.class) {
            return "NULL_LONG";
        }
        if (dataType == char.class) {
            return "NULL_CHAR";
        }
        if (dataType == double.class) {
            return "NULL_DOUBLE";
        }
        if (dataType == float.class) {
            return "NULL_FLOAT";
        }
        if (dataType == short.class) {
            return "NULL_SHORT";
        }
        if (dataType == byte.class) {
            return "NULL_BYTE";
        }
        return "(" + dataType.getName() + ")" + " null";
    }

    public static Class<?> typeFromName(final String dataTypeStr) {
        final Class<?> dataType;
        try {
            dataType = ClassUtil.lookupClass(dataTypeStr);
        } catch (ClassNotFoundException e) {
            throw new IllegalArgumentException("Type " + dataTypeStr + " not known", e);
        }
        return dataType;
    }
}
