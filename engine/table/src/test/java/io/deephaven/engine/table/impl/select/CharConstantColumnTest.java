//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl.select;

import io.deephaven.chunk.CharChunk;
import io.deephaven.chunk.WritableCharChunk;
import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.rowset.RowSet;
import io.deephaven.engine.rowset.RowSetFactory;
import io.deephaven.engine.table.ChunkSource;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.WritableColumnSource;
import io.deephaven.engine.testutil.junit4.EngineCleanup;
import io.deephaven.util.QueryConstants;
import org.junit.Rule;
import org.junit.Test;

import java.util.Collections;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

/**
 * Unit tests for {@link CharConstantColumn}.
 * <p>
 * This C-harConstantColumnTest is the source of truth; it is replicated to the other primitive types and to
 * {@link ObjectConstantColumn} (as ObjectConstantColumnTest) by io.deephaven.replicators.ReplicateConstantColumns.
 * Object-specific behavior that cannot be replicated from {@code char} (type inference, component types, null typing)
 * lives in the hand-written ObjectConstantColumnTypeInferenceTest.
 * <p>
 * (C-har is deliberately spelled that way to prevent Replicate from altering this comment.)
 */
public class CharConstantColumnTest {

    @Rule
    public final EngineCleanup cleanup = new EngineCleanup();

    private static final String COLUMN_NAME = "TestColumn";

    // The maximum legal row key; a ConstantColumn must return its value for every row key, not just small ones.
    private static final long MAX_ROW_KEY = Long.MAX_VALUE - 1;

    // region TestValue
    private static final char TEST_VALUE = 'X';
    // endregion TestValue

    @Test
    public void testCharConstantColumnContract() {
        final SelectColumn column = CharConstantColumn.of(COLUMN_NAME, TEST_VALUE);
        assertThat(column).isInstanceOf(CharConstantColumn.class);

        assertThat(column.getName()).isEqualTo(COLUMN_NAME);
        assertThat(column.getReturnedType()).isEqualTo(char.class);
        assertThat(column.getReturnedComponentType()).isNull();
        assertThat(column.getColumns()).isEqualTo(Collections.emptyList());
        assertThat(column.getColumnArrays()).isEqualTo(Collections.emptyList());
        assertThat(column.isStateless()).isTrue();
        assertThat(column.isRetain()).isFalse();

        // A ConstantColumn takes no inputs, so init returns no dependencies.
        assertThat(column.initInputs(RowSetFactory.empty().toTracking(), Collections.emptyMap())).isEmpty();
        assertThat(column.initDef(Collections.emptyMap())).isEmpty();

        // copy() returns the same stateless instance.
        assertThat(column.copy()).isSameAs(column);

        // getMatchPair() is unsupported for a ConstantColumn.
        assertThatThrownBy(column::getMatchPair).isInstanceOf(UnsupportedOperationException.class);

        // The data view and the lazy view expose a source of the correct type and (absent) component type.
        final ColumnSource<?> dataView = column.getDataView();
        assertThat(dataView.getType()).isEqualTo(char.class);
        assertThat(dataView.getComponentType()).isNull();
        final ColumnSource<?> lazyView = column.getLazyView();
        assertThat(lazyView.getType()).isEqualTo(char.class);
        assertThat(lazyView.getComponentType()).isNull();

        // The writable destination instances carry the correct type and component type as well.
        final WritableColumnSource<?> destInstance = column.newDestInstance(10);
        assertThat(destInstance.getType()).isEqualTo(char.class);
        assertThat(destInstance.getComponentType()).isNull();
        final WritableColumnSource<?> flatDestInstance = column.newFlatDestInstance(10);
        assertThat(flatDestInstance.getType()).isEqualTo(char.class);
        assertThat(flatDestInstance.getComponentType()).isNull();
    }

    @Test
    public void testCharConstantColumnValues() {
        final SelectColumn column = CharConstantColumn.of(COLUMN_NAME, TEST_VALUE);
        // The data view and the lazy view must behave identically.
        assertConstantView(column.getDataView(), TEST_VALUE, TEST_VALUE);
        assertConstantView(column.getLazyView(), TEST_VALUE, TEST_VALUE);
    }

    // region nullValue
    @Test
    public void testCharConstantColumnNullValueYieldsNullSelectColumn() {
        // The null sentinel must degrade to a NullSelectColumn rather than a CharConstantColumn.
        final SelectColumn column = CharConstantColumn.of(COLUMN_NAME, QueryConstants.NULL_CHAR);
        assertThat(column).isInstanceOf(NullSelectColumn.class);
        assertThat(column.getName()).isEqualTo(COLUMN_NAME);
        assertThat(column.getReturnedType()).isEqualTo(char.class);
        assertThat(column.getReturnedComponentType()).isNull();

        // Both views of the degraded column must yield the null sentinel (boxed null) for every row key.
        assertConstantView(column.getDataView(), QueryConstants.NULL_CHAR, null);
        assertConstantView(column.getLazyView(), QueryConstants.NULL_CHAR, null);
    }
    // endregion nullValue

    /**
     * Assert that {@code view} returns the same constant for every row key and every access path: the boxed and typed
     * element accessors (current and previous) at both the first and the maximum row key, and both the fill-chunk and
     * get-chunk paths (current and previous).
     *
     * @param view the column source under test
     * @param expected the expected typed value
     * @param expectedBoxed the expected boxed value ({@code null} for the null-sentinel case)
     */
    private static void assertConstantView(
            final ColumnSource<?> view,
            final char expected,
            final Character expectedBoxed) {
        // A constant column's value never changes, so its view must report itself as immutable.
        assertThat(view.isImmutable()).isTrue();

        // region getTypedMethods
        assertThat(view.getChar(0)).isEqualTo(expected);
        assertThat(view.getChar(MAX_ROW_KEY)).isEqualTo(expected);
        assertThat(view.getPrevChar(0)).isEqualTo(expected);
        assertThat(view.getPrevChar(MAX_ROW_KEY)).isEqualTo(expected);
        // endregion getTypedMethods

        assertThat(view.get(0)).isEqualTo(expectedBoxed);
        assertThat(view.get(MAX_ROW_KEY)).isEqualTo(expectedBoxed);
        assertThat(view.getPrev(0)).isEqualTo(expectedBoxed);
        assertThat(view.getPrev(MAX_ROW_KEY)).isEqualTo(expectedBoxed);

        final int size = 8;
        try (final RowSet rowSet = RowSetFactory.flat(size)) {
            // fillChunk() and fillPrevChunk() fill every requested position with the constant value.
            try (final ChunkSource.FillContext fillContext = view.makeFillContext(size);
                    final WritableCharChunk<Values> chunk = WritableCharChunk.makeWritableChunk(size)) {
                view.fillChunk(fillContext, chunk, rowSet);
                assertChunkAllEqual(chunk, size, expected);
                view.fillPrevChunk(fillContext, chunk, rowSet);
                assertChunkAllEqual(chunk, size, expected);
            }
            // getChunk() and getPrevChunk() return the constant value at every position.
            try (final ChunkSource.GetContext getContext = view.makeGetContext(size)) {
                assertChunkAllEqual(view.getChunk(getContext, rowSet).asCharChunk(), size, expected);
                assertChunkAllEqual(view.getPrevChunk(getContext, rowSet).asCharChunk(), size, expected);
            }
        }
    }

    private static void assertChunkAllEqual(
            final CharChunk<? extends Values> chunk,
            final int size,
            final char expected) {
        assertThat(chunk.size()).isEqualTo(size);
        for (int ii = 0; ii < size; ++ii) {
            assertThat(chunk.get(ii)).isEqualTo(expected);
        }
    }
}
