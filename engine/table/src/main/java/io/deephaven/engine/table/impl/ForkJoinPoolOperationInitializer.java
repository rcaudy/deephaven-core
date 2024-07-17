//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.chunk.util.pools.MultiChunkPool;
import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.util.datastructures.linked.IntrusiveDoublyLinkedNode;
import io.deephaven.util.datastructures.linked.IntrusiveDoublyLinkedQueue;
import io.deephaven.util.thread.ThreadInitializationFactory;
import org.jetbrains.annotations.NotNull;

import java.util.Objects;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
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
            // The pool will rename this thread when it internally registers it.
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

    private static final class Joiner extends IntrusiveDoublyLinkedNode.Impl<Joiner> implements Runnable {

        private static final ThreadLocal<Joiner> enclosing = ThreadLocal.withInitial(() -> null);

        private volatile ForkJoinTask<?> task;

        private final IntrusiveDoublyLinkedQueue<Joiner> children =
                new IntrusiveDoublyLinkedQueue<>(IntrusiveDoublyLinkedNode.Adapter.<Joiner>getInstance());

        private static Joiner joinerFor(@NotNull final Runnable taskRunnable) {
            final Joiner taskJoiner = new Joiner(taskRunnable);
            final Joiner enclosingJoiner = Joiner.enclosing.get();
            if (enclosingJoiner != null) {
                enclosingJoiner.addChild(taskJoiner);
            }
            return taskJoiner;
        }

        private Joiner(@NotNull final Runnable taskRunnable) {
            //noinspection NonAtomicOperationOnVolatileField (Safe publication: task can't have been invoked yet)
            task = ForkJoinTask.adapt(() -> {
                final Joiner previousEnclosing = enclosing.get();
                try {
                    enclosing.set(this);
                    taskRunnable.run();
                } finally {
                    task = null;
                    enclosing.set(previousEnclosing);
                }
            });
        }

        private void addChild(@NotNull final Joiner child) {
            synchronized (children) {
                children.offer(child);
            }
        }

        @Override
        public void run() {
            await();
        }

        private void await() {
            final ForkJoinTask<?> localTask = task;
            if (localTask != null) {
                localTask.quietlyJoin();
            }
            // At this time we know that `children` can no longer be mutated, because `task` has completed, and we're
            // guaranteed visibility of the final state of `children` because we have read `task` as `null` after
            // completion or joined `task`, creating a happens-after relationship w.r.t. changes to `children`.
            for (final Joiner child : children) {
                child.await();
            }
        }
    }

    @Override
    @NotNull
    public Runnable submit(@NotNull final Runnable taskRunnable) {
        final Joiner taskJoiner = Joiner.joinerFor(taskRunnable);
        pool.invoke(taskJoiner.task);
        return taskJoiner;
    }

    @Override
    public int parallelismFactor() {
        return pool.getParallelism();
    }
}
