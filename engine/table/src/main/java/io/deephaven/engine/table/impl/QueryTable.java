//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.api.*;
import io.deephaven.api.agg.Aggregation;
import io.deephaven.api.agg.AggregationOptimizer;
import io.deephaven.api.agg.AggregationOutputs;
import io.deephaven.api.agg.Partition;
import io.deephaven.api.agg.spec.AggSpec;
import io.deephaven.api.agg.spec.AggSpecColumnReferences;
import io.deephaven.api.filter.Filter;
import io.deephaven.api.snapshot.SnapshotWhenOptions;
import io.deephaven.api.snapshot.SnapshotWhenOptions.Flag;
import io.deephaven.api.updateby.UpdateByControl;
import io.deephaven.api.updateby.UpdateByOperation;
import io.deephaven.base.verify.Assert;
import io.deephaven.base.verify.Require;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.configuration.Configuration;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.exceptions.CancellationException;
import io.deephaven.engine.exceptions.TableInitializationException;
import io.deephaven.engine.liveness.Liveness;
import io.deephaven.engine.liveness.LivenessScope;
import io.deephaven.engine.primitive.iterator.*;
import io.deephaven.engine.rowset.*;
import io.deephaven.engine.table.*;
import io.deephaven.engine.table.hierarchical.RollupTable;
import io.deephaven.engine.table.hierarchical.TreeTable;
import io.deephaven.engine.table.impl.MemoizedOperationKey.SelectUpdateViewOrUpdateView.Flavor;
import io.deephaven.engine.table.impl.by.*;
import io.deephaven.engine.table.impl.filter.ExtractBarriers;
import io.deephaven.engine.table.impl.filter.ExtractShiftedColumnDefinitions;
import io.deephaven.engine.table.impl.filter.ExtractRespectedBarriers;
import io.deephaven.engine.table.impl.hierarchical.RollupTableImpl;
import io.deephaven.engine.table.impl.hierarchical.TreeTableImpl;
import io.deephaven.engine.table.impl.indexer.DataIndexer;
import io.deephaven.engine.table.impl.lang.QueryLanguageParser;
import io.deephaven.engine.table.impl.partitioned.PartitionedTableImpl;
import io.deephaven.engine.table.impl.perf.BasePerformanceEntry;
import io.deephaven.engine.table.impl.perf.QueryPerformanceNugget;
import io.deephaven.engine.table.impl.perf.QueryPerformanceRecorder;
import io.deephaven.engine.table.impl.rangejoin.RangeJoinOperation;
import io.deephaven.engine.table.impl.remote.ConstructSnapshot;
import io.deephaven.engine.table.impl.select.*;
import io.deephaven.engine.table.impl.select.analyzers.SelectAndViewAnalyzer;
import io.deephaven.engine.table.impl.snapshot.SnapshotIncrementalListener;
import io.deephaven.engine.table.impl.snapshot.SnapshotInternalListener;
import io.deephaven.engine.table.impl.snapshot.SnapshotUtils;
import io.deephaven.engine.table.impl.sources.*;
import io.deephaven.engine.table.impl.sources.ring.RingTableTools;
import io.deephaven.engine.table.impl.sources.sparse.SparseConstants;
import io.deephaven.engine.table.impl.updateby.UpdateBy;
import io.deephaven.engine.table.impl.util.*;
import io.deephaven.engine.table.iterators.*;
import io.deephaven.engine.updategraph.DynamicNode;
import io.deephaven.engine.updategraph.NotificationQueue;
import io.deephaven.engine.updategraph.UpdateGraph;
import io.deephaven.engine.util.IterableUtils;
import io.deephaven.engine.util.TableTools;
import io.deephaven.engine.util.systemicmarking.SystemicObject;
import io.deephaven.engine.util.systemicmarking.SystemicObjectTracker;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.util.SafeCloseable;
import io.deephaven.util.SafeCloseableList;
import io.deephaven.util.annotations.InternalUseOnly;
import io.deephaven.util.annotations.ReferentialIntegrity;
import io.deephaven.util.annotations.TestUseOnly;
import io.deephaven.util.annotations.VisibleForTesting;
import io.deephaven.util.mutable.MutableInt;
import io.deephaven.util.type.ArrayTypeUtils;
import io.deephaven.vector.Vector;
import org.apache.commons.lang3.mutable.Mutable;
import org.apache.commons.lang3.mutable.MutableObject;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.lang.ref.WeakReference;
import java.lang.reflect.Array;
import java.util.*;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.atomic.AtomicReferenceFieldUpdater;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static io.deephaven.engine.table.impl.MatchPair.matchString;
import static io.deephaven.engine.table.impl.partitioned.PartitionedTableCreatorImpl.CONSTITUENT;
import static java.lang.Boolean.TRUE;

/**
 * Primary coalesced table implementation.
 */
public class QueryTable extends BaseTable<QueryTable> {

    public interface Operation<T extends DynamicNode & NotificationStepReceiver> {

        default boolean snapshotNeeded() {
            return true;
        }

        /**
         * The resulting table and listener of the operation.
         */
        class Result<T extends DynamicNode & NotificationStepReceiver> {
            public final T resultNode;
            /**
             * The listener that should be attached to the parent. The listener may be null if the table does not need
             * to respond to ticks from other sources (e.g. the parent is non-refreshing).
             */
            public final TableUpdateListener resultListener;

            public Result(@NotNull final T resultNode) {
                this(resultNode, null);
            }

            /**
             * Construct the result of an operation. The listener may be null if the table does not need to respond to
             * ticks from other sources (e.g. the parent is non-refreshing).
             *
             * @param resultNode the result of the operation
             * @param resultListener the listener that should be attached to the parent (or null)
             */
            public Result(@NotNull final T resultNode,
                    @Nullable final TableUpdateListener resultListener) {
                this.resultNode = resultNode;
                this.resultListener = resultListener;
            }
        }

        /**
         * @return the description of this operation
         */
        String getDescription();

        /**
         * @return the log prefix of this operation
         */
        String getLogPrefix();

        /**
         * Perform pre-instantiation work.
         *
         * @param parent The parent table for the operation
         * @return A {@link SafeCloseable} that will be {@link SafeCloseable#close() closed} when the operation is
         *         complete, whether successful or not
         */
        default SafeCloseable beginOperation(@NotNull final QueryTable parent) {
            return () -> {
            };
        }

        default OperationSnapshotControl newSnapshotControl(final QueryTable parent) {
            return new OperationSnapshotControl(parent);
        }

        /**
         * Initialize this operation.
         *
         * @param usePrev data from the previous cycle should be used (otherwise use this cycle)
         * @param beforeClock the clock value that we captured before the function began; the function can use this
         *        value to bail out early if it notices something has gone wrong.
         * @return the result table / listener if successful, null if it should be retried.
         */
        Result<T> initialize(boolean usePrev, long beforeClock);
    }

    public interface MemoizableOperation<T extends DynamicNode & NotificationStepReceiver> extends Operation<T> {
        /**
         * @return the key that should be used to memoize off of
         */
        MemoizedOperationKey getMemoizedOperationKey();
    }

    private static final long serialVersionUID = 1L;

    static final Logger log = LoggerFactory.getLogger(QueryTable.class);

    // Should we save results of potentially expensive operations (can be disabled for unit tests)
    private static boolean memoizeResults =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.memoizeResults", true);

    /**
     * If set to true, then use a RedirectedColumnSource wrapping an ArrayBackedColumnSource for update() calls.
     * Otherwise, the default of a SparseArraySource is used.
     */
    static boolean USE_REDIRECTED_COLUMNS_FOR_UPDATE =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.redirectUpdate", false);
    /**
     * If set to true, then use a RedirectedColumnSource wrapping an ArrayBackedColumnSource for select() calls.
     * Otherwise, the default of a SparseArraySource is used.
     */
    static boolean USE_REDIRECTED_COLUMNS_FOR_SELECT =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.redirectSelect", false);

    /**
     * If the Configuration property "QueryTable.useDataIndexForWhere" is set to true (default), then permit where
     * filters to use a data index, when applicable. If false, data indexes are not used even if present.
     */
    public static boolean USE_DATA_INDEX_FOR_WHERE =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.useDataIndexForWhere", true);

    /**
     * If the Configuration property "QueryTable.useDataIndexForAggregation" is set to true (default), then permit
     * aggregation to use a data index, when applicable. If false, data indexes are not used even if present.
     */
    public static boolean USE_DATA_INDEX_FOR_AGGREGATION =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.useDataIndexForAggregation", true);

    /**
     * If the Configuration property "QueryTable.useDataIndexForJoins" is set to true (default), then permit naturalJoin
     * and aj to use a data index, when applicable. If false, data indexes are not used even if present.
     */
    public static boolean USE_DATA_INDEX_FOR_JOINS =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.useDataIndexForJoins", true);


    /**
     * For a static select(), we would prefer to flatten the table to avoid using memory unnecessarily (because the data
     * may be spread out across many blocks depending on the input RowSet). However, the select() can become slower
     * because it must look things up in a row redirection.
     * <p>
     * Values less than zero disable overhead checking, and result in never flattening the input.
     * <p>
     * A value of zero results in always flattening the input.
     */
    private static final double MAXIMUM_STATIC_SELECT_MEMORY_OVERHEAD =
            Configuration.getInstance().getDoubleWithDefault("QueryTable.maximumStaticSelectMemoryOverhead", 1.1);

    /**
     * For unit tests we may like to force parallel where computation to exercise the multiple notification path.
     */
    static boolean FORCE_PARALLEL_WHERE =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.forceParallelWhere", false);
    /**
     * For unit tests we may like to disable parallel where computation to exercise the single notification path.
     */
    static boolean DISABLE_PARALLEL_WHERE =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.disableParallelWhere", false);


    private static final ThreadLocal<Boolean> disableParallelWhereForThread = ThreadLocal.withInitial(() -> null);

    /**
     * The size of parallel where segments.
     */
    static long PARALLEL_WHERE_ROWS_PER_SEGMENT =
            Configuration.getInstance().getLongWithDefault("QueryTable.parallelWhereRowsPerSegment", 1 << 16);
    /**
     * The size of parallel where segments.
     */
    static int PARALLEL_WHERE_SEGMENTS =
            Configuration.getInstance().getIntegerWithDefault("QueryTable.parallelWhereSegments", -1);

    /**
     * Disable the usage of parquet row group metadata during push-down filtering.
     */
    public static boolean DISABLE_WHERE_PUSHDOWN_PARQUET_ROW_GROUP_METADATA =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.disableWherePushdownParquetRowGroupMetadata",
                    false);

    /**
     * Disable the usage of local data file indexes during push-down filtering.
     */
    public static boolean DISABLE_WHERE_PUSHDOWN_DATA_INDEX =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.disableWherePushdownDataIndex", false);

    /**
     * You can choose to enable or disable the column parallel select and update.
     */
    static boolean ENABLE_PARALLEL_SELECT_AND_UPDATE =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.enableParallelSelectAndUpdate", true);

    /**
     * Minimum select "chunk" size, defaults to 4 million.
     */
    public static long MINIMUM_PARALLEL_SELECT_ROWS =
            Configuration.getInstance().getLongWithDefault("QueryTable.minimumParallelSelectRows", 1L << 22);

    /**
     * For unit tests, we do want to force the column parallel select and update at times.
     */
    static boolean FORCE_PARALLEL_SELECT_AND_UPDATE =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.forceParallelSelectAndUpdate", false);

    /**
     * You can choose to enable or disable the parallel snapshot.
     */
    public static boolean ENABLE_PARALLEL_SNAPSHOT =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.enableParallelSnapshot", true);

    /**
     * Minimum snapshot "chunk" size for parallel reading of columns, defaults to 1 million.
     */
    public static long MINIMUM_PARALLEL_SNAPSHOT_ROWS =
            Configuration.getInstance().getLongWithDefault("QueryTable.minimumParallelSnapshotRows", 1L << 20);

    /**
     * If set to true, then the default behavior of condition filters is to be stateless. Stateless filters are allowed
     * to be processed in parallel by the engine.
     */
    public static boolean STATELESS_FILTERS_BY_DEFAULT =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.statelessFiltersByDefault", false);


    @VisibleForTesting
    public static boolean USE_CHUNKED_CROSS_JOIN =
            Configuration.getInstance().getBooleanWithDefault("QueryTable.chunkedJoin", true);

    private static final AtomicReferenceFieldUpdater<QueryTable, ModifiedColumnSet> MODIFIED_COLUMN_SET_UPDATER =
            AtomicReferenceFieldUpdater.newUpdater(QueryTable.class, ModifiedColumnSet.class, "modifiedColumnSet");
    private static final AtomicReferenceFieldUpdater<QueryTable, Map> CACHED_OPERATIONS_UPDATER =
            AtomicReferenceFieldUpdater.newUpdater(QueryTable.class, Map.class, "cachedOperations");
    private static final Map<MemoizedOperationKey, MemoizedResult<?>> EMPTY_CACHED_OPERATIONS = Collections.emptyMap();

    private final TrackingRowSet rowSet;
    private final LinkedHashMap<String, ColumnSource<?>> columns;
    @SuppressWarnings("FieldMayBeFinal") // Set via MODIFIED_COLUMN_SET_UPDATER if not initialized
    private volatile ModifiedColumnSet modifiedColumnSet;

    // Flattened table support
    private boolean flat;

    // Cached results
    @SuppressWarnings("FieldMayBeFinal") // Set via CACHED_OPERATIONS_UPDATER
    private volatile Map<MemoizedOperationKey, MemoizedResult<?>> cachedOperations = EMPTY_CACHED_OPERATIONS;

    /**
     * Creates a new table, inferring a definition but creating a new column source map.
     *
     * @param rowSet The RowSet of the new table. Callers may need to {@link WritableRowSet#toTracking() convert}.
     * @param columns The column source map for the table, which will be copied into a new column source map
     */
    public QueryTable(
            @NotNull final TrackingRowSet rowSet,
            @NotNull final Map<String, ? extends ColumnSource<?>> columns) {
        this(TableDefinition.inferFrom(columns).intern(),
                Require.neqNull(rowSet, "rowSet"), new LinkedHashMap<>(columns), null, null);
    }

    /**
     * Creates a new table, reusing a definition but creating a new column source map.
     *
     * @param definition The definition to use for this table, which will be re-ordered to match the same order as
     *        {@code columns} if it does not match
     * @param rowSet The RowSet of the new table. Callers may need to {@link WritableRowSet#toTracking() convert}.
     * @param columns The column source map for the table, which will be copied into a new column source map
     */
    public QueryTable(
            @NotNull final TableDefinition definition,
            @NotNull final TrackingRowSet rowSet,
            @NotNull final Map<String, ? extends ColumnSource<?>> columns) {
        this(definition.checkMutualCompatibility(TableDefinition.inferFrom(columns)).intern(),
                Require.neqNull(rowSet, "rowSet"), new LinkedHashMap<>(columns), null, null);
    }

    /**
     * Creates a new table, reusing a definition and column source map.
     *
     * @param definition The definition to use for this table, which will not be validated or re-ordered.
     * @param rowSet The RowSet of the new table. Callers may need to {@link WritableRowSet#toTracking() convert}.
     * @param columns The column source map for the table, which is not copied.
     * @param modifiedColumnSet Optional {@link ModifiedColumnSet} that should be re-used if supplied
     * @param attributes Optional value to use for initial attributes
     */
    public QueryTable(
            @NotNull final TableDefinition definition,
            @NotNull final TrackingRowSet rowSet,
            @NotNull final LinkedHashMap<String, ColumnSource<?>> columns,
            @Nullable final ModifiedColumnSet modifiedColumnSet,
            @Nullable final Map<String, Object> attributes) {
        super(definition, "QueryTable", attributes); // TODO: Better descriptions composed from query chain
        this.rowSet = rowSet;
        this.columns = columns;
        this.modifiedColumnSet = modifiedColumnSet;
    }

    /**
     * Create a new query table with the {@link ColumnDefinition ColumnDefinitions} of {@code template}, but in the
     * order of {@code this}. The tables must be mutually compatible, as defined via
     * {@link TableDefinition#checkMutualCompatibility(TableDefinition)}.
     *
     * @param template the new definition template to use
     * @return the new query table
     * @deprecated this is being used a workaround for testing purposes where previously mutations were being used at
     *             the {@link ColumnDefinition} level. Do not use this method without good reason.
     */
    @Deprecated
    public QueryTable withDefinitionUnsafe(TableDefinition template) {
        final TableDefinition inOrder = template.checkMutualCompatibility(definition);
        return (QueryTable) copy(inOrder, StandardOptions.COPY_ALL);
    }

    @Override
    public TrackingRowSet getRowSet() {
        return rowSet;
    }

    @Override
    public long size() {
        return rowSet.size();
    }

    @Override
    public <T> ColumnSource<T> getColumnSource(String sourceName) {
        final ColumnSource<?> columnSource = columns.get(sourceName);
        if (columnSource == null) {
            throw new NoSuchColumnException(columns.keySet(), sourceName);
        }
        // noinspection unchecked
        return (ColumnSource<T>) columnSource;
    }

    @Override
    public Map<String, ColumnSource<?>> getColumnSourceMap() {
        return Collections.unmodifiableMap(columns);
    }

    @Override
    public Collection<? extends ColumnSource<?>> getColumnSources() {
        return Collections.unmodifiableCollection(columns.values());
    }

    // region Column Iterators

    @Override
    public <TYPE> CloseableIterator<TYPE> columnIterator(@NotNull final String columnName) {
        return ChunkedColumnIterator.make(getColumnSource(columnName), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfChar characterColumnIterator(@NotNull final String columnName) {
        return new ChunkedCharacterColumnIterator(getColumnSource(columnName, char.class), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfByte byteColumnIterator(@NotNull final String columnName) {
        return new ChunkedByteColumnIterator(getColumnSource(columnName, byte.class), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfShort shortColumnIterator(@NotNull final String columnName) {
        return new ChunkedShortColumnIterator(getColumnSource(columnName, short.class), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfInt integerColumnIterator(@NotNull final String columnName) {
        return new ChunkedIntegerColumnIterator(getColumnSource(columnName, int.class), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfLong longColumnIterator(@NotNull final String columnName) {
        return new ChunkedLongColumnIterator(getColumnSource(columnName, long.class), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfFloat floatColumnIterator(@NotNull final String columnName) {
        return new ChunkedFloatColumnIterator(getColumnSource(columnName, float.class), getRowSet());
    }

    @Override
    public CloseablePrimitiveIteratorOfDouble doubleColumnIterator(@NotNull final String columnName) {
        return new ChunkedDoubleColumnIterator(getColumnSource(columnName, double.class), getRowSet());
    }

    @Override
    public <DATA_TYPE> CloseableIterator<DATA_TYPE> objectColumnIterator(@NotNull final String columnName) {
        return new ChunkedObjectColumnIterator<>(getColumnSource(columnName, Object.class), getRowSet());
    }

    @Override
    public <DATA_TYPE> CloseableIterator<DATA_TYPE> objectColumnIterator(@NotNull final String columnName,
            @NotNull Class<? extends DATA_TYPE> clazz) {
        return new ChunkedObjectColumnIterator<>(getColumnSource(columnName, clazz), getRowSet());
    }

    // endregion Column Iterators

    /**
     * Producers of tables should use the modified column set embedded within the table for their result.
     * <p>
     * You must not mutate the result of this method if you are not generating the updates for this table. Callers
     * should not rely on the dirty state of this modified column set.
     *
     * @return the modified column set for this table
     */
    public ModifiedColumnSet getModifiedColumnSetForUpdates() {
        return FieldUtils.ensureField(this, MODIFIED_COLUMN_SET_UPDATER, null, () -> new ModifiedColumnSet(columns));
    }

    /**
     * Create a {@link ModifiedColumnSet} to use when propagating updates from this table.
     *
     * @param columnNames The columns that should belong to the resulting set
     * @return The resulting ModifiedColumnSet for the given columnNames
     */
    public ModifiedColumnSet newModifiedColumnSet(final String... columnNames) {
        if (columnNames.length == 0) {
            return ModifiedColumnSet.EMPTY;
        }
        final ModifiedColumnSet newSet = new ModifiedColumnSet(getModifiedColumnSetForUpdates());
        newSet.setAll(columnNames);
        return newSet;
    }

    /**
     * Create a {@link ModifiedColumnSet.Transformer} that can be used to propagate dirty columns from this table to
     * listeners of the provided resultTable.
     *
     * @param resultTable the destination table
     * @param columnNames the columns that map one-to-one with the result table
     * @return a transformer that passes dirty details via an identity mapping
     */
    public ModifiedColumnSet.Transformer newModifiedColumnSetTransformer(QueryTable resultTable,
            String... columnNames) {
        final ModifiedColumnSet[] columnSets = new ModifiedColumnSet[columnNames.length];
        for (int i = 0; i < columnNames.length; ++i) {
            columnSets[i] = resultTable.newModifiedColumnSet(columnNames[i]);
        }
        return newModifiedColumnSetTransformer(columnNames, columnSets);
    }

    /**
     * Create a {@link ModifiedColumnSet.Transformer} that can be used to propagate dirty columns from this table to
     * listeners of the provided resultTable.
     *
     * @param resultTable the destination table
     * @param matchPairs the columns that map one-to-one with the result table
     * @return a transformer that passes dirty details via an identity mapping
     */
    public ModifiedColumnSet.Transformer newModifiedColumnSetTransformer(
            @NotNull final QueryTable resultTable,
            @NotNull final MatchPair... matchPairs) {
        final ModifiedColumnSet[] columnSets = new ModifiedColumnSet[matchPairs.length];
        for (int ii = 0; ii < matchPairs.length; ++ii) {
            columnSets[ii] = resultTable.newModifiedColumnSet(matchPairs[ii].leftColumn());
        }
        return newModifiedColumnSetTransformer(MatchPair.getRightColumns(matchPairs), columnSets);
    }

    /**
     * Create a {@link ModifiedColumnSet.Transformer} that can be used to propagate dirty columns from this table to
     * listeners of the provided resultTable.
     *
     * @param resultTable the destination table
     * @param pairs the columns that map one-to-one with the result table
     * @return a transformer that passes dirty details via an identity mapping
     */
    public ModifiedColumnSet.Transformer newModifiedColumnSetTransformer(
            @NotNull final QueryTable resultTable,
            @NotNull final Pair... pairs) {
        return newModifiedColumnSetTransformer(
                Arrays.stream(pairs)
                        .map(Pair::output)
                        .map(ColumnName::name)
                        .toArray(String[]::new),
                Arrays.stream(pairs)
                        .map(pair -> resultTable.newModifiedColumnSet(pair.input().name()))
                        .toArray(ModifiedColumnSet[]::new));
    }

    /**
     * Create a {@link ModifiedColumnSet.Transformer} that can be used to propagate dirty columns from this table to
     * listeners of the table used to construct columnSets. It is an error if {@code columnNames} and {@code columnSets}
     * are not the same length. The transformer will mark {@code columnSets[i]} as dirty if the column represented by
     * {@code columnNames[i]} is dirty.
     *
     * @param columnNames the source columns
     * @param columnSets the destination columns in the convenient ModifiedColumnSet form
     * @return a transformer that knows the dirty details
     */
    public ModifiedColumnSet.Transformer newModifiedColumnSetTransformer(final String[] columnNames,
            final ModifiedColumnSet[] columnSets) {
        return getModifiedColumnSetForUpdates().newTransformer(columnNames, columnSets);
    }

    /**
     * Create a transformer that uses an identity mapping from one ColumnSourceMap to another. The two CSMs must have
     * equivalent column names and column ordering.
     *
     * @param newColumns the column source map for result table
     * @return a simple Transformer that makes a cheap, but CSM compatible copy
     */
    public ModifiedColumnSet.Transformer newModifiedColumnSetIdentityTransformer(
            final Map<String, ColumnSource<?>> newColumns) {
        return getModifiedColumnSetForUpdates().newIdentityTransformer(newColumns);
    }

    /**
     * Create a transformer that uses an identity mapping from one Table another. The two tables must have equivalent
     * column names and column ordering.
     *
     * @param other the result table
     * @return a simple Transformer that makes a cheap, but CSM compatible copy
     */
    public ModifiedColumnSet.Transformer newModifiedColumnSetIdentityTransformer(final Table other) {
        if (other instanceof QueryTable) {
            return getModifiedColumnSetForUpdates().newIdentityTransformer(((QueryTable) other).columns);
        }
        return getModifiedColumnSetForUpdates().newIdentityTransformer(other.getColumnSourceMap());
    }

    @Override
    public PartitionedTable partitionBy(final boolean dropKeys, final String... keyColumnNames) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (isBlink()) {
                throw unsupportedForBlinkTables("partitionBy");
            }
            final List<ColumnName> columns = ColumnName.from(keyColumnNames);
            return memoizeResult(MemoizedOperationKey.partitionBy(dropKeys, columns), () -> {
                final Table partitioned = aggBy(Partition.of(CONSTITUENT, !dropKeys), columns);
                final Set<String> keyColumnNamesSet =
                        Arrays.stream(keyColumnNames).collect(Collectors.toCollection(LinkedHashSet::new));
                final TableDefinition constituentDefinition;
                if (dropKeys) {
                    constituentDefinition = TableDefinition.of(definition.getColumnStream()
                            .filter(cd -> !keyColumnNamesSet.contains(cd.getName())).toArray(ColumnDefinition[]::new));
                } else {
                    constituentDefinition = definition;
                }
                return new PartitionedTableImpl(partitioned, keyColumnNamesSet, true, CONSTITUENT.name(),
                        constituentDefinition, isRefreshing(), false);
            });
        }
    }

    @Override
    public PartitionedTable partitionedAggBy(final Collection<? extends Aggregation> aggregations,
            final boolean preserveEmpty, @Nullable final Table initialGroups, final String... keyColumnNames) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (isBlink()) {
                throw unsupportedForBlinkTables("partitionedAggBy");
            }
            final Optional<Partition> includedPartition = aggregations.stream()
                    .filter(agg -> agg instanceof Partition)
                    .map(agg -> (Partition) agg)
                    .findFirst();
            final Partition partition = includedPartition.orElseGet(() -> Partition.of(CONSTITUENT));
            final Collection<? extends Aggregation> aggregationsToUse = includedPartition.isPresent()
                    ? aggregations
                    : Stream.concat(aggregations.stream(), Stream.of(partition)).collect(Collectors.toList());
            final Table aggregated =
                    aggBy(aggregationsToUse, preserveEmpty, initialGroups, ColumnName.from(keyColumnNames));
            final Set<String> keyColumnNamesSet =
                    Arrays.stream(keyColumnNames).collect(Collectors.toCollection(LinkedHashSet::new));
            final TableDefinition constituentDefinition;
            if (partition.includeGroupByColumns()) {
                constituentDefinition = definition;
            } else {
                constituentDefinition = TableDefinition.of(definition.getColumnStream()
                        .filter(cd -> !keyColumnNamesSet.contains(cd.getName())).toArray(ColumnDefinition[]::new));
            }
            return new PartitionedTableImpl(aggregated, keyColumnNamesSet, true, partition.column().name(),
                    constituentDefinition, isRefreshing(), false);
        }
    }

    @Override
    public RollupTable rollup(final Collection<? extends Aggregation> aggregations, final boolean includeConstituents,
            final Collection<? extends ColumnName> groupByColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (isBlink() && includeConstituents) {
                throw unsupportedForBlinkTables("rollup with included constituents");
            }
            return memoizeResult(MemoizedOperationKey.rollup(aggregations, groupByColumns, includeConstituents),
                    () -> RollupTableImpl.makeRollup(this, aggregations, includeConstituents, groupByColumns));
        }
    }

    @Override
    public TreeTable tree(String idColumn, String parentColumn) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (isBlink()) {
                throw unsupportedForBlinkTables("tree");
            }
            return memoizeResult(MemoizedOperationKey.tree(idColumn, parentColumn),
                    () -> TreeTableImpl.makeTree(this, ColumnName.of(idColumn), ColumnName.of(parentColumn)));
        }
    }

    @Override
    public Table slice(final long firstPositionInclusive, final long lastPositionExclusive) {
        if (isBlink()) {
            throw unsupportedForBlinkTables("slice");
        }
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (firstPositionInclusive == lastPositionExclusive) {
                return getSubTable(RowSetFactory.empty().toTracking());
            }
            return getResult(SliceLikeOperation.slice(this, firstPositionInclusive, lastPositionExclusive, "slice"));
        }
    }

    @Override
    public Table slicePct(final double startPercentInclusive, final double endPercentExclusive) {
        if (isBlink()) {
            throw unsupportedForBlinkTables("slicePct");
        }
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return getResult(SliceLikeOperation.slicePct(this, startPercentInclusive, endPercentExclusive));
        }
    }

    @Override
    public Table head(final long size) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (size == 0) {
                return getSubTable(RowSetFactory.empty().toTracking());
            }
            if (isBlink()) {
                // The operation initialization and listener registration is handled inside BlinkTableTools
                return BlinkTableTools.blinkToAppendOnly(this, Require.geqZero(size, "size"));
            }
            return getResult(SliceLikeOperation.slice(this, 0, Require.geqZero(size, "size"), "head"));
        }
    }

    @Override
    public Table tail(final long size) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (size == 0) {
                return getSubTable(RowSetFactory.empty().toTracking());
            }
            if (isBlink()) {
                // The operation initialization and listener registration is handled inside BlinkTableTools
                return RingTableTools.of(this, Math.toIntExact(Require.geqZero(size, "size")));
            }
            return getResult(SliceLikeOperation.slice(this, -Require.geqZero(size, "size"), 0, "tail"));
        }
    }

    @Override
    public Table headPct(final double percent) {
        if (isBlink()) {
            throw unsupportedForBlinkTables("headPct");
        }
        if (percent < 0 || percent > 1) {
            throw new IllegalArgumentException(
                    "percentage of rows must be between [0,1]: percent=" + percent);
        }
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return getResult(SliceLikeOperation.headPct(this, percent));
        }
    }

    @Override
    public Table tailPct(final double percent) {
        if (isBlink()) {
            throw unsupportedForBlinkTables("tailPct");
        }
        if (percent < 0 || percent > 1) {
            throw new IllegalArgumentException(
                    "percentage of rows must be between [0,1]: percent=" + percent);
        }
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return getResult(SliceLikeOperation.tailPct(this, percent));
        }
    }

    @Override
    public Table exactJoin(
            Table rightTable,
            Collection<? extends JoinMatch> columnsToMatch,
            Collection<? extends JoinAddition> columnsToAdd) {
        return exactJoinImpl(
                rightTable,
                MatchPair.fromMatches(columnsToMatch),
                MatchPair.fromAddition(columnsToAdd));
    }

    private Table exactJoinImpl(Table table, MatchPair[] columnsToMatch, MatchPair[] columnsToAdd) {
        final UpdateGraph updateGraph = getUpdateGraph(table);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget(
                    "exactJoin(" + table + "," + Arrays.toString(columnsToMatch) + "," + Arrays.toString(columnsToMatch)
                            + ")",
                    sizeForInstrumentation(),
                    () -> naturalJoinInternal(table, columnsToMatch, columnsToAdd, NaturalJoinType.EXACTLY_ONE_MATCH));
        }
    }

    private static String toString(Collection<? extends Selectable> groupByList) {
        return groupByList.stream().map(Strings::of).collect(Collectors.joining(",", "[", "]"));
    }

    @Override
    public Table aggAllBy(AggSpec spec, ColumnName... groupByColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            for (ColumnName name : AggSpecColumnReferences.of(spec)) {
                if (!hasColumns(name.name())) {
                    throw new IllegalArgumentException(
                            "aggAllBy spec references column that does not exist: spec=" + spec + ", groupByColumns="
                                    + toString(Arrays.asList(groupByColumns)));
                }
            }
            final List<ColumnName> groupByList = Arrays.asList(groupByColumns);
            final List<ColumnName> tableColumns = definition.getTypedColumnNames();
            final Optional<Aggregation> agg = singleAggregation(spec, groupByList, tableColumns);
            if (agg.isEmpty()) {
                throw new IllegalArgumentException(
                        "aggAllBy has no columns to aggregate: spec=" + spec + ", groupByColumns="
                                + toString(groupByList));
            }
            final List<? extends Aggregation> aggs = List.of(agg.get());
            final MemoizedOperationKey aggKey = MemoizedOperationKey.aggBy(aggs, false, null, groupByList);
            return memoizeResult(aggKey, () -> {
                final QueryTable result =
                        aggNoMemo(AggregationProcessor.forAggregation(aggs), false, null, groupByList);
                spec.walk(new AggAllByCopyAttributes(this, result));
                return result;
            });
        }
    }

    /**
     * Computes the single-aggregation from the agg-all implied by the {@code spec} and {@code groupByColumns} by
     * removing the {@code groupByColumns} and any extra columns implied by the {@code spec}.
     *
     * @param spec the spec
     * @param groupByColumns the group by columns
     * @param tableColumns the table columns
     * @return the aggregation, if non-empty
     */
    @VisibleForTesting
    static Optional<Aggregation> singleAggregation(
            AggSpec spec, Collection<? extends ColumnName> groupByColumns,
            Collection<? extends ColumnName> tableColumns) {
        Set<ColumnName> exclusions = AggregateAllExclusions.of(spec, groupByColumns, tableColumns);
        List<ColumnName> columnsToAgg = new ArrayList<>(tableColumns.size());
        for (ColumnName column : tableColumns) {
            if (exclusions.contains(column)) {
                continue;
            }
            columnsToAgg.add(column);
        }
        return columnsToAgg.isEmpty() ? Optional.empty() : Optional.of(spec.aggregation(columnsToAgg));
    }

    @Override
    public Table aggBy(
            final Collection<? extends Aggregation> aggregations,
            final boolean preserveEmpty,
            final Table initialGroups,
            final Collection<? extends ColumnName> groupByColumns) {
        final UpdateGraph updateGraph = getUpdateGraph(initialGroups);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (aggregations.isEmpty()) {
                throw new IllegalArgumentException(
                        "aggBy must have at least one aggregation, none specified. groupByColumns="
                                + toString(groupByColumns));
            }
            final List<? extends Aggregation> optimized = AggregationOptimizer.of(aggregations);
            final MemoizedOperationKey aggKey =
                    MemoizedOperationKey.aggBy(optimized, preserveEmpty, initialGroups, groupByColumns);
            final Table aggregationTable = memoizeResult(aggKey, () -> aggNoMemo(
                    AggregationProcessor.forAggregation(optimized), preserveEmpty, initialGroups, groupByColumns));

            final List<ColumnName> optimizedOrder = AggregationOutputs.of(optimized).collect(Collectors.toList());
            final List<ColumnName> userOrder = AggregationOutputs.of(aggregations).collect(Collectors.toList());
            if (userOrder.equals(optimizedOrder)) {
                return aggregationTable;
            }

            // We need to re-order the result columns to match the user-provided order
            final List<ColumnName> resultOrder =
                    Stream.concat(groupByColumns.stream(), userOrder.stream()).collect(Collectors.toList());
            return aggregationTable.view(resultOrder);
        }
    }

    public QueryTable aggNoMemo(
            @NotNull final AggregationContextFactory aggregationContextFactory,
            final boolean preserveEmpty,
            @Nullable final Table initialGroups,
            @NotNull final Collection<? extends ColumnName> groupByColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final String description = "aggregation(" + aggregationContextFactory + ", " + groupByColumns + ")";
            final AggregationControl aggregationControl =
                    USE_DATA_INDEX_FOR_AGGREGATION ? AggregationControl.DEFAULT : AggregationControl.IGNORE_INDEXING;
            return QueryPerformanceRecorder.withNugget(description, sizeForInstrumentation(),
                    () -> ChunkedOperatorAggregationHelper.aggregation(aggregationControl,
                            aggregationContextFactory, this, preserveEmpty, initialGroups, groupByColumns));
        }
    }

    private static UnsupportedOperationException unsupportedForBlinkTables(@NotNull final String operationName) {
        return new UnsupportedOperationException("Blink tables do not support " + operationName
                + "; use BlinkTableTools.blinkToAppendOnly to accumulate full history");
    }

    @Override
    public Table headBy(long nRows, String... groupByColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget("headBy(" + nRows + ", " + Arrays.toString(groupByColumns) + ")",
                    sizeForInstrumentation(), () -> headOrTailBy(nRows, true, groupByColumns));
        }
    }

    @Override
    public Table tailBy(long nRows, String... groupByColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget("tailBy(" + nRows + ", " + Arrays.toString(groupByColumns) + ")",
                    sizeForInstrumentation(), () -> headOrTailBy(nRows, false, groupByColumns));
        }
    }

    private Table headOrTailBy(long nRows, boolean head, String... groupByColumns) {
        checkInitiateOperation();

        Require.gtZero(nRows, "nRows");

        final Set<String> groupByColsSet = new HashSet<>(Arrays.asList(groupByColumns));
        final List<String> colNames = getDefinition().getColumnNames();

        // Iterate through the columns and build updateView() arguments that will trim the columns to nRows rows
        String[] updates = new String[colNames.size() - groupByColumns.length];
        String[] casting = new String[colNames.size() - groupByColumns.length];
        for (int i = 0, j = 0; i < colNames.size(); i++) {
            String colName = colNames.get(i);
            if (!groupByColsSet.contains(colName)) {
                final Class<?> dataType = getDefinition().getColumn(colName).getDataType();
                casting[j] = colName + " = " + getCastFormula(dataType) + colName;
                if (head)
                    updates[j++] =
                            // Get the first nRows rows:
                            // colName = isNull(colName) ? null
                            // : colName.size() > nRows ? colName.subVector(0, nRows)
                            // : colName
                            String.format(
                                    "%s=isNull(%s) ? null" +
                                            ":%s.size() > %d ? %s.subVector(0, %d)" +
                                            ":%s",
                                    colName, colName, colName, nRows, colName, nRows, colName);
                else
                    updates[j++] =
                            // Get the last nRows rows:
                            // colName = isNull(colName) ? null
                            // : colName.size() > nRows ? colName.subVector(colName.size() - nRows, colName.size())
                            // : colName
                            String.format(
                                    "%s=isNull(%s) ? null" +
                                            ":%s.size() > %d ? %s.subVector(%s.size() - %d, %s.size())" +
                                            ":%s",
                                    colName, colName, colName, nRows, colName, colName, nRows, colName, colName);
            }
        }

        final List<Aggregation> aggs = colNames.stream()
                .filter(cn -> !groupByColsSet.contains(cn))
                .map(Aggregation::AggGroup)
                .collect(Collectors.toList());
        return aggBy(aggs, groupByColumns).updateView(updates).ungroup().updateView(casting);
    }

    @NotNull
    private String getCastFormula(Class<?> dataType) {
        return "(" + getCastFormulaInternal(dataType) + ")";
    }

    @NotNull
    private String getCastFormulaInternal(Class<?> dataType) {
        if (dataType.isPrimitive()) {
            if (dataType == int.class) {
                return "int";
            } else if (dataType == short.class) {
                return "short";
            } else if (dataType == long.class) {
                return "long";
            } else if (dataType == char.class) {
                return "char";
            } else if (dataType == byte.class) {
                return "byte";
            } else if (dataType == float.class) {
                return "float";
            } else if (dataType == double.class) {
                return "double";
            } else if (dataType == boolean.class) {
                return "Boolean";
            }
            throw Assert.statementNeverExecuted("Unknown primitive: " + dataType);
        } else if (dataType.isArray()) {
            return getCastFormulaInternal(dataType.getComponentType()) + "[]";
        } else {
            return dataType.getName();
        }
    }

    @Override
    public Table moveColumns(final int index, String... columnsToMove) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return renameColumnsImpl("moveColumns(" + index + ", ", Math.max(0, index),
                    Pair.from(columnsToMove));
        }
    }

    public static class FilteredTable extends QueryTable implements WhereFilter.RecomputeListener {
        private final QueryTable source;
        private boolean refilterMatchedRequested = false;
        private boolean refilterUnmatchedRequested = false;
        private WritableRowSet refilterRequestedRowset = null;
        private MergedListener whereListener;

        @ReferentialIntegrity
        Runnable delayedErrorReference;

        public FilteredTable(final TrackingRowSet currentMapping, final QueryTable source) {
            super(source.getDefinition(), currentMapping, source.columns, null, null);
            this.source = source;
        }

        @Override
        public void requestRecompute() {
            refilterMatchedRequested = refilterUnmatchedRequested = true;
            Require.neqNull(whereListener, "whereListener").notifyChanges();
        }

        @Override
        public void requestRecomputeUnmatched() {
            refilterUnmatchedRequested = true;
            Require.neqNull(whereListener, "whereListener").notifyChanges();
        }

        /**
         * Called if something about the filters has changed such that all matched rows of the source table should be
         * re-evaluated.
         */
        @Override
        public void requestRecomputeMatched() {
            refilterMatchedRequested = true;
            Require.neqNull(whereListener, "whereListener").notifyChanges();
        }

        @Override
        public void requestRecompute(RowSet rowSet) {
            if (refilterRequestedRowset == null) {
                refilterRequestedRowset = rowSet.copy();
            } else {
                refilterRequestedRowset.insert(rowSet);
            }
            Require.neqNull(whereListener, "whereListener").notifyChanges();
        }

        /**
         * Note that refilterRequested is only accessible so that {@link WhereListener} can get to it and is not part of
         * the public API.
         *
         * @return true if this table must be fully refiltered
         */
        @InternalUseOnly
        boolean refilterRequested() {
            return refilterUnmatchedRequested || refilterMatchedRequested || refilterRequestedRowset != null;
        }

        @NotNull
        @Override
        public FilteredTable getTable() {
            return this;
        }

        @Override
        public void setIsRefreshing(boolean refreshing) {
            setRefreshing(refreshing);
        }

        /**
         * Refilter relevant rows.
         * <p>
         * This method is not part of the public API, and is only exposed so that {@link WhereListener} can access it.
         *
         * @param upstream the upstream update
         */
        @InternalUseOnly
        void doRefilter(
                final WhereListener listener,
                final TableUpdate upstream) {
            final TableUpdateImpl update = new TableUpdateImpl();
            if (upstream == null) {
                update.modifiedColumnSet = getModifiedColumnSetForUpdates();
                update.modifiedColumnSet.clear();
            } else {
                // we need to hold on to the upstream update until we are completely done with it
                upstream.acquire();
                update.modifiedColumnSet = upstream.modifiedColumnSet();
            }

            // Remove upstream keys first, so that keys at rows that were removed and then added are propagated as such.
            // Note that it is a failure to propagate these as modifies, since modifiedColumnSet may not mark that all
            // columns have changed.
            update.removed = upstream == null
                    ? RowSetFactory.empty()
                    : getRowSet().writableCast().extract(upstream.removed());

            // Update our rowSet and compute removals due to splatting.
            if (upstream != null && upstream.shifted().nonempty()) {
                upstream.shifted().apply(getRowSet().writableCast());
            }

            if (refilterMatchedRequested && refilterUnmatchedRequested) {
                final WhereListener.ListenerFilterExecution filterExecution =
                        listener.makeRefilterExecution(source.getRowSet().copy());
                filterExecution.scheduleCompletion(
                        (matchedRows, unusedMods) -> completeRefilterUpdate(listener, upstream, update, matchedRows),
                        exception -> errorRefilterUpdate(listener, exception, upstream));
                refilterMatchedRequested = refilterUnmatchedRequested = false;
                if (refilterRequestedRowset != null) {
                    refilterRequestedRowset.close();
                    refilterRequestedRowset = null;
                }
            } else if (refilterUnmatchedRequested) {
                // things that are added or removed are already reflected in source.getRowSet
                final WritableRowSet unmatchedRows = source.getRowSet().minus(getRowSet());
                // we must check rows that have been modified instead of just preserving them
                if (upstream != null) {
                    unmatchedRows.insert(upstream.modified());
                }
                if (refilterRequestedRowset != null) {
                    unmatchedRows.insert(refilterRequestedRowset);
                    refilterRequestedRowset.close();
                    refilterRequestedRowset = null;
                }
                final WhereListener.ListenerFilterExecution filterExecution =
                        listener.makeRefilterExecution(unmatchedRows);
                filterExecution.scheduleCompletion((adds, unusedMods) -> {
                    final WritableRowSet newMapping = adds.writableCast();
                    // add back what we previously matched, but for modifications and removals
                    try (final WritableRowSet previouslyMatched = getRowSet().copy()) {
                        if (upstream != null) {
                            previouslyMatched.remove(upstream.added());
                            previouslyMatched.remove(upstream.modified());
                        }
                        newMapping.insert(previouslyMatched);
                    }
                    completeRefilterUpdate(listener, upstream, update, adds);
                }, exception -> errorRefilterUpdate(listener, exception, upstream));
                refilterUnmatchedRequested = false;
            } else if (refilterMatchedRequested) {
                // we need to take removed rows out of our rowSet so we do not read them, and also examine added or
                // modified rows
                final WritableRowSet matchedRows = getRowSet().copy();
                if (upstream != null) {
                    matchedRows.insert(upstream.added());
                    matchedRows.insert(upstream.modified());
                }
                if (refilterRequestedRowset != null) {
                    matchedRows.insert(refilterRequestedRowset);
                    refilterRequestedRowset.close();
                    refilterRequestedRowset = null;
                }

                final WhereListener.ListenerFilterExecution filterExecution =
                        listener.makeRefilterExecution(matchedRows);
                filterExecution.scheduleCompletion(
                        (adds, unusedMods) -> completeRefilterUpdate(listener, upstream, update, adds),
                        exception -> errorRefilterUpdate(listener, exception, upstream));
                refilterMatchedRequested = false;
            } else if (refilterRequestedRowset != null) {
                final WritableRowSet rowsToFilter = refilterRequestedRowset;
                if (upstream != null) {
                    rowsToFilter.insert(upstream.added());
                    rowsToFilter.insert(upstream.modified());
                }

                final WhereListener.ListenerFilterExecution filterExecution =
                        listener.makeRefilterExecution(rowsToFilter);

                filterExecution.scheduleCompletion((adds, unusedMods) -> {
                    final WritableRowSet newMapping = adds.writableCast();
                    // add back what we previously matched, except for modifications and removals
                    try (final WritableRowSet previouslyMatched = getRowSet().copy()) {
                        previouslyMatched.remove(rowsToFilter);
                        newMapping.insert(previouslyMatched);
                    }
                    completeRefilterUpdate(listener, upstream, update, adds);
                }, exception -> errorRefilterUpdate(listener, exception, upstream));


                refilterRequestedRowset = null;
            } else {
                throw new IllegalStateException("Refilter called when a refilter was not requested!");
            }
        }

        private void completeRefilterUpdate(
                final WhereListener listener,
                final TableUpdate upstream,
                final TableUpdateImpl update,
                final RowSet newMapping) {
            // Compute added/removed in post-shift keyspace.
            update.added = newMapping.minus(getRowSet());

            try (final WritableRowSet postShiftRemovals = getRowSet().minus(newMapping)) {
                getRowSet().writableCast().resetTo(newMapping);

                // Note that removed must be propagated to listeners in pre-shift keyspace.
                if (upstream != null) {
                    upstream.shifted().unapply(postShiftRemovals);
                }
                update.removed.writableCast().insert(postShiftRemovals);
            }

            if (upstream == null || upstream.modified().isEmpty()) {
                update.modified = RowSetFactory.empty();
            } else {
                update.modified = upstream.modified().intersect(getRowSet());
                update.modified.writableCast().remove(update.added);
            }

            update.shifted = upstream == null ? RowSetShiftData.EMPTY : upstream.shifted();

            notifyListeners(update);

            // Release the upstream update and set the final notification step.
            listener.finalizeUpdate(upstream);
        }

        private void errorRefilterUpdate(final WhereListener listener, final Exception e, final TableUpdate upstream) {
            // Notify listeners that we had an issue refreshing the table.
            if (getLastNotificationStep() == updateGraph.clock().currentStep()) {
                if (listener != null) {
                    listener.forceReferenceCountToZero();
                }
                delayedErrorReference = new DelayedErrorNotifier(e, listener == null ? null : listener.entry, this);
            } else {
                notifyListenersOnError(e, listener == null ? null : listener.entry);
                forceReferenceCountToZero();
            }
            // Release the upstream update and set the final notification step.
            listener.finalizeUpdate(upstream);
        }

        private void setWhereListener(MergedListener whereListener) {
            this.whereListener = whereListener;
        }
    }

    @Override
    public Table where(Filter filter) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return whereInternal(WhereFilter.fromInternal(filter));
        }
    }

    private void initializeAndPrioritizeFilters(@NotNull final WhereFilter... filters) {
        final DataIndexer dataIndexer = USE_DATA_INDEX_FOR_WHERE ? DataIndexer.existingOf(rowSet) : null;
        final int numFilters = filters.length;
        final BitSet priorityFilterIndexes = new BitSet(numFilters);

        final QueryCompilerRequestProcessor.BatchProcessor compilationProcessor = QueryCompilerRequestProcessor.batch();

        // Initialize our filters immediately so we can examine the columns they use. Note that filter
        // initialization is safe to invoke repeatedly.
        final Set<Object> knownBarriers = new HashSet<>();
        for (final WhereFilter filter : filters) {
            filter.init(getDefinition(), compilationProcessor);

            // Add barriers declared by this filter; filters may appear to depend on themselves when examined in
            // aggregate.
            final Collection<Object> newBarriers = ExtractBarriers.of(filter);
            final Optional<Object> dupBarrier = newBarriers.stream().filter(knownBarriers::contains).findFirst();
            if (dupBarrier.isPresent()) {
                throw new IllegalArgumentException("Filter Barriers must be unique! Found duplicate: " +
                        dupBarrier.get());
            }
            knownBarriers.addAll(newBarriers);

            for (final Object respectedBarrier : ExtractRespectedBarriers.of(filter)) {
                if (!knownBarriers.contains(respectedBarrier)) {
                    throw new IllegalArgumentException("Filter " + filter + " respects barrier " + respectedBarrier +
                            " that is not declared by any filter so far.");
                }
            }
        }
        compilationProcessor.compile();

        final Set<Object> priorityBarriers = new HashSet<>();
        for (int fi = 0; fi < numFilters; ++fi) {
            final WhereFilter filter = filters[fi];

            if (!filter.permitParallelization()) {
                // serial filters are guaranteed to see the expected rowset as if all previous filters were applied
                // thus, we're not allowed to reorder any remaining filters
                break;
            }

            if (!priorityBarriers.containsAll(ExtractRespectedBarriers.of(filter))) {
                // this filter is not permitted to be reordered as it depends on a filter that has not been prioritized
                continue;
            }

            // Simple filters against indexed columns get priority
            if (dataIndexer != null
                    && !(filter instanceof ReindexingFilter)
                    && filter.isSimpleFilter()
                    && DataIndexer.hasDataIndex(this, filter.getColumns().toArray(String[]::new))) {
                priorityFilterIndexes.set(fi);
                priorityBarriers.addAll(ExtractBarriers.of(filter));
            }
        }

        if (priorityFilterIndexes.isEmpty()) {
            return;
        }

        // Copy the priority filters to a temporary array
        final int numPriorityFilters = priorityFilterIndexes.cardinality();
        final WhereFilter[] priorityFilters = new WhereFilter[numPriorityFilters];
        // @formatter:off
        for (int pfi = 0, fi = priorityFilterIndexes.nextSetBit(0);
             fi >= 0;
             fi = priorityFilterIndexes.nextSetBit(fi + 1)) {
            // @formatter:on
            priorityFilters[pfi++] = filters[fi];
        }
        // Move the regular (non-priority) filters to the back of the array
        // @formatter:off
        for (int rfi = numFilters - 1, fi = priorityFilterIndexes.previousClearBit(numFilters - 1);
             fi >= 0;
             fi = priorityFilterIndexes.previousClearBit(fi - 1)) {
            // @formatter:on
            filters[rfi--] = filters[fi];
        }
        // Re-add the priority filters at the front of the array
        System.arraycopy(priorityFilters, 0, filters, 0, numPriorityFilters);
    }

    private QueryTable whereInternal(final WhereFilter... filters) {
        if (filters.length == 0) {
            return (QueryTable) prepareReturnThis();
        }

        final String whereDescription = "where(" + Arrays.toString(filters) + ")";
        return QueryPerformanceRecorder.withNugget(whereDescription, sizeForInstrumentation(),
                () -> {
                    initializeAndPrioritizeFilters(filters);

                    for (int fi = 0; fi < filters.length; ++fi) {
                        if (!(filters[fi] instanceof ReindexingFilter)) {
                            continue;
                        }
                        final ReindexingFilter reindexingFilter = (ReindexingFilter) filters[fi];
                        final boolean first = fi == 0;
                        final boolean last = fi == filters.length - 1;
                        if (last && !reindexingFilter.requiresSorting()) {
                            // If this is the last (or only) filter, we can just run it as normal unless it requires
                            // sorting.
                            break;
                        }
                        QueryTable result = this;
                        if (!first) {
                            result = result.whereInternal(Arrays.copyOf(filters, fi));
                        }
                        if (reindexingFilter.requiresSorting()) {
                            result = (QueryTable) result.sort(reindexingFilter.getSortColumns());
                            reindexingFilter.sortingDone();
                        }
                        result = result.whereInternal(reindexingFilter);
                        if (!last) {
                            result = result.whereInternal(Arrays.copyOfRange(filters, fi + 1, filters.length));
                        }
                        return result;
                    }

                    boolean hasConstArrayOffsetFilter = false;
                    for (final WhereFilter filter : filters) {
                        final Set<ShiftedColumnDefinition> shifted = ExtractShiftedColumnDefinitions.of(filter);
                        if (shifted != null && !shifted.isEmpty()) {
                            hasConstArrayOffsetFilter = true;
                            break;
                        }
                    }
                    if (hasConstArrayOffsetFilter) {
                        return (QueryTable) ShiftedColumnsFactory.where(this, Arrays.asList(filters));
                    }

                    return memoizeResult(MemoizedOperationKey.filter(filters), () -> {
                        try (final SafeCloseable ignored = Arrays.stream(filters)
                                .map(filter -> filter.beginOperation(this)).collect(SafeCloseableList.COLLECTOR)) {
                            final OperationSnapshotControl snapshotControl = createSnapshotControlIfRefreshing(
                                    (final BaseTable<?> parent) -> {
                                        /*
                                         * Note that the dependencies for instantiation may be different from the
                                         * dependencies for the WhereListener. Do not refactor to share this array with
                                         * the WhereListener unless you ensure that this no longer holds, i.e. if
                                         * MatchFilter starts applying data indexes during update processing.
                                         */
                                        final NotificationQueue.Dependency[] filterDependencies =
                                                WhereListener.extractDependencies(filters)
                                                        .toArray(NotificationQueue.Dependency[]::new);
                                        getUpdateGraph(filterDependencies);
                                        return filterDependencies.length > 0
                                                ? new OperationSnapshotControlEx(parent, filterDependencies)
                                                : new OperationSnapshotControl(parent);
                                    });

                            final Mutable<QueryTable> result = new MutableObject<>();
                            initializeWithSnapshot("where", snapshotControl,
                                    (prevRequested, beforeClock) -> {
                                        final boolean usePrev = prevRequested && isRefreshing();
                                        final RowSet rowSetToUse = usePrev ? rowSet.prev() : rowSet;

                                        final CompletableFuture<TrackingWritableRowSet> currentMappingFuture =
                                                new CompletableFuture<>();
                                        final InitialFilterExecution initialFilterExecution =
                                                new InitialFilterExecution(this, filters, rowSetToUse.copy(), usePrev);
                                        final TrackingWritableRowSet currentMapping;
                                        initialFilterExecution.scheduleCompletion((adds, mods) -> {
                                            currentMappingFuture.complete(adds.writableCast().toTracking());
                                        }, currentMappingFuture::completeExceptionally);

                                        try {
                                            currentMapping = currentMappingFuture.get();
                                        } catch (ExecutionException | InterruptedException e) {
                                            final Throwable cause = (e instanceof InterruptedException)
                                                    ? new CancellationException("interrupted while filtering")
                                                    : e.getCause();
                                            throw new TableInitializationException(whereDescription,
                                                    "an exception occurred while performing the initial filter",
                                                    cause);
                                        } finally {
                                            // account for work done in alternative threads
                                            final BasePerformanceEntry basePerformanceEntry =
                                                    initialFilterExecution.getBasePerformanceEntry();
                                            if (basePerformanceEntry != null) {
                                                QueryPerformanceRecorder.getInstance().getEnclosingNugget()
                                                        .accumulate(basePerformanceEntry);
                                            }
                                        }
                                        currentMapping.initializePreviousValue();

                                        final FilteredTable filteredTable = new FilteredTable(currentMapping, this);

                                        for (final WhereFilter filter : filters) {
                                            filter.setRecomputeListener(filteredTable);
                                        }
                                        final boolean refreshingFilters =
                                                Arrays.stream(filters).anyMatch(WhereFilter::isRefreshing);
                                        copyAttributes(filteredTable, CopyAttributeOperation.Filter);
                                        // as long as filters do not change, we can propagate add-only/append-only attrs
                                        if (!refreshingFilters) {
                                            if (isAddOnly()) {
                                                filteredTable.setAttribute(Table.ADD_ONLY_TABLE_ATTRIBUTE, TRUE);
                                            }
                                            if (isAppendOnly()) {
                                                filteredTable.setAttribute(Table.APPEND_ONLY_TABLE_ATTRIBUTE, TRUE);
                                            }
                                        }

                                        if (snapshotControl != null) {
                                            final ListenerRecorder recorder = new ListenerRecorder(
                                                    whereDescription, QueryTable.this,
                                                    filteredTable);
                                            final WhereListener whereListener = new WhereListener(
                                                    log, this, recorder, filteredTable, filters);
                                            filteredTable.setWhereListener(whereListener);
                                            recorder.setMergedListener(whereListener);
                                            snapshotControl.setListenerAndResult(recorder, filteredTable);
                                            filteredTable.addParentReference(whereListener);
                                        } else if (refreshingFilters) {
                                            final WhereListener whereListener = new WhereListener(
                                                    log, this, null, filteredTable, filters);
                                            filteredTable.setWhereListener(whereListener);
                                            filteredTable.addParentReference(whereListener);
                                        }
                                        result.setValue(filteredTable);
                                        return true;
                                    });
                            return result.getValue();
                        }
                    });
                });
    }

    @Override
    public Table whereIn(Table rightTable, Collection<? extends JoinMatch> columnsToMatch) {
        final UpdateGraph updateGraph = getUpdateGraph(rightTable);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return whereInInternal(rightTable, true, MatchPair.fromMatches(columnsToMatch));
        }
    }

    @Override
    public Table whereNotIn(Table rightTable, Collection<? extends JoinMatch> columnsToMatch) {
        final UpdateGraph updateGraph = getUpdateGraph(rightTable);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return whereInInternal(rightTable, false, MatchPair.fromMatches(columnsToMatch));
        }
    }

    private Table whereInInternal(final Table rightTable, final boolean inclusion,
            final MatchPair... columnsToMatch) {
        return QueryPerformanceRecorder.withNugget(
                "whereIn(rightTable, " + inclusion + ", " + matchString(columnsToMatch) + ")",
                sizeForInstrumentation(), () -> {
                    checkInitiateOperation(rightTable);

                    final Table distinctValues;
                    final boolean setRefreshing = rightTable.isRefreshing();

                    final String[] rightColumnNames = MatchPair.getRightColumns(columnsToMatch);
                    final DataIndex rightIndex = DataIndexer.getDataIndex(rightTable, rightColumnNames);
                    if (rightIndex != null) {
                        // We have a distinct index table, let's use it.
                        distinctValues = rightIndex.table();
                    } else if (setRefreshing) {
                        distinctValues = rightTable.selectDistinct(rightColumnNames);
                    } else {
                        final TableDefinition rightDef = rightTable.getDefinition();
                        final boolean allPartitioning =
                                Arrays.stream(rightColumnNames).allMatch(cn -> rightDef.getColumn(cn).isPartitioning());
                        if (allPartitioning) {
                            distinctValues = rightTable.selectDistinct(rightColumnNames);
                        } else {
                            distinctValues = rightTable.coalesce();
                        }
                    }

                    final DynamicWhereFilter dynamicWhereFilter =
                            new DynamicWhereFilter((QueryTable) distinctValues, inclusion, columnsToMatch);
                    final Table where = whereInternal(dynamicWhereFilter);
                    if (distinctValues.isRefreshing()) {
                        where.addParentReference(distinctValues);
                    }
                    if (dynamicWhereFilter.isRefreshing()) {
                        where.addParentReference(dynamicWhereFilter);
                    }
                    return where;
                });
    }

    @Override
    public Table flatten() {
        if (!flat && !isRefreshing() && rowSet.isFlat()) {
            // We're already flat, and we'll never update; so we can just return a flat copy
            final QueryTable copyWithFlat = copy();
            copyWithFlat.setFlat();
            return copyWithFlat;
        }
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (isFlat()) {
                return prepareReturnThis();
            }
            return getResult(new FlattenOperation(this));
        }
    }

    public void setFlat() {
        flat = true;
    }

    @Override
    public boolean isFlat() {
        if (flat) {
            Assert.assertion(rowSet.isFlat(), "rowSet.isFlat()", rowSet, "rowSet");
        }
        return flat;
    }

    @Override
    public void releaseCachedResources() {
        super.releaseCachedResources();
        columns.values().forEach(ColumnSource::releaseCachedResources);
    }

    @Override
    public Table select(Collection<? extends Selectable> columns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return selectInternal(SelectColumn.from(columns.isEmpty() ? definition.getTypedColumnNames() : columns));
        }
    }

    private Table selectInternal(SelectColumn... selectColumns) {
        if (!isRefreshing() && !isFlat() && exceedsMaximumStaticSelectOverhead()) {
            // if we are static, we will pass the select through a flatten call, to ensure that our result is as
            // efficient in terms of memory as possible
            return ((QueryTable) flatten()).selectInternal(selectColumns);
        }
        return selectOrUpdate(Flavor.Select, selectColumns);
    }

    private boolean exceedsMaximumStaticSelectOverhead() {
        return SparseConstants.sparseStructureExceedsOverhead(this.getRowSet(), MAXIMUM_STATIC_SELECT_MEMORY_OVERHEAD);
    }

    @Override
    public Table update(final Collection<? extends Selectable> newColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return selectOrUpdate(Flavor.Update, SelectColumn.from(newColumns));
        }
    }

    /**
     * This does a certain amount of validation and can be used to get confidence that the formulas are valid. If it is
     * not valid, you will get an exception. Positive test (should pass validation): "X = 12", "Y = X + 1") Negative
     * test (should fail validation): "X = 12", "Y = Z + 1")
     * <p>
     * DO NOT USE -- this API is in flux and may change or disappear in the future.
     */
    public SelectValidationResult validateSelect(final SelectColumn... selectColumns) {
        final SelectColumn[] clones = SelectColumn.copyFrom(selectColumns);
        SelectAndViewAnalyzer.AnalyzerContext analyzerContext = SelectAndViewAnalyzer.createContext(
                this, SelectAndViewAnalyzer.Mode.SELECT_STATIC, true, false, clones);
        return new SelectValidationResult(analyzerContext.createAnalyzer(), clones);
    }

    private Table selectOrUpdate(Flavor flavor, final SelectColumn... selectColumns) {
        final String humanReadablePrefix = flavor.toString();
        final String updateDescription = humanReadablePrefix + '(' + selectColumnString(selectColumns) + ')';
        return memoizeResult(MemoizedOperationKey.selectUpdateViewOrUpdateView(selectColumns, flavor),
                () -> QueryPerformanceRecorder.withNugget(updateDescription, sizeForInstrumentation(), () -> {
                    checkInitiateOperation();
                    final SelectAndViewAnalyzer.Mode mode;
                    if (isRefreshing()) {
                        if (!isFlat() && ((flavor == Flavor.Update && USE_REDIRECTED_COLUMNS_FOR_UPDATE)
                                || (flavor == Flavor.Select && USE_REDIRECTED_COLUMNS_FOR_SELECT))) {
                            mode = SelectAndViewAnalyzer.Mode.SELECT_REDIRECTED_REFRESHING;
                        } else {
                            mode = SelectAndViewAnalyzer.Mode.SELECT_REFRESHING;
                        }
                    } else {
                        if (flavor == Flavor.Update && exceedsMaximumStaticSelectOverhead()) {
                            mode = SelectAndViewAnalyzer.Mode.SELECT_REDIRECTED_STATIC;
                        } else {
                            mode = SelectAndViewAnalyzer.Mode.SELECT_STATIC;
                        }
                    }
                    final boolean publishTheseSources = flavor == Flavor.Update;
                    final SelectAndViewAnalyzer.AnalyzerContext analyzerContext = SelectAndViewAnalyzer.createContext(
                            this, mode, publishTheseSources, true, selectColumns);

                    final SelectAndViewAnalyzer analyzer = analyzerContext.createAnalyzer();
                    final SelectColumn[] processedColumns = analyzerContext.getProcessedColumns()
                            .toArray(SelectColumn[]::new);

                    // Init all the rows by cooking up a fake Update
                    final TableUpdate fakeUpdate = new TableUpdateImpl(
                            rowSet.copy(), RowSetFactory.empty(), RowSetFactory.empty(),
                            RowSetShiftData.EMPTY, ModifiedColumnSet.ALL);

                    final CompletableFuture<Void> waitForResult = new CompletableFuture<>();
                    final JobScheduler jobScheduler;
                    if ((QueryTable.FORCE_PARALLEL_SELECT_AND_UPDATE || QueryTable.ENABLE_PARALLEL_SELECT_AND_UPDATE)
                            && ExecutionContext.getContext().getOperationInitializer().canParallelize()
                            && analyzer.allowCrossColumnParallelization()) {
                        jobScheduler = new OperationInitializerJobScheduler();
                    } else {
                        jobScheduler = new ImmediateJobScheduler();
                    }

                    final QueryTable resultTable;
                    final LivenessScope liveResultCapture = isRefreshing() ? new LivenessScope() : null;
                    try (final SafeCloseable ignored1 = liveResultCapture != null ? liveResultCapture::release : null) {
                        try (final RowSet emptyRowSet = RowSetFactory.empty();
                                final SelectAndViewAnalyzer.UpdateHelper updateHelper =
                                        new SelectAndViewAnalyzer.UpdateHelper(emptyRowSet, fakeUpdate)) {

                            try {
                                analyzer.applyUpdate(
                                        fakeUpdate, emptyRowSet, updateHelper, jobScheduler, liveResultCapture,
                                        () -> waitForResult.complete(null),
                                        waitForResult::completeExceptionally);
                            } catch (Exception e) {
                                waitForResult.completeExceptionally(e);
                            }

                            try {
                                waitForResult.get();
                            } catch (InterruptedException e) {
                                throw new CancellationException("interrupted while computing select or update");
                            } catch (ExecutionException e) {
                                throw new TableInitializationException(updateDescription,
                                        "an exception occurred while performing the initial select or update",
                                        e.getCause());
                            } finally {
                                final BasePerformanceEntry baseEntry = jobScheduler.getAccumulatedPerformance();
                                if (baseEntry != null) {
                                    QueryPerformanceRecorder.getInstance().getEnclosingNugget().accumulate(baseEntry);
                                }
                            }
                        }

                        final TrackingRowSet resultRowSet = analyzer.flatResult() && !rowSet.isFlat()
                                ? RowSetFactory.flat(rowSet.size()).toTracking()
                                : rowSet;
                        resultTable = new QueryTable(resultRowSet, analyzerContext.getPublishedColumnSources());
                        if (liveResultCapture != null) {
                            analyzer.startTrackingPrev();
                            final Map<String, String[]> effects = analyzerContext.calcEffects();
                            final SelectOrUpdateListener soul = new SelectOrUpdateListener(
                                    updateDescription, this, resultTable, effects, analyzer);
                            liveResultCapture.transferTo(soul);
                            addUpdateListener(soul);
                            ConstituentDependency.install(resultTable, soul);
                        } else {
                            if (resultTable.getRowSet().isFlat()) {
                                resultTable.setFlat();
                            }
                            propagateDataIndexes(processedColumns, resultTable);
                        }
                    }
                    propagateFlatness(resultTable);
                    copySortableColumns(resultTable, processedColumns);
                    if (publishTheseSources) {
                        maybeCopyColumnDescriptions(resultTable, processedColumns);
                    } else {
                        maybeCopyColumnDescriptions(resultTable);
                    }
                    SelectAndViewAnalyzer.UpdateFlavor updateFlavor = flavor == Flavor.Update
                            ? SelectAndViewAnalyzer.UpdateFlavor.Update
                            : SelectAndViewAnalyzer.UpdateFlavor.Select;
                    return analyzerContext.applyShiftsAndRemainingColumns(this, resultTable, updateFlavor);
                }));
    }

    /**
     * Data indexes on select source columns may be valid in the result table. Add new mappings so the data indexes are
     * retrievable from the result table column sources.
     */
    private void propagateDataIndexes(SelectColumn[] selectColumns, QueryTable resultTable) {
        if (rowSet != resultTable.getRowSet()) {
            return;
        }

        // Get a list of all the data indexes in the source table.
        final DataIndexer dataIndexer = DataIndexer.existingOf(rowSet);
        if (dataIndexer == null) {
            return;
        }
        final List<DataIndex> dataIndexes = dataIndexer.dataIndexes(false);
        if (dataIndexes.isEmpty()) {
            return;
        }

        // Make a set containing only the columns that were part of indexes.
        Set<ColumnSource<?>> indexedColumns = new HashSet<>();
        dataIndexes.forEach(di -> {
            indexedColumns.addAll(di.keyColumnNamesByIndexedColumn().keySet());
        });

        final Set<ColumnSource<?>> usedOutputColumns = new HashSet<>();

        // Maintain a list of unique old to new mappings.
        // NOTE: this is complex because select() may return multiple aliases for the same source column. Until/unless
        // we have a guarantee that only a single alias is created, we must create a new data index for each alias and
        // this requires generating all unique mappings for these columns.
        final List<Map<ColumnSource<?>, ColumnSource<?>>> oldToNewMaps = new ArrayList<>();

        for (SelectColumn selectColumn : selectColumns) {
            if (selectColumn instanceof SwitchColumn) {
                selectColumn = ((SwitchColumn) selectColumn).getRealColumn();
            }

            SourceColumn sourceColumn = null;
            if (selectColumn instanceof SourceColumn) {
                sourceColumn = (SourceColumn) selectColumn;
            }

            if (sourceColumn == null) {
                continue;
            }

            final ColumnSource<?> resultSource = resultTable.getColumnSource(sourceColumn.getName());
            if (usedOutputColumns.contains(resultSource)) {
                // We already handled this result source.
                continue;
            }
            usedOutputColumns.add(resultSource);

            final ColumnSource<?> originalSource = getColumnSource(sourceColumn.getSourceName());
            if (!indexedColumns.contains(originalSource) || originalSource == resultSource) {
                // Not part of an index, or not changed, ignore this column.
                continue;
            }

            if (oldToNewMaps.isEmpty()) {
                oldToNewMaps.add(new HashMap<>());
            }

            // Map original source to the new source.
            final Map<ColumnSource<?>, ColumnSource<?>> firstMap = oldToNewMaps.get(0);
            if (firstMap.containsKey(originalSource)) {
                // We have a collision, which means our mapping won't be unique. We need to clone
                // conflicting mappings with a new map containing our updated target.
                final ColumnSource<?> previousResultSource = firstMap.get(originalSource);
                final List<Map<ColumnSource<?>, ColumnSource<?>>> newMaps = new ArrayList<>();
                oldToNewMaps.stream()
                        .filter(map -> map.get(originalSource) == previousResultSource)
                        .forEach(map -> {
                            final Map<ColumnSource<?>, ColumnSource<?>> newMap = new HashMap<>(map);
                            newMap.put(originalSource, resultSource);
                            newMaps.add(newMap);
                        });
                oldToNewMaps.addAll(newMaps);
            } else {
                oldToNewMaps.forEach(map -> map.put(originalSource, resultSource));
            }
        }

        if (oldToNewMaps.isEmpty()) {
            return;
        }

        // Add new DataIndex entries to the DataIndexer with the remapped column sources.
        for (final DataIndex dataIndex : dataIndexes) {
            // Create a new data index for each unique mapping.
            oldToNewMaps.forEach(map -> {
                if (Collections.disjoint(dataIndex.keyColumnNamesByIndexedColumn().keySet(), map.keySet())) {
                    // The index contains no remapped original sources, no work needed.
                    return;
                }

                // Create a new DataIndex using the new column sources as keys.
                final DataIndex remappedIndex = dataIndex.remapKeyColumns(map);

                // Add the new index to the DataIndexer.
                dataIndexer.addDataIndex(remappedIndex);
            });
        }
    }

    @Override
    public Table view(final Collection<? extends Selectable> viewColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (viewColumns == null || viewColumns.isEmpty()) {
                return prepareReturnThis();
            }
            return viewOrUpdateView(Flavor.View, SelectColumn.from(viewColumns));
        }
    }

    @Override
    public Table updateView(final Collection<? extends Selectable> viewColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return viewOrUpdateView(Flavor.UpdateView, SelectColumn.from(viewColumns));
        }
    }

    private Table viewOrUpdateView(Flavor flavor, final SelectColumn... viewColumns) {
        if (viewColumns == null || viewColumns.length == 0) {
            return prepareReturnThis();
        }

        final String humanReadablePrefix = flavor.toString();

        // Assuming that the description is human-readable, we make it once here and use it twice.
        final String updateDescription = humanReadablePrefix + '(' + selectColumnString(viewColumns) + ')';

        return memoizeResult(MemoizedOperationKey.selectUpdateViewOrUpdateView(viewColumns, flavor),
                () -> QueryPerformanceRecorder.withNugget(
                        updateDescription, sizeForInstrumentation(), () -> {
                            final Mutable<Table> result = new MutableObject<>();

                            final OperationSnapshotControl sc =
                                    createSnapshotControlIfRefreshing(OperationSnapshotControl::new);
                            initializeWithSnapshot(humanReadablePrefix, sc, (usePrev, beforeClockValue) -> {
                                final boolean publishTheseSources = flavor == Flavor.UpdateView;
                                final SelectAndViewAnalyzer.AnalyzerContext analyzerContext =
                                        SelectAndViewAnalyzer.createContext(
                                                this, SelectAndViewAnalyzer.Mode.VIEW_EAGER,
                                                publishTheseSources, true, viewColumns);
                                final SelectColumn[] processedViewColumns = analyzerContext.getProcessedColumns()
                                        .toArray(SelectColumn[]::new);
                                QueryTable queryTable = new QueryTable(
                                        rowSet, analyzerContext.getPublishedColumnSources());
                                if (sc != null) {
                                    final Map<String, String[]> effects = analyzerContext.calcEffects();
                                    final TableUpdateListener listener =
                                            new ViewOrUpdateViewListener(updateDescription, this, queryTable, effects);
                                    sc.setListenerAndResult(listener, queryTable);
                                }

                                propagateFlatness(queryTable);

                                copyAttributes(queryTable,
                                        flavor == Flavor.UpdateView ? CopyAttributeOperation.UpdateView
                                                : CopyAttributeOperation.View);
                                copySortableColumns(queryTable, processedViewColumns);
                                if (publishTheseSources) {
                                    maybeCopyColumnDescriptions(queryTable, processedViewColumns);
                                } else {
                                    maybeCopyColumnDescriptions(queryTable);
                                }
                                final SelectAndViewAnalyzer.UpdateFlavor updateFlavor =
                                        flavor == Flavor.UpdateView
                                                ? SelectAndViewAnalyzer.UpdateFlavor.UpdateView
                                                : SelectAndViewAnalyzer.UpdateFlavor.View;
                                queryTable = analyzerContext.applyShiftsAndRemainingColumns(
                                        this, queryTable, updateFlavor);

                                result.setValue(queryTable);

                                return true;
                            });

                            return result.getValue();
                        }));
    }

    /**
     * A Shift-Aware listener for {Update,}View. It uses the LayeredColumnReferences class to calculate how columns
     * affect other columns, then creates a column set transformer which will be used by onUpdate to transform updates.
     */
    private static class ViewOrUpdateViewListener extends ListenerImpl {
        private final QueryTable dependent;
        private final ModifiedColumnSet.Transformer transformer;

        /**
         * @param description Description of this listener
         * @param parent The parent table
         * @param dependent The dependent table
         * @param effects A map from a column name to the column names that it affects
         */
        ViewOrUpdateViewListener(String description, QueryTable parent, QueryTable dependent,
                Map<String, String[]> effects) {
            super(description, parent, dependent);
            this.dependent = dependent;

            // Now calculate the other dependencies and invert
            final String[] parentNames = new String[effects.size()];
            final ModifiedColumnSet[] mcss = new ModifiedColumnSet[effects.size()];
            int nextIndex = 0;
            for (Map.Entry<String, String[]> entry : effects.entrySet()) {
                parentNames[nextIndex] = entry.getKey();
                mcss[nextIndex] = dependent.newModifiedColumnSet(entry.getValue());
                ++nextIndex;
            }
            transformer = parent.newModifiedColumnSetTransformer(parentNames, mcss);
        }

        @Override
        public void onUpdate(final TableUpdate upstream) {
            final TableUpdateImpl downstream =
                    TableUpdateImpl.copy(upstream, dependent.getModifiedColumnSetForUpdates());
            transformer.clearAndTransform(upstream.modifiedColumnSet(), downstream.modifiedColumnSet);
            dependent.notifyListeners(downstream);
        }
    }

    @Override
    public Table lazyUpdate(final Collection<? extends Selectable> newColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final SelectColumn[] selectColumns = SelectColumn.from(newColumns);
            return QueryPerformanceRecorder.withNugget("lazyUpdate(" + selectColumnString(selectColumns) + ")",
                    sizeForInstrumentation(), () -> {
                        checkInitiateOperation();

                        final SelectAndViewAnalyzer.AnalyzerContext analyzerContext =
                                SelectAndViewAnalyzer.createContext(
                                        this, SelectAndViewAnalyzer.Mode.VIEW_LAZY, true, true, selectColumns);
                        final SelectColumn[] processedColumns = analyzerContext.getProcessedColumns()
                                .toArray(SelectColumn[]::new);
                        final QueryTable result = new QueryTable(
                                rowSet, analyzerContext.getPublishedColumnSources());
                        if (isRefreshing()) {
                            addUpdateListener(new ListenerImpl(
                                    "lazyUpdate(" + Arrays.deepToString(processedColumns) + ')', this, result));
                        }
                        propagateFlatness(result);
                        copyAttributes(result, CopyAttributeOperation.UpdateView);
                        copySortableColumns(result, processedColumns);
                        maybeCopyColumnDescriptions(result, processedColumns);

                        return analyzerContext.applyShiftsAndRemainingColumns(
                                this, result, SelectAndViewAnalyzer.UpdateFlavor.LazyUpdate);
                    });
        }
    }

    @Override
    public Table dropColumns(String... columnNames) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (columnNames == null || columnNames.length == 0) {
                return prepareReturnThis();
            }
            return memoizeResult(MemoizedOperationKey.dropColumns(columnNames), () -> QueryPerformanceRecorder
                    .withNugget("dropColumns(" + Arrays.toString(columnNames) + ")", sizeForInstrumentation(), () -> {
                        final Mutable<Table> result = new MutableObject<>();
                        definition.checkHasColumns(Arrays.asList(columnNames));
                        final Map<String, ColumnSource<?>> newColumns = new LinkedHashMap<>(columns);
                        for (String columnName : columnNames) {
                            newColumns.remove(columnName);
                        }

                        final OperationSnapshotControl snapshotControl =
                                createSnapshotControlIfRefreshing(OperationSnapshotControl::new);

                        initializeWithSnapshot("dropColumns", snapshotControl, (usePrev, beforeClockValue) -> {
                            final QueryTable resultTable = new QueryTable(rowSet, newColumns);
                            propagateFlatness(resultTable);

                            copyAttributes(resultTable, CopyAttributeOperation.DropColumns);
                            copySortableColumns(resultTable,
                                    resultTable.getDefinition().getColumnNameSet()::contains);
                            maybeCopyColumnDescriptions(resultTable);

                            if (snapshotControl != null) {
                                final ModifiedColumnSet.Transformer mcsTransformer =
                                        newModifiedColumnSetTransformer(resultTable,
                                                resultTable.getDefinition().getColumnNamesArray());
                                final ListenerImpl listener = new ListenerImpl(
                                        "dropColumns(" + Arrays.deepToString(columnNames) + ')', this, resultTable) {
                                    @Override
                                    public void onUpdate(final TableUpdate upstream) {
                                        final TableUpdateImpl downstream;
                                        final ModifiedColumnSet resultModifiedColumnSet =
                                                resultTable.getModifiedColumnSetForUpdates();
                                        mcsTransformer.clearAndTransform(upstream.modifiedColumnSet(),
                                                resultModifiedColumnSet);
                                        if (upstream.modified().isEmpty() || resultModifiedColumnSet.empty()) {
                                            downstream = TableUpdateImpl.copy(upstream, ModifiedColumnSet.EMPTY);
                                            if (downstream.modified().isNonempty()) {
                                                downstream.modified().close();
                                                downstream.modified = RowSetFactory.empty();
                                            }
                                        } else {
                                            downstream = TableUpdateImpl.copy(upstream, resultModifiedColumnSet);
                                        }
                                        resultTable.notifyListeners(downstream);
                                    }
                                };
                                snapshotControl.setListenerAndResult(listener, resultTable);
                            }

                            result.setValue(resultTable);

                            return true;
                        });

                        return result.getValue();
                    }));
        }
    }

    @Override
    public Table renameColumns(Collection<Pair> pairs) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return renameColumnsImpl("renameColumns(", -1, pairs);
        }
    }

    private Table renameColumnsImpl(
            @NotNull final String methodNuggetPrefix,
            final int movePosition,
            @NotNull final Collection<Pair> pairs) {
        final String pairsLogString = Strings.ofPairs(pairs);
        return QueryPerformanceRecorder.withNugget(methodNuggetPrefix + pairsLogString + ")",
                sizeForInstrumentation(), () -> {
                    if (pairs.isEmpty()) {
                        return prepareReturnThis();
                    }

                    Set<String> notFound = null;
                    Set<String> duplicateSource = null;
                    Set<String> duplicateDest = null;

                    final Set<ColumnName> newNames = new HashSet<>();
                    final Map<ColumnName, ColumnName> pairLookup = new LinkedHashMap<>();
                    for (final Pair pair : pairs) {
                        if (!columns.containsKey(pair.input().name())) {
                            (notFound == null ? notFound = new LinkedHashSet<>() : notFound)
                                    .add(pair.input().name());
                        }
                        if (pairLookup.put(pair.input(), pair.output()) != null) {
                            (duplicateSource == null ? duplicateSource = new LinkedHashSet<>(1) : duplicateSource)
                                    .add(pair.input().name());
                        }
                        if (!newNames.add(pair.output())) {
                            (duplicateDest == null ? duplicateDest = new LinkedHashSet<>() : duplicateDest)
                                    .add(pair.output().name());
                        }
                    }

                    // if we accumulated any errors, build one mega error message and throw it
                    if (notFound != null || duplicateSource != null || duplicateDest != null) {
                        throw new IllegalArgumentException(Stream.of(
                                notFound == null ? null : "Column(s) not found: " + String.join(", ", notFound),
                                duplicateSource == null ? null
                                        : "Duplicate source column(s): " + String.join(", ", duplicateSource),
                                duplicateDest == null ? null
                                        : "Duplicate destination column(s): " + String.join(", ", duplicateDest))
                                .filter(Objects::nonNull).collect(Collectors.joining("\n")));
                    }

                    final MutableInt mcsPairIdx = new MutableInt();
                    final Pair[] modifiedColumnSetPairs = new Pair[columns.size()];
                    final Map<String, ColumnSource<?>> newColumns = new LinkedHashMap<>();

                    final Runnable moveColumns = () -> {
                        for (final Map.Entry<ColumnName, ColumnName> rename : pairLookup.entrySet()) {
                            final ColumnName oldName = rename.getKey();
                            final ColumnName newName = rename.getValue();
                            final ColumnSource<?> columnSource = columns.get(oldName.name());
                            newColumns.put(newName.name(), columnSource);
                            modifiedColumnSetPairs[mcsPairIdx.getAndIncrement()] =
                                    Pair.of(newName, oldName);
                        }
                    };

                    for (final Map.Entry<String, ? extends ColumnSource<?>> entry : columns.entrySet()) {
                        final ColumnName oldName = ColumnName.of(entry.getKey());
                        final ColumnSource<?> columnSource = entry.getValue();
                        ColumnName newName = pairLookup.get(oldName);
                        if (newName == null) {
                            if (newNames.contains(oldName)) {
                                // this column is being replaced by a rename
                                continue;
                            }
                            newName = oldName;
                        } else if (movePosition >= 0) {
                            // we move this column when we get to the right position
                            continue;
                        }

                        if (mcsPairIdx.get() == movePosition) {
                            moveColumns.run();
                        }

                        modifiedColumnSetPairs[mcsPairIdx.getAndIncrement()] =
                                Pair.of(newName, oldName);
                        newColumns.put(newName.name(), columnSource);
                    }

                    if (mcsPairIdx.get() <= movePosition) {
                        moveColumns.run();
                    }

                    final Mutable<QueryTable> result = new MutableObject<>();

                    final OperationSnapshotControl snapshotControl =
                            createSnapshotControlIfRefreshing(OperationSnapshotControl::new);
                    initializeWithSnapshot("renameColumns", snapshotControl, (usePrev, beforeClockValue) -> {
                        final QueryTable resultTable = new QueryTable(rowSet, newColumns);
                        propagateFlatness(resultTable);

                        copyAttributes(resultTable, CopyAttributeOperation.RenameColumns);
                        copySortableColumns(resultTable, pairs);
                        maybeCopyColumnDescriptions(resultTable, pairs);

                        if (snapshotControl != null) {
                            final ModifiedColumnSet.Transformer mcsTransformer =
                                    newModifiedColumnSetTransformer(resultTable, modifiedColumnSetPairs);
                            final ListenerImpl listener = new ListenerImpl(
                                    methodNuggetPrefix + pairsLogString + ')', this, resultTable) {
                                @Override
                                public void onUpdate(final TableUpdate upstream) {
                                    final TableUpdateImpl downstream;
                                    if (upstream.modified().isNonempty()) {
                                        downstream = TableUpdateImpl.copy(upstream,
                                                resultTable.getModifiedColumnSetForUpdates());
                                        mcsTransformer.clearAndTransform(upstream.modifiedColumnSet(),
                                                downstream.modifiedColumnSet);
                                    } else {
                                        downstream = TableUpdateImpl.copy(upstream, ModifiedColumnSet.EMPTY);
                                    }
                                    resultTable.notifyListeners(downstream);
                                }
                            };
                            snapshotControl.setListenerAndResult(listener, resultTable);
                        }

                        result.setValue(resultTable);

                        return true;
                    });

                    return result.getValue();

                });
    }

    @Override
    public Table asOfJoin(
            Table rightTable,
            Collection<? extends JoinMatch> exactMatches,
            AsOfJoinMatch asOfMatch,
            Collection<? extends JoinAddition> columnsToAdd) {
        final MatchPair[] matches = Stream.concat(
                exactMatches.stream().map(MatchPair::of),
                Stream.of(new MatchPair(asOfMatch.leftColumn().name(), asOfMatch.rightColumn().name())))
                .toArray(MatchPair[]::new);
        final MatchPair[] additions = MatchPair.fromAddition(columnsToAdd);
        final AsOfJoinRule joinRule = asOfMatch.joinRule();
        switch (joinRule) {
            case GREATER_THAN_EQUAL:
            case GREATER_THAN:
                return ajImpl(rightTable, matches, additions, joinRule);
            case LESS_THAN_EQUAL:
            case LESS_THAN:
                return rajImpl(rightTable, matches, additions, joinRule);
            default:
                throw new IllegalStateException("Unexpected join rule " + joinRule);
        }
    }

    private Table ajImpl(final Table rightTable, final MatchPair[] columnsToMatch, final MatchPair[] columnsToAdd,
            AsOfJoinRule joinRule) {
        final UpdateGraph updateGraph = getUpdateGraph(rightTable);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (rightTable == null) {
                throw new IllegalArgumentException("aj() requires a non-null right hand side table.");
            }
            final Table rightTableCoalesced = rightTable.coalesce();
            return QueryPerformanceRecorder.withNugget(
                    "aj(" + "rightTable, " + matchString(columnsToMatch) + ", " + joinRule + ", "
                            + matchString(columnsToAdd) + ")",
                    () -> ajInternal(rightTableCoalesced, columnsToMatch, columnsToAdd, SortingOrder.Ascending,
                            joinRule));
        }
    }

    private Table rajImpl(final Table rightTable, final MatchPair[] columnsToMatch, final MatchPair[] columnsToAdd,
            AsOfJoinRule joinRule) {
        final UpdateGraph updateGraph = getUpdateGraph(rightTable);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            if (rightTable == null) {
                throw new IllegalArgumentException("raj() requires a non-null right hand side table.");
            }
            final Table rightTableCoalesced = rightTable.coalesce();
            return QueryPerformanceRecorder.withNugget(
                    "raj(" + "rightTable, " + matchString(columnsToMatch) + ", " + joinRule + ", "
                            + matchString(columnsToAdd) + ")",
                    () -> ajInternal(rightTableCoalesced.reverse(), columnsToMatch, columnsToAdd,
                            SortingOrder.Descending,
                            joinRule));
        }
    }

    private Table ajInternal(Table rightTable, MatchPair[] columnsToMatch, MatchPair[] columnsToAdd,
            final SortingOrder order, AsOfJoinRule joinRule) {
        if (rightTable == null) {
            throw new IllegalArgumentException("aj() requires a non-null right hand side table.");
        }

        columnsToAdd = createColumnsToAddIfMissing(rightTable, columnsToMatch, columnsToAdd);
        final List<MatchPair> revisedAdded = new ArrayList<>();
        final Set<String> addedColumns = new HashSet<>();
        for (MatchPair matchPair : columnsToMatch) {
            if (!columns.containsKey(matchPair.rightColumn)) {
                addedColumns.add(matchPair.rightColumn);
                revisedAdded.add(new MatchPair(matchPair.rightColumn, matchPair.rightColumn));
            }
        }
        for (MatchPair matchPair : columnsToAdd) {
            if (!addedColumns.contains(matchPair.rightColumn)) {
                revisedAdded.add(matchPair);
            } else if (!matchPair.leftColumn.equals(matchPair.rightColumn)) {
                for (int ii = 0; ii < revisedAdded.size(); ii++) {
                    final MatchPair pair = revisedAdded.get(ii);
                    if (pair.rightColumn.equals(matchPair.rightColumn)) {
                        revisedAdded.set(ii, matchPair);
                    }
                }
            }
        }
        columnsToAdd = revisedAdded.toArray(MatchPair.ZERO_LENGTH_MATCH_PAIR_ARRAY);

        final boolean disallowExactMatch;
        switch (joinRule) {
            case GREATER_THAN:
                if (order != SortingOrder.Ascending) {
                    throw new IllegalArgumentException("Invalid as of match rule for raj: " + joinRule);
                }
                disallowExactMatch = true;
                break;
            case GREATER_THAN_EQUAL:
                if (order != SortingOrder.Ascending) {
                    throw new IllegalArgumentException("Invalid as of match rule for raj: " + joinRule);
                }
                disallowExactMatch = false;
                break;
            case LESS_THAN:
                if (order != SortingOrder.Descending) {
                    throw new IllegalArgumentException("Invalid as of match rule for aj: " + joinRule);
                }
                disallowExactMatch = true;
                break;
            case LESS_THAN_EQUAL:
                if (order != SortingOrder.Descending) {
                    throw new IllegalArgumentException("Invalid as of match rule for aj: " + joinRule);
                }
                disallowExactMatch = false;
                break;
            default:
                throw new UnsupportedOperationException();
        }

        return AsOfJoinHelper.asOfJoin(this, (QueryTable) rightTable, columnsToMatch, columnsToAdd, order,
                disallowExactMatch);
    }

    @Override
    public Table naturalJoin(
            Table rightTable,
            Collection<? extends JoinMatch> columnsToMatch,
            Collection<? extends JoinAddition> columnsToAdd,
            NaturalJoinType joinType) {
        return naturalJoinImpl(
                rightTable,
                MatchPair.fromMatches(columnsToMatch),
                MatchPair.fromAddition(columnsToAdd),
                joinType);
    }

    private Table naturalJoinImpl(
            final Table rightTable,
            final MatchPair[] columnsToMatch,
            final MatchPair[] columnsToAdd,
            final NaturalJoinType joinType) {
        final UpdateGraph updateGraph = getUpdateGraph(rightTable);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget(
                    "naturalJoin(" + matchString(columnsToMatch) + ", " + matchString(columnsToAdd) + ")",
                    () -> naturalJoinInternal(rightTable, columnsToMatch, columnsToAdd, joinType));
        }
    }

    private Table naturalJoinInternal(
            final Table rightTable,
            final MatchPair[] columnsToMatch,
            MatchPair[] columnsToAdd,
            final NaturalJoinType joinType) {
        columnsToAdd = createColumnsToAddIfMissing(rightTable, columnsToMatch, columnsToAdd);

        final QueryTable rightTableCoalesced = (QueryTable) rightTable.coalesce();

        return NaturalJoinHelper.naturalJoin(this, rightTableCoalesced, columnsToMatch, columnsToAdd, joinType);
    }

    private MatchPair[] createColumnsToAddIfMissing(Table rightTable, MatchPair[] columnsToMatch,
            MatchPair[] columnsToAdd) {
        if (columnsToAdd.length == 0) {
            final Set<String> matchColumns = Arrays.stream(columnsToMatch).map(matchPair -> matchPair.leftColumn)
                    .collect(Collectors.toCollection(HashSet::new));
            final List<String> columnNames = rightTable.getDefinition().getColumnNames();
            return columnNames.stream().filter((name) -> !matchColumns.contains(name))
                    .map(name -> new MatchPair(name, name)).toArray(MatchPair[]::new);
        }
        return columnsToAdd;
    }

    private static String selectColumnString(final SelectColumn[] selectColumns) {
        final StringBuilder result = new StringBuilder();
        result.append('[');
        final Iterable<String> scs =
                Arrays.stream(selectColumns).map(SelectColumn::getName).filter(name -> name.length() > 0)::iterator;
        IterableUtils.appendCommaSeparatedList(result, scs);
        result.append("]");
        return result.toString();
    }

    static <T extends ColumnSource<?>> void startTrackingPrev(Collection<T> values) {
        values.forEach(ColumnSource::startTrackingPrevValues);
    }

    @Override
    public Table join(
            @NotNull final Table rightTable,
            @NotNull final Collection<? extends JoinMatch> columnsToMatch,
            @NotNull final Collection<? extends JoinAddition> columnsToAdd,
            int numRightBitsToReserve) {
        return joinImpl(
                rightTable,
                MatchPair.fromMatches(columnsToMatch),
                MatchPair.fromAddition(columnsToAdd),
                numRightBitsToReserve);
    }

    private Table joinImpl(final Table rightTable, MatchPair[] columnsToMatch, MatchPair[] columnsToAdd,
            int numRightBitsToReserve) {
        final UpdateGraph updateGraph = getUpdateGraph(rightTable);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return memoizeResult(
                    MemoizedOperationKey.crossJoin(rightTable, columnsToMatch, columnsToAdd,
                            numRightBitsToReserve),
                    () -> joinNoMemo(rightTable, columnsToMatch, columnsToAdd, numRightBitsToReserve));
        }
    }

    private Table joinNoMemo(
            final Table rightTableCandidate,
            final MatchPair[] columnsToMatch,
            final MatchPair[] columnsToAdd,
            int numRightBitsToReserve) {
        final MatchPair[] realColumnsToAdd =
                createColumnsToAddIfMissing(rightTableCandidate, columnsToMatch, columnsToAdd);

        if (USE_CHUNKED_CROSS_JOIN) {
            final QueryTable coalescedRightTable = (QueryTable) rightTableCandidate.coalesce();
            return QueryPerformanceRecorder.withNugget(
                    "join(" + matchString(columnsToMatch) + ", " + matchString(realColumnsToAdd) + ", "
                            + numRightBitsToReserve + ")",
                    () -> CrossJoinHelper.join(this, coalescedRightTable, columnsToMatch, realColumnsToAdd,
                            numRightBitsToReserve));
        }

        final Set<String> columnsToMatchSet =
                Arrays.stream(columnsToMatch).map(MatchPair::rightColumn)
                        .collect(Collectors.toCollection(HashSet::new));

        final Map<String, Selectable> columnsToAddSelectColumns = new LinkedHashMap<>();
        final List<String> columnsToUngroupBy = new ArrayList<>();
        final String[] rightColumnsToMatch = new String[columnsToMatch.length];
        for (int i = 0; i < rightColumnsToMatch.length; i++) {
            rightColumnsToMatch[i] = columnsToMatch[i].rightColumn;
            columnsToAddSelectColumns.put(columnsToMatch[i].rightColumn, ColumnName.of(columnsToMatch[i].rightColumn));
        }
        final ArrayList<MatchPair> columnsToAddAfterRename = new ArrayList<>(realColumnsToAdd.length);
        for (MatchPair matchPair : realColumnsToAdd) {
            columnsToAddAfterRename.add(new MatchPair(matchPair.leftColumn, matchPair.leftColumn));
            if (!columnsToMatchSet.contains(matchPair.leftColumn)) {
                columnsToUngroupBy.add(matchPair.leftColumn);
            }
            columnsToAddSelectColumns.put(matchPair.leftColumn,
                    Selectable.of(ColumnName.of(matchPair.leftColumn), ColumnName.of(matchPair.rightColumn)));
        }

        return QueryPerformanceRecorder
                .withNugget("join(" + matchString(columnsToMatch) + ", " + matchString(realColumnsToAdd) + ")", () -> {
                    boolean sentinelAdded = false;
                    final Table rightTable;
                    if (columnsToUngroupBy.isEmpty()) {
                        rightTable = rightTableCandidate.updateView("__sentinel__=null");
                        columnsToUngroupBy.add("__sentinel__");
                        columnsToAddSelectColumns.put("__sentinel__", ColumnName.of("__sentinel__"));
                        columnsToAddAfterRename.add(new MatchPair("__sentinel__", "__sentinel__"));
                        sentinelAdded = true;
                    } else {
                        rightTable = rightTableCandidate;
                    }

                    final Table rightGrouped = rightTable.groupBy(rightColumnsToMatch)
                            .view(columnsToAddSelectColumns.values());
                    final Table naturalJoinResult = naturalJoinImpl(rightGrouped, columnsToMatch,
                            columnsToAddAfterRename.toArray(MatchPair.ZERO_LENGTH_MATCH_PAIR_ARRAY),
                            NaturalJoinType.ERROR_ON_DUPLICATE);
                    final QueryTable ungroupedResult = (QueryTable) naturalJoinResult
                            .ungroup(columnsToUngroupBy.toArray(String[]::new));

                    maybeCopyColumnDescriptions(ungroupedResult, rightTable, columnsToMatch, realColumnsToAdd);

                    return sentinelAdded ? ungroupedResult.dropColumns("__sentinel__") : ungroupedResult;
                });
    }

    @Override
    public Table rangeJoin(
            @NotNull final Table rightTable,
            @NotNull final Collection<? extends JoinMatch> exactMatches,
            @NotNull final RangeJoinMatch rangeMatch,
            @NotNull final Collection<? extends Aggregation> aggregations) {
        return getResult(new RangeJoinOperation(this, rightTable, exactMatches, rangeMatch, aggregations));
    }

    /**
     * The triggerColumns are the column sources for the snapshot-triggering table. The baseColumns are the column
     * sources for the table being snapshotted. The triggerRowSet refers to snapshots that we want to take. Typically
     * this rowSet is expected to have size 1, but in some cases it could be larger. The baseRowSet refers to the rowSet
     * of the current table. Therefore we want to take triggerRowSet.size() snapshots, each of which being
     * baseRowSet.size() in size.
     *
     * @param triggerColumns Columns making up the triggering data
     * @param triggerRowSet The currently triggering rows
     * @param baseColumns Columns making up the data being snapshotted
     * @param baseRowSet The data to snapshot
     * @param dest The ColumnSources in which to store the data. The keys are drawn from triggerColumns.keys() and
     *        baseColumns.keys()
     * @param destOffset The offset in the 'dest' ColumnSources at which to write data
     * @return The new dest ColumnSource size, calculated as
     *         {@code destOffset + triggerRowSet.size() * baseRowSet.size()}
     */
    private static long snapshotHistoryInternal(
            @NotNull Map<String, ? extends ColumnSource<?>> triggerColumns, @NotNull RowSet triggerRowSet,
            @NotNull Map<String, ChunkSource.WithPrev<? extends Values>> baseColumns, @NotNull RowSet baseRowSet,
            @NotNull Map<String, ? extends WritableColumnSource<?>> dest, long destOffset) {
        assert triggerColumns.size() + baseColumns.size() == dest.size();
        if (triggerRowSet.isEmpty() || baseRowSet.isEmpty()) {
            // Nothing to do.
            return destOffset;
        }

        final long newCapacity = destOffset + triggerRowSet.size() * baseRowSet.size();
        // Ensure all the capacities
        for (WritableColumnSource<?> ws : dest.values()) {
            ws.ensureCapacity(newCapacity);
        }

        final int baseSize = baseRowSet.intSize();
        long[] destOffsetHolder = new long[] {destOffset};
        // For each key on the snapshotting side
        triggerRowSet.forAllRowKeys(snapshotKey -> {
            final long doff = destOffsetHolder[0];
            destOffsetHolder[0] += baseSize;
            try (final RowSet destRowSet = RowSetFactory.fromRange(doff, doff + baseSize - 1)) {
                SnapshotUtils.copyStampColumns(triggerColumns, snapshotKey, dest, destRowSet);
                SnapshotUtils.copyDataColumns(baseColumns, baseRowSet, dest, destRowSet, false);
            }
        });
        return newCapacity;
    }

    private Table snapshotHistory(final String nuggetName, final Table baseTable,
            Collection<? extends JoinAddition> stampColumns) {
        return QueryPerformanceRecorder.withNugget(nuggetName, baseTable.sizeForInstrumentation(),
                () -> ((QueryTable) withAttributes(Map.of(APPEND_ONLY_TABLE_ATTRIBUTE, TRUE)))
                        .maybeViewForSnapshot(stampColumns)
                        .snapshotHistoryInternal(baseTable));
    }

    private Table snapshotHistoryInternal(final Table baseTable) {
        checkInitiateBinaryOperation(this, baseTable);

        // resultColumns initially contains the trigger columns, then we insert the base columns into it
        final Map<String, WritableColumnSource<?>> resultColumns = SnapshotUtils
                .createColumnSourceMap(this.getColumnSourceMap(), ArrayBackedColumnSource::getMemoryColumnSource);
        final Map<String, WritableColumnSource<?>> baseColumns = SnapshotUtils.createColumnSourceMap(
                baseTable.getColumnSourceMap(), ArrayBackedColumnSource::getMemoryColumnSource);
        resultColumns.putAll(baseColumns);

        // BTW, we don't track prev because these items are never modified or removed.
        final Table triggerTable = this; // For readability.
        final Map<String, ? extends ColumnSource<?>> triggerStampColumns =
                SnapshotUtils.generateTriggerStampColumns(triggerTable);
        final Map<String, ChunkSource.WithPrev<? extends Values>> snapshotDataColumns =
                SnapshotUtils.generateSnapshotDataColumns(baseTable);
        final long initialSize = snapshotHistoryInternal(triggerStampColumns, triggerTable.getRowSet(),
                snapshotDataColumns, baseTable.getRowSet(), resultColumns, 0);
        final TrackingWritableRowSet resultRowSet = RowSetFactory.flat(initialSize).toTracking();
        final QueryTable result = new QueryTable(resultRowSet, resultColumns);
        if (isRefreshing()) {
            addUpdateListener(
                    new ShiftObliviousListenerImpl("snapshotHistory" + resultColumns.keySet(), this, result) {
                        private long lastKey = rowSet.lastRowKey();

                        @Override
                        public void onUpdate(final RowSet added, final RowSet removed, final RowSet modified) {
                            Assert.assertion(removed.size() == 0, "removed.size() == 0", removed, "removed");
                            Assert.assertion(modified.size() == 0, "modified.size() == 0", modified, "modified");
                            if (added.size() == 0 || baseTable.size() == 0) {
                                return;
                            }
                            Assert.assertion(added.firstRowKey() > lastKey, "added.firstRowKey() > lastRowKey", lastKey,
                                    "lastRowKey", added, "added");
                            final long oldSize = resultRowSet.size();
                            final long newSize = snapshotHistoryInternal(triggerStampColumns, added,
                                    snapshotDataColumns, baseTable.getRowSet(), resultColumns, oldSize);
                            final RowSet addedSnapshots = RowSetFactory.fromRange(oldSize, newSize - 1);
                            resultRowSet.insert(addedSnapshots);
                            lastKey = rowSet.lastRowKey();
                            result.notifyListeners(addedSnapshots, RowSetFactory.empty(), RowSetFactory.empty());
                        }

                        @Override
                        public boolean canExecute(final long step) {
                            return baseTable.satisfied(step) && super.canExecute(step);
                        }
                    });
        }
        result.setFlat();
        return result;
    }

    public Table silent() {
        return new QueryTable(getRowSet(), getColumnSourceMap());
    }

    private Table snapshot(String nuggetName, Table baseTable, boolean doInitialSnapshot,
            Collection<? extends JoinAddition> stampColumns) {
        return QueryPerformanceRecorder.withNugget(nuggetName, baseTable.sizeForInstrumentation(), () -> {
            QueryTable viewTable = maybeViewForSnapshot(stampColumns);
            // Due to the above logic, we need to pull the actual set of column names back from the viewTable.
            // Whatever viewTable came back from the above, we do the snapshot
            return viewTable.snapshotInternal(baseTable, doInitialSnapshot,
                    viewTable.getDefinition().getColumnNamesArray());
        });
    }

    private Table snapshotInternal(Table baseTable, boolean doInitialSnapshot, String... stampColumns) {
        // TODO: we would like to make this operation UGP safe, instead of requiring the lock here; there are two tables
        // but we do only need to listen to one of them; however we are dependent on two of them
        checkInitiateOperation();

        // There are no LazySnapshotTableProviders in the system currently, but they may be used for multicast
        // distribution systems and similar integrations.

        // If this table provides a lazy snapshot version, we should use that instead for the snapshot, this allows us
        // to run the table only immediately before the snapshot occurs. Because we know that we are uninterested
        // in things like previous values, it can save a significant amount of CPU to only run the table when
        // needed.
        final boolean lazySnapshot = baseTable instanceof LazySnapshotTableProvider;
        if (lazySnapshot) {
            baseTable = ((LazySnapshotTableProvider) baseTable).getLazySnapshotTable();
        } else if (baseTable instanceof UncoalescedTable) {
            // something that needs coalescing I guess
            baseTable = baseTable.coalesce();
        }

        if (isRefreshing()) {
            checkInitiateOperation(baseTable);
        }

        // Establish the "base" columns using the same names and types as the table being snapshotted
        final Map<String, WritableColumnSource<?>> baseColumns =
                SnapshotUtils.createColumnSourceMap(baseTable.getColumnSourceMap(),
                        ArrayBackedColumnSource::getMemoryColumnSource);

        // Now make the "trigger" columns (namely, the "snapshot key" columns). Because this flavor of "snapshot" only
        // keeps a single snapshot, each snapshot key column will have the same value in every row. So for efficiency we
        // use a SingleValueColumnSource for these columns.
        final Map<String, SingleValueColumnSource<?>> triggerColumns = new LinkedHashMap<>();
        for (String stampColumn : stampColumns) {
            final Class<?> stampColumnType = getColumnSource(stampColumn).getType();
            triggerColumns.put(stampColumn, SingleValueColumnSource.getSingleValueColumnSource(stampColumnType));
        }

        // make our result table
        final Map<String, ColumnSource<?>> allColumns = new LinkedHashMap<>(baseColumns);
        allColumns.putAll(triggerColumns);
        if (allColumns.size() != triggerColumns.size() + baseColumns.size()) {
            throwColumnConflictMessage(triggerColumns.keySet(), baseColumns.keySet());
        }

        final QueryTable result =
                new QueryTable(RowSetFactory.empty().toTracking(), allColumns);
        final SnapshotInternalListener listener = new SnapshotInternalListener(this, lazySnapshot, baseTable,
                result, triggerColumns, baseColumns, result.getRowSet().writableCast());

        if (doInitialSnapshot) {
            if (!isRefreshing() && baseTable.isRefreshing() && !lazySnapshot) {
                // if we are making a static copy of the table, we must ensure that it does not change out from under us
                ConstructSnapshot.callDataSnapshotFunction("snapshotInternal",
                        ConstructSnapshot.makeSnapshotControl(false, baseTable.isRefreshing(),
                                (NotificationStepSource) baseTable),
                        (usePrev, beforeClockUnused) -> {
                            listener.doSnapshot(false, usePrev);
                            result.getRowSet().writableCast().initializePreviousValue();
                            return true;
                        });

            } else {
                listener.doSnapshot(false, false);
            }
        }

        if (isRefreshing()) {
            startTrackingPrev(allColumns.values());
            addUpdateListener(listener);
        }

        result.setFlat();

        return result;
    }

    private Table snapshotIncremental(String nuggetName, Table baseTable, boolean doInitialSnapshot,
            Collection<? extends JoinAddition> stampColumns) {
        return QueryPerformanceRecorder.withNugget(nuggetName, baseTable.sizeForInstrumentation(), () -> {
            QueryTable viewTable = maybeViewForSnapshot(stampColumns);
            // Due to the above logic, we need to pull the actual set of column names back from the viewTable.
            // Whatever viewTable came back from the above, we do the snapshot
            return viewTable.snapshotIncrementalInternal(baseTable, doInitialSnapshot,
                    viewTable.getDefinition().getColumnNamesArray());
        });
    }

    private Table snapshotIncrementalInternal(final Table base, final boolean doInitialSnapshot,
            final String... stampColumns) {
        checkInitiateBinaryOperation(this, base);

        final QueryTable baseTable = (QueryTable) (base instanceof UncoalescedTable ? base.coalesce() : base);

        // Use the given columns (if specified); otherwise an empty array means all of my columns
        final String[] useStampColumns = stampColumns.length == 0
                ? definition.getColumnNamesArray()
                : stampColumns;

        final Map<String, ColumnSource<?>> triggerColumns = new LinkedHashMap<>();
        for (String stampColumn : useStampColumns) {
            triggerColumns.put(stampColumn,
                    SnapshotUtils.maybeTransformToDirectVectorColumnSource(getColumnSource(stampColumn)));
        }

        final Map<String, WritableColumnSource<?>> resultTriggerColumns = new LinkedHashMap<>();
        for (Map.Entry<String, ColumnSource<?>> entry : triggerColumns.entrySet()) {
            final String name = entry.getKey();
            final ColumnSource<?> cs = entry.getValue();
            final Class<?> type = cs.getType();
            final WritableColumnSource<?> stampDest = Vector.class.isAssignableFrom(type)
                    ? SparseArrayColumnSource.getSparseMemoryColumnSource(type, cs.getComponentType())
                    : SparseArrayColumnSource.getSparseMemoryColumnSource(type);

            resultTriggerColumns.put(name, stampDest);
        }

        final Map<String, WritableColumnSource<?>> resultBaseColumns = SnapshotUtils.createColumnSourceMap(
                baseTable.getColumnSourceMap(), SparseArrayColumnSource::getSparseMemoryColumnSource);
        final Map<String, WritableColumnSource<?>> resultColumns = new LinkedHashMap<>(resultBaseColumns);
        resultColumns.putAll(resultTriggerColumns);
        if (resultColumns.size() != resultTriggerColumns.size() + resultBaseColumns.size()) {
            throwColumnConflictMessage(resultTriggerColumns.keySet(), resultBaseColumns.keySet());
        }

        final QueryTable resultTable = new QueryTable(RowSetFactory.empty().toTracking(), resultColumns);

        if (isRefreshing() && baseTable.isRefreshing()) {

            // What's happening here: the trigger table gets "listener" (some complicated logic that has access
            // to the coalescer) whereas the base table (above) gets the one-liner above (but which also
            // has access to the same coalescer). So when the base table sees updates they are simply fed
            // to the coalescer.
            // The coalescer's job is just to remember what rows have changed. When the *trigger* table gets
            // updates, then the SnapshotIncrementalListener gets called, which does all the snapshotting
            // work.

            final ListenerRecorder baseListenerRecorder =
                    new ListenerRecorder("snapshotIncremental (baseTable)", baseTable, resultTable);
            baseTable.addUpdateListener(baseListenerRecorder);

            final ListenerRecorder triggerListenerRecorder =
                    new ListenerRecorder("snapshotIncremental (triggerTable)", this, resultTable);
            addUpdateListener(triggerListenerRecorder);

            final SnapshotIncrementalListener listener =
                    new SnapshotIncrementalListener(this, resultTable, resultColumns,
                            baseListenerRecorder, triggerListenerRecorder, baseTable, triggerColumns);

            baseListenerRecorder.setMergedListener(listener);
            triggerListenerRecorder.setMergedListener(listener);
            resultTable.addParentReference(listener);

            if (doInitialSnapshot) {
                listener.doFirstSnapshot(true);
            }

            startTrackingPrev(resultColumns.values());
            resultTable.getRowSet().writableCast().initializePreviousValue();
        } else if (doInitialSnapshot) {
            SnapshotIncrementalListener.copyRowsToResult(baseTable.getRowSet(), this,
                    SnapshotUtils.generateSnapshotDataColumns(baseTable),
                    triggerColumns, resultColumns);
            resultTable.getRowSet().writableCast().insert(baseTable.getRowSet());
            resultTable.getRowSet().writableCast().initializePreviousValue();
        } else if (isRefreshing()) {
            // we are not doing an initial snapshot, but are refreshing so need to take a snapshot of our (static)
            // base table on the very first tick of the triggerTable
            addUpdateListener(
                    new ListenerImpl("snapshotIncremental (triggerTable)", this, resultTable) {
                        @Override
                        public void onUpdate(TableUpdate upstream) {
                            SnapshotIncrementalListener.copyRowsToResult(baseTable.getRowSet(),
                                    QueryTable.this, SnapshotUtils.generateSnapshotDataColumns(baseTable),
                                    triggerColumns, resultColumns);
                            resultTable.getRowSet().writableCast().insert(baseTable.getRowSet());
                            resultTable.notifyListeners(resultTable.getRowSet().copy(),
                                    RowSetFactory.empty(),
                                    RowSetFactory.empty());
                            removeUpdateListener(this);
                        }
                    });
        }

        return resultTable;
    }

    @Override
    public Table snapshot() {
        // TODO(deephaven-core#3271): Make snapshot() concurrent
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget("snapshot()", sizeForInstrumentation(),
                    () -> ((QueryTable) TableTools.emptyTable(1)).snapshotInternal(this, true));
        }
    }

    @Override
    public Table snapshotWhen(Table trigger, SnapshotWhenOptions options) {
        final UpdateGraph updateGraph = getUpdateGraph(trigger);
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final boolean initial = options.has(Flag.INITIAL);
            final boolean incremental = options.has(Flag.INCREMENTAL);
            final boolean history = options.has(Flag.HISTORY);
            final String description = options.description();
            if (history) {
                if (initial || incremental) {
                    // noinspection ThrowableNotThrown
                    Assert.statementNeverExecuted(
                            "SnapshotWhenOptions should disallow history with initial or incremental");
                    return null;
                }
                return ((QueryTable) trigger).snapshotHistory(description, this, options.stampColumns());
            }
            if (incremental) {
                return ((QueryTable) trigger).snapshotIncremental(description, this, initial, options.stampColumns());
            }
            return ((QueryTable) trigger).snapshot(description, this, initial, options.stampColumns());
        }
    }

    private QueryTable maybeViewForSnapshot(Collection<? extends JoinAddition> stampColumns) {
        // When stampColumns is empty, we'll just use this table (instead of invoking view w/ empty list)
        return stampColumns.isEmpty() ? this
                : (QueryTable) viewOrUpdateView(Flavor.View, SourceColumn.from(stampColumns));
    }

    private static void throwColumnConflictMessage(Set<String> left, Set<String> right) {
        Iterable<String> conflicts = left.stream().filter(right::contains)::iterator;
        throw new RuntimeException("Column name conflicts: " + IterableUtils.makeCommaSeparatedList(conflicts));
    }

    @Override
    public Table sort(Collection<SortColumn> columnsToSortBy) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final SortPair[] sortPairs = SortPair.from(columnsToSortBy);
            if (sortPairs.length == 0) {
                return prepareReturnThis();
            } else if (sortPairs.length == 1) {
                final String columnName = sortPairs[0].getColumn();
                final SortingOrder order = sortPairs[0].getOrder();
                if (SortedColumnsAttribute.isSortedBy(this, columnName, order)) {
                    return prepareReturnThis();
                }
            }

            return getResult(new SortOperation(this, sortPairs));
        }
    }

    /**
     * This is the smallest "base" that is used by the ungroup function. Each row from the input table is allocated
     * 2^minimumUngroupBase rows in the output table at startup. If rows are added to the table, this base may need to
     * grow. If a single row in the input has more than 2^base rows, then the base must change for all of the rows.
     */
    static int minimumUngroupBase = 10;

    /**
     * For unit testing, it can be useful to reduce the minimum ungroup base.
     *
     * @param minimumUngroupBase the minimum ungroup base for newly created ungrouped tables.
     * @return The old value of minimumUngroupBase
     */
    static int setMinimumUngroupBase(int minimumUngroupBase) {
        final int oldValue = QueryTable.minimumUngroupBase;
        QueryTable.minimumUngroupBase = minimumUngroupBase;
        return oldValue;
    }

    /**
     * The reverse operation returns a new table that is the same as the original table, but the first row is last, and
     * the last row is first. This is an internal API to be used by .raj(), but is accessible for unit tests.
     *
     * @return the reversed table
     */
    @Override
    public Table reverse() {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return getResult(new ReverseOperation(this));
        }
    }


    @Override
    public Table ungroup(final boolean nullFill, final Collection<? extends ColumnName> columnsToUngroup) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final String[] columnsToUngroupBy;
            if (columnsToUngroup.isEmpty()) {
                columnsToUngroupBy = getDefinition()
                        .getColumnStream()
                        .filter(c -> c.getDataType().isArray() || QueryLanguageParser.isTypedVector(c.getDataType()))
                        .map(ColumnDefinition::getName)
                        .toArray(String[]::new);
            } else {
                columnsToUngroupBy = columnsToUngroup.stream().map(ColumnName::name).toArray(String[]::new);
            }

            if (columnsToUngroupBy.length == 0) {
                return prepareReturnThis();
            }

            return getResult(new UngroupOperation(this, nullFill, columnsToUngroupBy));
        }
    }

    @Override
    public Table selectDistinct(Collection<? extends Selectable> columns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget("selectDistinct(" + columns + ")",
                    sizeForInstrumentation(),
                    () -> {
                        final Collection<ColumnName> columnNames = ColumnName.cast(columns).orElse(null);
                        if (columnNames == null) {
                            return view(columns).selectDistinct();
                        }
                        final MemoizedOperationKey aggKey =
                                MemoizedOperationKey.aggBy(Collections.emptyList(), false, null, columnNames);
                        return memoizeResult(aggKey, () -> {
                            final QueryTable result =
                                    aggNoMemo(AggregationProcessor.forSelectDistinct(), false, null, columnNames);
                            if (isAddOnly()) {
                                result.setAttribute(Table.ADD_ONLY_TABLE_ATTRIBUTE, true);
                            }
                            if (isAppendOnly()) {
                                result.setAttribute(Table.APPEND_ONLY_TABLE_ATTRIBUTE, true);
                            }
                            return result;
                        });
                    });
        }
    }

    /**
     * <p>
     * If this table is flat, then set the result table flat.
     * </p>
     *
     * <p>
     * This function is for use when the result table shares a RowSet; such that if this table is flat, the result table
     * must also be flat.
     * </p>
     *
     * @param result the table derived from this table
     */
    public void propagateFlatness(QueryTable result) {
        if (isFlat()) {
            result.setFlat();
        }
    }

    /**
     * Get a {@link Table} that contains a sub-set of the rows from {@code this}. The result will share the same
     * {@link #getColumnSources() column sources} and {@link #getDefinition() definition} as this table.
     * <p>
     * The result will not update on its own, the caller must also establish an appropriate listener to update
     * {@code rowSet} and propagate {@link TableUpdate updates}.
     * <p>
     * No {@link QueryPerformanceNugget nugget} is opened for this table, to prevent operations that call this
     * repeatedly from having an inordinate performance penalty. If callers require a nugget, they must create one in
     * the enclosing operation.
     *
     * @param rowSet The result's {@link #getRowSet() row set}
     * @return A new table sharing this table's column sources with the specified row set
     */
    @Override
    public QueryTable getSubTable(@NotNull final TrackingRowSet rowSet) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return getSubTable(rowSet, null, null, ArrayTypeUtils.EMPTY_OBJECT_ARRAY);
        }
    }

    /**
     * Get a {@link Table} that adds, or overwrites, columns from {@code this}. The result will share the same
     * {@link #getRowSet() row set} as this table.
     * <p>
     * The result will not update on its own. The caller must also establish an appropriate listener to update the
     * provided column sources and propagate {@link TableUpdate updates}.
     * <p>
     * No attributes are propagated to the result table.
     *
     * @param additionalSources The additional columns to add or overwrite
     * @return A new table with the additional columns
     */
    public QueryTable withAdditionalColumns(@NotNull final Map<String, ColumnSource<?>> additionalSources) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final LinkedHashMap<String, ColumnSource<?>> columns = new LinkedHashMap<>(this.columns);
            columns.putAll(additionalSources);
            final TableDefinition definition = TableDefinition.inferFrom(columns);
            return new QueryTable(definition, rowSet, columns, null, null);
        }
    }

    /**
     * Get a {@link Table} that contains a sub-set of the rows from {@code this}. The result will share the same
     * {@link #getColumnSources() column sources} and {@link #getDefinition() definition} as this table.
     * <p>
     * The result will not update on its own, the caller must also establish an appropriate listener to update
     * {@code rowSet} and propagate {@link TableUpdate updates}.
     * <p>
     * This method is intended to be used for composing alternative engine operations, in particular
     * {@link #partitionBy(boolean, String...)}.
     * <p>
     * No {@link QueryPerformanceNugget nugget} is opened for this table, to prevent operations that call this
     * repeatedly from having an inordinate performance penalty. If callers require a nugget, they must create one in
     * the enclosing operation.
     *
     * @param rowSet The result's {@link #getRowSet() row set}
     * @param resultModifiedColumnSet The result's {@link #getModifiedColumnSetForUpdates() modified column set}, or
     *        {@code null} for default initialization
     * @param attributes The result's {@link #getAttributes() attributes}, or {@code null} for default initialization
     * @param parents Parent references for the result table
     * @return A new table sharing this table's column sources with the specified row set
     */
    public QueryTable getSubTable(
            @NotNull final TrackingRowSet rowSet,
            @Nullable final ModifiedColumnSet resultModifiedColumnSet,
            @Nullable final Map<String, Object> attributes,
            @NotNull final Object... parents) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            // There is no checkInitiateOperation check here, because partitionBy calls it internally and the RowSet
            // results are not updated internally, but rather externally.
            final QueryTable result = new QueryTable(definition, rowSet, columns, resultModifiedColumnSet, attributes);
            for (final Object parent : parents) {
                result.addParentReference(parent);
            }
            result.setLastNotificationStep(getLastNotificationStep());
            return result;
        }
    }

    /**
     * Copies this table, but with a new set of attributes.
     *
     * @return an identical table; but with a new set of attributes
     */
    @Override
    public QueryTable copy() {
        return copy(StandardOptions.COPY_ALL);
    }

    public QueryTable copy(Predicate<String> shouldCopy) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return copy(definition, shouldCopy);
        }
    }

    private enum StandardOptions implements Predicate<String> {
        COPY_ALL {
            @Override
            public boolean test(String attributeName) {
                return true;
            }
        },
        COPY_NONE {
            @Override
            public boolean test(String attributeName) {
                return false;
            }
        }
    }

    public QueryTable copy(TableDefinition definition, Predicate<String> shouldCopy) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget("copy()", sizeForInstrumentation(), () -> {
                final Mutable<QueryTable> result = new MutableObject<>();

                final OperationSnapshotControl snapshotControl =
                        createSnapshotControlIfRefreshing(OperationSnapshotControl::new);
                initializeWithSnapshot("copy", snapshotControl, (usePrev, beforeClockValue) -> {
                    final QueryTable resultTable = new CopiedTable(definition, this);
                    propagateFlatness(resultTable);
                    if (shouldCopy != StandardOptions.COPY_NONE) {
                        copyAttributes(resultTable, shouldCopy);
                    }
                    if (snapshotControl != null) {
                        final ListenerImpl listener = new ListenerImpl("copy()", this, resultTable);
                        snapshotControl.setListenerAndResult(listener, resultTable);
                    }

                    result.setValue(resultTable);

                    return true;
                });

                return result.getValue();
            });
        }
    }

    @VisibleForTesting
    static class CopiedTable extends QueryTable {
        private final QueryTable parent;

        private CopiedTable(TableDefinition definition, QueryTable parent) {
            super(definition, parent.rowSet, parent.columns, null, null);
            this.parent = parent;
        }

        @TestUseOnly
        boolean checkParent(Table expectedParent) {
            return expectedParent == this.parent;
        }

        @Override
        public <R> R memoizeResult(MemoizedOperationKey memoKey, Supplier<R> operation) {
            if (memoKey == null || !memoizeResults) {
                return operation.get();
            }

            final boolean attributesCompatible = memoKey.attributesCompatible(parent.getAttributes(), getAttributes());
            final Supplier<R> computeCachedOperation = attributesCompatible ? () -> {
                final R parentResult = parent.memoizeResult(memoKey, operation);
                if (parentResult instanceof QueryTable) {
                    final QueryTable myResult = ((QueryTable) parentResult).copy(StandardOptions.COPY_NONE);
                    copyAttributes((QueryTable) parentResult, myResult, memoKey.getParentCopyType());
                    copyAttributes(myResult, memoKey.copyType());
                    // noinspection unchecked
                    return (R) myResult;
                }
                return operation.get();
            } : operation;

            return super.memoizeResult(memoKey, computeCachedOperation);
        }
    }

    @Override
    public Table updateBy(@NotNull final UpdateByControl control,
            @NotNull final Collection<? extends UpdateByOperation> ops,
            @NotNull final Collection<? extends ColumnName> byColumns) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            return QueryPerformanceRecorder.withNugget("updateBy()", sizeForInstrumentation(),
                    () -> UpdateBy.updateBy(this, ops, byColumns, control));
        }
    }

    /**
     * For unit tests, provide a method to turn memoization on or off.
     *
     * @param memoizeResults should results be memoized?
     * @return the prior value
     */
    @VisibleForTesting
    public static boolean setMemoizeResults(boolean memoizeResults) {
        final boolean old = QueryTable.memoizeResults;
        QueryTable.memoizeResults = memoizeResults;
        return old;
    }

    /**
     * For unit testing, to simplify debugging.
     */
    @SuppressWarnings("unused")
    void clearMemoizedResults() {
        cachedOperations.clear();
    }

    /**
     * Saves a weak reference to the result of the given operation.
     *
     * @param memoKey a complete description of the operation, if null no memoization is performed
     * @param operation a supplier for the result
     * @return either the cached or newly generated result
     */
    public <R> R memoizeResult(MemoizedOperationKey memoKey, Supplier<R> operation) {
        if (memoKey == null || !memoizeResults) {
            return operation.get();
        }

        final MemoizedResult<R> cachedResult = getMemoizedResult(memoKey, ensureCachedOperations());
        return cachedResult.getOrCompute(operation);
    }

    private Map<MemoizedOperationKey, MemoizedResult<?>> ensureCachedOperations() {
        // noinspection unchecked
        return FieldUtils.ensureField(this, CACHED_OPERATIONS_UPDATER, EMPTY_CACHED_OPERATIONS, ConcurrentHashMap::new);
    }

    @NotNull
    private static <R> MemoizedResult<R> getMemoizedResult(MemoizedOperationKey memoKey,
            Map<MemoizedOperationKey, MemoizedResult<?>> cachedOperations) {
        // noinspection unchecked
        return (MemoizedResult<R>) cachedOperations.computeIfAbsent(memoKey, k -> new MemoizedResult<>());
    }

    private static class MemoizedResult<R> {
        private volatile WeakReference<R> reference;

        R getOrCompute(Supplier<R> operation) {
            final R cachedResult = getIfValid();
            if (cachedResult != null) {
                return maybeMarkSystemic(cachedResult);
            }

            synchronized (this) {
                final R cachedResultLocked = getIfValid();
                if (cachedResultLocked != null) {
                    return maybeMarkSystemic(cachedResultLocked);
                }

                final R result;
                result = operation.get();

                reference = new WeakReference<>(result);

                return result;
            }
        }

        private R maybeMarkSystemic(R cachedResult) {
            if (cachedResult instanceof SystemicObject && SystemicObjectTracker.isSystemicThread()) {
                // noinspection unchecked
                return (R) ((SystemicObject) cachedResult).markSystemic();
            }
            return cachedResult;
        }

        R getIfValid() {
            if (reference != null) {
                final R cachedResult = reference.get();
                if (!isFailed(cachedResult) && Liveness.verifyCachedObjectForReuse(cachedResult)) {
                    return cachedResult;
                }
            }
            return null;
        }

        private boolean isFailed(R cachedResult) {
            if (cachedResult instanceof Table) {
                return ((Table) cachedResult).isFailed();
            }
            if (cachedResult instanceof PartitionedTable) {
                return ((PartitionedTable) cachedResult).table().isFailed();
            }
            return false;
        }
    }

    public <T extends DynamicNode & NotificationStepReceiver> T getResult(final Operation<T> operation) {
        if (operation instanceof MemoizableOperation) {
            return memoizeResult(((MemoizableOperation<T>) operation).getMemoizedOperationKey(),
                    () -> getResultNoMemo(operation));
        }
        return getResultNoMemo(operation);
    }

    private <T extends DynamicNode & NotificationStepReceiver> T getResultNoMemo(final Operation<T> operation) {
        return QueryPerformanceRecorder.withNugget(operation.getDescription(), sizeForInstrumentation(), () -> {
            final Mutable<T> resultTable = new MutableObject<>();

            try (final SafeCloseable ignored = operation.beginOperation(this)) {
                final OperationSnapshotControl snapshotControl;
                if (isRefreshing() && operation.snapshotNeeded()) {
                    snapshotControl = operation.newSnapshotControl(this);
                } else {
                    snapshotControl = null;
                }

                initializeWithSnapshot(operation.getLogPrefix(), snapshotControl, (usePrev, beforeClockValue) -> {
                    final Operation.Result<T> result = operation.initialize(usePrev, beforeClockValue);
                    if (result == null) {
                        return false;
                    }

                    resultTable.setValue(result.resultNode);
                    if (snapshotControl != null) {
                        snapshotControl.setListenerAndResult(result.resultListener, result.resultNode);
                    }

                    return true;
                });

                return resultTable.getValue();
            }
        });
    }

    private void checkInitiateOperation() {
        checkInitiateOperation(this);
    }

    public static void checkInitiateOperation(@NotNull final Table table) {
        if (table.isRefreshing()) {
            table.getUpdateGraph().checkInitiateSerialTableOperation();
        }
    }

    public static void checkInitiateBinaryOperation(@NotNull final Table first, @NotNull final Table second) {
        if (first.isRefreshing() || second.isRefreshing()) {
            first.getUpdateGraph(second).checkInitiateSerialTableOperation();
        }
    }

    private <R> R applyInternal(@NotNull final Function<Table, R> function) {
        try (final SafeCloseable ignored =
                QueryPerformanceRecorder.getInstance().getNugget("apply(" + function + ")")) {
            return function.apply(this);
        }
    }

    @Override
    public <R> R apply(@NotNull final Function<Table, R> function) {
        if (function instanceof MemoizedOperationKey.Provider) {
            return memoizeResult(((MemoizedOperationKey.Provider) function).getMemoKey(),
                    () -> applyInternal(function));
        }

        return applyInternal(function);
    }

    public Table wouldMatch(WouldMatchPair... matchers) {
        final UpdateGraph updateGraph = getUpdateGraph();
        try (final SafeCloseable ignored = ExecutionContext.getContext().withUpdateGraph(updateGraph).open()) {
            final WouldMatchOperation operation = new WouldMatchOperation(this, matchers);
            operation.initializeFilters(this);
            return getResult(operation);
        }
    }

    public static SafeCloseable disableParallelWhereForThread() {
        final Boolean oldValue = disableParallelWhereForThread.get();
        disableParallelWhereForThread.set(true);
        return () -> disableParallelWhereForThread.set(oldValue);
    }

    static Boolean isParallelWhereDisabledForThread() {
        return disableParallelWhereForThread.get();
    }
}
