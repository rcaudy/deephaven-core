//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import io.deephaven.hash.KeyedObjectHashMap;
import io.deephaven.hash.KeyedObjectKey;
import io.deephaven.internal.log.LoggerFactory;
import io.deephaven.io.logger.Logger;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

/**
 * Cache for {@link AzureReadRequest} objects based on their URI and fragment index.
 */
final class AzureReadRequestCache {

    private static final Logger log = LoggerFactory.getLogger(AzureReadRequestCache.class);

    private final int fragmentSize;
    private final KeyedObjectHashMap<AzureReadRequest.ID, AzureReadRequest> requests;

    AzureReadRequestCache(final int fragmentSize) {
        this.fragmentSize = fragmentSize;
        this.requests = new KeyedObjectHashMap<>(RequestKey.INSTANCE);
    }

    private static final class RequestKey extends KeyedObjectKey.Basic<AzureReadRequest.ID, AzureReadRequest> {
        private static final KeyedObjectKey<AzureReadRequest.ID, AzureReadRequest> INSTANCE = new RequestKey();

        @Override
        public AzureReadRequest.ID getKey(@NotNull final AzureReadRequest request) {
            return request.getId();
        }
    }

    int getFragmentSize() {
        return fragmentSize;
    }

    @Nullable
    AzureReadRequest.Acquired getRequest(@NotNull final AzureUri uri, final long fragmentIndex) {
        final AzureReadRequest.ID key = new AzureReadRequest.ID(uri, fragmentIndex);
        final AzureReadRequest existingRequest = requests.get(key);
        if (existingRequest != null) {
            final AzureReadRequest.Acquired acquired = existingRequest.tryAcquire();
            if (acquired != null) {
                return acquired;
            }
            remove(existingRequest);
        }
        return null;
    }

    @NotNull
    AzureReadRequest.Acquired getOrCreateRequest(
            @NotNull final AzureUri uri,
            final long fragmentIndex,
            @NotNull final AzureReadContext context) {
        final AzureReadRequest.ID key = new AzureReadRequest.ID(uri, fragmentIndex);
        AzureReadRequest.Acquired newAcquired = null;
        AzureReadRequest existingRequest = requests.get(key);
        while (true) {
            if (existingRequest != null) {
                final AzureReadRequest.Acquired acquired = existingRequest.tryAcquire();
                if (acquired != null) {
                    return acquired;
                } else {
                    remove(existingRequest);
                }
            }
            if (newAcquired == null) {
                newAcquired = AzureReadRequest.createAndAcquire(fragmentIndex, context);
            }
            if ((existingRequest = requests.putIfAbsent(key, newAcquired.request())) == null) {
                if (log.isDebugEnabled()) {
                    log.debug().append("Added new request to cache: ").append(String.format("ctx=%d ",
                            System.identityHashCode(context))).append(newAcquired.request().requestStr()).endl();
                }
                return newAcquired;
            }
        }
    }

    void remove(@NotNull final AzureReadRequest request) {
        if (log.isDebugEnabled()) {
            log.debug().append("Clearing request from cache: ").append(request.requestStr()).endl();
        }
        requests.remove(request.getId(), request);
    }

    void clear() {
        requests.clear();
    }
}
