/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.parquet.table.metadata;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import io.deephaven.annotations.BuildableStyle;
import io.deephaven.api.ColumnName;
import io.deephaven.api.SortColumn;
import org.immutables.value.Value;
import org.jetbrains.annotations.NotNull;

@Value.Immutable
@BuildableStyle
@JsonSerialize(as = ImmutableSortColumnInfo.class)
@JsonDeserialize(as = ImmutableSortColumnInfo.class)
@JsonInclude(JsonInclude.Include.NON_EMPTY)
public abstract class SortColumnInfo {
    public enum SortDirection {
        Ascending, Descending
    }

    public abstract String columnName();

    public abstract SortDirection sortDirection();

    // @Value.Check
    final void checkColumnName() {
        if (columnName().isEmpty()) {
            throw new IllegalArgumentException("Empty column name");
        }
    }

    public final SortColumn toSortColumn() {
        ColumnName cname = ColumnName.of(columnName());
        return sortDirection() == SortDirection.Ascending ? SortColumn.asc(cname) : SortColumn.desc(cname);
    }

    public static SortColumnInfo of(@NotNull final SortColumn sortingColumn) {
        return builder()
                .columnName(sortingColumn.column().name())
                .sortDirection(sortingColumn.order() == SortColumn.Order.ASCENDING
                        ? SortColumnInfo.SortDirection.Ascending
                        : SortColumnInfo.SortDirection.Descending)
                .build();
    }

    public static Builder builder() {
        return ImmutableSortColumnInfo.builder();
    }

    public interface Builder {

        Builder columnName(String columnName);

        Builder sortDirection(SortDirection sortDirection);

        SortColumnInfo build();
    }
}
