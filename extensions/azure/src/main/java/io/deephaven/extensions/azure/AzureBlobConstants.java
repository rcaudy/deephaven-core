//
// Copyright (c) 2016-2026 Deephaven Data Labs and Patent Pending
//
package io.deephaven.extensions.azure;

import java.util.Set;

public final class AzureBlobConstants {
    public static final String ABFS_URI_SCHEME = "abfs";
    public static final String ABFSS_URI_SCHEME = "abfss";
    public static final String WASB_URI_SCHEME = "wasb";
    public static final String WASBS_URI_SCHEME = "wasbs";
    public static final Set<String> AZURE_SCHEMES =
            Set.of(ABFS_URI_SCHEME, ABFSS_URI_SCHEME, WASB_URI_SCHEME, WASBS_URI_SCHEME);

    static final String DEFAULT_ENDPOINT_SUFFIX = "blob.core.windows.net";

    private AzureBlobConstants() {}
}
