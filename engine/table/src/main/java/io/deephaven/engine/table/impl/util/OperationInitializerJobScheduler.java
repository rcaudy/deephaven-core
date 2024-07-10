//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl.util;

import io.deephaven.base.log.LogOutputAppendable;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.table.impl.perf.BasePerformanceEntry;
import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.io.log.impl.LogOutputStringImpl;
import io.deephaven.util.SafeCloseable;
import io.deephaven.util.process.ProcessEnvironment;
import org.jetbrains.annotations.NotNull;

import java.util.function.Consumer;

public class OperationInitializerJobScheduler implements JobScheduler {

    private final BasePerformanceEntry accumulatedBaseEntry = new BasePerformanceEntry();
    private final OperationInitializer operationInitializer;

    public OperationInitializerJobScheduler(@NotNull final OperationInitializer operationInitializer) {
        this.operationInitializer = operationInitializer;
    }

    public OperationInitializerJobScheduler() {
        this(ExecutionContext.getContext().getOperationInitializer());
    }

    @Override
    @NotNull
    public Runnable submit(
            final ExecutionContext executionContext,
            final Runnable task,
            final LogOutputAppendable description,
            final Consumer<Exception> onError) {
        return operationInitializer.submit(() -> {
            final BasePerformanceEntry basePerformanceEntry = new BasePerformanceEntry();
            basePerformanceEntry.onBaseEntryStart();
            try (final SafeCloseable ignored = executionContext == null ? null : executionContext.open()) {
                task.run();
            } catch (Exception e) {
                onError.accept(e);
            } catch (Error e) {
                final String logMessage = new LogOutputStringImpl().append(description).append(" Error").toString();
                ProcessEnvironment.getGlobalFatalErrorReporter().report(logMessage, e);
                throw e;
            } finally {
                basePerformanceEntry.onBaseEntryEnd();
                accumulatedBaseEntry.accumulate(basePerformanceEntry);
            }
        });
    }

    @Override
    public BasePerformanceEntry getAccumulatedPerformance() {
        return accumulatedBaseEntry;
    }

    @Override
    public int threadCount() {
        return operationInitializer.parallelismFactor();
    }
}
