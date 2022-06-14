/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.engine.table.impl;

import io.deephaven.engine.table.Table;
import io.deephaven.engine.liveness.LivenessScopeStack;
import io.deephaven.chunk.util.pools.ChunkPoolReleaseTracking;
import io.deephaven.util.SafeCloseable;

import java.util.Random;

import static io.deephaven.engine.table.impl.TstUtils.getTable;
import static io.deephaven.engine.table.impl.TstUtils.initColumnInfos;

public class TestTableValidator extends RefreshingTableTestCase {
    public void testValidator() {
        ChunkPoolReleaseTracking.enableStrict();

        try (final SafeCloseable sc = LivenessScopeStack.open()) {

            final Random random = new Random(0);
            final TstUtils.ColumnInfo[] columnInfo;
            final int size = 50;
            final QueryTable queryTable = getTable(size, random,
                    columnInfo = initColumnInfos(new String[] {"Sym", "intCol", "doubleCol"},
                            new TstUtils.SetGenerator<>("a", "b", "c", "d", "e"),
                            new TstUtils.IntGenerator(10, 100),
                            new TstUtils.SetGenerator<>(10.1, 20.1, 30.1)));

            final EvalNugget[] en = new EvalNugget[] {
                    new EvalNugget() {
                        public Table e() {
                            return queryTable;
                        }
                    },
            };

            for (int i = 0; i < 10; i++) {
                simulateShiftAwareStep(size, random, queryTable, columnInfo, en);
            }
        }

        ChunkPoolReleaseTracking.checkAndDisable();
    }
}
