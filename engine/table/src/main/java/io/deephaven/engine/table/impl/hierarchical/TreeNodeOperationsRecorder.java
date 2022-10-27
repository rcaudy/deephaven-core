package io.deephaven.engine.table.impl.hierarchical;

import io.deephaven.api.SortColumn;
import io.deephaven.api.filter.Filter;
import io.deephaven.engine.table.Table;
import io.deephaven.engine.table.TableDefinition;
import io.deephaven.engine.table.hierarchical.TreeTable;
import io.deephaven.engine.table.impl.select.SelectColumn;
import io.deephaven.engine.table.impl.select.WhereFilter;
import org.jetbrains.annotations.NotNull;

import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * {@link TreeTable.NodeOperationsRecorder} implementation.
 */
class TreeNodeOperationsRecorder extends BaseNodeOperationsRecorder<TreeTable.NodeOperationsRecorder>
        implements TreeTable.NodeOperationsRecorder {

    private final Collection<? extends WhereFilter> recordedFilters;

    TreeNodeOperationsRecorder(@NotNull final TableDefinition definition) {
        this(definition, List.of(), List.of(), List.of());
    }

    private TreeNodeOperationsRecorder(
            @NotNull final TableDefinition definition,
            @NotNull final Collection<? extends SelectColumn> recordedFormats,
            @NotNull final Collection<SortColumn> recordedSorts,
            @NotNull final Collection<? extends WhereFilter> recordedFilters) {
        super(definition, recordedFormats, recordedSorts);
        this.recordedFilters = recordedFilters;
    }

    @Override
    TreeTable.NodeOperationsRecorder withFormats(@NotNull final Stream<? extends SelectColumn> formats) {
        return new TreeNodeOperationsRecorder(definition,
                Stream.concat(recordedFormats.stream(), formats).collect(Collectors.toList()),
                recordedSorts, recordedFilters);
    }

    @Override
    TreeTable.NodeOperationsRecorder withSorts(@NotNull final Stream<SortColumn> sorts) {
        return new TreeNodeOperationsRecorder(definition, recordedFormats,
                Stream.concat(sorts, recordedSorts.stream()).collect(Collectors.toList()), recordedFilters);
    }

    TreeTable.NodeOperationsRecorder withFilters(@NotNull final Stream<? extends WhereFilter> filters) {
        return new TreeNodeOperationsRecorder(definition, recordedFormats, recordedSorts,
                Stream.concat(recordedFilters.stream(), filters).collect(Collectors.toList()));
    }

    TreeNodeOperationsRecorder withOperations(@NotNull final TreeNodeOperationsRecorder other) {
        if (!definition.equals(other.definition)) {
            throw new IllegalArgumentException(
                    "Incompatible operation recorders; compatible recorders must be created from the same table");
        }
        return new TreeNodeOperationsRecorder(definition,
                Stream.concat(recordedFormats.stream(), other.getRecordedFormats().stream())
                        .collect(Collectors.toList()),
                Stream.concat(other.getRecordedSorts().stream(), recordedSorts.stream()).collect(Collectors.toList()),
                Stream.concat(recordedFilters.stream(), other.recordedFilters.stream()).collect(Collectors.toList()));
    }

    Collection<? extends WhereFilter> getRecordedFilters() {
        return recordedFilters;
    }

    @Override
    public TreeTable.NodeOperationsRecorder where(String... filters) {
        final FilterRecordingTableAdapter adapter = new FilterRecordingTableAdapter(definition);
        adapter.where(filters);
        return withFilters(adapter.whereFilters());
    }

    @Override
    public TreeTable.NodeOperationsRecorder where(Collection<? extends Filter> filters) {
        final FilterRecordingTableAdapter adapter = new FilterRecordingTableAdapter(definition);
        adapter.where(filters);
        return withFilters(adapter.whereFilters());
    }

    @Override
    public TreeTable.NodeOperationsRecorder where(Filter... filters) {
        final FilterRecordingTableAdapter adapter = new FilterRecordingTableAdapter(definition);
        adapter.where(filters);
        return withFilters(adapter.whereFilters());
    }

    private static final class FilterRecordingTableAdapter extends RecordingTableAdapter {

        private Collection<? extends Filter> filters;

        private FilterRecordingTableAdapter(@NotNull final TableDefinition definition) {
            super(definition);
        }

        @Override
        public Table where(@NotNull final Collection<? extends Filter> filters) {
            this.filters = filters;
            return this;
        }

        private Stream<? extends WhereFilter> whereFilters() {
            return Stream.of(WhereFilter.from(filters)).peek(wf -> wf.init(getDefinition()));
        }
    }
}