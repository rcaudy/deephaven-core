//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl;

import io.deephaven.base.cache.RetentionCache;
import io.deephaven.base.verify.Require;
import io.deephaven.engine.exceptions.UncheckedTableException;
import io.deephaven.engine.table.Table;
import io.deephaven.engine.table.TableUpdate;
import io.deephaven.time.DateTimeUtils;
import io.deephaven.engine.liveness.Liveness;
import io.deephaven.engine.table.impl.util.AsyncErrorLogger;
import io.deephaven.engine.table.impl.util.AsyncClientErrorNotifier;
import io.deephaven.util.Utils;
import io.deephaven.util.annotations.ReferentialIntegrity;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.annotation.OverridingMethodsMustInvokeSuper;
import java.io.IOException;
import java.util.stream.LongStream;

/**
 * This class is used for ShiftAwareListeners that represent "leaf" nodes in the update propagation tree.
 *
 * It provides an optional retention cache, to prevent listeners from being garbage collected.
 *
 * For creating internally ticking table nodes, instead use {@link BaseTable.ListenerImpl}
 */
public abstract class InstrumentedTableUpdateListenerAdapter extends InstrumentedTableUpdateListener {

    private static final RetentionCache<InstrumentedTableUpdateListenerAdapter> RETENTION_CACHE =
            new RetentionCache<>();

    private final boolean retain;

    @ReferentialIntegrity
    protected final Table source;

    /**
     * Create an instrumented listener for source. No description is provided.
     *
     * @param source The source table this listener will subscribe to - needed for preserving referential integrity
     * @param retain Whether a hard reference to this listener should be maintained to prevent it from being collected.
     *        In most scenarios, it's better to specify {@code false} and keep a reference in the calling code.
     */
    public InstrumentedTableUpdateListenerAdapter(@NotNull final Table source, final boolean retain) {
        this(null, source, retain);
    }

    /**
     * @param description A description for the UpdatePerformanceTracker to append to its entry description
     * @param source The source table this listener will subscribe to - needed for preserving referential integrity
     * @param retain Whether a hard reference to this listener should be maintained to prevent it from being collected.
     *        In most scenarios, it's better to specify {@code false} and keep a reference in the calling code.
     */
    public InstrumentedTableUpdateListenerAdapter(@Nullable final String description, @NotNull final Table source,
            final boolean retain) {
        super(description, false, () -> {
            if (source instanceof HasParentPerformanceIds) {
                return ((HasParentPerformanceIds) source).parentPerformanceEntryIds().toArray();
            }
            return null;
        });
        this.source = Require.neqNull(source, "source");
        if (this.retain = retain) {
            RETENTION_CACHE.retain(this);
            if (Liveness.DEBUG_MODE_ENABLED) {
                Liveness.log.info().append("LivenessDebug: InstrumentedTableUpdateListenerAdapter ")
                        .append(Utils.REFERENT_FORMATTER, this)
                        .append(" created with retention enabled").endl();
            }
        }
        manage(source);
    }

    @Override
    public abstract void onUpdate(TableUpdate upstream);

    /**
     * Called when the source table produces an error
     *
     * @param originalException the original throwable that caused this error
     * @param sourceEntry the performance tracker entry that was active when the error occurred
     */
    @Override
    public void onFailureInternal(Throwable originalException, Entry sourceEntry) {
        AsyncErrorLogger.log(DateTimeUtils.nowMillisResolution(), sourceEntry, sourceEntry, originalException);
        try {
            AsyncClientErrorNotifier.reportError(originalException);
        } catch (IOException e) {
            throw new UncheckedTableException("Exception in " + sourceEntry.toString(), originalException);
        }
    }

    @Override
    public boolean canExecute(final long step) {
        return source.satisfied(step);
    }

    @OverridingMethodsMustInvokeSuper
    @Override
    protected void destroy() {
        super.destroy();
        source.removeUpdateListener(this);
        if (retain) {
            RETENTION_CACHE.forget(this);
        }
    }
}
