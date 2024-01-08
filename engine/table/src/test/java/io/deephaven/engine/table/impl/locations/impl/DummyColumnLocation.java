/**
 * Copyright (c) 2016-2023 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.locations.impl;

import io.deephaven.chunk.attributes.Values;
import io.deephaven.engine.table.ColumnDefinition;
import io.deephaven.engine.table.impl.locations.ColumnLocation;
import io.deephaven.engine.table.impl.locations.TableLocation;
import io.deephaven.engine.table.impl.sources.regioned.*;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class DummyColumnLocation implements ColumnLocation {
    private final DummyTableLocation dummyTableLocation;
    private final @NotNull String name;

    public DummyColumnLocation(DummyTableLocation dummyTableLocation, @NotNull String name) {
        this.dummyTableLocation = dummyTableLocation;
        this.name = name;
    }

    @NotNull
    @Override
    public TableLocation getTableLocation() {
        return dummyTableLocation;
    }

    @NotNull
    @Override
    public String getName() {
        return name;
    }

    @Override
    public boolean exists() {
        throw new UnsupportedOperationException();
    }

    @Nullable
    @Override
    public <METADATA_TYPE> METADATA_TYPE getMetadata(@NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionChar<Values> makeColumnRegionChar(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionByte<Values> makeColumnRegionByte(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionShort<Values> makeColumnRegionShort(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionInt<Values> makeColumnRegionInt(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionLong<Values> makeColumnRegionLong(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionFloat<Values> makeColumnRegionFloat(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ColumnRegionDouble<Values> makeColumnRegionDouble(
            @NotNull ColumnDefinition<?> columnDefinition) {
        throw new UnsupportedOperationException();
    }

    @Override
    public <TYPE> ColumnRegionObject<TYPE, Values> makeColumnRegionObject(
            @NotNull ColumnDefinition<TYPE> columnDefinition) {
        throw new UnsupportedOperationException();
    }

}
