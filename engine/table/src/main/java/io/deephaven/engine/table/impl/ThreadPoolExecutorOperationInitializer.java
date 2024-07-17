//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.chunk.util.pools.MultiChunkPool;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.util.thread.NamingThreadFactory;
import io.deephaven.util.thread.ThreadInitializationFactory;
import org.jetbrains.annotations.NotNull;

import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import static io.deephaven.util.thread.ThreadHelpers.getOrComputeThreadCountProperty;

/**
 * Implementation of {@link OperationInitializer} that delegates to a {@link ThreadPoolExecutor}.
 */
public class ThreadPoolExecutorOperationInitializer implements OperationInitializer {

    private final ThreadPoolExecutor executorService;

    private final ThreadLocal<Boolean> isInitializationThread = ThreadLocal.withInitial(() -> false);

    public ThreadPoolExecutorOperationInitializer(
            @NotNull final ThreadInitializationFactory threadInitializationFactory,
            final int parallelism) {
        final ThreadGroup threadGroup = new ThreadGroup("OperationInitializationThreadPool");
        final ThreadFactory threadFactory = new NamingThreadFactory(
                threadGroup, ThreadPoolExecutorOperationInitializer.class, "initializationExecutor", true) {
            @Override
            public Thread newThread(@NotNull final Runnable r) {
                return super.newThread(threadInitializationFactory.createInitializer(() -> {
                    isInitializationThread.set(true);
                    MultiChunkPool.enableDedicatedPoolForThisThread();
                    ExecutionContext.newBuilder().setOperationInitializer(OperationInitializer.NON_PARALLELIZABLE)
                            .build().apply(r);
                }));
            }
        };
        executorService = new ThreadPoolExecutor(
                parallelism, parallelism, 0L, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<>(), threadFactory);

        executorService.prestartAllCoreThreads();
    }

    public ThreadPoolExecutorOperationInitializer(
            @NotNull final ThreadInitializationFactory threadInitializationFactory) {
        this(threadInitializationFactory,
                getOrComputeThreadCountProperty("OperationInitializationThreadPool.threads", -1));
    }

    @Override
    public boolean canParallelize() {
        return parallelismFactor() > 1 && !isInitializationThread.get();
    }

    @Override
    @NotNull
    public Runnable submit(@NotNull final Runnable task) {
        executorService.execute(task);
        return () -> {};
    }

    @Override
    public int parallelismFactor() {
        return executorService.getCorePoolSize();
    }
}
