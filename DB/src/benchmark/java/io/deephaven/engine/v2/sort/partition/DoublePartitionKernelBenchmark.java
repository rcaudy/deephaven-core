/* ---------------------------------------------------------------------------------------------------------------------
 * AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY - for any changes edit CharPartitionKernelBenchmark and regenerate
 * ------------------------------------------------------------------------------------------------------------------ */
package io.deephaven.engine.v2.sort.partition;

import io.deephaven.engine.util.tuples.generated.DoubleLongTuple;
import io.deephaven.engine.v2.sort.timsort.BaseTestDoubleTimSortKernel;
import io.deephaven.engine.v2.sort.timsort.TestTimSortKernel;
import io.deephaven.engine.v2.utils.RowSet;
import io.deephaven.engine.v2.utils.RowSetBuilderSequential;
import io.deephaven.engine.v2.utils.RowSetFactoryImpl;
import org.openjdk.jmh.annotations.*;

import java.util.List;
import java.util.Random;
import java.util.concurrent.TimeUnit;

@State(Scope.Thread)
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
@Warmup(iterations = 1, time = 1)
@Measurement(iterations = 5, time = 1)
@Fork(1)
public class DoublePartitionKernelBenchmark {
    @Param({"32"})
    private int chunkSize;

    @Param({"128"})
    private int dataSize;

    @Param({"random", "runs", "ascending", "descending"})
    private String runType;

    @Param({"true", "false"})
    private boolean preserveEquality;

    @Param({"sqrt", "2", "8", "1024"})
    private String numPartitions;

    private Runnable doPartition;

    @TearDown(Level.Trial)
    public void finishTrial() {
    }

    @Setup(Level.Iteration)
    public void setupIteration() {
        System.out.println("Size = " + chunkSize);

        final TestTimSortKernel.GenerateTupleList<DoubleLongTuple> generate;
        switch (runType) {
            case "random":
                generate = BaseTestDoubleTimSortKernel::generateDoubleRandom;
                break;
            case "runs":
                generate = BaseTestDoubleTimSortKernel::generateDoubleRuns;
                break;
            case "ascending":
                generate = BaseTestDoubleTimSortKernel::generateAscendingDoubleRuns;
                break;
            case "descending":
                generate = BaseTestDoubleTimSortKernel::generateDescendingDoubleRuns;
                break;
            default:
                throw new IllegalArgumentException("Bad runType: " + runType);
        }

        // i would prefer to update the seed here
        final Random random = new Random(0);
        final List<DoubleLongTuple> stuffToSort = generate.generate(random, dataSize);

        final RowSetBuilderSequential sequentialBuilder = RowSetFactoryImpl.INSTANCE.getSequentialBuilder();
        stuffToSort.stream().mapToLong(DoubleLongTuple::getSecondElement).forEach(sequentialBuilder::appendKey);
        final RowSet rowSet = sequentialBuilder.build();
        final int numPartitionsValue;
        if ("sqrt".equals(numPartitions)) {
            numPartitionsValue = (int) Math.sqrt(stuffToSort.size());
        } else {
            numPartitionsValue = Integer.parseInt(numPartitions);
        }
        final BaseTestDoubleTimSortKernel.DoublePartitionKernelStuff partitionStuff = new BaseTestDoubleTimSortKernel.DoublePartitionKernelStuff(stuffToSort, rowSet, chunkSize, numPartitionsValue, preserveEquality);
        doPartition = partitionStuff::run;
    }

    @Benchmark
    public void partition() {
        doPartition.run();
    }
}