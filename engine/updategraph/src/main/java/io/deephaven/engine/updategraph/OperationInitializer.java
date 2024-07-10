//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.updategraph;

import org.jetbrains.annotations.NotNull;

/**
 * Execution framework for possibly-parallel operation initialization tasks. Provides guidance for initialization
 * operations on how they can parallelize.
 */
public interface OperationInitializer {

    OperationInitializer NON_PARALLELIZABLE = new OperationInitializer() {
        @Override
        public boolean canParallelize() {
            return false;
        }

        @Override
        @NotNull
        public Runnable submit(@NotNull final Runnable task) {
            task.run();
            return () -> {
            };
        }

        @Override
        public int parallelismFactor() {
            return 1;
        }
    };

    /**
     * Whether the current thread can parallelize operations using this OperationInitializer.
     */
    boolean canParallelize();

    /**
     * Submits a task to run in this OperationInitializer.
     *
     * @param task The task to be {@link Runnable#run() run}
     * @return A {@link Runnable} that should be invoked if or when the calling thread cannot make progress until the
     *         job is completed. Some implementations may use this to ensure progress for nested parallel jobs.
     */
    @NotNull
    Runnable submit(@NotNull Runnable task);

    /**
     * Number of threads that are potentially available.
     */
    int parallelismFactor();
}
