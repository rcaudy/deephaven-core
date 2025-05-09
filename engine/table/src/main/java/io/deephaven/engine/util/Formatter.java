//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.engine.util;

import io.deephaven.engine.table.impl.locations.TableDataService;
import io.deephaven.util.annotations.ScriptApi;
import io.deephaven.util.text.Indenter;

/**
 * Formatters to transform strings into more usable forms.
 */
public class Formatter {
    /**
     * Add new lines and indentation to a String produced by {@link Object#toString()}
     *
     * @param tdsStr the output of {@link Object#toString()}
     * @return the same string with newlines and tabs.
     */
    @ScriptApi
    public static String formatTableDataService(String tdsStr) {
        StringBuilder sb = new StringBuilder();
        Indenter indenter = new Indenter();

        boolean[] skip = new boolean[] {false};
        char nl = '\n';
        tdsStr.chars().forEach(c -> {
            boolean skipspace = skip[0];
            skip[0] = false;
            // noinspection StatementWithEmptyBody
            if (c == ' ' && skipspace) {
                // do nothing.
            } else if (c == '{' || c == '[') {
                indenter.increaseLevel();
                sb.append((char) c).append(nl).append(indenter);
            } else if (c == '}' || c == ']') {
                indenter.decreaseLevel();
                sb.append(nl).append(indenter);
                sb.append((char) c);
            } else if (c == ',') {
                sb.append((char) c).append(nl).append(indenter);
                skip[0] = true;
            } else {
                sb.append((char) c);
            }
        });
        return sb.toString();
    }

}
