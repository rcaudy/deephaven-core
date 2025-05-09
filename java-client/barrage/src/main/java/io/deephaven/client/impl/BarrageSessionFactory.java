//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.client.impl;

import io.grpc.ManagedChannel;

public interface BarrageSessionFactory {

    /**
     * Creates a new {@link BarrageSession}. Closing the session does <b>not</b> close the {@link #managedChannel()}.
     *
     * @return the new barrage session
     */
    BarrageSession newBarrageSession();

    /**
     * The {@link ManagedChannel} associated with {@code this} factory. Use {@link ManagedChannel#shutdown()} when
     * {@code this} factory and sessions are no longer needed.
     *
     * @return the managed channel
     */
    ManagedChannel managedChannel();
}
