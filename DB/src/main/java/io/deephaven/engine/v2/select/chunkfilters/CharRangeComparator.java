package io.deephaven.engine.v2.select.chunkfilters;

import io.deephaven.engine.util.DhCharComparisons;
import io.deephaven.engine.v2.select.ChunkFilter;
import io.deephaven.engine.v2.sources.chunk.*;
import io.deephaven.engine.v2.sources.chunk.Attributes.OrderedRowKeys;
import io.deephaven.engine.v2.sources.chunk.Attributes.Values;

public class CharRangeComparator {
    private CharRangeComparator() {} // static use only

    private abstract static class CharCharFilter implements ChunkFilter.CharChunkFilter {
        final char lower;
        final char upper;

        CharCharFilter(char lower, char upper) {
            this.lower = lower;
            this.upper = upper;
        }

        abstract public void filter(CharChunk<? extends Values> values, LongChunk<OrderedRowKeys> keys, WritableLongChunk<OrderedRowKeys> results);
    }

    static class CharCharInclusiveInclusiveFilter extends CharCharFilter {
        private CharCharInclusiveInclusiveFilter(char lower, char upper) {
            super(lower, upper);
        }

        public void filter(CharChunk<? extends Values> values, LongChunk<OrderedRowKeys> keys, WritableLongChunk<OrderedRowKeys> results) {
            results.setSize(0);
            for (int ii = 0; ii < values.size(); ++ii) {
                final char value = values.get(ii);
                if (DhCharComparisons.geq(value, lower) && DhCharComparisons.leq(value, upper)) {
                    results.add(keys.get(ii));
                }
            }
        }
    }

    static class CharCharInclusiveExclusiveFilter extends CharCharFilter {
        private CharCharInclusiveExclusiveFilter(char lower, char upper) {
            super(lower, upper);
        }

        public void filter(CharChunk<? extends Values> values, LongChunk<OrderedRowKeys> keys, WritableLongChunk<OrderedRowKeys> results) {
            results.setSize(0);
            for (int ii = 0; ii < values.size(); ++ii) {
                final char value = values.get(ii);
                if (DhCharComparisons.geq(value, lower) && DhCharComparisons.lt(value, upper)) {
                    results.add(keys.get(ii));
                }
            }
        }
    }

    static class CharCharExclusiveInclusiveFilter extends CharCharFilter {
        private CharCharExclusiveInclusiveFilter(char lower, char upper) {
            super(lower, upper);
        }

        public void filter(CharChunk<? extends Values> values, LongChunk<OrderedRowKeys> keys, WritableLongChunk<Attributes.OrderedRowKeys> results) {
            results.setSize(0);
            for (int ii = 0; ii < values.size(); ++ii) {
                final char value = values.get(ii);
                if (DhCharComparisons.gt(value, lower) && DhCharComparisons.leq(value, upper)) {
                    results.add(keys.get(ii));
                }
            }
        }
    }

    static class CharCharExclusiveExclusiveFilter extends CharCharFilter {
        private CharCharExclusiveExclusiveFilter(char lower, char upper) {
            super(lower, upper);
        }

        public void filter(CharChunk<? extends Values> values, LongChunk<OrderedRowKeys> keys, WritableLongChunk<OrderedRowKeys> results) {
            results.setSize(0);
            for (int ii = 0; ii < values.size(); ++ii) {
                final char value = values.get(ii);
                if (DhCharComparisons.gt(value, lower) && DhCharComparisons.lt(value, upper)) {
                    results.add(keys.get(ii));
                }
            }
        }
    }

    public static ChunkFilter.CharChunkFilter makeCharFilter(char lower, char upper, boolean lowerInclusive, boolean upperInclusive) {
        if (lowerInclusive) {
            if (upperInclusive) {
                return new CharCharInclusiveInclusiveFilter(lower, upper);
            } else {
                return new CharCharInclusiveExclusiveFilter(lower, upper);
            }
        } else {
            if (upperInclusive) {
                return new CharCharExclusiveInclusiveFilter(lower, upper);
            } else {
                return new CharCharExclusiveExclusiveFilter(lower, upper);
            }
        }
    }
}
