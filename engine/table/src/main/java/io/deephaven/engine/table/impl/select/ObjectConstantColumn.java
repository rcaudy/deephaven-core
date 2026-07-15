//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit CharConstantColumn and run "./gradlew replicateConstantColumns" to regenerate
//
// @formatter:off
package io.deephaven.engine.table.impl.select;

import io.deephaven.chunk.ChunkType;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.TrackingRowSet;
import io.deephaven.engine.table.*;
import io.deephaven.engine.table.impl.MatchPair;
import io.deephaven.engine.table.impl.sources.ObjectSingleValueSource;
import io.deephaven.engine.table.impl.sources.ViewColumnSource;
import io.deephaven.vector.Vector;
import org.jetbrains.annotations.NotNull;

import java.util.Collections;
import java.util.List;
import java.util.Map;

/**
 * {@link SelectColumn} implementation to assign a constant {@code Object} value.
 * <p>
 * The C-harConstantColumn is replicated to all other types with io.deephaven.replicators.ReplicateConstantColumns.
 * <p>
 * (C-har is deliberately spelled that way in order to prevent Replicate from altering this very comment).
 */
public class ObjectConstantColumn<T> implements SelectColumn {

    private final String outputColumnName;

    // region Typed Fields
    private final T outputValue;
    private final Class<T> type;
    private final Class<?> componentType;
    // endregion Typed Fields

    // region Constructor
    private ObjectConstantColumn(
            @NotNull final String outputColumnName,
            @NotNull final T outputValue,
            @NotNull final Class<T> type,
            final Class<?> componentType) {
        this.outputColumnName = outputColumnName;
        this.outputValue = outputValue;
        this.type = type;
        this.componentType = componentType;
    }

    /**
     * Create a {@link SelectColumn} that assigns a constant {@code Object} value with explicit type and
     * component type.
     *
     * @param outputColumnName the name of the output column
     * @param outputValue the constant value
     * @param type the type of the value
     * @param componentType the component type (for array/vector types), or null
     * @return a {@link NullSelectColumn} if {@code outputValue} is null, otherwise a new
     *         ObjectConstantColumn
     */
    public static <T> SelectColumn of(
            @NotNull final String outputColumnName,
            final T outputValue,
            @NotNull final Class<T> type,
            final Class<?> componentType) {
        if (outputValue == null) {
            return new NullSelectColumn<>(type, componentType, outputColumnName);
        }
        return new ObjectConstantColumn<>(outputColumnName, outputValue, type, componentType);
    }

    /**
     * Create a {@link SelectColumn} that assigns a constant {@code Object} value with explicit type and
     * null component type.
     *
     * @param outputColumnName the name of the output column
     * @param outputValue the constant value
     * @param type the type of the value
     * @return a {@link NullSelectColumn} if {@code outputValue} is null, otherwise a new
     *         ObjectConstantColumn
     */
    public static <T> SelectColumn of(
            @NotNull final String outputColumnName,
            final T outputValue,
            @NotNull final Class<T> type) {
        return of(outputColumnName, outputValue, type, null);
    }

    /**
     * Create a {@link SelectColumn} that assigns a constant {@code Object} value, inferring the type and
     * component type from the value. If the value is null, the type will be {@code Object}.
     *
     * @param outputColumnName the name of the output column
     * @param outputValue the constant value
     * @return a {@link NullSelectColumn} if {@code outputValue} is null, otherwise a new
     *         ObjectConstantColumn
     */
    @SuppressWarnings("unchecked")
    public static <T> SelectColumn of(
            @NotNull final String outputColumnName,
            final T outputValue) {
        if (outputValue == null) {
            return of(outputColumnName, null, (Class<T>) (Class<?>) Object.class, null);
        }
        final Class<T> type = (Class<T>) outputValue.getClass();
        final Class<?> componentType;
        if (type.isArray()) {
            componentType = type.getComponentType();
        } else if (outputValue instanceof Vector) {
            componentType = ((Vector<?>) outputValue).getComponentType();
        } else {
            componentType = null;
        }
        return of(outputColumnName, outputValue, type, componentType);
    }
    // endregion Constructor

    @Override
    public List<String> initInputs(
            @NotNull final TrackingRowSet rowSet,
            @NotNull final Map<String, ? extends ColumnSource<?>> columnsOfInterest) {
        return getColumns();
    }

    @Override
    public List<String> initDef(@NotNull final Map<String, ColumnDefinition<?>> columnDefinitionMap) {
        return getColumns();
    }

    @Override
    public List<String> getColumns() {
        return Collections.emptyList();
    }

    @NotNull
    @Override
    public ColumnSource<?> getDataView() {
        return new ViewColumnSource<>(type, new OutputFormula(), true, true);
    }

    @Override
    public String getName() {
        return outputColumnName;
    }

    @Override
    public SelectColumn copy() {
        return this;
    }

    @Override
    public final Class<?> getReturnedType() {
        return type;
    }

    // region getReturnedComponentType
    @Override
    public Class<?> getReturnedComponentType() {
        return componentType;
    }
    // endregion getReturnedComponentType

    @Override
    public final List<String> getColumnArrays() {
        return Collections.emptyList();
    }

    @NotNull
    @Override
    public final ColumnSource<?> getLazyView() {
        return getDataView();
    }

    @Override
    public final MatchPair getMatchPair() {
        throw new UnsupportedOperationException();
    }

    @Override
    public final WritableColumnSource<?> newDestInstance(final long size) {
        return new ObjectSingleValueSource<>(type, componentType);
    }

    @Override
    public final WritableColumnSource<?> newFlatDestInstance(final long size) {
        return new ObjectSingleValueSource<>(type, componentType);
    }

    @Override
    public final boolean isRetain() {
        return false;
    }

    @Override
    public final boolean isStateless() {
        return true;
    }

    private static final class OutputFormulaFillContext implements Formula.FillContext {

        private static final Formula.FillContext INSTANCE = new OutputFormulaFillContext();

        private OutputFormulaFillContext() {}

        @Override
        public void close() {}
    }

    private final class OutputFormula extends Formula {

        private OutputFormula() {
            super(null);
        }

        @Override
        public Object get(final long rowKey) {
            return outputValue;
        }

        @Override
        public Object getPrev(final long rowKey) {
            return get(rowKey);
        }

        // region getTypedMethods
        // endregion getTypedMethods

        @Override
        protected ChunkType getChunkType() {
            return ChunkType.Object;
        }

        @Override
        public FillContext makeFillContext(final int chunkCapacity) {
            return OutputFormulaFillContext.INSTANCE;
        }

        @Override
        public void fillChunk(
                @NotNull final FillContext context,
                @NotNull final WritableChunk<? super Values> destination,
                @NotNull final RowSequence rowSequence) {
            destination.setSize(rowSequence.intSize());
            destination.asWritableObjectChunk().fillWithValue(0, destination.size(), outputValue);
        }

        @Override
        public void fillPrevChunk(
                @NotNull final FillContext context,
                @NotNull final WritableChunk<? super Values> destination,
                @NotNull final RowSequence rowSequence) {
            fillChunk(context, destination, rowSequence);
        }
    }
}
