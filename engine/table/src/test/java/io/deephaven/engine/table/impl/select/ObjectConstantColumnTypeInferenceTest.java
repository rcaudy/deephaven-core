//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl.select;

import io.deephaven.engine.testutil.junit4.EngineCleanup;
import io.deephaven.vector.IntVector;
import io.deephaven.vector.IntVectorDirect;
import org.junit.Rule;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

/**
 * Hand-written companion to the generated {@code *ConstantColumnTest} classes (see {@link CharConstantColumnTest}),
 * covering the {@link ObjectConstantColumn} behavior that cannot be replicated from the {@code char} source of truth:
 * type and component-type inference, explicit widening, and null typing. The uniform contract/value behavior for
 * {@code Object} is covered by the generated {@code ObjectConstantColumnTest}.
 */
public class ObjectConstantColumnTypeInferenceTest {

    @Rule
    public final EngineCleanup cleanup = new EngineCleanup();

    private static final String COLUMN_NAME = "TestColumn";

    // region type inference
    @Test
    public void testObjectConstantColumnInferType() {
        // Type is inferred from the value's runtime class.
        final String value = "TestValue";
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, value);

        assertThat(column.getReturnedType()).isEqualTo(String.class);
        assertThat(column.getReturnedComponentType()).isNull();
        assertThat(column.getDataView().getType()).isEqualTo(String.class);
    }

    @Test
    public void testObjectConstantColumnExplicitType() {
        // An explicit type widens beyond the value's runtime class.
        final String value = "TestValue";
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, value, CharSequence.class);

        assertThat(column.getReturnedType()).isEqualTo(CharSequence.class);
        assertThat(column.getReturnedComponentType()).isNull();
        assertThat(column.copy().getReturnedType()).isEqualTo(CharSequence.class);
        assertThat(column.getDataView().getType()).isEqualTo(CharSequence.class);
    }

    @Test
    public void testObjectConstantColumnExplicitComponentType() {
        // Explicit array type and component type are preserved, including through copy().
        final String[] value = {"a", "b", "c"};
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, value, String[].class, String.class);

        assertThat(column.getReturnedType()).isEqualTo(String[].class);
        assertThat(column.getReturnedComponentType()).isEqualTo(String.class);
        assertThat(column.copy().getReturnedType()).isEqualTo(String[].class);
        assertThat(column.copy().getReturnedComponentType()).isEqualTo(String.class);
    }

    @Test
    public void testObjectConstantColumnInferArrayComponentType() {
        // A bare array value infers its component type from the array class.
        final String[] value = {"a", "b", "c"};
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, value);

        assertThat(column.getReturnedType()).isEqualTo(String[].class);
        assertThat(column.getReturnedComponentType()).isEqualTo(String.class);
    }

    @Test
    public void testObjectConstantColumnInferVectorComponentType() {
        // A Vector value infers its component type from Vector.getComponentType().
        final IntVector value = new IntVectorDirect(1, 2, 3);
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, value);

        assertThat(column.getReturnedType()).isEqualTo(IntVectorDirect.class);
        assertThat(column.getReturnedComponentType()).isEqualTo(int.class);
    }
    // endregion type inference

    // region null typing
    @Test
    public void testObjectConstantColumnNullWithExplicitType() {
        // A null value with an explicit type degrades to a NullSelectColumn of that type.
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, null, String.class);

        assertThat(column).isInstanceOf(NullSelectColumn.class);
        assertThat(column.getName()).isEqualTo(COLUMN_NAME);
        assertThat(column.getReturnedType()).isEqualTo(String.class);
        assertThat(column.getReturnedComponentType()).isNull();
        assertThat(column.getDataView().getType()).isEqualTo(String.class);
    }

    @Test
    public void testObjectConstantColumnNullWithComponentType() {
        // A null value retains an explicit component type on the resulting NullSelectColumn.
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, null, String[].class, String.class);

        assertThat(column).isInstanceOf(NullSelectColumn.class);
        assertThat(column.getReturnedType()).isEqualTo(String[].class);
        assertThat(column.getReturnedComponentType()).isEqualTo(String.class);
    }

    @Test
    public void testObjectConstantColumnNullInferType() {
        // A null value with no explicit type degrades to a NullSelectColumn typed as Object.
        final SelectColumn column = ObjectConstantColumn.of(COLUMN_NAME, null);

        assertThat(column).isInstanceOf(NullSelectColumn.class);
        assertThat(column.getReturnedType()).isEqualTo(Object.class);
        assertThat(column.getReturnedComponentType()).isNull();
    }
    // endregion null typing
}
