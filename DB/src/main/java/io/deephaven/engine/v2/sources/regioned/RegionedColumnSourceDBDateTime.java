package io.deephaven.engine.v2.sources.regioned;

import io.deephaven.engine.tables.utils.DBDateTime;
import io.deephaven.engine.tables.utils.DBTimeUtils;
import io.deephaven.engine.v2.sources.ColumnSourceGetDefaults;
import io.deephaven.engine.v2.sources.chunk.*;
import io.deephaven.engine.structures.RowSequence;

import static io.deephaven.engine.v2.utils.ReadOnlyIndex.NULL_KEY;

/**
 * Regioned column source implementation for columns of {@link DBDateTime}s.
 */
final class RegionedColumnSourceDBDateTime
        extends
        RegionedColumnSourceReferencing<DBDateTime, Attributes.Values, Long, ColumnRegionLong<Attributes.Values>>
        implements ColumnSourceGetDefaults.ForObject<DBDateTime> {

    public RegionedColumnSourceDBDateTime() {
        super(ColumnRegionLong.createNull(PARAMETERS.regionMask), DBDateTime.class,
                RegionedColumnSourceLong.NativeType.AsValues::new);
    }

    @Override
    public void convertRegion(WritableChunk<? super Attributes.Values> destination,
            Chunk<? extends Attributes.Values> source, RowSequence rowSequence) {
        WritableObjectChunk<DBDateTime, ? super Attributes.Values> objectChunk = destination.asWritableObjectChunk();
        LongChunk<? extends Attributes.Values> longChunk = source.asLongChunk();

        final int size = objectChunk.size();
        final int length = longChunk.size();

        for (int i = 0; i < length; ++i) {
            objectChunk.set(size + i, DBTimeUtils.nanosToTime(longChunk.get(i)));
        }
        objectChunk.setSize(size + length);
    }

    @Override
    public DBDateTime get(long elementIndex) {
        return elementIndex == NULL_KEY ? null
                : DBTimeUtils.nanosToTime(lookupRegion(elementIndex).getReferencedRegion().getLong(elementIndex));
    }
}
