//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl.select;

import io.deephaven.chunk.ChunkType;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.TrackingRowSet;
import io.deephaven.engine.table.*;
import io.deephaven.engine.table.impl.MatchPair;
import io.deephaven.engine.table.impl.sources.CharacterSingleValueSource;
import io.deephaven.engine.table.impl.sources.ViewColumnSource;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.type.TypeUtils;
import org.jetbrains.annotations.NotNull;

import java.util.Collections;
import java.util.List;
import java.util.Map;

/**
 * {@link SelectColumn} implementation to assign a constant {@code char} value.
 * <p>
 * The C-harConstantColumn is replicated to all other types with
 * io.deephaven.replicators.ReplicateConstantColumns.
 * <p>
 * (C-har is deliberately spelled that way in order to prevent Replicate from altering this very comment).
 */
public class CharConstantColumn implements SelectColumn {

    private final String outputColumnName;

    // region Typed Fields
    private final char outputValue;
    // endregion Typed Fields

    // region Constructor
    private CharConstantColumn(
            @NotNull final String outputColumnName,
            final char outputValue) {
        this.outputColumnName = outputColumnName;
        this.outputValue = outputValue;
    }

    /**
     * Create a {@link SelectColumn} that assigns a constant {@code char} value.
     *
     * @param outputColumnName the name of the output column
     * @param outputValue the constant value
     * @return a {@link NullSelectColumn} if {@code outputValue} is {@link QueryConstants#NULL_CHAR}, otherwise a new
     *         CharConstantColumn
     */
    public static SelectColumn of(
            @NotNull final String outputColumnName,
            final char outputValue) {
        if (outputValue == QueryConstants.NULL_CHAR) {
            return new NullSelectColumn<>(char.class, null, outputColumnName);
        }
        return new CharConstantColumn(outputColumnName, outputValue);
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
        return new ViewColumnSource<>(char.class, new OutputFormula(), true, true);
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
        return char.class;
    }

    // region getReturnedComponentType
    @Override
    public Class<?> getReturnedComponentType() {
        // char does not have a component type
        return null;
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
        return new CharacterSingleValueSource();
    }

    @Override
    public final WritableColumnSource<?> newFlatDestInstance(final long size) {
        return new CharacterSingleValueSource();
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
        public Character get(final long rowKey) {
            return TypeUtils.box(outputValue);
        }

        @Override
        public Character getPrev(final long rowKey) {
            return get(rowKey);
        }

        // region getTypedMethods
        @Override
        public char getChar(long rowKey) {
            return outputValue;
        }

        @Override
        public char getPrevChar(long rowKey) {
            return getChar(rowKey);
        }
        // endregion getTypedMethods

        @Override
        protected ChunkType getChunkType() {
            return ChunkType.Char;
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
            destination.asWritableCharChunk().fillWithValue(0, destination.size(), outputValue);
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
