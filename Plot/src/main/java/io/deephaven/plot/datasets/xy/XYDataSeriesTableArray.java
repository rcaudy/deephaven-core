//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.plot.datasets.xy;

import io.deephaven.engine.context.ExecutionContext;
import io.deephaven.plot.AxesImpl;
import io.deephaven.plot.SeriesInternal;
import io.deephaven.plot.datasets.data.IndexableNumericDataTable;
import io.deephaven.plot.errors.PlotInfo;
import io.deephaven.plot.util.ArgumentValidations;
import io.deephaven.plot.util.tables.TableHandle;
import io.deephaven.engine.table.Table;
import io.deephaven.engine.context.QueryScope;

import java.util.function.Function;

public class XYDataSeriesTableArray extends XYDataSeriesArray implements SeriesInternal {

    private final TableHandle tableHandle;
    private final String x;
    private final String y;

    public XYDataSeriesTableArray(final AxesImpl axes, final int id, final Comparable name,
            final TableHandle tableHandle, final String x, final String y) {
        super(axes, id, name, new IndexableNumericDataTable(tableHandle, x, new PlotInfo(axes, name)),
                new IndexableNumericDataTable(tableHandle, y, new PlotInfo(axes, name)));

        this.tableHandle = tableHandle;
        this.x = x;
        this.y = y;
    }

    private XYDataSeriesTableArray(final XYDataSeriesTableArray series, final AxesImpl axes) {
        super(series, axes);
        this.tableHandle = series.tableHandle;
        this.x = series.x;
        this.y = series.y;
    }

    @Override
    public XYDataSeriesTableArray copy(final AxesImpl axes) {
        return new XYDataSeriesTableArray(this, axes);
    }

    private <S, T> Table constructTableFromFunction(final Table t, final Function<S, T> function,
            final Class resultClass, final String onColumn, final String columnName) {
        ArgumentValidations.assertNotNull(function, "function", getPlotInfo());
        final String queryFunction = columnName + "Function";
        QueryScope.addParam(queryFunction, function);
        ExecutionContext.getContext().getQueryLibrary().importClass(resultClass);
        return t.update(
                columnName + " = (" + resultClass.getSimpleName() + ") " + queryFunction + ".apply(" + onColumn + ")");
    }
}
