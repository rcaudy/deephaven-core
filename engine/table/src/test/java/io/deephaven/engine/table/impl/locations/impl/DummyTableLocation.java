/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.locations.impl;

import io.deephaven.api.SortColumn;
import io.deephaven.engine.table.Table;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import io.deephaven.engine.table.impl.locations.TableKey;
import io.deephaven.engine.table.impl.locations.TableLocationKey;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.List;

public final class DummyTableLocation extends AbstractTableLocation {

    public DummyTableLocation(
            @NotNull final TableKey tableKey,
            @NotNull final TableLocationKey tableLocationKey) {
        super(tableKey, tableLocationKey, false);
    }

    @Override
    public void refresh() {

    }

    @Override
    public @NotNull List<SortColumn> getSortedColumns() {
        // TODO NATE NOCOMMIT?
        return List.of();
    }

    @Override
    public boolean hasDataIndexFor(@NotNull String... columns) {
        return false;
    }

    @Override
    protected @Nullable Table getDataIndexImpl(@NotNull String... columns) {
        return null;
    }

    @NotNull
    @Override
    protected ColumnLocation makeColumnLocation(@NotNull String name) {
        return new DummyColumnLocation(this, name);
    }
}
