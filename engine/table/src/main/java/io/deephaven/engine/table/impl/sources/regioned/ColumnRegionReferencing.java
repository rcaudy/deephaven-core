/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl.sources.regioned;

import io.deephaven.chunk.attributes.Any;
import io.deephaven.chunk.Chunk;
import io.deephaven.chunk.ChunkType;
import io.deephaven.chunk.WritableChunk;
import io.deephaven.engine.rowset.RowSequence;
import io.deephaven.engine.rowset.WritableRowSet;
import io.deephaven.util.annotations.FinalDefault;
import org.jetbrains.annotations.NotNull;

public interface ColumnRegionReferencing<ATTR extends Any, REFERENCED_COLUMN_REGION extends ColumnRegion<ATTR>>
        extends ColumnRegion<ATTR> {

    @NotNull
    REFERENCED_COLUMN_REGION getReferencedRegion();

    @Override
    @FinalDefault
    default ChunkType getChunkType() {
        throw new UnsupportedOperationException(getClass() + " does not know its chunk type");
    }

    interface Converter<ATTR extends Any> {

        /**
         * Converts all the native source values represented by {@code rowSequence} <em>from a single region</em> into
         * the {@code destination} chunk by appending.
         */
        void convertRegion(
                @NotNull WritableChunk<? super ATTR> destination,
                @NotNull Chunk<? extends ATTR> source,
                @NotNull RowSequence rowSequence);

        /**
         * Convert an array of values in the region type to an array of values in boxed native format.
         *
         * @param values the values to convert
         * @return a new array of converted values
         */
        @NotNull
        Object[] convertArray(@NotNull Object[] values);
    }

    class Null<ATTR extends Any, REFERENCED_COLUMN_REGION extends ColumnRegion<ATTR>>
            extends ColumnRegion.Null<ATTR>
            implements ColumnRegionReferencing<ATTR, REFERENCED_COLUMN_REGION> {

        private final REFERENCED_COLUMN_REGION nullReferencedColumnRegion;

        public Null(REFERENCED_COLUMN_REGION nullReferencedColumnRegion) {
            super((nullReferencedColumnRegion.mask()));
            this.nullReferencedColumnRegion = nullReferencedColumnRegion;
        }

        @Override
        @NotNull
        public REFERENCED_COLUMN_REGION getReferencedRegion() {
            return nullReferencedColumnRegion;
        }

        @Override
        public WritableRowSet match(
                final boolean invertMatch,
                final boolean usePrev,
                final boolean caseInsensitive,
                @NotNull final RowSequence rowSequence,
                final Object... sortedKeys) {
            return nullReferencedColumnRegion.match(invertMatch, usePrev, caseInsensitive, rowSequence, sortedKeys);
        }
    }
}
