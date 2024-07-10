//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.context;

import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.util.ExecutionContextRegistrationException;
import org.jetbrains.annotations.NotNull;

public class PoisonedOperationInitializer implements OperationInitializer {

    public static final PoisonedOperationInitializer INSTANCE = new PoisonedOperationInitializer();

    private <T> T fail() {
        throw ExecutionContextRegistrationException.onFailedComponentAccess("OperationInitializer");
    }

    @Override
    public boolean canParallelize() {
        return fail();
    }

    @Override
    @NotNull
    public Runnable submit(@NotNull final Runnable task) {
        return fail();
    }

    @Override
    public int parallelismFactor() {
        return fail();
    }
}
