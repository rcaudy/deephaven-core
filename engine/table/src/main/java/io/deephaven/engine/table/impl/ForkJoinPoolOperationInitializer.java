//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.chunk.util.pools.MultiChunkPool;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.util.thread.ThreadInitializationFactory;
import org.jetbrains.annotations.NotNull;

import java.util.Objects;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinWorkerThread;

import static io.deephaven.util.thread.ThreadHelpers.getOrComputeThreadCountProperty;

/**
 * Implementation of {@link OperationInitializer} that delegates to a {@link ForkJoinPool}.
 */
public class ForkJoinPoolOperationInitializer implements OperationInitializer {

    @NotNull
    public static OperationInitializer fromCommonPool() {
        return COMMON;
    }

    private static final ForkJoinPoolOperationInitializer COMMON =
            new ForkJoinPoolOperationInitializer(ForkJoinPool.commonPool()) {
                @Override
                public @NotNull Runnable submit(@NotNull final Runnable task) {
                    return super.submit(() -> {
                        ExecutionContext.newBuilder()
                                .setOperationInitializer(this)
                                .build()
                                .apply(task);
                    });
                }
            };

    private final ForkJoinPool pool;

    private ForkJoinPoolOperationInitializer(@NotNull final ForkJoinPool pool) {
        this.pool = Objects.requireNonNull(pool);
    }

    public ForkJoinPoolOperationInitializer(
            @NotNull final ThreadInitializationFactory threadInitializationFactory,
            final int parallelism) {
        final ForkJoinPool.ForkJoinWorkerThreadFactory threadFactory = pool -> {
            final ForkJoinWorkerThread thread = new ForkJoinWorkerThread(pool) {
                @Override
                public void run() {
                    threadInitializationFactory.createInitializer(() -> {
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
        pool = new ForkJoinPool(parallelism, threadFactory, null, false);
    }

    public ForkJoinPoolOperationInitializer(@NotNull final ThreadInitializationFactory threadInitializationFactory) {
        this(threadInitializationFactory,
                getOrComputeThreadCountProperty("OperationInitializationThreadPool.threads", -1));
    }

    @Override
    public boolean canParallelize() {
        return parallelismFactor() > 1;
    }

    @Override
    @NotNull
    public Runnable submit(@NotNull final Runnable task) {
        return pool.submit(task)::join;
    }

    @Override
    public int parallelismFactor() {
        return pool.getParallelism();
    }
}
