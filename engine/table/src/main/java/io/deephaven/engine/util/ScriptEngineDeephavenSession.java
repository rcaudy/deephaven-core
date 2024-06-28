//
// Copyright (c) 2016-2024 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.util;

import io.deephaven.engine.context.QueryScope;
import io.deephaven.engine.updategraph.OperationInitializer;
import io.deephaven.engine.updategraph.UpdateGraph;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import io.deephaven.plugin.type.ObjectTypeLookup;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Map;
import java.util.Set;
import java.util.function.Function;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;

/**
 * Kotlin {@link ScriptSession}. Not safe for concurrent use.
 */
public class ScriptEngineDeephavenSession extends AbstractScriptSession<?> {

    private static final Logger log = LoggerFactory.getLogger(ScriptEngineDeephavenSession.class);

    private final ScriptEngine engine;

    public ScriptEngineDeephavenSession(
            @NotNull final UpdateGraph updateGraph,
            @NotNull final OperationInitializer operationInitializer,
            @NotNull final ObjectTypeLookup objectTypeLookup,
            @Nullable final Listener changeListener,
            @NotNull final String extension) {
        super(updateGraph, operationInitializer, objectTypeLookup, changeListener);
        engine = new ScriptEngineManager().getEngineByExtension(extension);
    }



    @Override
    protected Snapshot emptySnapshot() {
        return null;
    }

    @Override
    protected Snapshot takeSnapshot() {
        return null;
    }

    @Override
    protected void evaluate(String command, @Nullable String scriptName) {

    }

    @Override
    protected <T> T getVariable(String name) throws QueryScope.MissingVariableException {
        return null;
    }

    @Override
    protected Set<String> getVariableNames() {
        return Set.of();
    }

    @Override
    protected boolean hasVariable(String name) {
        return false;
    }

    @Override
    protected Object setVariable(String name, @Nullable Object value) {
        return null;
    }

    @Override
    protected <T> Map<String, T> getAllValues(@Nullable Function<Object, T> valueMapper, QueryScope.@NotNull ParamFilter<T> filter) {
        return Map.of();
    }

    @Override
    protected Changes createDiff(Snapshot from, Snapshot to, RuntimeException e) {
        return null;
    }

    @Override
    public String scriptType() {
        return "";
    }
}
