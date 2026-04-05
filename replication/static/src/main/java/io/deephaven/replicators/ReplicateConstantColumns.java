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

    public static void main(String[] args) throws IOException {
        // Replicate to all primitive types except boolean and char (char is the source, boolean uses Object)
        ReplicatePrimitiveCode.charToAllButBoolean(TASK, CHAR_CONSTANT_COLUMN_PATH);

        // Replicate to Object
        fixupObjectConstantColumn(ReplicatePrimitiveCode.charToObject(TASK, CHAR_CONSTANT_COLUMN_PATH));
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
                // Remove unused TypeUtils import and add Vector import
                "import io.deephaven.util.type.TypeUtils;",
                "import io.deephaven.vector.Vector;");

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
                "            final T outputValue,",
                "            @NotNull final Class<T> type,",
                "            final Class<?> componentType) {",
                "        this.outputColumnName = outputColumnName;",
                "        this.outputValue = outputValue;",
                "        this.type = type;",
                "        this.componentType = componentType;",
                "    }",
                "",
                "    /**",
                "     * Create an ObjectConstantColumn with explicit type and component type.",
                "     *",
                "     * @param outputColumnName the name of the output column",
                "     * @param outputValue the constant value",
                "     * @param type the type of the value",
                "     * @param componentType the component type (for array/vector types), or null",
                "     * @return the new ObjectConstantColumn",
                "     */",
                "    public static <T> ObjectConstantColumn<T> of(",
                "            @NotNull final String outputColumnName,",
                "            final T outputValue,",
                "            @NotNull final Class<T> type,",
                "            final Class<?> componentType) {",
                "        return new ObjectConstantColumn<>(outputColumnName, outputValue, type, componentType);",
                "    }",
                "",
                "    /**",
                "     * Create an ObjectConstantColumn with explicit type and null component type.",
                "     *",
                "     * @param outputColumnName the name of the output column",
                "     * @param outputValue the constant value",
                "     * @param type the type of the value",
                "     * @return the new ObjectConstantColumn",
                "     */",
                "    public static <T> ObjectConstantColumn<T> of(",
                "            @NotNull final String outputColumnName,",
                "            final T outputValue,",
                "            @NotNull final Class<T> type) {",
                "        return new ObjectConstantColumn<>(outputColumnName, outputValue, type, null);",
                "    }",
                "",
                "    /**",
                "     * Create an ObjectConstantColumn inferring the type and component type from the value.",
                "     * If the value is null, the type will be {@code Object}.",
                "     *",
                "     * @param outputColumnName the name of the output column",
                "     * @param outputValue the constant value",
                "     * @return the new ObjectConstantColumn",
                "     */",
                "    @SuppressWarnings(\"unchecked\")",
                "    public static <T> ObjectConstantColumn<T> of(",
                "            @NotNull final String outputColumnName,",
                "            final T outputValue) {",
                "        if (outputValue == null) {",
                "            return (ObjectConstantColumn<T>) new ObjectConstantColumn<>(",
                "                    outputColumnName, null, Object.class, null);",
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
                "        return new ObjectConstantColumn<>(outputColumnName, outputValue, type, componentType);",
                "    }"));

        FileUtils.writeLines(file, lines);
    }
}
