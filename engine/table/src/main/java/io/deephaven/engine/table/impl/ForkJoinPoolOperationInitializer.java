//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.chunk.util.pools.MultiChunkPool;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.util.thread.ThreadInitializationFactory;
import org.jetbrains.annotations.NotNull;

import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinWorkerThread;

import static io.deephaven.util.thread.ThreadHelpers.getOrComputeThreadCountProperty;

/**
 * Implementation of {@link OperationInitializer} that delegates to a {@link ForkJoinPool}.
 */
public class ForkJoinPoolOperationInitializer implements OperationInitializer {

    /**
     * The number of threads that will be used for parallel initialization in this process
     */
    private static final int NUM_THREADS =
            getOrComputeThreadCountProperty("OperationInitializationThreadPool.threads", -1);

    private final ForkJoinPool pool;

    public ForkJoinPoolOperationInitializer(ThreadInitializationFactory factory) {
        final ForkJoinPool.ForkJoinWorkerThreadFactory threadFactory = pool -> {
            final ForkJoinWorkerThread thread = new ForkJoinWorkerThread(pool) {
                @Override
                public void run() {
                    factory.createInitializer(() -> {
                        MultiChunkPool.enableDedicatedPoolForThisThread();
                        ExecutionContext.newBuilder()
                                .setOperationInitializer(ForkJoinPoolOperationInitializer.this)
                                .build()
                                .apply(super::run);
                    }).run();
                }
            };
            thread.setDaemon(true);
            thread.setName("OperationInitializationThreadPool-unregistered");
            return thread;
        };
        pool = new ForkJoinPool(NUM_THREADS, threadFactory, null, false);
    }

    @Override
    public boolean canParallelize() {
        return NUM_THREADS > 1;
    }

    @Override
    @NotNull
    public Runnable submit(@NotNull final Runnable task) {
        return pool.submit(task)::join;
    }

    @Override
    public int parallelismFactor() {
        return NUM_THREADS;
    }
}
