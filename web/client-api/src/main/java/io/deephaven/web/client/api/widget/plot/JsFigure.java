//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.web.client.api.widget.plot;

import elemental2.core.JsArray;
import elemental2.core.JsObject;
import elemental2.promise.Promise;
import io.deephaven.javascript.proto.dhinternal.io.deephaven_core.proto.console_pb.FigureDescriptor;
import io.deephaven.javascript.proto.dhinternal.io.deephaven_core.proto.console_pb.figuredescriptor.AxisDescriptor;
import io.deephaven.javascript.proto.dhinternal.io.deephaven_core.proto.object_pb.FetchObjectResponse;
import io.deephaven.javascript.proto.dhinternal.io.deephaven_core.proto.table_pb.ExportedTableCreationResponse;
import io.deephaven.javascript.proto.dhinternal.io.deephaven_core.proto.ticket_pb.TypedTicket;
import io.deephaven.web.client.api.Callbacks;
import io.deephaven.web.client.api.JsPartitionedTable;
import io.deephaven.web.client.api.JsTable;
import io.deephaven.web.client.api.WorkerConnection;
import io.deephaven.web.client.api.console.JsVariableType;
import io.deephaven.web.client.api.lifecycle.HasLifecycle;
import io.deephaven.web.client.api.widget.JsWidget;
import io.deephaven.web.client.fu.JsLog;
import io.deephaven.web.client.fu.LazyPromise;
import io.deephaven.web.client.state.ClientTableState;
import io.deephaven.web.shared.fu.JsBiConsumer;
import jsinterop.annotations.JsIgnore;
import jsinterop.annotations.JsNullable;
import jsinterop.annotations.JsOptional;
import jsinterop.annotations.JsProperty;
import jsinterop.annotations.JsType;
import jsinterop.base.Js;
import jsinterop.base.JsPropertyMap;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Provides the details for a figure.
 *
 * The Deephaven JS API supports automatic lossless downsampling of time-series data, when that data is plotted in one
 * or more line series. Using a scatter plot or a X-axis of some type other than DateTime will prevent this feature from
 * being applied to a series. To enable this feature, invoke <b>Axis.range(...)</b> to specify the length in pixels of
 * the axis on the screen, and the range of values that are visible, and the server will use that width (and range, if
 * any) to reduce the number of points sent to the client.
 *
 * Downsampling can also be controlled when calling either <b>Figure.subscribe()</b> or <b>Series.subscribe()</b> - both
 * can be given an optional <b>dh.plot.DownsampleOptions</b> argument. Presently only two valid values exist,
 * <b>DEFAULT</b>, and <b>DISABLE</b>, and if no argument is specified, <b>DEFAULT</b> is assumed. If there are more
 * than 30,000 rows in a table, downsampling will be encouraged - data will not load without calling
 * <b>subscribe(DISABLE)</b> or enabling downsampling via <b>Axis.range(...)</b>. If there are more than 200,000 rows,
 * data will refuse to load without downsampling and <b>subscribe(DISABLE)</b> would have no effect.
 *
 * Downsampled data looks like normal data, except that select items have been removed if they would be redundant in the
 * UI given the current configuration. Individual rows are intact, so that a tooltip or some other UI item is sure to be
 * accurate and consistent, and at least the highest and lowest value for each axis will be retained as well, to ensure
 * that the "important" values are visible.
 *
 * Four events exist to help with interacting with downsampled data, all fired from the <b>Figure</b> instance itself.
 * First, <b>downsampleneeded</b> indicates that more than 30,000 rows would be fetched, and so specifying downsampling
 * is no longer optional - it must either be enabled (calling <b>axis.range(...)</b>), or disabled. If the figure is
 * configured for downsampling, when a change takes place that requires that the server perform some downsampling work,
 * the <b>downsamplestarted</b> event will first be fired, which can be used to present a brief loading message,
 * indicating to the user why data is not ready yet - when the server side process is complete,
 * <b>downsamplefinished</b> will be fired. These events will repeat when the range changes, such as when zooming,
 * panning, or resizing the figure. Finally, <b>downsamplefailed</b> indicates that something when wrong when
 * downsampling, or possibly that downsampling cannot be disabled due to the number of rows in the table.
 *
 * At this time, not marked as a ServerObject, due to internal implementation issues which leave the door open to
 * client-created figures.
 */
@JsType(name = "Figure", namespace = "dh.plot")
public class JsFigure extends HasLifecycle {

    /**
     * The data within this figure was updated. <b>event.detail</b> is <b>FigureUpdateEventData</b>
     */
    @JsProperty(namespace = "dh.plot.Figure")
    public static final String EVENT_UPDATED = "updated",
            /**
             * A series used within this figure was added as part of a multi-series in a chart. The series instance is
             * the detail for this event.
             */
            EVENT_SERIES_ADDED = "seriesadded",
            EVENT_DISCONNECT = JsTable.EVENT_DISCONNECT,
            EVENT_RECONNECT = JsTable.EVENT_RECONNECT,
            EVENT_RECONNECTFAILED = JsTable.EVENT_RECONNECTFAILED,
            /**
             * The API is updating how downsampling works on this Figure, probably in response to a call to
             * <b>Axis.range()</b> or subscribe(). The <b>event.detail</b> value is an array of <b>Series</b> instances
             * which are affected by this.
             */
            EVENT_DOWNSAMPLESTARTED = "downsamplestarted",
            /**
             * Downsampling has finished on the given <b>Series</b> instances, and data will arrive shortly. The
             * <b>event.detail</b> value is the array of <b>Series</b> instances.
             */
            EVENT_DOWNSAMPLEFINISHED = "downsamplefinished",
            /**
             * Downsampling failed for some reason on one or more series. The <b>event.detail</b> object has three
             * properties, the <b>message</b> string describing what went wrong, the <b>size</b> number showing the full
             * size of the table, and the <b>series</b> property, an array of <b>Series</b> instances affected.
             */
            EVENT_DOWNSAMPLEFAILED = "downsamplefailed",
            /**
             * There are too many points to be drawn in the table which backs these series, and downsampling should be
             * enabled. As an alternative, downsampling can be explicitly disabled, provided there are less than 200,000
             * rows in the table.
             */
            EVENT_DOWNSAMPLENEEDED = "downsampleneeded";

    public interface FigureFetch {
        void fetch(JsBiConsumer<Object, FetchObjectResponse> callback);
    }

    public interface FigureTableFetch {
        Promise<FigureTableFetchData> fetch(JsFigure figure, FetchObjectResponse descriptor);
    }

    public interface FigureClose {
        void close(JsFigure figure);
    }

    public class FigureSourceException extends RuntimeException {
        @JsProperty
        transient JsTable table;

        @JsProperty
        transient SeriesDataSource source;

        FigureSourceException(JsTable table, SeriesDataSource source, String message) {
            super(message);

            this.table = table;
            this.source = source;
        }
    }

    public class FigureFetchError {
        @JsProperty
        Object error;

        @JsProperty
        JsArray<String> errors;

        FigureFetchError(Object error, JsArray<String> errors) {
            this.error = error;
            this.errors = errors;
        }

        public String toString() {
            return error.toString();
        }
    }

    private final FigureFetch fetch;
    private final FigureTableFetch tableFetch;
    private FigureClose onClose;

    private FigureDescriptor descriptor;

    private JsChart[] charts;

    private JsArray<String> errors;

    private JsTable[] tables;
    private Map<Integer, JsTable> plotHandlesToTables;

    private JsPartitionedTable[] partitionedTables;
    private Map<Integer, JsPartitionedTable> plotHandlesToPartitionedTables;

    private final Map<AxisDescriptor, DownsampledAxisDetails> downsampled = new HashMap<>();

    private final Map<FigureSubscription, FigureSubscription> activeFigureSubscriptions = new HashMap<>();

    private boolean subCheckEnqueued = false;

    @JsIgnore
    public JsFigure(WorkerConnection connection, FigureFetch fetch) {
        this(fetch, new DefaultFigureTableFetch(connection));
    }

    @JsIgnore
    public JsFigure(FigureFetch fetch, FigureTableFetch tableFetch) {
        this.fetch = fetch;
        this.tableFetch = tableFetch;
    }

    @JsIgnore
    public Promise<JsFigure> refetch() {
        plotHandlesToTables = new HashMap<>();
        plotHandlesToPartitionedTables = new HashMap<>();

        return Callbacks.grpcUnaryPromise(fetch::fetch).then(response -> {
            this.descriptor = FigureDescriptor.deserializeBinary(response.getData_asU8());

            charts = descriptor.getChartsList().asList().stream()
                    .map(chartDescriptor -> new JsChart(chartDescriptor, this)).toArray(JsChart[]::new);
            JsObject.freeze(charts);

            errors = JsObject.freeze(descriptor.getErrorsList().slice());

            return this.tableFetch.fetch(this, response);
        }).then(tableFetchData -> {
            // all tables are wired up, need to map them to the series instances
            tables = tableFetchData.tables;
            partitionedTables = tableFetchData.jsPartitionedTables;
            onClose = tableFetchData.onClose;

            for (int i = 0; i < tables.length; i++) {
                JsTable table = tables[i];
                registerTableWithId(table, Js.cast(JsArray.of((double) i)));
            }
            for (int i = 0; i < partitionedTables.length; i++) {
                JsPartitionedTable partitionedTable = partitionedTables[i];
                registerPartitionedTableWithId(partitionedTable, Js.cast(JsArray.of((double) i)));
            }
            Arrays.stream(charts)
                    .flatMap(c -> Arrays.stream(c.getSeries()))
                    .forEach(s -> s.initSources(plotHandlesToTables, plotHandlesToPartitionedTables));
            Arrays.stream(charts)
                    .flatMap(c -> Arrays.stream(c.getMultiSeries()))
                    .forEach(s -> s.initSources(plotHandlesToPartitionedTables));

            return null;
        }).then(ignore -> {
            unsuppressEvents();
            fireEvent(EVENT_RECONNECT);
            return Promise.resolve(this);
        }, err -> {
            final FigureFetchError fetchError = new FigureFetchError(LazyPromise.ofObject(err),
                    this.descriptor != null ? this.descriptor.getErrorsList() : new JsArray<>());
            // noinspection unchecked
            unsuppressEvents();
            fireEvent(EVENT_RECONNECTFAILED, fetchError);
            suppressEvents();

            // noinspection unchecked,rawtypes
            return (Promise<JsFigure>) (Promise) Promise.reject(fetchError);
        });
    }

    /**
     * Asks the figure to fire a reconnect event after its tables are ready.
     */
    @JsIgnore
    public void reconnect() {
        // For each table and partitioned table, listen for reconnect events - when all have reconnected,
        // signal that the figure itself has disconnected. If any one table disconnects, this will be canceled.
        Promise.all(
                Stream.concat(
                        Arrays.stream(tables),
                        Arrays.stream(partitionedTables))
                        .map(HasLifecycle::nextReconnect)
                        .toArray(Promise[]::new))
                .then(ignore -> {
                    verifyTables();
                    return null;
                }).then(ignore -> {
                    unsuppressEvents();
                    fireEvent(EVENT_RECONNECT);
                    enqueueSubscriptionCheck();
                    return null;
                }, failure -> {
                    unsuppressEvents();
                    fireEvent(EVENT_RECONNECTFAILED, failure);
                    suppressEvents();
                    return null;
                });
    }


    /**
     * The title of the figure.
     * 
     * @return String
     */
    @JsProperty
    @JsNullable
    public String getTitle() {
        if (descriptor.hasTitle()) {
            return descriptor.getTitle();
        }
        return null;
    }

    @JsProperty
    public String getTitleFont() {
        return descriptor.getTitleFont();
    }

    @JsProperty
    public String getTitleColor() {
        return descriptor.getTitleColor();
    }

    @JsProperty
    public double getUpdateInterval() {
        return Long.parseLong(descriptor.getUpdateInterval());
    }

    @JsProperty
    public int getCols() {
        return descriptor.getCols();
    }

    @JsProperty
    public int getRows() {
        return descriptor.getRows();
    }

    /**
     * The charts to draw.
     * 
     * @return dh.plot.Chart
     */
    @JsProperty
    public JsChart[] getCharts() {
        return charts;
    }

    @JsProperty
    public JsArray<String> getErrors() {
        return errors;
    }

    /**
     * Enable updates for all series in this figure.
     */
    @JsIgnore
    public void subscribe() {
        subscribe(null);
    }

    public void subscribe(@JsOptional DownsampleOptions forceDisableDownsample) {
        // iterate all series, mark all as subscribed, will enqueue a check automatically
        Arrays.stream(charts).flatMap(c -> Arrays.stream(c.getSeries()))
                .forEach(s -> s.subscribe(forceDisableDownsample));
    }

    /**
     * Disable updates for all series in this figure.
     */
    public void unsubscribe() {
        // iterate all series, mark all as unsubscribed
        Arrays.stream(charts).flatMap(c -> Arrays.stream(c.getSeries()))
                .forEach(JsSeries::markUnsubscribed);

        // clear all subscriptions, no need to do a real check
        activeFigureSubscriptions.keySet().forEach(FigureSubscription::unsubscribe);
        activeFigureSubscriptions.clear();
    }

    @JsIgnore
    public void downsampleNeeded(String message, Set<JsSeries> series, double tableSize) {
        fireEvent(EVENT_DOWNSAMPLENEEDED,
                JsPropertyMap.of("series", series, "message", message, "size", tableSize));
    }

    @JsIgnore
    public void downsampleFailed(String message, Set<JsSeries> series, double tableSize) {
        fireEvent(EVENT_DOWNSAMPLEFAILED,
                JsPropertyMap.of("series", series, "message", message, "size", tableSize));
    }

    private void updateSubscriptions() {
        // mark that we're performing the subscription check, any future changes will need to re-enqueue this step
        subCheckEnqueued = false;

        // Collect the subscriptions that we will need for the current series and their configurations
        final Map<JsTable, Map<AxisRange, DownsampleParams>> downsampleMappings = Arrays.stream(charts)
                .flatMap(c -> Arrays.stream(c.getSeries()))
                .filter(JsSeries::isSubscribed)
                .filter(series -> series.getOneClick() == null
                        || (series.getOneClick().allRequiredValuesSet() && series.getOneClick().getTable() != null))
                .collect(
                        Collectors.groupingBy(
                                this::tableForSeries,
                                Collectors.groupingBy(
                                        this::groupByAxisRange,
                                        Collectors.reducing(DownsampleParams.EMPTY, this::makeParamsForSeries,
                                                DownsampleParams::merge))));

        final Set<FigureSubscription> newSubscriptions = downsampleMappings.entrySet().stream().flatMap(outerEntry -> {
            JsTable table = outerEntry.getKey();
            Map<AxisRange, DownsampleParams> mapping = outerEntry.getValue();
            return mapping.entrySet().stream().map(innerEntry -> {
                AxisRange range = innerEntry.getKey();
                DownsampleParams params = innerEntry.getValue();
                return new FigureSubscription(this, table, range, range == null ? null : params,
                        new HashSet<>(Arrays.asList(params.series)));
            });
        }).collect(Collectors.toSet());

        // Given those subscriptions, check our existing subscriptions to determine which new subscriptions
        // need to be created, and which existing ones are no longer needed.
        // Note that when we compare these, we only check the original table and the mutations applied to that table
        // (filters, downsample), we don't include the series instances themselves, as there is no need to re-subscribe
        // just because a series is now being drawn which shares the same data as other visible series.

        // Both unsubscribing and creating a subscription will delegate to the FigureSubscription class to let it
        // get things started.
        final Set<FigureSubscription> unseen = new HashSet<>(activeFigureSubscriptions.values());
        for (final FigureSubscription newSubscription : newSubscriptions) {
            if (activeFigureSubscriptions.containsKey(newSubscription)) {
                // already present, update series (if needed), and let it fire events
                activeFigureSubscriptions.get(newSubscription).replaceSeries(newSubscription.getSeries());
                JsLog.info("Saw same subscription again", activeFigureSubscriptions.get(newSubscription));

                // mark as seen
                unseen.remove(newSubscription);
            } else {
                // new subscription, not present yet
                activeFigureSubscriptions.put(newSubscription, newSubscription);
                JsLog.info("Adding new subscription", newSubscription);
                newSubscription.subscribe();
            }
        }
        // remove all now-unused subscriptions
        for (final FigureSubscription unseenSub : unseen) {
            JsLog.info("Removing unused subscription", unseenSub);
            unseenSub.unsubscribe();
            activeFigureSubscriptions.remove(unseenSub);
        }
    }

    private JsTable tableForSeries(JsSeries s) {
        // if we have a oneclick, then grab the loaded table
        if (s.getOneClick() != null) {
            return s.getOneClick().getTable();
        }

        // otherwise grab the first table we can find
        // TODO loop, assert all match
        return plotHandlesToTables.get(s.getDescriptor().getDataSourcesList().getAt(0).getTableId());
    }

    // First, break down the ranges so we can tell when they are entirely incompatible. They
    // won't forever be incompatible by max/min, but today they are.
    public static class AxisRange {
        final String xCol;
        final Long min;
        final Long max;

        AxisRange(final String xCol, final Long min, final Long max) {
            this.xCol = xCol;
            this.min = min;
            this.max = max;
        }

        @Override
        public boolean equals(final Object o) {
            if (this == o)
                return true;
            if (o == null || getClass() != o.getClass())
                return false;

            final AxisRange axisRange = (AxisRange) o;

            if (!xCol.equals(axisRange.xCol))
                return false;
            if (min != null ? !min.equals(axisRange.min) : axisRange.min != null)
                return false;
            return max != null ? max.equals(axisRange.max) : axisRange.max == null;
        }

        @Override
        public int hashCode() {
            int result = xCol.hashCode();
            result = 31 * result + (min != null ? min.hashCode() : 0);
            result = 31 * result + (max != null ? max.hashCode() : 0);
            return result;
        }

        public String getxCol() {
            return xCol;
        }

        public Long getMin() {
            return min;
        }

        public Long getMax() {
            return max;
        }
    }

    private AxisRange groupByAxisRange(JsSeries s) {
        if (s.getDownsampleOptions() == DownsampleOptions.DISABLE) {
            return null;
        }
        if (!canDownsampleSeries(s)) {
            return null;
        }
        for (int i = 0; i < s.getSources().length; i++) {
            SeriesDataSource source = s.getSources()[i];
            if (!source.getColumnType().equals("java.time.Instant")) {
                continue;
            }
            DownsampledAxisDetails downsampledAxisDetails = downsampled.get(source.getAxis().getDescriptor());
            if (downsampledAxisDetails == null) {
                continue;
            }
            return new AxisRange(source.getDescriptor().getColumnName(), downsampledAxisDetails.min,
                    downsampledAxisDetails.max);
        }
        return null;
    }

    private boolean canDownsampleSeries(JsSeries series) {
        if (series.getShapesVisible() == Boolean.TRUE) {
            return false;
        }
        // this was formerly a switch/case, but since we're referencing JS we need to use expressions that look like
        // non-constants to java
        int plotStyle = series.getPlotStyle();
        if (plotStyle == FigureDescriptor.SeriesPlotStyle.getBAR()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getSTACKED_BAR()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getPIE()) {
            // category charts, can't remove categories
            return false;
        } else if (plotStyle == FigureDescriptor.SeriesPlotStyle.getSCATTER()) {
            // pointless without shapes visible, this ensures we aren't somehow trying to draw it
            return false;
        } else if (plotStyle == FigureDescriptor.SeriesPlotStyle.getLINE()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getAREA()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getSTACKED_AREA()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getHISTOGRAM()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getOHLC()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getSTEP()
                || plotStyle == FigureDescriptor.SeriesPlotStyle.getERROR_BAR()) {
            // allowed, fall through (listed so we can default to not downsample)
            return true;
        }
        // unsupported
        return false;
    }

    private DownsampleParams makeParamsForSeries(JsSeries s) {
        String[] yCols = new String[0];
        int pixels = 0;
        // ... again, loop and find x axis, this time also y cols
        for (int i = 0; i < s.getSources().length; i++) {
            SeriesDataSource source = s.getSources()[i];
            DownsampledAxisDetails downsampledAxisDetails =
                    source.getAxis() != null ? downsampled.get(source.getAxis().getDescriptor()) : null;
            if (downsampledAxisDetails == null) {
                yCols[yCols.length] = source.getDescriptor().getColumnName();
            } else {
                pixels = downsampledAxisDetails.pixels;
            }
        }
        return new DownsampleParams(new JsSeries[] {s}, yCols, pixels);
    }

    // Then, aggregate the series instances and find the max pixel count, all the value columns to use
    public static class DownsampleParams {
        static DownsampleParams EMPTY = new DownsampleParams(new JsSeries[0], new String[0], 0);

        private final JsSeries[] series;
        private final String[] yCols;
        private final int pixelCount;

        DownsampleParams(final JsSeries[] series, final String[] yCols, final int pixelCount) {
            this.series = series;
            this.yCols = yCols;
            this.pixelCount = pixelCount;
        }

        public DownsampleParams merge(DownsampleParams other) {
            return new DownsampleParams(
                    Stream.of(series, other.series)
                            .flatMap(Arrays::stream)
                            .distinct()
                            .toArray(JsSeries[]::new),
                    Stream.of(yCols, other.yCols)
                            .flatMap(Arrays::stream)
                            .distinct()
                            .toArray(String[]::new),
                    Math.max(pixelCount, other.pixelCount));
        }

        public JsSeries[] getSeries() {
            return series;
        }

        public String[] getyCols() {
            return yCols;
        }

        public int getPixelCount() {
            return pixelCount;
        }
    }

    @JsIgnore
    public void enqueueSubscriptionCheck() {
        if (!subCheckEnqueued) {
            for (JsTable table : tables) {
                if (table.isClosed()) {
                    throw new IllegalStateException("Cannot subscribe, at least one table is disconnected");
                }
            }
            subCheckEnqueued = true;
            LazyPromise.runLater(this::updateSubscriptions);
        }
    }

    /**
     * Verifies that the underlying tables have the columns the series are expected. Throws an FigureSourceException if
     * not found
     */
    @JsIgnore
    public void verifyTables() {
        Arrays.stream(charts)
                .flatMap(c -> Arrays.stream(c.getSeries()))
                .forEach(s -> {
                    JsTable table = tableForSeries(s);
                    Arrays.stream(s.getSources())
                            .forEach(source -> {
                                try {
                                    table.findColumn(source.getDescriptor().getColumnName());
                                } catch (NoSuchElementException e) {
                                    throw new FigureSourceException(table, source, e.toString());
                                }
                            });
                });
    }

    /**
     * Close the figure, and clean up subscriptions.
     */
    public void close() {
        // explicit unsubscribe first, since those are handled separately from the table obj itself
        unsubscribe();

        if (onClose != null) {
            onClose.close(this);
        }

        if (tables != null) {
            Arrays.stream(tables).filter(t -> !t.isClosed()).forEach(JsTable::close);
        }
        if (partitionedTables != null) {
            Arrays.stream(partitionedTables).forEach(JsPartitionedTable::close);
        }
    }

    @JsIgnore
    public int registerTable(JsTable table) {
        int id = plotHandlesToTables.size();
        registerTableWithId(table, Js.uncheckedCast(new double[] {id}));
        return id;
    }

    private void registerTableWithId(JsTable table, JsArray<Double> plotTableHandles) {
        assert table != null;
        for (int j = 0; j < plotTableHandles.length; j++) {
            plotHandlesToTables.put((int) (double) plotTableHandles.getAt(j), table);
        }
    }

    private void registerPartitionedTableWithId(JsPartitionedTable partitionedTable, JsArray<Double> plotTableHandles) {
        assert partitionedTable != null;
        for (int j = 0; j < plotTableHandles.length; j++) {
            plotHandlesToPartitionedTables.put((int) (double) plotTableHandles.getAt(j), partitionedTable);
        }
    }

    @JsIgnore
    public void updateDownsampleRange(AxisDescriptor axis, Integer pixels, Long min, Long max) {
        if (pixels == null) {
            downsampled.remove(axis);
        } else {
            if (axis.getLog() || axis.getType() != AxisDescriptor.AxisType.getX() || axis.getInvert()) {
                return;
            }
            downsampled.put(axis, new DownsampledAxisDetails(pixels, min, max));
        }
        enqueueSubscriptionCheck();
    }

    /**
     * Tracks ranges that an axis has registered for.
     */
    public static class DownsampledAxisDetails {
        private final int pixels;
        private final Long min;
        private final Long max;

        public DownsampledAxisDetails(final int pixels, final Long min, final Long max) {
            this.pixels = pixels;
            this.min = min;
            this.max = max;
        }

        @Override
        public boolean equals(final Object o) {
            if (this == o)
                return true;
            if (o == null || getClass() != o.getClass())
                return false;

            final DownsampledAxisDetails that = (DownsampledAxisDetails) o;

            if (pixels != that.pixels)
                return false;
            if (min != null ? !min.equals(that.min) : that.min != null)
                return false;
            return max != null ? max.equals(that.max) : that.max == null;
        }

        @Override
        public int hashCode() {
            int result = pixels;
            result = 31 * result + (min != null ? min.hashCode() : 0);
            result = 31 * result + (max != null ? max.hashCode() : 0);
            return result;
        }
    }

    public static class FigureTableFetchData {
        private JsTable[] tables;

        private JsPartitionedTable[] jsPartitionedTables;
        private FigureClose onClose;

        public FigureTableFetchData(
                JsTable[] tables,
                JsPartitionedTable[] jsPartitionedTables) {
            this(tables, jsPartitionedTables, null);
        }

        public FigureTableFetchData(
                JsTable[] tables,
                JsPartitionedTable[] jsPartitionedTables,
                FigureClose onClose) {
            this.tables = tables;
            this.jsPartitionedTables = jsPartitionedTables;

            // Called when the figure is being closed
            this.onClose = onClose;
        }
    }


    private static class DefaultFigureTableFetch implements FigureTableFetch {
        private WorkerConnection connection;

        DefaultFigureTableFetch(WorkerConnection connection) {
            this.connection = connection;
        }

        @Override
        public Promise<FigureTableFetchData> fetch(JsFigure figure, FetchObjectResponse response) {
            JsTable[] tables = new JsTable[0];
            JsPartitionedTable[] partitionedTables = new JsPartitionedTable[0];

            Promise<?>[] promises = new Promise[response.getTypedExportIdsList().length];

            int nextTableIndex = 0;
            int nextPartitionedTableIndex = 0;
            for (int i = 0; i < response.getTypedExportIdsList().length; i++) {
                TypedTicket ticket = response.getTypedExportIdsList().getAt(i);
                if (ticket.getType().equals(JsVariableType.TABLE)) {
                    // Note that creating a CTS like this means we can't actually refetch it, but that's okay, we can't
                    // reconnect in this way without refetching the entire figure anyway.
                    int tableIndex = nextTableIndex++;
                    promises[i] = Callbacks.<ExportedTableCreationResponse, Object>grpcUnaryPromise(c -> {
                        connection.tableServiceClient().getExportedTableCreationResponse(ticket.getTicket(),
                                connection.metadata(),
                                c::apply);
                    }).then(etcr -> {
                        ClientTableState cts = connection.newStateFromUnsolicitedTable(etcr, "table for figure");
                        JsTable table = new JsTable(connection, cts);
                        // TODO(deephaven-core#3604) if using a new session don't attempt a reconnect, since we might
                        // have a different figure schema entirely
                        // table.addEventListener(JsTable.EVENT_DISCONNECT, ignore -> table.close());
                        tables[tableIndex] = table;
                        return Promise.resolve(table);
                    });
                } else if (ticket.getType().equals(JsVariableType.PARTITIONEDTABLE)) {
                    int partitionedTableIndex = nextPartitionedTableIndex++;
                    JsPartitionedTable partitionedTable =
                            new JsPartitionedTable(connection, new JsWidget(connection, ticket));
                    // TODO(deephaven-core#3604) if using a new session don't attempt a reconnect, since we might
                    // have a different figure schema entirely
                    // partitionedTable.addEventListener(JsPartitionedTable.EVENT_DISCONNECT, ignore ->
                    // partitionedTable.close());
                    partitionedTables[partitionedTableIndex] = partitionedTable;
                    promises[i] = partitionedTable.refetch();
                } else {
                    throw new IllegalStateException("Ticket type not recognized in a Figure: " + ticket.getType());
                }
            }

            return Promise.all(promises)
                    .then(ignore -> {
                        connection.registerSimpleReconnectable(figure);

                        return Promise.resolve(
                                new FigureTableFetchData(tables, partitionedTables,
                                        f -> this.connection.unregisterSimpleReconnectable(f)));
                    });
        }
    }
}
