//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.replicators;

import io.deephaven.replication.ReplicatePrimitiveCode;
import io.deephaven.replication.ReplicationUtils;
import org.apache.commons.io.FileUtils;
import org.jetbrains.annotations.NotNull;

import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.List;

/**
 * Replicator for CharConstantColumn to Object and all primitive types.
 */
public class ReplicateConstantColumns {

    private static final String TASK = "replicateConstantColumns";

    private static final String CHAR_CONSTANT_COLUMN_PATH =
            "engine/table/src/main/java/io/deephaven/engine/table/impl/select/CharConstantColumn.java";

    private static final String CHAR_CONSTANT_COLUMN_TEST_PATH =
            "engine/table/src/test/java/io/deephaven/engine/table/impl/select/CharConstantColumnTest.java";

    public static void main(String[] args) throws IOException {
        // Replicate to all primitive types except boolean and char (char is the source, boolean uses Object)
        ReplicatePrimitiveCode.charToAllButBoolean(TASK, CHAR_CONSTANT_COLUMN_PATH);

        // Replicate to Object
        fixupObjectConstantColumn(ReplicatePrimitiveCode.charToObject(TASK, CHAR_CONSTANT_COLUMN_PATH));

        // Replicate the unit tests to all primitive types except boolean and char, substituting a representative value
        // for each type (the char source's literal does not read naturally for numeric types).
        fixupPrimitiveTestValue(
                ReplicatePrimitiveCode.charToByte(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH),
                "    private static final byte TEST_VALUE = (byte) 42;");
        fixupPrimitiveTestValue(
                ReplicatePrimitiveCode.charToShort(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH, null),
                "    private static final short TEST_VALUE = (short) 12_345;");
        fixupPrimitiveTestValue(
                ReplicatePrimitiveCode.charToInteger(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH, null),
                "    private static final int TEST_VALUE = 1_000_000;");
        fixupPrimitiveTestValue(
                ReplicatePrimitiveCode.charToLong(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH),
                "    private static final long TEST_VALUE = 1_000_000_000_000L;");
        fixupPrimitiveTestValue(
                ReplicatePrimitiveCode.charToFloat(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH, null),
                "    private static final float TEST_VALUE = 3.5f;");
        fixupPrimitiveTestValue(
                ReplicatePrimitiveCode.charToDouble(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH, null),
                "    private static final double TEST_VALUE = 2.718281828459045;");

        // Replicate the unit tests to Object. The Object-specific type-inference and null-typing behavior lives in the
        // hand-written ObjectConstantColumnTypeInferenceTest.
        fixupObjectConstantColumnTest(ReplicatePrimitiveCode.charToObject(TASK, CHAR_CONSTANT_COLUMN_TEST_PATH));
    }

    private static void fixupPrimitiveTestValue(@NotNull final String path, @NotNull final String valueDeclaration)
            throws IOException {
        final File file = new File(path);
        List<String> lines = FileUtils.readLines(file, Charset.defaultCharset());
        lines = ReplicationUtils.replaceRegion(lines, "TestValue", List.of(valueDeclaration));
        FileUtils.writeLines(file, lines);
    }

    private static void fixupObjectConstantColumnTest(@NotNull final String path) throws IOException {
        final File file = new File(path);
        List<String> lines = FileUtils.readLines(file, Charset.defaultCharset());

        // Object chunks carry an extra element-type parameter.
        lines = ReplicationUtils.fixupChunkAttributes(lines, "Object");

        // Object has no primitive typed accessors (getObject/getPrevObject) and no null sentinel constant, so drop the
        // typed-accessor assertions and the null-sentinel test. Object null typing is covered by the hand-written
        // ObjectConstantColumnTypeInferenceTest.
        lines = ReplicationUtils.removeRegion(lines, "getTypedMethods");
        lines = ReplicationUtils.removeRegion(lines, "nullValue");

        // Use a representative Object value; its concrete type is String, not Object.
        lines = ReplicationUtils.replaceRegion(lines, "TestValue", List.of(
                "    private static final String TEST_VALUE = \"TestValue\";"));
        lines = ReplicationUtils.globalReplacements(lines,
                "isEqualTo\\(Object\\.class\\)", "isEqualTo(String.class)");

        // QueryConstants is only referenced by the (now removed) null-sentinel test.
        lines = ReplicationUtils.removeImport(lines,
                "\\s*import\\s+io\\.deephaven\\.util\\.QueryConstants\\s*;");

        FileUtils.writeLines(file, lines);
    }

    private static void fixupObjectConstantColumn(@NotNull final String objectPath) throws IOException {
        final File file = new File(objectPath);
        List<String> lines = FileUtils.readLines(file, Charset.defaultCharset());

        // Fix chunk attributes for Object type
        lines = ReplicationUtils.fixupChunkAttributes(lines, "Object");

        // Remove the getTypedMethods region - Object doesn't have getObject/getPrevObject in Formula
        lines = ReplicationUtils.removeRegion(lines, "getTypedMethods");

        // Object version needs special handling - use simpler line-by-line replacements
        lines = ReplicationUtils.globalReplacements(lines,
                // Make class generic
                "public class ObjectConstantColumn implements SelectColumn",
                "public class ObjectConstantColumn<T> implements SelectColumn",
                // Fix ViewColumnSource
                "new ViewColumnSource<>\\(Object\\.class,",
                "new ViewColumnSource<>(type,",
                // Fix getReturnedType
                "return Object\\.class;",
                "return type;",
                // Fix ObjectSingleValueSource - the replicated version has no args
                "new ObjectSingleValueSource\\(\\)",
                "new ObjectSingleValueSource<>(type, componentType)",
                // Remove TypeUtils.box for Object
                "TypeUtils\\.box\\(outputValue\\)",
                "outputValue",
                // Replace unused QueryConstants import with Vector import
                "import io.deephaven.util.QueryConstants;",
                "import io.deephaven.vector.Vector;");

        // Remove unused TypeUtils import
        lines = ReplicationUtils.removeImport(lines,
                "\\s*import\\s+io\\.deephaven\\.util\\.type\\.TypeUtils\\s*;");

        // Replace Typed Fields region with generic typed fields
        lines = ReplicationUtils.replaceRegion(lines, "Typed Fields", List.of(
                "    private final T outputValue;",
                "    private final Class<T> type;",
                "    private final Class<?> componentType;"));

        // Replace getReturnedComponentType to return componentType
        lines = ReplicationUtils.replaceRegion(lines, "getReturnedComponentType", List.of(
                "    @Override",
                "    public Class<?> getReturnedComponentType() {",
                "        return componentType;",
                "    }"));

        // Replace Constructor region with private constructor and factory methods
        lines = ReplicationUtils.replaceRegion(lines, "Constructor", List.of(
                "    private ObjectConstantColumn(",
                "            @NotNull final String outputColumnName,",
                "            @NotNull final T outputValue,",
                "            @NotNull final Class<T> type,",
                "            final Class<?> componentType) {",
                "        this.outputColumnName = outputColumnName;",
                "        this.outputValue = outputValue;",
                "        this.type = type;",
                "        this.componentType = componentType;",
                "    }",
                "",
                "    /**",
                "     * Create a {@link SelectColumn} that assigns a constant {@code Object} value with explicit type and",
                "     * component type.",
                "     *",
                "     * @param outputColumnName the name of the output column",
                "     * @param outputValue the constant value",
                "     * @param type the type of the value",
                "     * @param componentType the component type (for array/vector types), or null",
                "     * @return a {@link NullSelectColumn} if {@code outputValue} is null, otherwise a new",
                "     *         ObjectConstantColumn",
                "     */",
                "    public static <T> SelectColumn of(",
                "            @NotNull final String outputColumnName,",
                "            final T outputValue,",
                "            @NotNull final Class<T> type,",
                "            final Class<?> componentType) {",
                "        if (outputValue == null) {",
                "            return new NullSelectColumn<>(type, componentType, outputColumnName);",
                "        }",
                "        return new ObjectConstantColumn<>(outputColumnName, outputValue, type, componentType);",
                "    }",
                "",
                "    /**",
                "     * Create a {@link SelectColumn} that assigns a constant {@code Object} value with explicit type and",
                "     * null component type.",
                "     *",
                "     * @param outputColumnName the name of the output column",
                "     * @param outputValue the constant value",
                "     * @param type the type of the value",
                "     * @return a {@link NullSelectColumn} if {@code outputValue} is null, otherwise a new",
                "     *         ObjectConstantColumn",
                "     */",
                "    public static <T> SelectColumn of(",
                "            @NotNull final String outputColumnName,",
                "            final T outputValue,",
                "            @NotNull final Class<T> type) {",
                "        return of(outputColumnName, outputValue, type, null);",
                "    }",
                "",
                "    /**",
                "     * Create a {@link SelectColumn} that assigns a constant {@code Object} value, inferring the type and",
                "     * component type from the value. If the value is null, the type will be {@code Object}.",
                "     *",
                "     * @param outputColumnName the name of the output column",
                "     * @param outputValue the constant value",
                "     * @return a {@link NullSelectColumn} if {@code outputValue} is null, otherwise a new",
                "     *         ObjectConstantColumn",
                "     */",
                "    @SuppressWarnings(\"unchecked\")",
                "    public static <T> SelectColumn of(",
                "            @NotNull final String outputColumnName,",
                "            final T outputValue) {",
                "        if (outputValue == null) {",
                "            return of(outputColumnName, null, (Class<T>) (Class<?>) Object.class, null);",
                "        }",
                "        final Class<T> type = (Class<T>) outputValue.getClass();",
                "        final Class<?> componentType;",
                "        if (type.isArray()) {",
                "            componentType = type.getComponentType();",
                "        } else if (outputValue instanceof Vector) {",
                "            componentType = ((Vector<?>) outputValue).getComponentType();",
                "        } else {",
                "            componentType = null;",
                "        }",
                "        return of(outputColumnName, outputValue, type, componentType);",
                "    }"));

        FileUtils.writeLines(file, lines);
    }
}
