//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.benchmark.engine;

import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.table.Table;
import io.deephaven.engine.table.TableUpdate;
import io.deephaven.engine.testutil.ControlledUpdateGraph;
import io.deephaven.engine.updategraph.DynamicNode;
import io.deephaven.engine.table.impl.InstrumentedTableUpdateListenerAdapter;
import io.deephaven.engine.table.impl.select.IncrementalReleaseFilter;
import io.deephaven.engine.table.impl.select.RollingReleaseFilter;

import java.util.function.BiFunction;
import java.util.function.Function;

class IncrementalBenchmark {
    static <R> R incrementalBenchmark(final Function<Table, R> function, final Table inputTable, final int steps) {
        final long sizePerStep = Math.max(inputTable.size() / steps, 1);
        final IncrementalReleaseFilter incrementalReleaseFilter =
                new IncrementalReleaseFilter(sizePerStep, sizePerStep);
        final Table filtered = inputTable.where(incrementalReleaseFilter);

        final R result = function.apply(filtered);

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.enableUnitTestMode();

        while (filtered.size() < inputTable.size()) {
            updateGraph.runWithinUnitTestCycle(incrementalReleaseFilter::run);
        }

        return result;
    }

    static <R> R rollingBenchmark(final Function<Table, R> function, final Table inputTable, final int steps) {
        final long sizePerStep = Math.max(inputTable.size() / steps, 1);
        final RollingReleaseFilter incrementalReleaseFilter = new RollingReleaseFilter(sizePerStep * 2, sizePerStep);
        final Table filtered = inputTable.where(incrementalReleaseFilter);

        final R result = function.apply(filtered);

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.enableUnitTestMode();

        for (int currentStep = 0; currentStep <= steps; currentStep++) {
            updateGraph.runWithinUnitTestCycle(incrementalReleaseFilter::run);
        }

        return result;
    }

    static <R> R incrementalBenchmark(final Function<Table, R> function, final Table inputTable) {
        return incrementalBenchmark(function, inputTable, 10);
    }

    static <R> R rollingBenchmark(final Function<Table, R> function, final Table inputTable) {
        return rollingBenchmark(function, inputTable, 10);
    }

    static <R> R incrementalBenchmark(final BiFunction<Table, Table, R> function, final Table inputTable1,
            final Table inputTable2) {
        return incrementalBenchmark(function, inputTable1, inputTable2, 0.1, 9);
    }

    static <R> R incrementalBenchmark(final BiFunction<Table, Table, R> function, final Table inputTable1,
            final Table inputTable2, double initialFraction, int steps) {
        final long initialSize1 = (long) (inputTable1.size() * initialFraction);
        final long initialSize2 = (long) (inputTable2.size() * initialFraction);

        final long sizePerStep1 = Math.max((inputTable1.size() - initialSize1) / steps, 1);
        final long sizePerStep2 = Math.max((inputTable2.size() - initialSize2) / steps, 1);

        final IncrementalReleaseFilter incrementalReleaseFilter1 =
                new IncrementalReleaseFilter(initialSize1, sizePerStep1);
        final IncrementalReleaseFilter incrementalReleaseFilter2 =
                new IncrementalReleaseFilter(initialSize2, sizePerStep2);
        final Table filtered1 = inputTable1.where(incrementalReleaseFilter1);
        final Table filtered2 = inputTable2.where(incrementalReleaseFilter2);

        final R result = function.apply(filtered1, filtered2);

        final InstrumentedTableUpdateListenerAdapter failureListener;
        if (DynamicNode.isDynamicAndIsRefreshing(result)) {
            failureListener =
                    new InstrumentedTableUpdateListenerAdapter("Failure Listener", (Table) result,
                            false) {
                        @Override
                        public void onUpdate(TableUpdate upstream) {}

                        @Override
                        public void onFailureInternal(Throwable originalException, Entry sourceEntry) {
                            originalException.printStackTrace();
                            System.exit(1);
                        }
                    };
            ((Table) result).addUpdateListener(failureListener);
        } else {
            failureListener = null;
        }

        final ControlledUpdateGraph updateGraph = ExecutionContext.getContext().getUpdateGraph().cast();
        updateGraph.enableUnitTestMode();

        while (filtered1.size() < inputTable1.size() || filtered2.size() < inputTable2.size()) {
            updateGraph.runWithinUnitTestCycle(incrementalReleaseFilter1::run);
            updateGraph.runWithinUnitTestCycle(incrementalReleaseFilter2::run);
        }

        if (failureListener != null) {
            ((Table) result).removeUpdateListener(failureListener);
        }

        return result;
    }
}
