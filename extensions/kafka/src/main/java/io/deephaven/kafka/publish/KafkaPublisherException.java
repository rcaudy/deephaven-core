//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.kafka.publish;

import io.deephaven.UncheckedDeephavenException;

/**
 * This exception is thrown when there is a failure to produce a Kafka record during Deephaven to Kafka publication.
 */
public class KafkaPublisherException extends UncheckedDeephavenException {
    /**
     * Constructs a new KafkaIngesterException with the specified reason.
     *
     * @param reason the exception detail message
     * @param cause the exception cause
     */
    public KafkaPublisherException(String reason, Throwable cause) {
        super(reason, cause);
    }

    /**
     * Constructs a new KafkaIngesterException with the specified reason.
     *
     * @param reason the exception detail message
     */
    public KafkaPublisherException(String reason) {
        super(reason);
    }
}
