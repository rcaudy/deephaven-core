//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Edit TestCharacterImmutable2DArraySource and run "./gradlew replicateSourceAndChunkTests" to regenerate
//
// @formatter:off
package io.deephaven.engine.table.impl.sources;

import io.deephaven.chunk.WritableFloatChunk;
import io.deephaven.engine.rowset.RowSetFactory;
import io.deephaven.engine.table.ChunkSink;
import io.deephaven.engine.table.impl.sources.immutable.Immutable2DFloatArraySource;
import org.jetbrains.annotations.NotNull;

public class TestFloatImmutable2DArraySource extends AbstractFloatColumnSourceTest {
    @Override
    int getSourceSize() {
        return 1 << 16;
    }

    @NotNull
    @Override
    Immutable2DFloatArraySource makeTestSource() {
        final int capacity = getSourceSize();
        final Immutable2DFloatArraySource flatFloatArraySource = new Immutable2DFloatArraySource(12);
        flatFloatArraySource.ensureCapacity(capacity);
        try (final ChunkSink.FillFromContext ffc = flatFloatArraySource.makeFillFromContext(capacity);
                final WritableFloatChunk nullChunk = WritableFloatChunk.makeWritableChunk(capacity)) {
            nullChunk.fillWithNullValue(0, capacity);
            flatFloatArraySource.fillFromChunk(ffc, nullChunk, RowSetFactory.flat(capacity));
        }
        return flatFloatArraySource;
    }
}
