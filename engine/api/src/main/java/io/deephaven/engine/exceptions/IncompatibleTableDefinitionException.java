package io.deephaven.engine.exceptions;

import io.deephaven.UncheckedDeephavenException;

/**
 * Runtime exception representing an incompatibility between table definitions.
 */
@SuppressWarnings({"WeakerAccess", "unused"})
public class IncompatibleTableDefinitionException extends UncheckedDeephavenException {

    public IncompatibleTableDefinitionException() {
        super();
    }

    public IncompatibleTableDefinitionException(String message) {
        super(message);
    }

    public IncompatibleTableDefinitionException(String message, Throwable cause) {
        super(message, cause);
    }

    public IncompatibleTableDefinitionException(Throwable cause) {
        super(cause);
    }
}
