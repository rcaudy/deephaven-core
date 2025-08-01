//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import com.google.common.collect.Lists;
import gnu.trove.list.TLongList;
import gnu.trove.list.array.TLongArrayList;
import io.deephaven.api.ColumnName;
import io.deephaven.api.RawString;
import io.deephaven.api.Selectable;
import io.deephaven.api.filter.Filter;
import io.deephaven.base.verify.Assert;
import io.deephaven.chunk.*;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.context.QueryScope;
import io.deephaven.engine.exceptions.CancellationException;
import io.deephaven.engine.exceptions.TableInitializationException;
import io.deephaven.engine.liveness.LivenessScopeStack;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.RowSetFactory;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.engine.rowset.chunkattributes.OrderedRowKeys;
import io.deephaven.engine.table.*;
import io.deephaven.engine.table.impl.chunkfilter.ChunkFilter;
import io.deephaven.engine.table.impl.chunkfilter.IntRangeComparator;
import io.deephaven.engine.table.impl.indexer.DataIndexer;
import io.deephaven.engine.table.impl.select.*;
import io.deephaven.engine.table.impl.sources.*;
import io.deephaven.engine.table.impl.util.JobScheduler;
import io.deephaven.engine.table.impl.verify.TableAssertions;
import io.deephaven.engine.table.vectors.ColumnVectors;
import io.deephaven.engine.testutil.*;
import io.deephaven.engine.testutil.QueryTableTestBase.TableComparator;
import io.deephaven.engine.testutil.filters.RowSetCapturingFilter;
import io.deephaven.engine.testutil.generator.*;
import io.deephaven.engine.testutil.junit4.EngineCleanup;
import io.deephaven.engine.testutil.sources.IntTestSource;
import io.deephaven.engine.util.PrintListener;
import io.deephaven.engine.util.TableTools;
import io.deephaven.gui.table.filters.Condition;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.time.DateTimeUtils;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.SafeCloseable;
import io.deephaven.util.annotations.ReflexiveUse;
import io.deephaven.util.datastructures.CachingSupplier;
import junit.framework.TestCase;
import org.apache.commons.lang3.mutable.MutableBoolean;
import org.apache.commons.lang3.mutable.MutableObject;
import org.junit.After;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.Test;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.time.Instant;
import java.time.ZonedDateTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.function.Consumer;
import java.util.function.IntUnaryOperator;
import java.util.function.LongConsumer;
import java.util.stream.IntStream;

import static io.deephaven.engine.testutil.TstUtils.*;
import static io.deephaven.engine.testutil.testcase.RefreshingTableTestCase.printTableUpdates;
import static io.deephaven.engine.testutil.testcase.RefreshingTableTestCase.simulateShiftAwareStep;
import static io.deephaven.engine.util.TableTools.*;
import static io.deephaven.time.DateTimeUtils.parseInstant;
import static org.junit.Assert.*;
import static org.junit.Assert.assertEquals;

public abstract class QueryTableWhereTest {
    private final Logger log = LoggerFactory.getLogger(QueryTableWhereTest.class);

    @Rule
    public final EngineCleanup base = new EngineCleanup();

    private boolean oldParallel;
    private boolean oldDisable;
    private int oldSegments;
    private long oldSize;

    @Before
    public void setUp() throws Exception {
        oldParallel = QueryTable.FORCE_PARALLEL_WHERE;
        oldDisable = QueryTable.DISABLE_PARALLEL_WHERE;
        oldSegments = QueryTable.PARALLEL_WHERE_SEGMENTS;
        oldSize = QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT;
    }

    @After
    public void tearDown() throws Exception {
        QueryTable.FORCE_PARALLEL_WHERE = oldParallel;
        QueryTable.DISABLE_PARALLEL_WHERE = oldDisable;
        QueryTable.PARALLEL_WHERE_SEGMENTS = oldSegments;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = oldSize;
    }

    @Test
    public void testWhere() {
        java.util.function.Function<String, WhereFilter> filter = ConditionFilter::createConditionFilter;

        final QueryTable table = testRefreshingTable(i(2, 4, 6).toTracking(),
                col("x", 1, 2, 3), col("y", 'a', 'b', 'c'));

        assertTableEquals(table.where("k%2 == 0"), table);
        assertTableEquals(table.where(filter.apply("k%2 == 0")), table);

        assertTableEquals(table.where("i%2 == 0"),
                testRefreshingTable(i(2, 6).toTracking(), col("x", 1, 3), col("y", 'a', 'c')));
        assertTableEquals(table.where(filter.apply("i%2 == 0")), testRefreshingTable(
                i(2, 6).toTracking(), col("x", 1, 3), col("y", 'a', 'c')));

        assertTableEquals(table.where("(y-'a') = 2"), testRefreshingTable(
                i(2).toTracking(), col("x", 3), col("y", 'c')));
        assertTableEquals(table.where(filter.apply("(y-'a') = 2")), testRefreshingTable(
                i(2).toTracking(), col("x", 3), col("y", 'c')));

        final QueryTable whereResult = (QueryTable) table.where(filter.apply("x%2 == 1"));
        final ShiftObliviousListener whereResultListener = base.newListenerWithGlobals(whereResult);
        whereResult.addUpdateListener(whereResultListener);
        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 6).toTracking(), col("x", 1, 3), col("y", 'a', 'c')));

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(table, i(7, 9), col("x", 4, 5), col("y", 'd', 'e'));
            table.notifyListeners(i(7, 9), i(), i());
        });

        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 6, 9).toTracking(), col("x", 1, 3, 5), col("y", 'a', 'c', 'e')));
        assertEquals(base.added, i(9));
        assertEquals(base.removed, i());
        assertEquals(base.modified, i());

        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(table, i(7, 9), col("x", 3, 10), col("y", 'e', 'd'));
            table.notifyListeners(i(), i(), i(7, 9));
        });

        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 6, 7).toTracking(), col("x", 1, 3, 3), col("y", 'a', 'c', 'e')));

        assertEquals(base.added, i(7));
        assertEquals(base.removed, i(9));
        assertEquals(base.modified, i());

        updateGraph.runWithinUnitTestCycle(() -> {
            removeRows(table, i(2, 6, 7));
            table.notifyListeners(i(), i(2, 6, 7), i());
        });

        assertTableEquals(testRefreshingTable(i().toTracking(), intCol("x"), charCol("y")), whereResult);

        assertEquals(base.added, i());
        assertEquals(base.removed, i(2, 6, 7));
        assertEquals(base.modified, i());

        updateGraph.runWithinUnitTestCycle(() -> {
            removeRows(table, i(9));
            addToTable(table, i(2, 4, 6), col("x", 1, 21, 3), col("y", 'a', 'x', 'c'));
            table.notifyListeners(i(2, 6), i(9), i(4));
        });

        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 4, 6).toTracking(), col("x", 1, 21, 3), col("y", 'a', 'x', 'c')));

        assertEquals(base.added, i(2, 4, 6));
        assertEquals(base.removed, i());
        assertEquals(base.modified, i());

    }

    @Test
    public void testFailedFilter() {
        final Table input = TableTools.newTable(stringCol("Date", "2025-05-14", "2025-05-30", "2025-06-02"));
        // This failed filter previously would double free a chunk. The double free Exception would have been
        // suppresssed by the filter exception. The validation here is simply validating that the check() on the
        // ReleaseTracker did not identify a double-free during execution.
        final Exception e = assertThrows(Exception.class, () -> input.where("Date>= 2025-05-15"));
        assertTrue(e.getMessage().contains(
                "Error while initializing where([Date>= 2025-05-15]): an exception occurred while performing the initial filter"));
        assertTrue(e.getCause().getMessage()
                .contains("java.lang.ClassCastException encountered in filter={ Date>= 2025-05-15 }"));
    }

    @Test
    public void testWhereBiggerTable() {
        final Table table = TableTools.emptyTable(100000).update("Sym=ii%2==0 ? `AAPL` : `BANANA`", "II=ii").select();
        final Table filtered = table.where("Sym = (`AAPL`)");
        assertTableEquals(TableTools.emptyTable(50000).update("Sym=`AAPL`", "II=ii*2"), filtered);
        showWithRowSet(filtered);
    }

    @Test
    public void testIandK() {
        final Table table = testRefreshingTable(i(2, 4, 6).toTracking(), intCol("x", 1, 2, 3));

        assertTableEquals(newTable(intCol("x", 2)), table.where("k=4"));
        assertTableEquals(newTable(intCol("x", 2, 3)), table.where("ii > 0"));
        assertTableEquals(newTable(intCol("x", 1)), table.where("i < 1"));
    }

    // adds a second clause
    @Test
    public void testWhereOneOfTwo() {
        final QueryTable table = testRefreshingTable(i(2, 4, 6, 8).toTracking(),
                col("x", 1, 2, 3, 4), col("y", 'a', 'b', 'c', 'f'));

        final QueryTable whereResult = (QueryTable) table.where(Filter.or(Filter.from("x%2 == 1", "y=='f'")));
        final ShiftObliviousListener whereResultListener = base.newListenerWithGlobals(whereResult);
        whereResult.addUpdateListener(whereResultListener);
        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 6, 8).toTracking(), col("x", 1, 3, 4), col("y", 'a', 'c', 'f')));

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(table, i(7, 9), col("x", 4, 5), col("y", 'd', 'e'));
            table.notifyListeners(i(7, 9), i(), i());
        });

        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 6, 8, 9).toTracking(),
                col("x", 1, 3, 4, 5),
                col("y", 'a', 'c', 'f', 'e')));
        assertEquals(base.added, i(9));
        assertEquals(base.removed, i());
        assertEquals(base.modified, i());

        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(table, i(7, 9), col("x", 3, 10), col("y", 'e', 'd'));
            table.notifyListeners(i(), i(), i(7, 9));
        });

        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 6, 7, 8).toTracking(),
                col("x", 1, 3, 3, 4),
                col("y", 'a', 'c', 'e', 'f')));

        assertEquals(base.added, i(7));
        assertEquals(base.removed, i(9));
        assertEquals(base.modified, i());

        updateGraph.runWithinUnitTestCycle(() -> {
            removeRows(table, i(2, 6, 7));
            table.notifyListeners(i(), i(2, 6, 7), i());
        });

        assertTableEquals(whereResult, testRefreshingTable(i(8).toTracking(), col("x", 4), col("y", 'f')));

        assertEquals(base.added, i());
        assertEquals(base.removed, i(2, 6, 7));
        assertEquals(base.modified, i());

        updateGraph.runWithinUnitTestCycle(() -> {
            removeRows(table, i(9));
            addToTable(table, i(2, 4, 6), col("x", 1, 21, 3), col("y", 'a', 'x', 'c'));
            table.notifyListeners(i(2, 6), i(9), i(4));
        });

        assertTableEquals(whereResult, testRefreshingTable(
                i(2, 4, 6, 8).toTracking(), col("x", 1, 21, 3, 4), col("y", 'a', 'x', 'c', 'f')));

        assertEquals(base.added, i(2, 4, 6));
        assertEquals(base.removed, i());
        assertEquals(base.modified, i());

        showWithRowSet(table);
        final Table usingStringArray = table.where(Filter.or(Filter.from("x%3 == 0", "y=='f'")));
        assertTableEquals(usingStringArray, testRefreshingTable(
                i(4, 6, 8).toTracking(), col("x", 21, 3, 4), col("y", 'x', 'c', 'f')));
    }

    @Test
    public void testWhereInDependency() {
        testWhereInDependencyInternal(false, false, true, true);
        testWhereInDependencyInternal(false, false, true, false);
        testWhereInDependencyInternal(false, false, false, true);
        testWhereInDependencyInternal(false, false, false, false);
    }

    @Test
    public void testWhereInDependencyIndexed() {
        testWhereInDependencyInternal(true, false, true, true);
        testWhereInDependencyInternal(true, false, true, false);
        testWhereInDependencyInternal(true, false, false, true);
        testWhereInDependencyInternal(true, false, false, false);

        testWhereInDependencyInternal(false, true, true, true);
        testWhereInDependencyInternal(false, true, true, false);
        testWhereInDependencyInternal(false, true, false, true);
        testWhereInDependencyInternal(false, true, false, false);

        testWhereInDependencyInternal(true, true, true, true);
        testWhereInDependencyInternal(true, true, true, false);
        testWhereInDependencyInternal(true, true, false, true);
        testWhereInDependencyInternal(true, true, false, false);
    }

    private void testWhereInDependencyInternal(
            boolean filterIndexed,
            boolean setIndexed,
            boolean sourceRefreshing,
            boolean setRefreshing) {

        final QueryTable tableToFilter = sourceRefreshing
                ? testRefreshingTable(i(10, 11, 12, 13, 14, 15).toTracking(), col("A", 1, 2, 3, 4, 5, 6),
                        col("B", 2, 4, 6, 8, 10, 12), col("C", 'a', 'b', 'c', 'd', 'e', 'f'))
                : testTable(i(10, 11, 12, 13, 14, 15).toTracking(), col("A", 1, 2, 3, 4, 5, 6),
                        col("B", 2, 4, 6, 8, 10, 12), col("C", 'a', 'b', 'c', 'd', 'e', 'f'));
        if (filterIndexed) {
            DataIndexer.getOrCreateDataIndex(tableToFilter, "A");
            DataIndexer.getOrCreateDataIndex(tableToFilter, "B");
        }

        final QueryTable setTable = setRefreshing
                ? testRefreshingTable(i(100, 101, 102).toTracking(), col("A", 1, 2, 3), col("B", 2, 4, 6))
                : testTable(i(100, 101, 102).toTracking(), col("A", 1, 2, 3), col("B", 2, 4, 6));
        final Table setTable1 = setTable.where("A > 2");
        final Table setTable2 = setTable.where("B > 6");
        if (setIndexed) {
            DataIndexer.getOrCreateDataIndex(setTable, "A");
            DataIndexer.getOrCreateDataIndex(setTable, "B");

            DataIndexer.getOrCreateDataIndex(setTable1, "A");
            DataIndexer.getOrCreateDataIndex(setTable1, "B");

            DataIndexer.getOrCreateDataIndex(setTable2, "A");
            DataIndexer.getOrCreateDataIndex(setTable2, "B");
        }

        final DynamicWhereFilter dynamicFilter1 =
                new DynamicWhereFilter((QueryTable) setTable1, true, MatchPairFactory.getExpressions("A"));
        final DynamicWhereFilter dynamicFilter2 =
                new DynamicWhereFilter((QueryTable) setTable2, true, MatchPairFactory.getExpressions("B"));

        final WhereFilter composedFilter = DisjunctiveFilter.makeDisjunctiveFilter(dynamicFilter1, dynamicFilter2);
        final Table composed = tableToFilter.where(composedFilter);

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.runWithinUnitTestCycle(() -> {
            TestCase.assertTrue(dynamicFilter1.satisfied(updateGraph.clock().currentStep()));
            TestCase.assertTrue(dynamicFilter2.satisfied(updateGraph.clock().currentStep()));
            TestCase.assertTrue(composed.satisfied(updateGraph.clock().currentStep()));
        });

        if (setRefreshing) {
            updateGraph.runWithinUnitTestCycle(() -> {
                addToTable(setTable, i(103), col("A", 5), col("B", 8));
                setTable.notifyListeners(i(103), i(), i());
            });

            TableTools.show(composed);

            final Table expected =
                    TableTools.newTable(intCol("A", 3, 4, 5), intCol("B", 6, 8, 10), charCol("C", 'c', 'd', 'e'));

            assertTableEquals(composed, expected);
        }
    }

    @Test
    public void testWhereInOptimalIndexSelectionWithNoneAvailable() {
        final Table lhs = emptyTable(10).update("Part=ii % 2 == 0 ? `Apple` : `Pie`", "Hello=ii", "Goodbye = `A`+ii");
        DataIndexer.getOrCreateDataIndex(lhs, "Part");
        final Table rhs = emptyTable(2).update("Hello=ii", "Goodbye = `A`+ii");
        final Table result = lhs.whereIn(rhs, "Goodbye");
        assertTableEquals(lhs.head(2), result);
    }

    @Test
    public void testWhereDynamicIn() {
        final QueryTable setTable = testRefreshingTable(i(2, 4, 6, 8).toTracking(), col("X", "A", "B", "C", "B"));
        final QueryTable filteredTable = testRefreshingTable(i(1, 2, 3, 4, 5).toTracking(),
                col("X", "A", "B", "C", "D", "E"));

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();

        final Table result = updateGraph.exclusiveLock().computeLocked(
                () -> filteredTable.whereIn(setTable, "X"));
        final Table resultInverse = updateGraph.exclusiveLock().computeLocked(
                () -> filteredTable.whereNotIn(setTable, "X"));
        show(result);
        assertEquals(3, result.size());
        assertArrayEquals(new String[] {"A", "B", "C"}, ColumnVectors.ofObject(result, "X", String.class).toArray());
        assertEquals(2, resultInverse.size());
        assertArrayEquals(new String[] {"D", "E"}, ColumnVectors.ofObject(resultInverse, "X", String.class).toArray());

        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(filteredTable, i(6), col("X", "A"));
            filteredTable.notifyListeners(i(6), i(), i());
        });
        show(result);
        assertEquals(4, result.size());
        assertArrayEquals(new String[] {"A", "B", "C", "A"},
                ColumnVectors.ofObject(result, "X", String.class).toArray());
        assertEquals(2, resultInverse.size());
        assertArrayEquals(new String[] {"D", "E"}, ColumnVectors.ofObject(resultInverse, "X", String.class).toArray());

        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(setTable, i(7), col("X", "D"));
            setTable.notifyListeners(i(7), i(), i());
        });
        showWithRowSet(result);
        assertEquals(5, result.size());
        assertArrayEquals(new String[] {"A", "B", "C", "D", "A"},
                ColumnVectors.ofObject(result, "X", String.class).toArray());
        assertEquals(1, resultInverse.size());
        assertArrayEquals(new String[] {"E"}, ColumnVectors.ofObject(resultInverse, "X", String.class).toArray());

        // Real modification to set table, followed by spurious modification to set table
        IntStream.range(0, 2).forEach(ri -> {
            updateGraph.runWithinUnitTestCycle(() -> {
                addToTable(setTable, i(7), col("X", "C"));
                setTable.notifyListeners(i(), i(), i(7));
            });
            showWithRowSet(result);
            assertEquals(4, result.size());
            assertArrayEquals(new String[] {"A", "B", "C", "A"},
                    ColumnVectors.ofObject(result, "X", String.class).toArray());
            assertEquals(2, resultInverse.size());
            assertArrayEquals(new String[] {"D", "E"},
                    ColumnVectors.ofObject(resultInverse, "X", String.class).toArray());
        });
    }

    @Test
    public void testWhereDynamicInIncremental() {
        testWhereDynamicIncrementalInternal(false, false, true, true);
        testWhereDynamicIncrementalInternal(false, false, true, false);
        testWhereDynamicIncrementalInternal(false, false, false, true);
        testWhereDynamicIncrementalInternal(false, false, false, false);
    }

    @Test
    public void testWhereDynamicInIncrementalIndexed() {
        testWhereDynamicIncrementalInternal(true, false, true, true);
        testWhereDynamicIncrementalInternal(true, false, true, false);
        testWhereDynamicIncrementalInternal(true, false, false, true);
        testWhereDynamicIncrementalInternal(true, false, false, false);

        testWhereDynamicIncrementalInternal(false, true, true, true);
        testWhereDynamicIncrementalInternal(false, true, true, false);
        testWhereDynamicIncrementalInternal(false, true, false, true);
        testWhereDynamicIncrementalInternal(false, true, false, false);

        testWhereDynamicIncrementalInternal(true, true, true, true);
        testWhereDynamicIncrementalInternal(true, true, true, false);
        testWhereDynamicIncrementalInternal(true, true, false, true);
        testWhereDynamicIncrementalInternal(true, true, false, false);
    }

    private static void testWhereDynamicIncrementalInternal(
            boolean filterIndexed,
            boolean setIndexed,
            boolean sourceRefreshing,
            boolean setRefreshing) {
        final ColumnInfo<?, ?>[] setInfo;
        final ColumnInfo<?, ?>[] filteredInfo;

        final int setSize = 100;
        final int filteredSize = 5000;
        final Random random = new Random(0);

        final String[] columnNames =
                new String[] {"Sym", "intCol", "doubleCol", "charCol", "byteCol", "floatCol", "longCol", "shortCol"};

        final QueryTable setTable = getTable(setRefreshing, setSize, random, setInfo = initColumnInfos(
                columnNames,
                new SetGenerator<>("aa", "bb"),
                new IntGenerator(0, 10),
                new DoubleGenerator(0, 100),
                new SetGenerator<>('a', 'b', 'c', 'd', 'e', 'f'),
                new ByteGenerator((byte) 0, (byte) 64),
                new SetGenerator<>(1.0f, 2.0f, 3.3f, null),
                new LongGenerator(0, 1000),
                new ShortGenerator((short) 500, (short) 600)));
        if (setIndexed) {
            // Add an index on every column but "doubleCol"
            for (final String columnName : columnNames) {
                if (!columnName.equals("doubleCol")) {
                    DataIndexer.getOrCreateDataIndex(setTable, columnName);
                }
            }
            // Add the multi-column index for "Sym", "intCol"
            DataIndexer.getOrCreateDataIndex(setTable, "Sym", "intCol");
        }

        final QueryTable filteredTable = getTable(sourceRefreshing, filteredSize, random,
                filteredInfo = initColumnInfos(
                        columnNames,
                        new SetGenerator<>("aa", "bb", "cc", "dd"),
                        new IntGenerator(0, 20),
                        new DoubleGenerator(0, 100),
                        new CharGenerator('a', 'z'),
                        new ByteGenerator((byte) 0, (byte) 127),
                        new SetGenerator<>(1.0f, 2.0f, 3.3f, null, 4.4f, 5.5f, 6.6f),
                        new LongGenerator(1500, 2500),
                        new ShortGenerator((short) 400, (short) 700)));

        if (filterIndexed) {
            // Add an index on every column but "doubleCol"
            for (final String columnName : columnNames) {
                if (!columnName.equals("doubleCol")) {
                    DataIndexer.getOrCreateDataIndex(filteredTable, columnName);
                }
            }
            // Add the multi-column index for "Sym", "intCol"
            DataIndexer.getOrCreateDataIndex(filteredTable, "Sym", "intCol");
        }

        final EvalNugget[] en = new EvalNugget[] {
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "Sym")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "Sym")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "Sym", "intCol")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "intCol", "Sym")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "charCol")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "byteCol")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "shortCol")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "intCol")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "longCol")),
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "floatCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "Sym", "intCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "intCol", "Sym")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "charCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "byteCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "shortCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "intCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "longCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "floatCol")),
        };

        validate(en);

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        for (int step = 0; step < 100; step++) {
            final boolean modSet = random.nextInt(10) < 1;
            final boolean modFiltered = random.nextBoolean();

            if (setRefreshing) {
                updateGraph.runWithinUnitTestCycle(() -> {
                    if (modSet) {
                        GenerateTableUpdates.generateShiftAwareTableUpdates(GenerateTableUpdates.DEFAULT_PROFILE,
                                setSize, random, setTable, setInfo);
                    }
                });
                validate(en);
            }

            if (sourceRefreshing) {
                updateGraph.runWithinUnitTestCycle(() -> {
                    if (modFiltered) {
                        GenerateTableUpdates.generateShiftAwareTableUpdates(GenerateTableUpdates.DEFAULT_PROFILE,
                                filteredSize, random, filteredTable, filteredInfo);
                    }
                });
                validate(en);
            }
        }
    }

    @Test
    public void testWhereInDynamicPartial() {
        testWhereInDynamicPartialIndexedInternal(true);
        testWhereInDynamicPartialIndexedInternal(false);
    }

    private void testWhereInDynamicPartialIndexedInternal(final boolean setRefreshing) {
        final ColumnInfo<?, ?>[] setInfo;
        final ColumnInfo<?, ?>[] filteredInfo;

        final int setSize = 100;
        final int filteredSize = 5000;
        final Random random = new Random(0);

        final String[] columnNames =
                new String[] {"Sym", "intCol", "doubleCol", "charCol", "byteCol", "floatCol", "longCol", "shortCol"};

        final QueryTable setTable = getTable(setRefreshing, setSize, random, setInfo = initColumnInfos(
                columnNames,
                new SetGenerator<>("aa", "bb"),
                new IntGenerator(0, 10),
                new DoubleGenerator(0, 100),
                new SetGenerator<>('a', 'b', 'c', 'd', 'e', 'f'),
                new ByteGenerator((byte) 0, (byte) 64),
                new SetGenerator<>(1.0f, 2.0f, 3.3f, null),
                new LongGenerator(0, 1000),
                new ShortGenerator((short) 500, (short) 600)));

        final QueryTable filteredTable = getTable(filteredSize, random, filteredInfo = initColumnInfos(
                columnNames,
                new SetGenerator<>("aa", "bb", "cc", "dd"),
                new IntGenerator(0, 20),
                new DoubleGenerator(0, 100),
                new CharGenerator('a', 'z'),
                new ByteGenerator((byte) 0, (byte) 127),
                new SetGenerator<>(1.0f, 2.0f, 3.3f, null, 4.4f, 5.5f, 6.6f),
                new LongGenerator(1500, 2500),
                new ShortGenerator((short) 400, (short) 700)));

        DataIndexer.getOrCreateDataIndex(filteredTable, "Sym");
        DataIndexer.getOrCreateDataIndex(filteredTable, "Sym", "charCol");
        DataIndexer.getOrCreateDataIndex(filteredTable, "Sym", "charCol", "longCol");
        DataIndexer.getOrCreateDataIndex(filteredTable, "Sym", "charCol", "longCol", "shortCol");

        final EvalNugget[] en = new EvalNugget[] {
                EvalNugget.from(() -> filteredTable.whereIn(setTable, "Sym", "intCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "Sym", "intCol")),

                EvalNugget.from(() -> filteredTable.whereIn(setTable, "intCol", "Sym")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "intCol", "Sym")),

                EvalNugget.from(() -> filteredTable.whereIn(setTable, "Sym", "charCol", "intCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "Sym", "charCol", "intCol")),

                EvalNugget.from(() -> filteredTable.whereIn(setTable, "intCol", "charCol", "Sym")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "intCol", "charCol", "Sym")),

                EvalNugget.from(() -> filteredTable.whereIn(setTable, "Sym", "charCol", "longCol", "byteCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "Sym", "charCol", "longCol", "byteCol")),

                EvalNugget.from(() -> filteredTable.whereIn(setTable, "charCol", "Sym", "byteCol", "longCol")),
                EvalNugget.from(() -> filteredTable.whereNotIn(setTable, "charCol", "Sym", "byteCol", "longCol")),

                EvalNugget.from(
                        () -> filteredTable.whereIn(setTable, "Sym", "charCol", "longCol", "shortCol", "byteCol")),
                EvalNugget.from(
                        () -> filteredTable.whereNotIn(setTable, "Sym", "charCol", "longCol", "shortCol", "byteCol")),

                EvalNugget.from(
                        () -> filteredTable.whereIn(setTable, "charCol", "Sym", "byteCol", "longCol", "shortCol")),
                EvalNugget.from(
                        () -> filteredTable.whereNotIn(setTable, "charCol", "Sym", "byteCol", "longCol", "shortCol")),

        };

        validate(en);

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        for (int step = 0; step < 100; step++) {
            final boolean modSet = random.nextInt(10) < 1;
            final boolean modFiltered = random.nextBoolean();

            if (setRefreshing) {
                updateGraph.runWithinUnitTestCycle(() -> {
                    if (modSet) {
                        GenerateTableUpdates.generateShiftAwareTableUpdates(GenerateTableUpdates.DEFAULT_PROFILE,
                                setSize, random, setTable, setInfo);
                    }
                });
                validate(en);
            }

            updateGraph.runWithinUnitTestCycle(() -> {
                if (modFiltered) {
                    GenerateTableUpdates.generateShiftAwareTableUpdates(GenerateTableUpdates.DEFAULT_PROFILE,
                            filteredSize, random, filteredTable, filteredInfo);
                }
            });
            validate(en);
        }
    }

    @Test
    public void testWhereRefresh() {
        final Table t1 = TableTools.newTable(col("A", "b", "c", "d"));
        assertFalse(t1.isRefreshing());
        final Table t2 = ExecutionContext.getContext().getUpdateGraph().exclusiveLock()
                .computeLocked(() -> t1.where("A in `b`"));
        assertFalse(t2.isRefreshing());
        final Table t3 =
                ExecutionContext.getContext().getUpdateGraph().exclusiveLock().computeLocked(() -> t1.whereIn(t1, "A"));
        assertFalse(t3.isRefreshing());

        final Random random = new Random(0);
        final QueryTable t4 = getTable(10, random, initColumnInfos(new String[] {"B"}, new SetGenerator<>("a", "b")));
        assertTrue(t4.isRefreshing());
        final Table t5 = ExecutionContext.getContext().getUpdateGraph().exclusiveLock()
                .computeLocked(() -> t4.where("B in `b`"));
        assertTrue(t5.isRefreshing());
        final Table t6 = ExecutionContext.getContext().getUpdateGraph().exclusiveLock()
                .computeLocked(() -> t4.whereIn(t1, "B=A"));
        assertTrue(t6.isRefreshing());

        final Table t7 = ExecutionContext.getContext().getUpdateGraph().exclusiveLock()
                .computeLocked(() -> t1.whereIn(t4, "A=B"));
        assertTrue(t7.isRefreshing());
    }

    @Test
    public void testWhereInDiamond() {
        final ColumnInfo<?, ?>[] filteredInfo;

        final int size = 500;
        final Random random = new Random(0);

        final QueryTable table = getTable(size, random,
                filteredInfo = initColumnInfos(new String[] {"Sym", "intCol", "intCol2"},
                        new SetGenerator<>("aa", "bb", "bc", "cc", "dd", "ee", "ff", "gg", "hh", "ii"),
                        new IntGenerator(0, 100),
                        new IntGenerator(0, 100)));

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        final EvalNugget[] en = new EvalNugget[] {
                EvalNugget.from(() -> updateGraph.exclusiveLock().computeLocked(
                        () -> table.whereIn(table.where("intCol % 25 == 0"), "intCol2=intCol"))),
        };

        try {
            for (int step = 0; step < 1000; step++) {
                updateGraph.runWithinUnitTestCycle(() -> GenerateTableUpdates.generateShiftAwareTableUpdates(
                        GenerateTableUpdates.DEFAULT_PROFILE, size, random, table, filteredInfo));
                validate(en);
            }
        } catch (Exception e) {
            TestCase.fail(e.getClass().getName() + ": " + e.getMessage());
        }
    }

    @Test
    public void testWhereInDiamond2() {
        final QueryTable table = testRefreshingTable(i(1, 2, 3).toTracking(), col("x", 1, 2, 3), col("y", 2, 4, 6));
        final Table setTable = table.where("x % 2 == 0").dropColumns("y");
        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        final Table filteredTable = updateGraph.exclusiveLock().computeLocked(
                () -> table.whereIn(setTable, "y=x"));

        TableTools.show(filteredTable);

        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(table, i(4), col("x", 4), col("y", 8));
            table.notifyListeners(i(4), i(), i());
        });

        TableTools.show(setTable);
        TableTools.show(filteredTable);
    }

    private static class TestUncoalescedTable extends UncoalescedTable<TestUncoalescedTable> {
        private final Table delegate;
        private final List<Collection<? extends Selectable>> selectDistinctColumns = new ArrayList<>();

        public TestUncoalescedTable(final Table delegate) {
            super(delegate.getDefinition(), "TestUncoalescedTable");
            this.delegate = delegate;
        }

        @Override
        protected Table doCoalesce() {
            return delegate.coalesce();
        }

        @Override
        protected TestUncoalescedTable copy() {
            return this;
        }

        @Override
        public Table selectDistinct(final Collection<? extends Selectable> columns) {
            selectDistinctColumns.add(columns);
            return super.selectDistinct(columns);
        }
    }

    @Test
    public void testWhereInUncoalesced() {
        final Table table = TableTools.newTable(intCol("x", 1, 2, 3), intCol("y", 2, 4, 6));
        final Table setTable = TableTools.newTable(intCol("x", 3));

        final Table expected = table.whereIn(setTable, "x");
        final Table result = table.whereIn(new TestUncoalescedTable(setTable), "x");
        assertTableEquals(expected, result);
    }

    @Test
    public void testWhereInUncoalescedPartitioned() {
        final Table table = TableTools.newTable(intCol("x", 1, 2, 3), intCol("y", 2, 4, 6));
        final Table setTableRaw = TableTools.newTable(intCol("x", 3), intCol("y", 2));
        final TableDefinition definition =
                TableDefinition.of(setTableRaw.getDefinition().getColumn("x").withPartitioning(),
                        setTableRaw.getDefinition().getColumn("y"));
        final Table setTable = new QueryTable(definition, setTableRaw.getRowSet(), setTableRaw.getColumnSourceMap());

        final Table expected1 = table.whereIn(setTable, "x");
        final Table expected2 = table.whereIn(setTable, "y");

        final TestUncoalescedTable uncoalesced = new TestUncoalescedTable(setTable);
        final Table resultPart = table.whereIn(uncoalesced, "x");
        assertTableEquals(expected1, resultPart);
        assertEquals(1, uncoalesced.selectDistinctColumns.size());
        assertEquals(List.of(ColumnName.of("x")), uncoalesced.selectDistinctColumns.get(0));
        uncoalesced.selectDistinctColumns.clear();

        final Table resultNoPart = table.whereIn(uncoalesced, "y");
        assertTableEquals(expected2, resultNoPart);
        assertEquals(0, uncoalesced.selectDistinctColumns.size());
    }

    @Test
    public void testWhereNotInEmpty() {
        final Table x = newTable(intCol("X", 1, 2, 3));
        final Table emptyX = newTable(intCol("X"));
        final Table xWhereNotIn = x.whereNotIn(emptyX, "X");
        assertTableEquals(x, xWhereNotIn);

        final int[] emptyArray = new int[0];
        QueryScope.addParam("emptyArray", emptyArray);
        final Table expressionNot = x.where("X not in emptyArray");
        assertTableEquals(x, expressionNot);

        final Table xWhereIn = x.whereIn(emptyX, "X");
        assertTableEquals(emptyX, xWhereIn);

        final Table expressionIn = x.where("X in emptyArray");
        assertTableEquals(emptyX, expressionIn);
        QueryScope.addParam("emptyArray", null);
    }

    @Test
    public void testWhereOneOfIncremental() {

        final ColumnInfo<?, ?>[] filteredInfo;

        final int setSize = 10;
        final int filteredSize = 500;
        final Random random = new Random(0);

        final QueryTable filteredTable = getTable(setSize, random,
                filteredInfo = initColumnInfos(new String[] {"Sym", "intCol", "doubleCol"},
                        new SetGenerator<>("aa", "bb", "bc", "cc", "dd", "ee", "ff", "gg", "hh", "ii"),
                        new IntGenerator(0, 100),
                        new DoubleGenerator(0, 100)));

        final EvalNugget[] en = new EvalNugget[] {
                EvalNugget.from(() -> filteredTable.where(
                        Filter.or(Filter.from("Sym in `aa`, `ee`", "intCol % 2 == 0")))),
                EvalNugget.from(() -> filteredTable.where(Filter.or(
                        Filter.and(Filter.from("intCol % 2 == 0", "intCol % 2 == 1")),
                        RawString.of("Sym in `aa`, `ee`")))),
                EvalNugget.from(() -> filteredTable.where(Filter.or(
                        Filter.and(Filter.from("intCol % 2 == 0", "Sym in `aa`, `ii`")),
                        RawString.of("Sym in `aa`, `ee`")))),
                EvalNugget.from(() -> filteredTable.where(Filter.or(
                        RawString.of("intCol % 2 == 0"),
                        RawString.of("intCol % 2 == 1"),
                        RawString.of("Sym in `aa`, `ee`")))),
        };

        try {
            final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
            for (int i = 0; i < 100; i++) {
                log.debug().append("Step = " + i).endl();

                updateGraph.runWithinUnitTestCycle(() -> GenerateTableUpdates.generateShiftAwareTableUpdates(
                        GenerateTableUpdates.DEFAULT_PROFILE, filteredSize, random, filteredTable, filteredInfo));
                validate(en);
            }
        } catch (Exception e) {
            TestCase.fail(e.getMessage());
        }
    }

    @Test
    public void testWhereWithExcessiveShifting() {
        // Select a prime that guarantees shifts from the merge operations.
        final int PRIME = 61409;
        assertTrue(2 * PRIME > UnionRedirection.ALLOCATION_UNIT_ROW_KEYS);

        final ColumnInfo<?, ?>[] filteredInfo;

        final int setSize = 10;
        final int filteredSize = 500;
        final Random random = new Random(0);

        final QueryTable growingTable = testRefreshingTable(i(1).toTracking(), col("intCol", 1));
        final QueryTable randomTable = getTable(setSize, random, filteredInfo = initColumnInfos(new String[] {"intCol"},
                new IntGenerator(0, 1 << 8)));
        final Table m2 = TableTools.merge(growingTable, randomTable).updateView("intCol=intCol*53");

        final EvalNugget[] en = new EvalNugget[] {
                EvalNugget.from(() -> TableTools.merge(growingTable, randomTable)),
                EvalNugget.from(() -> TableTools.merge(growingTable, m2).where("intCol % 3 == 0")),
        };

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        for (int ii = 1; ii < 100; ++ii) {
            final int fii = PRIME * ii;
            updateGraph.runWithinUnitTestCycle(() -> {
                addToTable(growingTable, i(fii), col("intCol", fii));
                growingTable.notifyListeners(i(fii), i(), i());
                GenerateTableUpdates.generateShiftAwareTableUpdates(GenerateTableUpdates.DEFAULT_PROFILE, filteredSize,
                        random, randomTable, filteredInfo);
            });
            validate(en);
        }
    }

    @Test
    public void testWhereBoolean() {
        final Random random = new Random(0);
        final int size = 10;

        final ColumnInfo<?, ?>[] columnInfo;
        final QueryTable filteredTable = getTable(size, random,
                columnInfo = initColumnInfos(new String[] {"Sentinel", "boolCol", "nullBoolCol"},
                        new IntGenerator(0, 10000),
                        new BooleanGenerator(0.5),
                        new BooleanGenerator(0.5, 0.2)));

        final EvalNugget[] en = new EvalNugget[] {
                EvalNugget.from(() -> filteredTable.where("boolCol")),
                EvalNugget.from(() -> filteredTable.where("!boolCol")),
                EvalNugget.from(() -> SparseSelect.sparseSelect(filteredTable).where("boolCol")),
                EvalNugget.from(() -> SparseSelect.sparseSelect(filteredTable).sort("Sentinel").where("boolCol")),
                EvalNugget.from(
                        () -> SparseSelect.sparseSelect(filteredTable).sort("Sentinel").reverse().where("boolCol")),
                EvalNugget.from(() -> filteredTable.updateView("boolCol2=!!boolCol").where("boolCol2")),
        };

        for (int step = 0; step < 100; ++step) {
            simulateShiftAwareStep(size, random, filteredTable, columnInfo, en);
        }
    }

    private static class SleepCounter implements IntUnaryOperator {
        final int sleepDurationNanos;
        AtomicLong invokes = new AtomicLong();
        CountDownLatch latch = new CountDownLatch(1);

        private SleepCounter(int sleepDurationNanos) {
            this.sleepDurationNanos = sleepDurationNanos;
        }

        @Override
        public int applyAsInt(int value) {
            if (sleepDurationNanos > 0) {
                final long start = System.nanoTime();
                final long end = start + sleepDurationNanos;
                // noinspection StatementWithEmptyBody
                while (System.nanoTime() < end);
            }
            if (invokes.incrementAndGet() == 1) {
                latch.countDown();
            }
            return value;
        }

        void reset() {
            invokes = new AtomicLong();
            latch = new CountDownLatch(1);
        }
    }

    private static class TestChunkFilter implements ChunkFilter {
        final CountDownLatch latch = new CountDownLatch(1);
        final ChunkFilter actualFilter;
        final long sleepDurationNanos;
        long invokes;
        long invokedValues;

        private TestChunkFilter(ChunkFilter actualFilter, long sleepDurationNanos) {
            this.actualFilter = actualFilter;
            this.sleepDurationNanos = sleepDurationNanos;
        }

        @Override
        public void filter(
                final Chunk<? extends Values> values,
                final LongChunk<OrderedRowKeys> keys,
                final WritableLongChunk<OrderedRowKeys> results) {
            if (++invokes == 1) {
                latch.countDown();
            }
            invokedValues += values.size();
            if (sleepDurationNanos > 0) {
                long nanos = sleepDurationNanos * values.size();
                final long start = System.nanoTime();
                final long end = start + nanos;
                // noinspection StatementWithEmptyBody
                while (System.nanoTime() < end);
            }
            actualFilter.filter(values, keys, results);
        }

        @Override
        public int filter(
                final Chunk<? extends Values> values,
                final WritableBooleanChunk<Values> results) {
            if (++invokes == 1) {
                latch.countDown();
            }
            invokedValues += values.size();
            if (sleepDurationNanos > 0) {
                long nanos = sleepDurationNanos * values.size();
                final long timeStart = System.nanoTime();
                final long timeEnd = timeStart + nanos;
                // noinspection StatementWithEmptyBody
                while (System.nanoTime() < timeEnd);
            }
            return actualFilter.filter(values, results);
        }

        @Override
        public int filterAnd(
                final Chunk<? extends Values> values,
                final WritableBooleanChunk<Values> results) {
            if (++invokes == 1) {
                latch.countDown();
            }
            invokedValues += values.size();
            if (sleepDurationNanos > 0) {
                long nanos = sleepDurationNanos * values.size();
                final long timeStart = System.nanoTime();
                final long timeEnd = timeStart + nanos;
                // noinspection StatementWithEmptyBody
                while (System.nanoTime() < timeEnd);
            }
            return actualFilter.filterAnd(values, results);
        }

        void reset() {
            invokes = invokedValues = 0;
        }
    }

    @Test
    public void testInterFilterInterruption() {
        final Table tableToFilter = TableTools.emptyTable(2_000_000).update("X=i");

        final SleepCounter slowCounter = new SleepCounter(2);
        final SleepCounter fastCounter = new SleepCounter(0);

        QueryScope.addParam("slowCounter", slowCounter);
        QueryScope.addParam("fastCounter", fastCounter);

        final long start = System.currentTimeMillis();
        final Table filtered = tableToFilter.where(
                "slowCounter.applyAsInt(X) % 2 == 0", "fastCounter.applyAsInt(X) % 3 == 0");
        final long end = System.currentTimeMillis();
        log.debug().append("Duration: " + (end - start)).endl();

        assertTableEquals(tableToFilter.where("X%6==0"), filtered);

        assertEquals(2_000_000, slowCounter.invokes.get());
        assertEquals(1_000_000, fastCounter.invokes.get());

        fastCounter.reset();
        slowCounter.reset();

        final MutableObject<Exception> caught = new MutableObject<>();
        final ExecutionContext executionContext = ExecutionContext.getContext();
        final Thread t = new Thread(() -> {
            final long start1 = System.currentTimeMillis();
            try (final SafeCloseable ignored = executionContext.open()) {
                tableToFilter.where(Filter.and(
                        RawString.of("slowCounter.applyAsInt(X) % 2 == 0").withSerial(),
                        RawString.of("fastCounter.applyAsInt(X) % 3 == 0").withSerial()));
            } catch (Exception e) {
                log.error().append("extra thread caught ").append(e).endl();
                caught.setValue(e);
            }
            final long end1 = System.currentTimeMillis();
            log.debug().append("Duration: " + (end1 - start1)).endl();
        });
        t.start();

        waitForLatch(slowCounter.latch);

        t.interrupt();

        try {
            final long timeout_ms = 300_000; // 5 min
            t.join(timeout_ms);
            if (t.isAlive()) {
                throw new RuntimeException("Thread did not terminate within " + timeout_ms + " ms");
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        if (QueryTable.FORCE_PARALLEL_WHERE) {
            assertTrue(slowCounter.invokes.get() > 0);
        } else {
            assertEquals(2_000_000, slowCounter.invokes.get());
        }

        // we want to make sure we can push something through the thread pool and are not hogging it
        final CountDownLatch latch = new CountDownLatch(1);
        ExecutionContext.getContext().getOperationInitializer().submit(latch::countDown);
        waitForLatch(latch);

        assertEquals(0, fastCounter.invokes.get());
        Throwable err = caught.getValue();
        assertNotNull(err);
        assertEquals(TableInitializationException.class, err.getClass());
        err = err.getCause();
        assertEquals(CancellationException.class, err.getClass());

        QueryScope.addParam("slowCounter", null);
        QueryScope.addParam("fastCounter", null);
    }

    private void waitForLatch(CountDownLatch latch) {
        try {
            if (!latch.await(50000, TimeUnit.MILLISECONDS)) {
                throw new IllegalStateException("Latch never reached zero!");
            }
        } catch (InterruptedException ignored) {
        }
    }

    @Test
    public void testChunkFilterInterruption() {
        final Table tableToFilter = TableTools.emptyTable(2_000_000).update("X=i");

        final TestChunkFilter slowCounter =
                new TestChunkFilter(IntRangeComparator.makeIntFilter(0, 1_000_000, true, false), 100);

        QueryScope.addParam("slowCounter", slowCounter);

        final long start = System.currentTimeMillis();
        final RowSet result =
                ChunkFilter.applyChunkFilter(tableToFilter.getRowSet(), tableToFilter.getColumnSource("X"),
                        false, slowCounter);
        final long end = System.currentTimeMillis();
        log.debug().append("Duration: " + (end - start)).endl();

        assertEquals(RowSetFactory.fromRange(0, 999_999), result);

        assertEquals(2_000_000, slowCounter.invokedValues);
        slowCounter.reset();

        final MutableObject<Exception> caught = new MutableObject<>();
        final ExecutionContext executionContext = ExecutionContext.getContext();
        final Thread t = new Thread(() -> {
            final long start1 = System.currentTimeMillis();
            try (final SafeCloseable ignored = executionContext.open()) {
                ChunkFilter.applyChunkFilter(tableToFilter.getRowSet(), tableToFilter.getColumnSource("X"), false,
                        slowCounter);
            } catch (Exception e) {
                caught.setValue(e);
            }
            final long end1 = System.currentTimeMillis();
            log.debug().append("Duration: " + (end1 - start1)).endl();
        });
        t.start();

        waitForLatch(slowCounter.latch);

        t.interrupt();

        try {
            t.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        log.debug().append("Invoked Values: " + slowCounter.invokedValues).endl();
        log.debug().append("Invokes: " + slowCounter.invokes).endl();

        assertTrue(slowCounter.invokedValues < 2_000_000L);
        assertEquals(1 << 20, slowCounter.invokedValues);
        assertNotNull(caught.getValue());
        assertEquals(CancellationException.class, caught.getValue().getClass());

        QueryScope.addParam("slowCounter", null);
    }

    @ReflexiveUse(referrers = "QueryTableWhereTest.class")
    public static BigInteger convertToBigInteger(long value) {
        return value == QueryConstants.NULL_LONG ? null : BigInteger.valueOf(value);
    }

    private static Table multiplyAssertSorted(Table table, SortingOrder order, String... columns) {
        for (String colName : columns) {
            table = TableAssertions.assertSorted(table, colName, order);
        }
        return table;
    }

    @Test
    public void testComparableBinarySearch() {
        final Random random = new Random(0);

        final int size = 100;

        final ColumnInfo<?, ?>[] columnInfo;
        final QueryTable table = getTable(size, random,
                columnInfo = initColumnInfos(new String[] {"BD1", "D2", "L3", "CH", "DT"},
                        new BigDecimalGenerator(BigInteger.ONE, BigInteger.TEN),
                        new DoubleGenerator(0.0, 100.0, 0, 0, 0, 0),
                        new LongGenerator(-100, 100, 0.01),
                        new CharGenerator('A', 'Z', 0.1),
                        new UnsortedInstantGenerator(DateTimeUtils.parseInstant("2020-01-01T00:00:00 NY"),
                                DateTimeUtils.parseInstant("2020-01-01T01:00:00 NY"))));
        final String bigIntConversion = "BI4=" + getClass().getCanonicalName() + ".convertToBigInteger(L3)";
        final Table augmentedInts =
                table.update(bigIntConversion, "D5=(double)L3", "I6=(int)L3", "S7=(short)L3", "B8=(byte)L3");
        final Table augmentedFloats = table.update("F6=(float)D2");

        final Table sortedBD1 = table.sort("BD1");
        final Table sortedDT = table.sort("DT");
        final Table sortedCH = table.sort("CH");
        final Table sortedD2 = multiplyAssertSorted(augmentedFloats.sort("D2"), SortingOrder.Ascending, "F6");
        final Table sortedL3 =
                multiplyAssertSorted(augmentedInts.sort("L3"), SortingOrder.Ascending, "BI4", "D5", "I6", "S7", "B8");
        final Table sortedBD1R = table.sortDescending("BD1");
        final Table sortedD2R =
                multiplyAssertSorted(augmentedFloats.sortDescending("D2"), SortingOrder.Descending, "F6");
        final Table sortedL3R = multiplyAssertSorted(augmentedInts.sortDescending("L3"), SortingOrder.Descending, "BI4",
                "D5", "I6", "S7", "B8");

        final BigDecimal two = BigDecimal.valueOf(2);
        final BigDecimal nine = BigDecimal.valueOf(9);
        final String filterTimeString = "2020-01-01T00:30:00 NY";
        final Instant filterTime = DateTimeUtils.parseInstant(filterTimeString);

        QueryScope.addParam("two", two);
        QueryScope.addParam("nine", nine);

        final EvalNuggetInterface[] en = new EvalNuggetInterface[] {
                new TableComparator(sortedBD1.where("BD1.compareTo(two) > 0 && BD1.compareTo(nine) < 0"),
                        sortedBD1.where(ComparableRangeFilter.makeForTest("BD1", two, nine, false, false))),
                new TableComparator(sortedD2.where("D2 > 50 && D2 < 75"),
                        sortedD2.where(new DoubleRangeFilter("D2", 50.0, 75.0, false, false))),
                new TableComparator(sortedL3.where("L3 > -50 && L3 < 80"),
                        sortedL3.where(new LongRangeFilter("L3", -50, 80, false, false))),
                new TableComparator(sortedL3.where("L3 > -50 && L3 <= 80"),
                        sortedL3.where(new LongRangeFilter("L3", -50, 80, false, true))),
                new TableComparator(sortedL3.where("L3 >= -50 && L3 < 80"),
                        sortedL3.where(new LongRangeFilter("L3", -50, 80, true, false))),
                new TableComparator(sortedL3.where("L3 >= -50 && L3 <= 80"),
                        sortedL3.where(new LongRangeFilter("L3", -50, 80, true, true))),
                new TableComparator(sortedL3.where("L3 * 2 >= -100"), sortedL3.where("L3 >= -50")),
                new TableComparator(sortedL3.where("L3 * 2 > -100"), sortedL3.where("L3 > -50")),
                new TableComparator(sortedL3.where("L3 * 2 < -100"), sortedL3.where("L3 < -50")),
                new TableComparator(sortedL3.where("L3 * 2 <= -100"), sortedL3.where("L3 <= -50")),
                new TableComparator(sortedBD1R.where("BD1.compareTo(two) > 0 && BD1.compareTo(nine) < 0"),
                        sortedBD1R.where(ComparableRangeFilter.makeForTest("BD1", two, nine, false, false))),
                new TableComparator(sortedD2R.where("D2 > 50 && D2 < 75"),
                        sortedD2R.where(new DoubleRangeFilter("D2", 50.0, 75.0, false, false))),
                new TableComparator(sortedD2R.where("D2 > 50 && D2 <= 75"), sortedD2R.where("F6 > 50", "F6 <= 75")),
                new TableComparator(sortedL3R.where("L3 > -50 && L3 < 80"),
                        sortedL3R.where(new LongRangeFilter("L3", -50, 80, false, false))),
                new TableComparator(sortedL3R.where("L3 > -50 && L3 <= 80"),
                        sortedL3R.where(new LongRangeFilter("L3", -50, 80, false, true))),
                new TableComparator(sortedL3R.where("L3 >= -50 && L3 < 80"),
                        sortedL3R.where(new LongRangeFilter("L3", -50, 80, true, false))),
                new TableComparator(sortedL3R.where("L3 >= -50 && L3 <= 80"),
                        sortedL3R.where(new LongRangeFilter("L3", -50, 80, true, true))),
                new TableComparator(sortedL3R.where("L3 * 2 >= -100"), sortedL3R.where("L3 >= -50")),
                new TableComparator(sortedL3R.where("L3 * 2 > -100"), sortedL3R.where("L3 > -50")),
                new TableComparator(sortedL3R.where("L3 * 2 < -100"), sortedL3R.where("L3 < -50")),
                new TableComparator(sortedL3R.where("L3 * 2 <= -100"), sortedL3R.where("L3 <= -50")),
                new TableComparator(sortedL3.where("L3 >= -50"), sortedL3.where("D5 >= -50")),
                new TableComparator(sortedL3.where("L3 > -100"), sortedL3.where("D5 > -100")),
                new TableComparator(sortedL3.where("L3 < -50"), sortedL3.where("D5 < -50")),
                new TableComparator(sortedL3.where("L3 <= -50"), sortedL3.where("D5 <= -50")),
                new TableComparator(sortedL3.where("L3 > 10 && L3 < 20"),
                        sortedL3.where(ComparableRangeFilter.makeForTest("BI4", BigInteger.valueOf(10),
                                BigInteger.valueOf(20), false, false))),
                new TableComparator(sortedL3R.where("L3 > 10 && L3 < 20"),
                        sortedL3R.where(ComparableRangeFilter.makeForTest("BI4", BigInteger.valueOf(10),
                                BigInteger.valueOf(20), false, false))),
                new TableComparator(sortedL3.where("L3 <= 20"), "L3", sortedL3.where("BI4 <= 20"), "BI4"),
                new TableComparator(sortedL3R.where("L3 > 20"), "L3", sortedL3R.where("BI4 > 20"), "BI4"),
                new TableComparator(sortedL3.where("L3 < 20"), "L3", sortedL3.where("BI4 < 20"), "BI4"),
                new TableComparator(sortedL3R.where("L3 >= 20"), "L3", sortedL3R.where("BI4 >= 20"), "BI4"),
                new TableComparator(sortedL3R.where("L3 >= 20 && true"), sortedL3R.where("I6 >= 20")),
                new TableComparator(sortedL3R.where("L3 >= 20 && true"), sortedL3R.where("B8 >= 20")),
                new TableComparator(sortedL3R.where("L3 >= 20 && true"), sortedL3R.where("S7 >= 20")),
                new TableComparator(sortedL3R.where("L3 < 20 && true"), sortedL3R.where("I6 < 20")),
                new TableComparator(sortedL3R.where("L3 < 20 && true"), sortedL3R.where("B8 < 20")),
                new TableComparator(sortedL3R.where("L3 < 20 && true"), sortedL3R.where("S7 < 20")),
                new TableComparator(
                        sortedDT.where("epochNanos(DT) < " + DateTimeUtils.epochNanos(filterTime)),
                        sortedDT.where("DT < '" + filterTimeString + "'")),
                new TableComparator(
                        sortedDT.where("epochNanos(DT) >= " + DateTimeUtils.epochNanos(filterTime)),
                        sortedDT.where("DT >= '" + filterTimeString + "'")),
                new TableComparator(sortedCH.where("true && CH > 'M'"), sortedCH.where("CH > 'M'")),
                new TableComparator(sortedCH.where("CH==null || CH <= 'O'"), sortedCH.where("CH <= 'O'")),
                new TableComparator(sortedCH.where("true && CH >= 'Q'"), sortedCH.where("CH >= 'Q'")),
                new TableComparator(sortedCH.where("true && CH < 'F'"), sortedCH.where("CH < 'F'")),
        };

        for (int step = 0; step < 500; step++) {
            if (printTableUpdates) {
                System.out.print("Step = " + step);
            }
            simulateShiftAwareStep(size, random, table, columnInfo, en);
        }

        QueryScope.addParam("two", null);
        QueryScope.addParam("nine", null);
    }

    @Test
    public void testZonedDateRangeFilter() {
        final ZonedDateTime startTime = DateTimeUtils.parseZonedDateTime("2021-04-23T09:30 NY");
        final ZonedDateTime[] array = new ZonedDateTime[10];
        for (int ii = 0; ii < array.length; ++ii) {
            array[ii] = DateTimeUtils.plus(startTime, 60_000_000_000L * ii);
        }
        final Table table = TableTools.newTable(col("ZDT", array));
        showWithRowSet(table);

        testRangeFilterHelper(table, "ZDT", array[5]);
    }

    @Test
    public void testInstantRangeFilter() {
        final Instant startTime = DateTimeUtils.parseInstant("2021-04-23T09:30 NY");
        final Instant[] array = new Instant[10];
        for (int ii = 0; ii < array.length; ++ii) {
            array[ii] = DateTimeUtils.plus(startTime, 60_000_000_000L * ii);
        }
        final Table table = TableTools.newTable(col("DT", array));
        showWithRowSet(table);

        testRangeFilterHelper(table, "DT", array[5]);
    }

    @Test
    public void testCharRangeFilter() {
        char[] array = new char[10];
        for (int ii = 0; ii < array.length; ++ii) {
            if (ii % 3 == 0) {
                array[ii] = (char) ('Z' - ii);
            } else if (ii % 2 == 0) {
                array[ii] = QueryConstants.NULL_CHAR;
            } else {
                array[ii] = (char) ('A' + ii);
            }
        }
        final Table table = TableTools.newTable(charCol("CH", array));
        showWithRowSet(table);

        testRangeFilterHelper(table, "CH", array[5]);
    }

    private <T> void testRangeFilterHelper(Table table, String name, T mid) {
        final Table sorted = table.sort(name);
        final Table backwards = table.sort(name);

        showWithRowSet(sorted);
        log.debug().append("Pivot: " + mid).endl();

        final Table rangeFiltered = sorted.where(name + " < '" + mid + "'");
        final Table standardFiltered = sorted.where("'" + mid + "' > " + name);

        showWithRowSet(rangeFiltered);
        showWithRowSet(standardFiltered);
        assertTableEquals(rangeFiltered, standardFiltered);
        assertTableEquals(backwards.where(name + " < '" + mid + "'"), backwards.where("'" + mid + "' > " + name));
        assertTableEquals(backwards.where(name + " <= '" + mid + "'"), backwards.where("'" + mid + "' >= " + name));
        assertTableEquals(backwards.where(name + " > '" + mid + "'"), backwards.where("'" + mid + "' < " + name));
        assertTableEquals(backwards.where(name + " >= '" + mid + "'"), backwards.where("'" + mid + "' <= " + name));
    }

    @Test
    public void testSingleSidedRangeFilterSimple() {
        final Table table = TableTools.emptyTable(10).update("L1=ii");
        final String bigIntConversion = "BI2=" + getClass().getCanonicalName() + ".convertToBigInteger(L1)";
        final Table augmented = table.update(bigIntConversion).sort("BI2");
        final Table augmentedBackwards = table.update(bigIntConversion).sortDescending("BI2");

        assertTableEquals(augmented.where("L1 < 5"), augmented.where("BI2 < 5"));
        assertTableEquals(augmented.where("L1 <= 5"), augmented.where("BI2 <= 5"));
        assertTableEquals(augmented.where("L1 > 5"), augmented.where("BI2 > 5"));
        assertTableEquals(augmented.where("L1 >= 5"), augmented.where("BI2 >= 5"));

        assertTableEquals(augmentedBackwards.where("L1 < 5"), augmentedBackwards.where("BI2 < 5"));
        assertTableEquals(augmentedBackwards.where("L1 <= 5"), augmentedBackwards.where("BI2 <= 5"));
        assertTableEquals(augmentedBackwards.where("L1 > 5"), augmentedBackwards.where("BI2 > 5"));
        assertTableEquals(augmentedBackwards.where("L1 >= 5"), augmentedBackwards.where("BI2 >= 5"));
    }

    @Test
    public void testComparableRangeFilter() {
        final Random random = new Random(0);

        final int size = 100;

        final ColumnInfo<?, ?>[] columnInfo;
        final QueryTable table = getTable(size, random,
                columnInfo = initColumnInfos(new String[] {"L1"}, new LongGenerator(90, 110, 0.1)));

        final String bigIntConversion = "BI2=" + getClass().getCanonicalName() + ".convertToBigInteger(L1)";
        final Table augmented = table.update(bigIntConversion);

        final EvalNuggetInterface[] en = new EvalNuggetInterface[] {
                new TableComparator(augmented.where("L1 > 100"), augmented.where("BI2 > 100")),
                new TableComparator(augmented.where("L1 < 100"), augmented.where("BI2 < 100")),
                new TableComparator(augmented.where("L1 >= 100"), augmented.where("BI2 >= 100")),
                new TableComparator(augmented.where("L1 <= 100"), augmented.where("BI2 <= 100")),

                new TableComparator(augmented.where("L1 > 100"),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), false, true))),
                new TableComparator(augmented.where("L1 < 100"),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), false, false))),
                new TableComparator(augmented.where("L1 >= 100"),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), true, true))),
                new TableComparator(augmented.where("L1 <= 100"),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), true, false))),

                new TableComparator(augmented.where("L1 > 95 && L1 <= 100"),
                        augmented.where(ComparableRangeFilter.makeForTest("BI2", BigInteger.valueOf(95),
                                BigInteger.valueOf(100), false, true))),
                new TableComparator(augmented.where("L1 > 95 && L1 < 100"),
                        augmented.where(ComparableRangeFilter.makeForTest("BI2", BigInteger.valueOf(95),
                                BigInteger.valueOf(100), false, false))),
                new TableComparator(augmented.where("L1 >= 95 && L1 < 100"),
                        augmented.where(ComparableRangeFilter.makeForTest("BI2", BigInteger.valueOf(95),
                                BigInteger.valueOf(100), true, false))),
                new TableComparator(augmented.where("L1 >= 95 && L1 <= 100"),
                        augmented.where(ComparableRangeFilter.makeForTest("BI2", BigInteger.valueOf(95),
                                BigInteger.valueOf(100), true, true))),
        };

        for (int i = 0; i < 500; i++) {
            simulateShiftAwareStep(size, random, table, columnInfo, en);
        }
    }

    @Test
    public void testComparableRangeFilterCopies() {
        final Random random = new Random(0);

        final int size = 100;

        final ColumnInfo<?, ?>[] columnInfo;
        final QueryTable table = getTable(size, random,
                columnInfo = initColumnInfos(new String[] {"L1"}, new LongGenerator(90, 110, 0.1)));

        final String bigIntConversion = "BI2=" + getClass().getCanonicalName() + ".convertToBigInteger(L1)";
        final Table augmented = table.update(bigIntConversion);

        final EvalNuggetInterface[] en = new EvalNuggetInterface[] {
                // Test the SingleSidedComparableRangeFilter against copies
                new TableComparator(
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), false, true)),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), false, true).copy())),
                new TableComparator(
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), false, false)),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), false, false).copy())),
                new TableComparator(
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), true, true)),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), true, true).copy())),
                new TableComparator(
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), true, false)),
                        augmented.where(SingleSidedComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(100), true, false).copy())),

                // Test the ComparableRangeFilter against copies
                new TableComparator(
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), false, true)),
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), false, true)
                                .copy())),
                new TableComparator(
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), false, false)),
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), false, false)
                                .copy())),
                new TableComparator(
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), true, true)),
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), true, true)
                                .copy())),
                new TableComparator(
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), true, false)),
                        augmented.where(ComparableRangeFilter
                                .makeForTest("BI2", BigInteger.valueOf(95), BigInteger.valueOf(100), true, false)
                                .copy())),
        };

        for (int i = 0; i < 500; i++) {
            simulateShiftAwareStep(size, random, table, columnInfo, en);
        }
    }

    @Test
    public void testBigTable() {
        final Table source = new QueryTable(
                RowSetFactory.flat(10_000_000L).toTracking(),
                Collections.singletonMap("A", RowKeyColumnSource.INSTANCE));
        final IncrementalReleaseFilter incrementalReleaseFilter = new IncrementalReleaseFilter(0, 1000000L);
        final Table filtered = source.where(incrementalReleaseFilter);
        final Table result = filtered.where("A >= 6_000_000L", "A < 7_000_000L");

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        while (filtered.size() < source.size()) {
            updateGraph.runWithinUnitTestCycle(incrementalReleaseFilter::run);
        }

        assertEquals(1_000_000, result.size());
        assertEquals(6_000_000L, result.getColumnSource("A").getLong(result.getRowSet().firstRowKey()));
        assertEquals(6_999_999L, result.getColumnSource("A").getLong(result.getRowSet().get(result.size() - 1)));
    }

    @Test
    public void testBigTableInitial() {
        final Table source = new QueryTable(
                RowSetFactory.flat(10_000_000L).toTracking(),
                Collections.singletonMap("A", RowKeyColumnSource.INSTANCE));
        final Table result = source.where("A >= 6_000_000L", "A < 7_000_000L");

        assertEquals(1_000_000, result.size());
        assertEquals(6_000_000L, result.getColumnSource("A").getLong(result.getRowSet().firstRowKey()));
        assertEquals(6_999_999L, result.getColumnSource("A").getLong(result.getRowSet().get(result.size() - 1)));
    }

    @Test
    public void testBigTableIndexed() {
        final Random random = new Random(0);
        final int size = 100_000;

        final QueryTable source = getTable(size, random,
                initColumnInfos(
                        new String[] {"A"},
                        new LongGenerator(0, 1000, 0.01)));
        DataIndexer.getOrCreateDataIndex(source, "A");

        final Table result = source.where("A >= 600", "A < 700");
        Table sorted = result.sort("A");
        show(sorted);

        Assert.geq(sorted.getColumnSource("A").getLong(sorted.getRowSet().firstRowKey()), "lowest value", 600, "600");
        Assert.leq(sorted.getColumnSource("A").getLong(sorted.getRowSet().get(result.size() - 1)), "highest value", 699,
                "699");
    }

    @Test
    public void testFilterErrorInitial() {
        final QueryTable table = testRefreshingTable(
                i(2, 4, 6, 8).toTracking(),
                col("x", 1, 2, 3, 4),
                col("y", "a", "b", "c", null));

        try {
            final QueryTable whereResult = (QueryTable) table.where("y.length() > 0");
            Assert.statementNeverExecuted("Expected exception not thrown.");
        } catch (Throwable e) {
            Assert.eqTrue(e instanceof TableInitializationException,
                    "TableInitializationException expected.");
            e = e.getCause();
            Assert.eqTrue(e instanceof FormulaEvaluationException
                    && e.getCause() != null && e.getCause() instanceof NullPointerException,
                    "NPE causing FormulaEvaluationException expected.");
        }
    }

    @Test
    public void testFilterErrorUpdate() {
        final QueryTable table = testRefreshingTable(
                i(2, 4, 6).toTracking(),
                col("x", 1, 2, 3),
                col("y", "a", "b", "c"));

        final QueryTable whereResult = (QueryTable) table.where("y.length() > 0");

        Assert.eqFalse(table.isFailed(), "table.isFailed()");
        Assert.eqFalse(whereResult.isFailed(), "whereResult.isFailed()");

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.runWithinUnitTestCycle(() -> {
            addToTable(table, i(8), col("x", 5), col("y", (String) null));
            table.notifyListeners(i(8), i(), i());
        });

        Assert.eqFalse(table.isFailed(), "table.isFailed()");

        // The where result should have failed, because the filter expression is invalid for the new data.
        Assert.eqTrue(whereResult.isFailed(), "whereResult.isFailed()");
    }

    @Test
    public void testMatchFilterFallback() {
        final Table table = emptyTable(10).update("X=i");
        ExecutionContext.getContext().getQueryScope().putParam("var1", 10);
        ExecutionContext.getContext().getQueryScope().putParam("var2", 20);

        final MutableBoolean called = new MutableBoolean(false);
        final MatchFilter filter = new MatchFilter(
                new CachingSupplier<>(() -> {
                    called.setValue(true);
                    return (ConditionFilter) ConditionFilter.createConditionFilter("var1 != var2");
                }),
                MatchFilter.CaseSensitivity.IgnoreCase, MatchFilter.MatchType.Inverted, "var1", "var2");

        final Table result = table.where(filter);
        assertTableEquals(table, result);

        Assert.eqTrue(called.booleanValue(), "called.booleanValue()");
    }

    @Test
    public void testRangeFilterFallback() {
        final Table table = emptyTable(10).update("X=i");
        ExecutionContext.getContext().getQueryScope().putParam("var1", 10);
        ExecutionContext.getContext().getQueryScope().putParam("var2", 20);

        final RangeFilter filter = new RangeFilter(
                "0", Condition.LESS_THAN, "var2", "0 < var2", FormulaParserConfiguration.parser);

        final Table result = table.where(filter);
        assertTableEquals(table, result);

        final WhereFilter realFilter = filter.getRealFilter();
        Assert.eqTrue(realFilter instanceof ConditionFilter, "realFilter instanceof ConditionFilter");
    }

    @Test
    public void testEnsureColumnsTakePrecedence() {
        final Table table = emptyTable(10).update("X=i", "Y=i%2");
        ExecutionContext.getContext().getQueryScope().putParam("Y", 5);

        {
            final Table r1 = table.where("X == Y");
            final Table r2 = table.where("Y == X");
            Assert.equals(r1.getRowSet(), "r1.getRowSet()", RowSetFactory.flat(2));
            assertTableEquals(r1, r2);
        }

        {
            final Table r1 = table.where("X >= Y");
            final Table r2 = table.where("Y <= X");
            Assert.equals(r1.getRowSet(), "r1.getRowSet()", RowSetFactory.flat(10));
            assertTableEquals(r1, r2);
        }

        {
            final Table r1 = table.where("X > Y");
            final Table r2 = table.where("Y < X");
            Assert.equals(r1.getRowSet(), "r1.getRowSet()", RowSetFactory.fromRange(2, 9));
            assertTableEquals(r1, r2);
        }

        {
            final Table r1 = table.where("X < Y");
            final Table r2 = table.where("Y > X");
            Assert.equals(r1.getRowSet(), "r1.getRowSet()", RowSetFactory.empty());
            assertTableEquals(r1, r2);
        }

        {
            final Table r1 = table.where("X <= Y");
            final Table r2 = table.where("Y >= X");
            Assert.equals(r1.getRowSet(), "r1.getRowSet()", RowSetFactory.flat(2));
            assertTableEquals(r1, r2);
        }
    }

    @Test
    public void testEnsureColumnArraysTakePrecedence() {
        final Table table = emptyTable(10).update("X = i", "Y = ii == 1 ? 5 : -1");
        ExecutionContext.getContext().getQueryScope().putParam("Y_", new int[] {0, 4, 0});

        {
            final Table result = table.where("X == Y_[1]");
            Assert.equals(result.getRowSet(), "result.getRowSet()", RowSetFactory.fromKeys(5));

            // check that the mirror matches the expected result
            final Table mResult = table.where("Y_[1] == X");
            assertTableEquals(result, mResult);
        }

        {
            final Table result = table.where("X < Y_[1]");
            Assert.equals(result.getRowSet(), "result.getRowSet()", RowSetFactory.flat(5));

            // check that the mirror matches the expected result
            final Table mResult = table.where("Y_[1] > X");
            assertTableEquals(result, mResult);
        }

        // note that array access doesn't match the RangeFilter/MatchFilter regex, so let's try to override the
        // array access with a type that would otherwise work.
        ExecutionContext.getContext().getQueryScope().putParam("Y_", 4);
        try {
            table.where("X == Y_");
            // noinspection ThrowableNotThrown
            Assert.statementNeverExecuted();
        } catch (IllegalArgumentException expected) {

        }
    }

    @Test
    public void testIntToByteCoercion() {
        final Table table = emptyTable(11).update("X = ii % 2 == 0 ? (byte) ii : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", byte.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);
    }

    @Test
    public void testIntToShortCoercion() {
        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? (short) ii : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", short.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);
    }

    @Test
    public void testLongToIntCoercion() {
        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? (int) ii : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", int.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_LONG);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5L);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);
    }

    @Test
    public void testIntToLongCoercion() {
        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? ii : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", long.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);
    }

    @Test
    public void testIntToFloatCoercion() {
        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? (float) ii : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", float.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);
    }

    @Test
    public void testIntToDoubleCoercion() {
        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? (double) ii : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", double.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);
    }

    @Test
    public void testBigIntegerCoercion() {
        ExecutionContext.getContext().getQueryLibrary().importClass(BigInteger.class);

        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? BigInteger.valueOf(ii) : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", BigInteger.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);

        // let's also test BigDecimal -> BigInteger conversion; note that conversion does not round
        ExecutionContext.getContext().getQueryScope().putParam("bd_5", BigDecimal.valueOf(5.8));
        final Table bd_result = table.where("X >= bd_5");
        assertTableEquals(range_result, bd_result);
    }

    @Test
    public void testBigDecimalCoercion() {
        ExecutionContext.getContext().getQueryLibrary().importClass(BigDecimal.class);

        final Table table = emptyTable(11).update("X= ii % 2 == 0 ? BigDecimal.valueOf(ii) : null");
        final Class<Object> colType = table.getDefinition().getColumn("X").getDataType();
        Assert.eq(colType, "colType", BigDecimal.class);

        ExecutionContext.getContext().getQueryScope().putParam("real_null", null);
        ExecutionContext.getContext().getQueryScope().putParam("val_null", QueryConstants.NULL_INT);
        ExecutionContext.getContext().getQueryScope().putParam("val_5", 5);

        final Table real_null_result = table.where("X == real_null");
        final Table null_result = table.where("X == val_null");
        Assert.eq(null_result.size(), "null_result.size()", 5);
        assertTableEquals(real_null_result, null_result);

        final Table range_result = table.where("X >= val_5");
        Assert.eq(range_result.size(), "range_result.size()", 3);

        // let's also test BigInteger -> BigDecimal conversion
        ExecutionContext.getContext().getQueryScope().putParam("bi_5", BigInteger.valueOf(5));
        final Table bi_result = table.where("X >= bi_5");
        assertTableEquals(range_result, bi_result);
    }

    @Test
    public void testAddAndRemoveRefilter() {
        final QueryTable source = testRefreshingTable(i(10, 20, 30).toTracking(), stringCol("FV", "A", "B", "C"),
                intCol("Sentinel", 10, 20, 30));
        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();

        final QueryTable setTable = testRefreshingTable(i(10, 30).toTracking(), stringCol("FV", "A", "C"));

        final Table result = source.whereIn(setTable, "FV");
        final SimpleListener listener = new SimpleListener(result);
        result.addUpdateListener(listener);

        final PrintListener plResult = new PrintListener("testAddAndRemoveRefilter-result", result);
        assertTableEquals(source.where("FV in `A`, `C`"), result);

        updateGraph.runWithinUnitTestCycle(() -> {
            TstUtils.addToTable(setTable, i(20), stringCol("FV", "B"));
            TstUtils.removeRows(setTable, i(30));
            setTable.notifyListeners(i(20), i(30), i());
            TstUtils.addToTable(source, i(10), stringCol("FV", "A"), intCol("Sentinel", 40));
            source.notifyListeners(i(10), i(10), i());
        });

        assertEquals(i(10, 20), listener.update.added());
        assertEquals(i(10, 30), listener.update.removed());
        assertEquals(i(), listener.update.modified());

        assertTableEquals(source.where("FV in `A`, `B`"), result);
    }

    @Test
    public void testWhereFilterEquality() {
        final Table x = TableTools.newTable(intCol("A", 1, 2, 3), intCol("B", 4, 2, 1), stringCol("S", "A", "B", "C"));

        final WhereFilter f1 = WhereFilterFactory.getExpression("A in 7");
        final WhereFilter f2 = WhereFilterFactory.getExpression("A in 8");
        final WhereFilter f3 = WhereFilterFactory.getExpression("A in 7");

        final Table ignored = x.where(Filter.and(f1, f2, f3));

        assertEquals(f1, f3);
        assertNotEquals(f1, f2);
        assertNotEquals(f2, f3);

        final WhereFilter fa = WhereFilterFactory.getExpression("A in 7");
        final WhereFilter fb = WhereFilterFactory.getExpression("B in 7");
        final WhereFilter fap = WhereFilterFactory.getExpression("A not in 7");

        final Table ignored2 = x.where(Filter.and(fa, fb, fap));

        assertNotEquals(fa, fb);
        assertNotEquals(fa, fap);
        assertNotEquals(fb, fap);

        final WhereFilter fs = WhereFilterFactory.getExpression("S icase in `A`");
        final WhereFilter fs2 = WhereFilterFactory.getExpression("S icase in `A`, `B`, `C`");
        final WhereFilter fs3 = WhereFilterFactory.getExpression("S icase in `A`, `B`, `C`");
        final Table ignored3 = x.where(Filter.and(fs, fs2, fs3));
        assertNotEquals(fs, fs2);
        assertNotEquals(fs, fs3);
        assertEquals(fs2, fs3);

        final WhereFilter fof1 = WhereFilterFactory.getExpression("A = B");
        final WhereFilter fof2 = WhereFilterFactory.getExpression("A = B");
        final Table ignored4 = x.where(fof1);
        final Table ignored5 = x.where(fof2);
        // the ConditionFilters do not compare as equal, so this is unfortunate, but expected behavior
        assertNotEquals(fof1, fof2);
    }

    /**
     * Test column sources that simulate push-down operations.
     */
    private static class PushdownColumnSourceHeler {
        static void pushdownFilter(
                final WhereFilter filter,
                final RowSet selection,
                final boolean usePrev,
                final ColumnSource<?> source,
                final double maybePercentage,
                final Consumer<PushdownResult> onComplete) {
            try (final SafeCloseable ignored = LivenessScopeStack.open()) {
                final String colName = filter.getColumns().get(0);
                final Map<String, ColumnSource<?>> csMap = Collections.singletonMap(colName, source);
                final Table dummy = new QueryTable(selection.copy().toTracking(), csMap);

                try (final WritableRowSet matches = filter.filter(selection, selection, dummy, usePrev)) {
                    final long size = matches.size();
                    final long maybeSize = (long) (size * maybePercentage);
                    try (
                            final WritableRowSet addedRowSet = matches.subSetByPositionRange(0, maybeSize);
                            final WritableRowSet maybeRowSet = matches.subSetByPositionRange(maybeSize, size)) {
                        // Obvious these row sets do not overlap
                        onComplete.accept(PushdownResult.of(selection, addedRowSet, maybeRowSet));
                    }
                }
            }
        }
    }

    private static class PushdownIntTestSource extends IntTestSource {
        private static final AtomicInteger counter = new AtomicInteger(0);

        private final long pushdownCost;
        private final double maybePercentage;

        private int encounterOrder = -1;

        public PushdownIntTestSource(RowSet rowSet, long pushdownCost, double maybePercentage, int... data) {
            super(rowSet, IntChunk.chunkWrap(data));
            this.pushdownCost = pushdownCost;
            this.maybePercentage = maybePercentage;
        }

        @Override
        public void estimatePushdownFilterCost(WhereFilter filter, RowSet selection, boolean usePrev,
                PushdownFilterContext context, JobScheduler jobScheduler, LongConsumer onComplete,
                Consumer<Exception> onError) {
            onComplete.accept(pushdownCost);
        }

        @Override
        public void pushdownFilter(final WhereFilter filter, final RowSet input,
                final boolean usePrev, final PushdownFilterContext context,
                final long costCeiling, final JobScheduler jobScheduler, final Consumer<PushdownResult> onComplete,
                final Consumer<Exception> onError) {
            encounterOrder = counter.getAndIncrement();
            PushdownColumnSourceHeler.pushdownFilter(filter, input, usePrev, this, maybePercentage, onComplete);
        }

        public static void resetCounter() {
            counter.set(0);
        }

        public int getEncounterOrder() {
            return encounterOrder;
        }
    }

    @Test
    public void testWherePushdownSingleColumn() {
        final WritableRowSet rowSet = RowSetFactory.flat(5);
        final Map<String, ColumnSource<?>> csMap = Map.of(
                "A", new PushdownIntTestSource(rowSet, 100L, 0.5, 1, 2, 3, 4, 5),
                "B", new PushdownIntTestSource(rowSet, 90L, 0.0, 1, 2, 3, 4, 5),
                "C", new PushdownIntTestSource(rowSet, 80L, 1.0, 1, 2, 3, 4, 5));

        final Table source = new QueryTable(rowSet.toTracking(), csMap);
        Table result;

        final WhereFilter f1 = WhereFilterFactory.getExpression("A <= 4");
        result = source.where(f1);
        try (final RowSet expected = i(0, 1, 2, 3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }

        final WhereFilter f2 = WhereFilterFactory.getExpression("A >= 2");
        result = source.where(Filter.and(f1, f2));
        try (final RowSet expected = i(1, 2, 3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }

        final WhereFilter f3 = WhereFilterFactory.getExpression("B <= 4");
        result = source.where(f3);
        try (final RowSet expected = i(0, 1, 2, 3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }

        final WhereFilter f4 = WhereFilterFactory.getExpression("B >= 2");
        result = source.where(Filter.and(f3, f4));
        try (final RowSet expected = i(1, 2, 3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }

        final WhereFilter f5 = WhereFilterFactory.getExpression("C <= 4");
        result = source.where(f5);
        try (final RowSet expected = i(0, 1, 2, 3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }

        final WhereFilter f6 = WhereFilterFactory.getExpression("C >= 2");
        result = source.where(Filter.and(f5, f6));
        try (final RowSet expected = i(1, 2, 3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
    }

    /**
     * Validate that user filter order is maintained when pushdown filter costs are equal.
     */
    @Test
    public void testWherePushdownUserOrder() {
        final WritableRowSet rowSet = RowSetFactory.flat(10);

        // Thse have the same cost, so user order should be followed.
        final PushdownIntTestSource sourceA =
                new PushdownIntTestSource(rowSet, 100L, 0.5, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        final PushdownIntTestSource sourceB =
                new PushdownIntTestSource(rowSet, 100L, 0.0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        final PushdownIntTestSource sourceC =
                new PushdownIntTestSource(rowSet, 100L, 1.0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

        final Map<String, ColumnSource<?>> csMap = Map.of("A", sourceA, "B", sourceB, "C", sourceC);

        final Table source = new QueryTable(rowSet.toTracking(), csMap);
        Table result;

        // Two column test #1
        PushdownIntTestSource.resetCounter();
        result = source.where("A <= 4", "B >= 2");
        try (final RowSet expected = i(2, 3, 4)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceA.getEncounterOrder() == 0, "sourceA.getEncounterOrder()");
        Assert.eqTrue(sourceB.getEncounterOrder() == 1, "sourceB.getEncounterOrder()");

        // Two column test #2
        PushdownIntTestSource.resetCounter();
        result = source.where("B >= 2", "A <= 4");
        try (final RowSet expected = i(2, 3, 4)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceB.getEncounterOrder() == 0, "sourceB.getEncounterOrder()");
        Assert.eqTrue(sourceA.getEncounterOrder() == 1, "sourceA.getEncounterOrder()");

        // Two column test #3
        PushdownIntTestSource.resetCounter();
        result = source.where("C = 3", "A <= 4");
        try (final RowSet expected = i(3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceC.getEncounterOrder() == 0, "sourceC.getEncounterOrder()");
        Assert.eqTrue(sourceA.getEncounterOrder() == 1, "sourceA.getEncounterOrder()");

        // Three column test #1
        PushdownIntTestSource.resetCounter();
        result = source.where("A <= 4", "B >= 2", "C=3");
        try (final RowSet expected = i(3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceA.getEncounterOrder() == 0, "sourceA.getEncounterOrder()");
        Assert.eqTrue(sourceB.getEncounterOrder() == 1, "sourceB.getEncounterOrder()");
        Assert.eqTrue(sourceC.getEncounterOrder() == 2, "sourceC.getEncounterOrder()");

        // Three column test #2
        PushdownIntTestSource.resetCounter();
        result = source.where("B >= 2", "A <= 4", "C=3");
        try (final RowSet expected = i(3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceB.getEncounterOrder() == 0, "sourceB.getEncounterOrder()");
        Assert.eqTrue(sourceA.getEncounterOrder() == 1, "sourceA.getEncounterOrder()");
        Assert.eqTrue(sourceC.getEncounterOrder() == 2, "sourceC.getEncounterOrder()");

        // Three column test #3
        PushdownIntTestSource.resetCounter();
        result = source.where("C=3", "A <= 4", "B >= 2");
        try (final RowSet expected = i(3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceC.getEncounterOrder() == 0, "sourceC.getEncounterOrder()");
        Assert.eqTrue(sourceA.getEncounterOrder() == 1, "sourceA.getEncounterOrder()");
        Assert.eqTrue(sourceB.getEncounterOrder() == 2, "sourceB.getEncounterOrder()");

        // Three column test #4
        PushdownIntTestSource.resetCounter();
        result = source.where("A <= 4", "C=3", "B >= 2");
        try (final RowSet expected = i(3)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
        Assert.eqTrue(sourceA.getEncounterOrder() == 0, "sourceA.getEncounterOrder()");
        Assert.eqTrue(sourceC.getEncounterOrder() == 1, "sourceC.getEncounterOrder()");
        Assert.eqTrue(sourceB.getEncounterOrder() == 2, "sourceB.getEncounterOrder()");
    }

    /**
     * Test PPM for simple verification of filter execution code.
     */
    private static class TestPPM implements PushdownPredicateManager {
        private final long pushdownCost;
        private final double maybePercentage;

        private Table table;

        public TestPPM(long pushdownCost, double maybePercentage) {
            this.pushdownCost = pushdownCost;
            this.maybePercentage = maybePercentage;
        }

        public void assignTable(Table table) {
            this.table = table;
        }

        @Override
        public void estimatePushdownFilterCost(
                final WhereFilter filter,
                final RowSet selection,
                final boolean usePrev,
                final PushdownFilterContext context,
                final JobScheduler jobScheduler,
                final LongConsumer onComplete,
                final Consumer<Exception> onError) {
            onComplete.accept(pushdownCost);
        }

        @Override
        public void pushdownFilter(
                final WhereFilter filter,
                final RowSet selection,
                final boolean usePrev,
                final PushdownFilterContext context,
                final long costCeiling,
                final JobScheduler jobScheduler,
                final Consumer<PushdownResult> onComplete,
                final Consumer<Exception> onError) {
            if (table == null) {
                throw new IllegalStateException("Table not assigned to TestPPM");
            }
            try (
                    final SafeCloseable ignored = LivenessScopeStack.open();
                    final WritableRowSet matches = filter.filter(selection, table.getRowSet(), table, usePrev)) {
                final long size = matches.size();
                final long maybeSize = (long) (size * maybePercentage);
                try (
                        final WritableRowSet addedRowSet = matches.subSetByPositionRange(0, maybeSize);
                        final WritableRowSet maybeRowSet = matches.subSetByPositionRange(maybeSize, size)) {
                    // Obvious these row sets do not overlap
                    onComplete.accept(PushdownResult.of(selection, addedRowSet, maybeRowSet));
                }
            }
        }

        @Override
        public PushdownFilterContext makePushdownFilterContext(
                final WhereFilter filter,
                final List<ColumnSource<?>> filterSources) {
            return PushdownFilterContext.NO_PUSHDOWN_CONTEXT;
        }
    }

    private static class PPMIntTestSource extends IntTestSource {
        final PushdownPredicateManager ppm;

        public PPMIntTestSource(PushdownPredicateManager ppm, RowSet rowSet, int... data) {
            super(rowSet, IntChunk.chunkWrap(data));
            this.ppm = ppm;
        }

        @Override
        public PushdownPredicateManager pushdownManager() {
            return ppm;
        }
    }

    @Test
    public void testWherePushdownMultiColumn() {
        final TestPPM ppm = new TestPPM(100L, 0.5);

        final WritableRowSet rowSet = RowSetFactory.flat(5);
        final Map<String, ColumnSource<?>> csMap = Map.of(
                "A", new PPMIntTestSource(ppm, rowSet, 1, 2, 3, 4, 5),
                "B", new PPMIntTestSource(ppm, rowSet, 1, 2, 3, 4, 5),
                "C", new PPMIntTestSource(ppm, rowSet, 1, 2, 3, 4, 5));

        final Table source = new QueryTable(rowSet.toTracking(), csMap);
        // This test PPM needs to be aware of the source table to simulate pushdown filtering.
        ppm.assignTable(source);

        Table result;

        final WhereFilter f1 = WhereFilterFactory.getExpression("A <= 1");
        final WhereFilter f2 = WhereFilterFactory.getExpression("B >= 5");

        result = source.where(Filter.or(f1, f2));
        try (final RowSet expected = i(0, 4)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }

        final WhereFilter f3 = WhereFilterFactory.getExpression("C = 3");
        result = source.where(Filter.or(f1, f2, f3));
        try (final RowSet expected = i(0, 2, 4)) {
            assertEquals("result.getRowSet().equals(expected)", result.getRowSet(), expected);
        }
    }

    @Test
    public void testDataIndexNoBarrierPrioritizes() {
        // this is a baseline test for the barrier related tests that follow
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final Table result = sourceWithData.where(
                Filter.and(preFilter, RawString.of("A < 50000"), postFilter));

        // we expect the pre-filter to see after the raw-string filter
        assertEquals(50_000, numRowsFiltered(preFilter));
        assertEquals(50_000, numRowsFiltered(postFilter));
        assertEquals(50_000, result.size());
    }

    @Test
    public void testDataIndexSerialDoesNotPrioritize() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final Table result = sourceWithData.where(
                Filter.and(preFilter, RawString.of("A < 50000").withSerial(), postFilter));

        assertEquals(100_000, numRowsFiltered(preFilter));
        assertEquals(50_000, numRowsFiltered(postFilter));
        assertEquals(50_000, result.size());
    }

    @Test
    public void testDataIndexRespectBarrierDoesNotPrioritize() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final Object barrier = new Object(); // dummy barrier object for testing
        final Table result = sourceWithData.where(
                Filter.and(
                        preFilter.withBarriers(barrier),
                        RawString.of("A < 50000").respectsBarriers(barrier),
                        postFilter));

        assertEquals(100_000, numRowsFiltered(preFilter));
        assertEquals(50_000, numRowsFiltered(postFilter));
        assertEquals(50_000, result.size());
    }

    @Test
    @Ignore
    public void testDataIndexRespectBarrierPartialPrioritization() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        final DataIndex dataIndex = DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter preFilter2 = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final Object barrier = new Object(); // dummy barrier object for testing
        // we are looking to see the RawString prioritize over preFilter2
        final Table result = sourceWithData.where(
                Filter.and(
                        preFilter.withBarriers(barrier),
                        preFilter2,
                        RawString.of("A < 50000").respectsBarriers(barrier),
                        postFilter));

        assertEquals(100_000, numRowsFiltered(preFilter));
        assertEquals(50_000, numRowsFiltered(preFilter2)); // raw-string prioritizes over prefilter2
        assertEquals(50_000, numRowsFiltered(postFilter));
        assertEquals(50_000, result.size());
    }

    @Test
    public void testDataIndexRespectBarrierDeepEqValidates() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final class DeepEqBarrier {
            final String name;

            DeepEqBarrier(String name) {
                this.name = name;
            }

            @Override
            public boolean equals(Object obj) {
                if (this == obj)
                    return true;
                if (!(obj instanceof DeepEqBarrier))
                    return false;
                final DeepEqBarrier other = (DeepEqBarrier) obj;
                return name.equals(other.name);
            }

            @Override
            public int hashCode() {
                return name.hashCode();
            }
        }

        final Table result = sourceWithData.where(
                Filter.and(
                        preFilter.withBarriers(new DeepEqBarrier("my_test_barrier")),
                        RawString.of("A < 50000").respectsBarriers(new DeepEqBarrier("my_test_barrier")),
                        postFilter));

        assertEquals(100_000, numRowsFiltered(preFilter));
        assertEquals(50_000, numRowsFiltered(postFilter));
        assertEquals(50_000, result.size());
    }

    @Test
    public void testDataIndexRespectBarrierThrowsIfNotFound() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final IllegalArgumentException err = assertThrows(IllegalArgumentException.class, () -> {
            sourceWithData.where(Filter.and(
                    preFilter.withBarriers(new Object()),
                    RawString.of("A < 50000").respectsBarriers(new Object()),
                    postFilter));
        });
        assertTrue(err.getMessage().contains("respects barrier"));
        assertTrue(err.getMessage().contains("that is not declared by any filter"));

        // filters should not have run at all
        assertEquals(0, getAndSortSizes(preFilter).size());
        assertEquals(0, getAndSortSizes(postFilter).size());
    }

    @Test
    public void testDuplicateBarrierDeclarationThrows() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final Object barrier = new Object(); // dummy barrier object for testing
        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final IllegalArgumentException err = assertThrows(IllegalArgumentException.class, () -> {
            sourceWithData.where(Filter.and(
                    preFilter.withBarriers(barrier),
                    RawString.of("A < 50000").withBarriers(barrier),
                    postFilter));
        });
        assertTrue(err.getMessage().contains("Filter Barriers must be unique!"));

        // filters should not have run at all
        assertEquals(0, getAndSortSizes(preFilter).size());
        assertEquals(0, getAndSortSizes(postFilter).size());
    }

    @Test
    public void testDataIndexPrioritizesBarriersAndDependees() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final Object barrier = new Object();
        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter midFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final Table result = sourceWithData.where(
                Filter.and(
                        preFilter,
                        RawString.of("A < 50000").withBarriers(barrier),
                        midFilter.respectsBarriers(barrier),
                        RawString.of("A < 25000").respectsBarriers(barrier),
                        postFilter));

        // note that while the mid-filter respects the barrier, but will not be prioritized
        assertEquals(25_000, numRowsFiltered(preFilter));
        assertEquals(25_000, numRowsFiltered(midFilter));
        assertEquals(25_000, numRowsFiltered(postFilter));
    }

    @Test
    public void testDataIndexBarriersRespectTransitiveDependencies() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final Object barrier = new Object();
        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter midFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final RowSetCapturingFilter filter1 = new RowSetCapturingFilter(RawString.of("A < 50000"));
        final RowSetCapturingFilter filter2 = new RowSetCapturingFilter(RawString.of("A < 25000"));

        final Table result = sourceWithData.where(
                Filter.and(
                        preFilter,
                        filter1.withSerial().withBarriers(barrier),
                        midFilter.withBarriers("mid_barrier").respectsBarriers(barrier),
                        filter2.respectsBarriers("mid_barrier"),
                        postFilter));

        // note that while the mid-filter respects the barrier, but will not be prioritized
        assertEquals(100_000, numRowsFiltered(preFilter));
        assertEquals(100_000, numRowsFiltered(filter1));
        assertEquals(50_000, numRowsFiltered(midFilter));
        assertEquals(50_000, numRowsFiltered(filter2));
        assertEquals(25_000, numRowsFiltered(postFilter));
    }

    @Test
    public void testPushdownBarriersAndSerial() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;

        final int[] columnData = new int[100_000];
        for (int ii = 0; ii < columnData.length; ++ii) {
            columnData[ii] = ii;
        }

        final WritableRowSet rowSet = RowSetFactory.flat(columnData.length);
        final Map<String, ColumnSource<?>> csMap = Map.of(
                "A", new PushdownIntTestSource(rowSet, 100L, 1.0, columnData),
                "B", new PushdownIntTestSource(rowSet, 90L, 1.0, columnData),
                "C", new PushdownIntTestSource(rowSet, 80L, 1.0, columnData));

        final Table source = new QueryTable(rowSet.toTracking(), csMap);
        final QueryTable sourceWithData = (QueryTable) source.update("I = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "I");

        final Object barrier = new Object();
        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter midFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final RowSetCapturingFilter filter1 = new RowSetCapturingFilter(RawString.of("A >= 20000"));
        final RowSetCapturingFilter filter2 = new RowSetCapturingFilter(RawString.of("C < 25000"));

        final ArrayList<RowSetCapturingFilter> allFilters =
                Lists.newArrayList(preFilter, midFilter, postFilter, filter1, filter2);

        // total reorder filter2 in front of filter1
        sourceWithData.where(Filter.and(
                preFilter,
                filter1,
                midFilter,
                filter2,
                postFilter));
        // should bubble up filter2, then filter1, finally remaining three filters
        assertEquals(5_000, numRowsFiltered(preFilter));
        assertEquals(25_000, numRowsFiltered(filter1));
        assertEquals(5_000, numRowsFiltered(midFilter));
        assertEquals(100_000, numRowsFiltered(filter2));
        assertEquals(5_000, numRowsFiltered(postFilter));

        // partial reorder filter2 right behind filter1
        allFilters.forEach(RowSetCapturingFilter::reset);
        sourceWithData.where(Filter.and(
                preFilter,
                filter1.withBarriers(barrier),
                midFilter,
                filter2.respectsBarriers(barrier),
                postFilter));
        // should bubble up filter1, then filter2, finally remaining three filters
        assertEquals(5_000, numRowsFiltered(preFilter));
        assertEquals(100_000, numRowsFiltered(filter1));
        assertEquals(5_000, numRowsFiltered(midFilter));
        assertEquals(80_000, numRowsFiltered(filter2));
        assertEquals(5_000, numRowsFiltered(postFilter));

        // partial reorder where filter2 bumps up to the serial filter, but not up to the respected barrier
        allFilters.forEach(RowSetCapturingFilter::reset);
        sourceWithData.where(Filter.and(
                preFilter,
                filter1.withBarriers(barrier),
                midFilter.withSerial(),
                postFilter,
                filter2.respectsBarriers(barrier)));
        // should bubble up filter 1, preFilter, midFilter, then filter2 and postFilter
        assertEquals(80_000, numRowsFiltered(preFilter));
        assertEquals(100_000, numRowsFiltered(filter1));
        assertEquals(80_000, numRowsFiltered(midFilter));
        assertEquals(80_000, numRowsFiltered(filter2));
        assertEquals(5_000, numRowsFiltered(postFilter));

        // partial reorder where filter 1 cannot move, and filter 2 bumps up to the serial filter
        allFilters.forEach(RowSetCapturingFilter::reset);
        sourceWithData.where(Filter.and(
                preFilter.withBarriers(preFilter),
                filter1.respectsBarriers(preFilter).withBarriers(barrier),
                midFilter.withSerial(),
                postFilter,
                filter2.respectsBarriers(barrier)));
        // should bubble up preFilter, filter 1, midFilter, then filter2 and postFilter
        assertEquals(100_000, numRowsFiltered(preFilter));
        assertEquals(100_000, numRowsFiltered(filter1));
        assertEquals(80_000, numRowsFiltered(midFilter));
        assertEquals(80_000, numRowsFiltered(filter2));
        assertEquals(5_000, numRowsFiltered(postFilter));
    }

    @Test
    public void testPushdownTransitiveBarriers() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;

        final int[] columnData = new int[100_000];
        for (int ii = 0; ii < columnData.length; ++ii) {
            columnData[ii] = ii;
        }

        final WritableRowSet rowSet = RowSetFactory.flat(columnData.length);
        final Map<String, ColumnSource<?>> csMap = Map.of(
                "A", new PushdownIntTestSource(rowSet, 100L, 1.0, columnData),
                "B", new PushdownIntTestSource(rowSet, 90L, 1.0, columnData),
                "C", new PushdownIntTestSource(rowSet, 80L, 1.0, columnData));

        final Table source = new QueryTable(rowSet.toTracking(), csMap);
        final QueryTable sourceWithData = (QueryTable) source.update("I = ii");
        DataIndexer.getOrCreateDataIndex(sourceWithData, "I");

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        final RowSetCapturingFilter filter1 = new RowSetCapturingFilter(RawString.of("A >= 20000"));
        final RowSetCapturingFilter filter2 = new RowSetCapturingFilter(RawString.of("B < 50000"));
        final RowSetCapturingFilter filter3 = new RowSetCapturingFilter(RawString.of("C < 25000"));

        sourceWithData.where(Filter.and(
                preFilter,
                filter1.withBarriers("1"),
                filter2.respectsBarriers("1").withBarriers("2"),
                filter3.respectsBarriers("2"),
                postFilter));
        // should be f1, f2, f3, pre, then post
        assertEquals(5_000, numRowsFiltered(preFilter));
        assertEquals(100_000, numRowsFiltered(filter1));
        assertEquals(80_000, numRowsFiltered(filter2));
        assertEquals(30_000, numRowsFiltered(filter3));
        assertEquals(5_000, numRowsFiltered(postFilter));
    }

    @Test
    public void testSerialOnConstantArrayAccess() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        final DataIndex dataIndex = DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final RowSetCapturingFilter filter0 = new RowSetCapturingFilter(RawString.of("A < 50000"));
        final RowSetCapturingFilter filter1 = new RowSetCapturingFilter(RawString.of("A > 15000"));

        final Table res0 = sourceWithData.where(Filter.and(
                filter0,
                RawString.of("A_[ii - 1] < 25000").withSerial(),
                filter1));
        assertEquals(filter0.numRowsProcessed(), 100000);
        assertEquals(10_000, res0.size());
        assertEquals(filter1.numRowsProcessed(), 25001);
    }


    @Test
    public void testBarrierOnConstantArrayAccess() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");
        final DataIndex dataIndex = DataIndexer.getOrCreateDataIndex(sourceWithData, "A");

        final Object barrier = new Object();
        final RowSetCapturingFilter filter0 = new RowSetCapturingFilter(RawString.of("A < 50000"));
        final RowSetCapturingFilter filter1 = new RowSetCapturingFilter(RawString.of("A > 15000"));

        final Table res0 = sourceWithData.where(Filter.and(
                filter0,
                RawString.of("A_[ii - 1] < 25000").withBarriers(barrier),
                filter1.respectsBarriers(barrier)));
        assertEquals(filter0.numRowsProcessed(), 100000);
        assertEquals(10_000, res0.size());
        assertEquals(filter1.numRowsProcessed(), 25001);
    }

    @Test
    public void testRespectsBarrierOnConstantArrayAccess() {
        QueryTable.PARALLEL_WHERE_SEGMENTS = 10;
        QueryTable.PARALLEL_WHERE_ROWS_PER_SEGMENT = 10_000;
        final QueryTable source = testRefreshingTable(RowSetFactory.flat(100_000).toTracking());
        final QueryTable sourceWithData = (QueryTable) source.update("A = ii");

        final Object barrier = new Object();
        final RowSetCapturingFilter filter0 = new RowSetCapturingFilter(RawString.of("A < 50000"));
        // note that we can't fetch the inner filter from RowSetCapturingFilter
        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();

        // ensure that we get what we expect without the respectsBarrier first
        final Table res0 = sourceWithData.where(Filter.and(
                filter0.withBarriers(barrier),
                preFilter,
                RawString.of("A_[ii - 1] < 25000")));
        assertEquals(filter0.numRowsProcessed(), 100000);
        assertEquals(preFilter.numRowsProcessed(), 50000);
        assertEquals(25_001, res0.size());

        filter0.reset();
        preFilter.reset();

        // TODO: this respectsBarrier could be lost and we wouldn't know it!
        final Table res1 = sourceWithData.where(Filter.and(
                filter0.withBarriers(barrier),
                preFilter,
                RawString.of("A_[ii - 1] < 25000").respectsBarriers(barrier)));
        assertEquals(filter0.numRowsProcessed(), 100000);
        assertEquals(preFilter.numRowsProcessed(), 50000);
        assertEquals(25_001, res1.size());

        TstUtils.assertTableEquals(res0, res1);
    }

    @Test
    public void testRowKeyAgnosticColumnSources() {
        SingleValueColumnSource<?> src;

        // Boolean Source
        src = SingleValueColumnSource.getSingleValueColumnSource(boolean.class);
        ((SingleValueColumnSource<Boolean>) src).set(true);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = true", "A = false"); // match
        ((SingleValueColumnSource<Boolean>) src).set(false); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = false", "A = true"); // match

        // Byte Source
        src = SingleValueColumnSource.getSingleValueColumnSource(byte.class);
        src.set((byte) 42);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition
        src.set((byte) 0); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 0", "A = 42"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 0", "A < 0"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 1", "A + 1 < 1"); // condition

        // Char Source
        src = SingleValueColumnSource.getSingleValueColumnSource(char.class);
        src.set('A');
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 'A'", "A = 'B'"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 'A'", "A < 'A'"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 'B'", "A + 1 < 'B'"); // condition
        src.set('B'); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 'B'", "A = 'A'"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 'B'", "A < 'B'"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 'C'", "A + 1 < 'C'"); // condition

        // Short Source
        src = SingleValueColumnSource.getSingleValueColumnSource(short.class);
        src.set((short) 42);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition
        src.set((short) 0); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 0", "A = 42"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 0", "A < 0"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 1", "A + 1 < 1"); // condition

        // Int Source
        src = SingleValueColumnSource.getSingleValueColumnSource(int.class);
        src.set(42);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition
        src.set(0); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 0", "A = 42"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 0", "A < 0"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 1", "A + 1 < 1"); // condition

        // Long Source
        src = SingleValueColumnSource.getSingleValueColumnSource(long.class);
        src.set(42L);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition
        src.set(0L); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 0", "A = 42"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 0", "A < 0"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 1", "A + 1 < 1"); // condition

        // Float Source
        src = SingleValueColumnSource.getSingleValueColumnSource(float.class);
        src.set(42.0f);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition
        src.set(0.0f); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 0", "A = 42"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 0", "A < 0"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 1", "A + 1 < 1"); // condition

        // Double Source
        src = SingleValueColumnSource.getSingleValueColumnSource(double.class);
        src.set(42.0);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition
        src.set(0.0); // change the value
        testRowKeyAgnosticColumnSource(src, "A", "A = 0", "A = 42"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 0", "A < 0"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 1", "A + 1 < 1"); // condition

        // Object Source
        SingleValueColumnSource<String> objectSource = SingleValueColumnSource.getSingleValueColumnSource(String.class);
        objectSource.set("AAA");
        testRowKeyAgnosticColumnSource(objectSource, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(objectSource, "A", "A = `AAA`", "A = `BBB`"); // match
        testRowKeyAgnosticColumnSource(objectSource, "A", "A >= `AAA`", "A < `AAA`"); // range
        testRowKeyAgnosticColumnSource(objectSource, "A", "A + `BBB` >= `AAABBB`", "A + `BBB` < `AAABBB`"); // condition
        objectSource.set("BBB"); // change the value
        testRowKeyAgnosticColumnSource(objectSource, "A", "A = `BBB`", "A = `AAA`"); // match
        testRowKeyAgnosticColumnSource(objectSource, "A", "A >= `BBB`", "A < `BBB`"); // range
        testRowKeyAgnosticColumnSource(objectSource, "A", "A + `CCC` >= `BBBCCC`", "A + `CCC` < `BBBCCC`"); // condition

        // Instant Source
        SingleValueColumnSource<Instant> instantSource =
                SingleValueColumnSource.getSingleValueColumnSource(Instant.class);
        instantSource.set(parseInstant("2020-01-01T00:00:00 NY"));
        testRowKeyAgnosticColumnSource(instantSource, "A", "A != null", "A == null"); // null
        testRowKeyAgnosticColumnSource(instantSource, "A", "A = '2020-01-01T00:00:00 NY'",
                "A = '2020-01-02T00:00:00 NY'"); // match
        testRowKeyAgnosticColumnSource(instantSource, "A", "A <= '2020-01-01T00:00:00 NY'",
                "A > '2020-01-01T00:00:00 NY'"); // range
        testRowKeyAgnosticColumnSource(instantSource, "A",
                "A >= '2020-01-01T00:00:00 NY' && A <= '2020-01-01T00:00:00 NY'",
                "A >= '2020-01-02T00:00:00 NY' && A <= '2020-01-02T00:00:00 NY'"); // condition
        instantSource.set(parseInstant("2020-01-02T00:00:00 NY")); // change the value
        testRowKeyAgnosticColumnSource(instantSource, "A", "A = '2020-01-02T00:00:00 NY'",
                "A = '2020-01-01T00:00:00 NY'"); // match
        testRowKeyAgnosticColumnSource(instantSource, "A", "A <= '2020-01-02T00:00:00 NY'",
                "A > '2020-01-02T00:00:00 NY'"); // range
        testRowKeyAgnosticColumnSource(instantSource, "A",
                "A >= '2020-01-02T00:00:00 NY' && A <= '2020-01-02T00:00:00 NY'",
                "A >= '2020-01-01T00:00:00 NY' && A <= '2020-01-01T00:00:00 NY'"); // condition
    }

    @Test
    public void testImmutableRowKeyAgnosticColumnSources() {
        ColumnSource<?> src;

        // Immutable Byte Source
        src = InMemoryColumnSource.makeImmutableConstantSource(byte.class, null, (byte) 42);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition

        // Immutable Char Source
        src = InMemoryColumnSource.makeImmutableConstantSource(char.class, null, 'A');
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 'A'", "A = 'B'"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 'A'", "A < 'A'"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 'B'", "A + 1 < 'B'"); // condition

        // Immutable Short Source
        src = InMemoryColumnSource.makeImmutableConstantSource(short.class, null, (short) 42);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition

        // Immutable Int Source
        src = InMemoryColumnSource.makeImmutableConstantSource(int.class, null, 42);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition

        // Immutable Long Source
        src = InMemoryColumnSource.makeImmutableConstantSource(long.class, null, 42L);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition

        // Immutable Float Source
        src = InMemoryColumnSource.makeImmutableConstantSource(float.class, null, 42.0f);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition

        // Immutable Double Source
        src = InMemoryColumnSource.makeImmutableConstantSource(double.class, null, 42.0);
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = 42", "A = 0"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= 42", "A < 42"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + 1 >= 43", "A + 1 < 43"); // condition

        // Immutable Object Source
        src = InMemoryColumnSource.makeImmutableConstantSource(String.class, null, "AAA");
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = `AAA`", "A = `BBB`"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A >= `AAA`", "A < `AAA`"); // range
        testRowKeyAgnosticColumnSource(src, "A", "A + `BBB` >= `AAABBB`", "A + `BBB` < `AAABBB`"); // condition

        // Immutable Instant Source
        src = InMemoryColumnSource.makeImmutableConstantSource(Instant.class, null,
                parseInstant("2020-01-01T00:00:00 NY"));
        testRowKeyAgnosticColumnSource(src, "A", "A != null", "A = null"); // null
        testRowKeyAgnosticColumnSource(src, "A", "A = '2020-01-01T00:00:00 NY'",
                "A = '2020-01-02T00:00:00 NY'"); // match
        testRowKeyAgnosticColumnSource(src, "A", "A <= '2020-01-01T00:00:00 NY'", "A > '2020-01-01T00:00:00 NY'"); // range
        testRowKeyAgnosticColumnSource(src, "A",
                "A >= '2020-01-01T00:00:00 NY' && A <= '2020-01-01T00:00:00 NY'",
                "A >= '2020-01-02T00:00:00 NY' && A <= '2020-01-02T00:00:00 NY'"); // condition
    }

    @Test
    public void testNullRowKeyAgnosticColumnSources() {
        // Null Byte Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(byte.class, null),
                "A", "A = null", "A != null");

        // Null Char Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(char.class, null),
                "A", "A = null", "A != null");

        // Null Short Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(short.class, null),
                "A", "A = null", "A != null");

        // Null Int Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(int.class, null),
                "A", "A = null", "A != null");

        // Null Long Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(long.class, null),
                "A", "A = null", "A != null");

        // Null Float Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(float.class, null),
                "A", "A = null", "A != null");

        // Null Double Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(double.class, null),
                "A", "A = null", "A != null");

        // Null Boolean Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(Boolean.class, null),
                "A", "A = null", "A != null");

        // Null String Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(String.class, null),
                "A", "A = null", "A != null");

        // Null Instant Source
        testRowKeyAgnosticColumnSource(
                NullValueColumnSource.getInstance(Instant.class, null),
                "A", "A = null", "A != null");
    }

    /**
     * Private helper to force parallelization of the RowSetCapturingFilter.
     */
    private class ParallelizedRowSetCapturingFilter extends RowSetCapturingFilter {
        public ParallelizedRowSetCapturingFilter(Filter filter) {
            super(filter);
        }

        @Override
        public boolean permitParallelization() {
            return true;
        }
    }

    private void testRowKeyAgnosticColumnSource(
            final ColumnSource<?> columnSource,
            final String columnName,
            final String filterAllPass,
            final String filterNonePass) {

        final Map<String, ColumnSource<?>> columnSourceMap = Map.of(columnName, columnSource);
        final QueryTable source = new QueryTable(RowSetFactory.flat(100_000).toTracking(), columnSourceMap);
        source.setRefreshing(true);

        final RowSetCapturingFilter preFilter = new RowSetCapturingFilter();
        final RowSetCapturingFilter filter0 = new ParallelizedRowSetCapturingFilter(RawString.of(filterAllPass));
        final RowSetCapturingFilter postFilter = new RowSetCapturingFilter();

        // force pre and post filters to run when expected using barriers
        final Table res0 = source.where(Filter.and(
                preFilter.withBarriers("1"),
                filter0.respectsBarriers("1").withBarriers("2"),
                postFilter.respectsBarriers("2")));
        assertEquals(100_000, preFilter.numRowsProcessed());
        assertEquals(1, filter0.numRowsProcessed());
        assertEquals(100_000, postFilter.numRowsProcessed()); // All rows passed

        assertEquals(100_000, res0.size());

        preFilter.reset();
        postFilter.reset();

        final RowSetCapturingFilter filter1 = new ParallelizedRowSetCapturingFilter(RawString.of(filterNonePass));

        // force pre and post filters to run when expected using barriers
        final Table res1 = source.where(Filter.and(
                preFilter.withBarriers("1"),
                filter1.respectsBarriers("1").withBarriers("2"),
                postFilter.respectsBarriers("2")));
        assertEquals(100_000, preFilter.numRowsProcessed());
        assertEquals(1, filter1.numRowsProcessed());
        assertEquals(0, postFilter.numRowsProcessed()); // No rows passed

        assertEquals(0, res1.size());
    }

    protected static TLongList getAndSortSizes(final RowSetCapturingFilter filter) {
        final List<RowSet> rowSets = filter.rowSets();
        TLongList sizes = new TLongArrayList(rowSets.size());
        filter.rowSets().stream()
                .mapToLong(RowSet::size)
                .forEach(sizes::add);
        sizes.sort();
        return sizes;
    }

    protected static long numRowsFiltered(final RowSetCapturingFilter filter) {
        return filter.rowSets().stream()
                .mapToLong(RowSet::size)
                .sum();
    }
}
