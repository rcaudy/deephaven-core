//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.table.impl.sources;

import io.deephaven.base.verify.Assert;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.impl.MutableColumnSourceGetDefaults;
import io.deephaven.vector.ObjectVector;

public class UngroupedObjectVectorColumnSource<T> extends UngroupedColumnSource<T>
        implements MutableColumnSourceGetDefaults.ForObject<T> {
    private final ColumnSource<ObjectVector<T>> innerSource;
    private final boolean isUngroupable;

    @Override
    public Class<?> getComponentType() {
        return innerSource.getComponentType().getComponentType();
    }

    public UngroupedObjectVectorColumnSource(ColumnSource<ObjectVector<T>> innerSource) {
        // noinspection unchecked
        super((Class<T>) innerSource.getComponentType());
        this.innerSource = innerSource;
        this.isUngroupable = UngroupableColumnSource.isUngroupable(innerSource);
    }

    @Override
    public T get(long rowKey) {
        if (rowKey < 0) {
            return null;
        }
        long segment = rowKey >> base;
        long offset = rowKey & ((1 << base) - 1);
        if (isUngroupable) {
            // noinspection unchecked
            return (T) ((UngroupableColumnSource) innerSource).getUngrouped(segment, (int) offset);
        } else {
            final ObjectVector<T> vector = innerSource.get(segment);
            return vector == null ? null : vector.get((int) offset);
        }
    }

    @Override
    public T getPrev(long rowKey) {
        if (rowKey < 0) {
            return null;
        }
        long segment = rowKey >> getPrevBase();
        long offset = rowKey & ((1 << getPrevBase()) - 1);

        if (isUngroupable) {
            // noinspection unchecked
            return (T) ((UngroupableColumnSource) innerSource).getUngroupedPrev(segment, (int) offset);
        } else {
            Assert.neqNull(innerSource, "innerSource");
            final ObjectVector<T> prevArray = innerSource.getPrev(segment);
            return prevArray == null ? null : prevArray.get((int) offset);
        }
    }

    @Override
    public Boolean getBoolean(long rowKey) {
        return (Boolean) get(rowKey);
    }

    @Override
    public Boolean getPrevBoolean(long rowKey) {
        return (Boolean) getPrev(rowKey);
    }

    @Override
    public boolean isImmutable() {
        return innerSource.isImmutable();
    }
}
