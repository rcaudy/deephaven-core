package io.deephaven.engine.table.impl.sources.regioned.instructions;

import io.deephaven.annotations.BuildableStyle;
import io.deephaven.engine.table.impl.SourceTable;
import org.immutables.value.Value;
import org.jetbrains.annotations.NotNull;

import java.util.Map;

/**
 * A contextual class to control the underlying behaviors of {@link SourceTable source tables}. This can be used to
 * control the behaviors of different region types, for example Parquet and Deephaven regions. It can also be used to
 * control behaviors of the source table itself.
 */

@Value.Immutable
@BuildableStyle
public abstract class SourceTableInstructions {
    public static final SourceTableInstructions EMPTY = builder().build();

    @Value.Default
    public boolean groupingDisabled() {
        return false;
    }

    abstract Map<String, SourceTableColumnInstructions> columnInstructions();

    public static Builder builder() {
        return ImmutableSourceTableInstructions.builder();
    }

    public final SourceTableColumnInstructions getInstructions(@NotNull final String column) {
        return columnInstructions().getOrDefault(column, SourceTableColumnInstructions.DEFAULT);
    }

    public interface Builder {
        Builder groupingDisabled(boolean disabled);

        Builder putColumnInstructions(@NotNull final String colName,
                @NotNull final SourceTableColumnInstructions instructions);

        SourceTableInstructions build();
    }
}
