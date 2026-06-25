# DH-22795 Azure Blob Storage Support for Parquet and Iceberg

Add Azure Blob Storage as a storage backend for Deephaven's Parquet reading/writing and Iceberg catalog integration, following the established S3 architecture.

## Team(s)

### Primary team

- **I/O Team**: Core Azure extension, channel provider, Iceberg bridge

### Cross-team dependencies

- **Engine & API Team**: Review of public API surface (`AzureInstructions`, `AzureCredentials`, `IcebergToolsAzure`)

## Problem / Feature Gap

Deephaven has robust S3 support for reading/writing Parquet files and browsing Iceberg catalogs backed by S3 storage. Azure Blob Storage is a widely-used alternative, but there is currently no way to read Parquet files from or write Parquet files to Azure Blob Storage, nor to use Iceberg catalogs backed by Azure storage. Customers on Azure are blocked from using Deephaven's Iceberg integration with their existing data infrastructure.

## Scope

### In Scope / Requirements

- Reading Parquet files from Azure Blob Storage via `abfs://`, `abfss://`, `wasb://`, `wasbs://` URI schemes
- Writing Parquet files to Azure Blob Storage
- Iceberg catalog integration for tables backed by Azure Blob Storage (using Iceberg's `ADLSFileIO`)
- Configuration via an `AzureInstructions` immutable object (parallel to `S3Instructions`)
- Credential support: DefaultAzureCredential, shared key, SAS token, connection string, anonymous
- Convenience API via `IcebergToolsAzure` (parallel to `IcebergToolsS3`)
- Automated testing with Azurite (Azure Storage emulator) via Testcontainers
- Making Iceberg property injection pluggable so Azure can add defaults without modifying the core Iceberg module

### Out of Scope / Limitations

- Azure Data Lake Storage Gen1 (legacy ADLS, uses a completely different API)
- Azure Files or Azure Queue support (only Blob Storage / ADLS Gen2)
- Automatic migration tooling from S3 to Azure
- Azure-specific Iceberg catalog implementations (e.g., Azure-backed Nessie or Hive Metastore)

### Risks

- **ADLSFileIO client exposure**: Iceberg's `ADLSFileIO` may not expose its internal `BlobServiceClient` the way `S3FileIO` exposes its `S3AsyncClient`. If so, the "reuse client from FileIO" optimization path is not available and all reads go through a separately-created client. This is functionally correct but less efficient.
- **Reactor dependency**: Azure's async client brings in `reactor-core`. Need to verify no conflicts with existing Deephaven dependencies. Fallback: use sync client with dedicated thread pool.
- **Azure SDK version management**: No Azure BOM is currently in the project. Need to establish version management for Azure SDK dependencies.

## Technical Design

### Decisions

**Module structure**: Three new Gradle modules, mirroring the S3 structure exactly:
- `extensions/azure/` (`:extensions-azure`) -- core channel provider, parallel to `extensions/s3/`
- `extensions/iceberg/azure/` (`:extensions-iceberg-azure`) -- Iceberg bridge, parallel to `extensions/iceberg/s3/`
- Modification to `extensions/iceberg/` -- pluggable property injection

**Async client strategy**: Use Azure's `BlobAsyncClient` with `Mono.toFuture()` to bridge to `CompletableFuture`. This avoids blocking thread pool threads and matches the S3 pattern where async operations back the fragment-based read-ahead system. Azure SDK already depends on `reactor-core`, so no new conceptual dependency is introduced.

**URI handling**: Implement a Deephaven `AzureUri` parser since the Azure SDK has no equivalent of AWS's `S3Uri`. Azure URIs encode container and account in the authority: `abfss://container@account.dfs.core.windows.net/path/to/blob`.

**Write model**: Azure's block blob staged upload maps cleanly to S3's multipart upload. Stage blocks with generated block IDs, then commit block list. Block IDs are zero-padded sequential integers encoded as Base64 (Azure requires uniform-length IDs within a blob). No explicit abort needed -- uncommitted blocks expire automatically.

**Property injection**: Refactor `InjectAWSProperties` into a `PropertyInjector` SPI discovered via `ServiceLoader`. This allows `extensions/iceberg/azure/` to add `InjectAzureProperties` without the core `extensions/iceberg/` module depending on Azure.

### Development Plan

#### Phase 1: Core Azure Extension (`extensions/azure/`)

1. **Version catalog and build setup**
   - Add Azure SDK dependencies to `gradle/libs.versions.toml`: `azure-storage-blob`, `azure-identity`
   - Add `iceberg-azure` to the Iceberg libraries (managed by existing iceberg BOM)
   - Create `extensions/azure/build.gradle` following `extensions/s3/build.gradle` pattern
   - Register in `settings.gradle`

2. **Constants and URI parsing**
   - `AzureBlobConstants` -- URI scheme constants (`abfs`, `abfss`, `wasb`, `wasbs`) and scheme set
     - Parallels: `S3Constants`
   - `AzureUri` -- Parse Azure URIs into account, container, blob path; reconstruct URIs for scheme translation
     - New class (S3 uses SDK-provided `S3Uri`; Azure SDK has no equivalent)

3. **Credentials**
   - `AzureCredentials` -- Public interface with static factories: `resolving()`, `defaultCredentials()`, `sharedKey(accountName, accountKey)`, `sasToken(token)`, `connectionString(connStr)`, `anonymous()`
     - Parallels: `Credentials`
   - `AzureSdkCredentials` -- Internal interface that produces Azure SDK credential objects
     - Parallels: `AwsSdkV2Credentials`
   - Concrete implementations: `ResolvingAzureCredentials`, `SharedKeyAzureCredentials`, `SasTokenAzureCredentials`, `ConnectionStringAzureCredentials`, `AnonymousAzureCredentials`

4. **Configuration**
   - `AzureInstructions` -- `@Immutable @CopyableStyle` configuration object
     - Parallels: `S3Instructions`
     - Fields: `accountName`, `endpointSuffix` (default `"blob.core.windows.net"`), `endpointOverride`, `credentials`, `maxConcurrentRequests`, `readAheadCount`, `fragmentSize`, `connectionTimeout`, `readTimeout`, `writeTimeout`, `writeBlockSize`, `numConcurrentWriteBlocks`
     - Note: no `regionName` (Azure uses account-based endpoint resolution)

5. **Client factory**
   - `AzureBlobClientFactory` -- Creates/caches `BlobServiceAsyncClient` and `BlobServiceClient`
     - Parallels: `S3ClientFactory`
     - Caches HTTP clients keyed by `(maxConcurrentRequests, connectionTimeout)`
     - Configures retry, timeout, credentials from `AzureInstructions`

6. **Read infrastructure**
   - `AzureReadRequestCache` -- Shared cache for fragment read requests
     - Parallels: `S3ReadRequestCache`
   - `AzureReadRequest` -- Single fragment read: issues `BlobAsyncClient.downloadStreamWithResponse()` with `BlobRange`, subscribes to `Flux<ByteBuffer>` to fill buffer, exposes `CompletableFuture<Boolean>`
     - Parallels: `S3ReadRequest`
   - `AzureReadContext` -- Manages read-ahead buffers, fragment tracking, URI state
     - Parallels: `S3ReadContext`
   - `AzureSeekableByteChannel` -- Read-only `SeekableByteChannel` delegating to `AzureReadContext`
     - Parallels: `S3SeekableByteChannel`

7. **Write infrastructure**
   - `AzureWriteContext` -- Buffer pool (`ArrayBlockingQueue<ByteBuffer>`)
     - Parallels: `S3WriteContext`
   - `AzureCompletableOutputStream` -- Block-based upload: stage blocks → commit block list
     - Parallels: `S3CompletableOutputStream`
     - Key difference: block IDs are Base64-encoded zero-padded integers (Azure requires uniform-length IDs); no explicit upload ID or abort needed; max 50,000 blocks (vs S3's 10,000 parts)

8. **Provider and plugin**
   - `AzureSeekableChannelProvider` -- Implements `SeekableChannelsProvider`
     - Parallels: `S3SeekableChannelProvider`
     - `exists()` via `BlobAsyncClient.getProperties()` (HEAD equivalent)
     - `list()` via `ContainerAsyncClient.listBlobsByHierarchy()`
     - `walk()` via `ContainerAsyncClient.listBlobs()`
     - File size cache with `SoftReference` (same pattern as S3)
   - `AzureDelegateProvider` -- Translates between Azure URI schemes (normalize to `abfss` internally)
     - Parallels: `S3DelegateProvider`
   - `UniversalAzureProvider` -- Multi-scheme dispatcher
     - Parallels: `UniversalS3Provider`
   - `AzureSeekableChannelProviderPlugin` -- `@AutoService(SeekableChannelsProviderPlugin.class)`, handles all Azure schemes
     - Parallels: `UniversalS3SeekableChannelProviderPlugin`

9. **Tests with Azurite**
   - Create Docker registry entry for Azurite (`docker/registry/azurite`)
   - `AzureSeekableChannelProviderTest` -- read/write round-trip with Azurite
   - `AzureInstructionsTest` -- validation tests
   - `AzureCredentialsTest` -- credential construction tests
   - `testOutOfBand` Gradle task for Testcontainer-based tests

#### Phase 2: Pluggable Property Injection (`extensions/iceberg/`)

10. **PropertyInjector SPI**
    - Create `PropertyInjector` interface in `io.deephaven.iceberg.util` with `inject(Map<String, String>)` method
    - Refactor `InjectAWSProperties` to implement `PropertyInjector`, register via `@AutoService`
    - Update `IcebergTools.injectDeephavenProperties()` to iterate `ServiceLoader.load(PropertyInjector.class)`
    - Verify all existing S3/Iceberg tests pass unchanged

#### Phase 3: Iceberg-Azure Bridge (`extensions/iceberg/azure/`)

11. **Build setup**
    - Create `extensions/iceberg/azure/build.gradle` following `extensions/iceberg/s3/build.gradle` pattern
    - Dependencies: `extensions-iceberg`, `extensions-azure`, `iceberg-azure`, `azure-storage-blob`, `azure-identity`
    - Register in `settings.gradle`

12. **Instructions factory**
    - `AzureInstructionsBasedClientFactory` -- Stores `AzureInstructions` in static `ConcurrentHashMap` keyed by UUID, injects into catalog properties, provides retrieval and cleanup
      - Parallels: `S3InstructionsBasedAwsClientFactory`

13. **Instructions provider plugin**
    - `AzureInstructionsProviderPlugin` -- `@AutoService(DataInstructionsProviderPlugin.class)`, creates `AzureInstructions` from Iceberg's `ADLSProperties` or from `AzureInstructionsBasedClientFactory`-registered instructions
      - Parallels: `S3InstructionsProviderPlugin`

14. **FileIO adapters**
    - `ADLSFallbackFileIOAdapter` -- `@AutoService(FileIOAdapter.class)`, creates `AzureSeekableChannelProvider` from instructions for any Azure scheme (primary adapter)
      - Parallels: `S3FallbackFileIOAdapter`
    - `ADLSFileIOAdapter` -- If `ADLSFileIO` exposes its client, reuse it; otherwise skip this class
      - Parallels: `S3FileIOAdapter`

15. **Property injection**
    - `InjectAzureProperties` -- `@AutoService(PropertyInjector.class)`, injects Azure-specific defaults when Azure properties or Azure URI schemes are detected in catalog properties
      - Parallels: `InjectAWSProperties`

16. **Convenience API**
    - `IcebergToolsAzure` -- `createAdapter(BuildCatalogOptions, AzureInstructions)` with phantom cleanup registration
      - Parallels: `IcebergToolsS3`

17. **Integration tests with Azurite + Iceberg**
    - Iceberg catalog backed by Azure storage via Azurite
    - Test read/write round-trip through Iceberg table API
    - `testOutOfBand` Gradle task

### Delivery Plan

#### Target

Community repository (`deephaven-core`), targeting the next minor release.

#### Customer Risks

None for existing customers -- this is additive. Azure support is a new module with no changes to S3 behavior (Phase 2 refactors `InjectAWSProperties` but preserves exact behavior).

#### Documentation

- API documentation (Javadoc) on `AzureInstructions`, `AzureCredentials`, `IcebergToolsAzure`
- User guide examples showing:
  - Reading a Parquet file from Azure Blob Storage
  - Writing a Parquet file to Azure Blob Storage
  - Connecting to an Iceberg REST catalog backed by Azure storage
- Update existing Iceberg documentation to mention Azure as a supported backend

#### Testing

##### Automated Tests

- `AzureInstructionsTest` -- validation bounds checking
- `AzureCredentialsTest` -- credential factory methods
- `AzureUriTest` -- URI parsing for all four schemes, edge cases
- `AzureSeekableChannelProviderTest` -- read/write/list/walk with Azurite (testcontainers)
- `AzureCompletableOutputStreamTest` -- block upload lifecycle, abort on error
- `IcebergAzuriteTest` -- end-to-end Iceberg catalog with Azurite
- `PropertyInjectorTest` -- verify SPI-based injection, verify AWS behavior unchanged

##### Manual Tests

1. Read a Parquet file from a real Azure Blob Storage account using `abfss://` URI
2. Write a Parquet file to Azure Blob Storage and read it back
3. Connect to an Iceberg REST catalog with Azure-backed warehouse, browse tables, read data
4. Verify that existing S3 functionality is unaffected
5. Test with different credential types: shared key, SAS token, DefaultAzureCredential

## Research Appendix

### Azure Blob Storage vs. S3 Concept Mapping

| Concept | S3 | Azure Blob Storage |
|---------|----|--------------------|
| Top-level namespace | Bucket | Container (within Storage Account) |
| Object | Object (key) | Blob (blob name) |
| URI authority | `bucket` as host | `container@account.suffix` |
| URI schemes | `s3://`, `s3a://`, `s3n://` | `abfs://`, `abfss://`, `wasb://`, `wasbs://` |
| Multi-part write | CreateMultipartUpload / UploadPart / Complete | StageBlock / CommitBlockList |
| Max parts/blocks | 10,000 | 50,000 |
| Min part/block size | 5 MiB | No minimum |
| Range read | GetObject with Range header | Download with BlobRange |
| HEAD equivalent | HeadObject | GetBlobProperties |
| List | ListObjectsV2 | ListBlobs / ListBlobsByHierarchy |
| Async SDK | `S3AsyncClient` (CompletableFuture) | `BlobAsyncClient` (Reactor Mono/Flux) |
| Iceberg FileIO | `S3FileIO` (iceberg-aws) | `ADLSFileIO` (iceberg-azure) |
| Local emulator | LocalStack, MinIO | Azurite |

### Azure SDK Dependencies

The following Azure SDK libraries are needed:
- `com.azure:azure-storage-blob` -- BlobServiceClient, BlobContainerClient, BlobClient, BlockBlobClient
- `com.azure:azure-identity` -- DefaultAzureCredential, ClientSecretCredential, ManagedIdentityCredential
- `org.apache.iceberg:iceberg-azure` -- ADLSFileIO, ADLSProperties (managed by iceberg BOM 1.10.1)

### Key S3 Files to Use as Templates

| Azure class | S3 template | Path |
|-------------|-------------|------|
| `AzureSeekableChannelProvider` | `S3SeekableChannelProvider` | `extensions/s3/src/main/java/.../S3SeekableChannelProvider.java` |
| `AzureSeekableByteChannel` | `S3SeekableByteChannel` | `extensions/s3/src/main/java/.../S3SeekableByteChannel.java` |
| `AzureReadContext` | `S3ReadContext` | `extensions/s3/src/main/java/.../S3ReadContext.java` |
| `AzureReadRequest` | `S3ReadRequest` | `extensions/s3/src/main/java/.../S3ReadRequest.java` |
| `AzureCompletableOutputStream` | `S3CompletableOutputStream` | `extensions/s3/src/main/java/.../S3CompletableOutputStream.java` |
| `AzureInstructions` | `S3Instructions` | `extensions/s3/src/main/java/.../S3Instructions.java` |
| `AzureCredentials` | `Credentials` | `extensions/s3/src/main/java/.../Credentials.java` |
| `AzureBlobClientFactory` | `S3ClientFactory` | `extensions/s3/src/main/java/.../S3ClientFactory.java` |
| `AzureSeekableChannelProviderPlugin` | `UniversalS3SeekableChannelProviderPlugin` | `extensions/s3/src/main/java/.../UniversalS3SeekableChannelProviderPlugin.java` |
| `ADLSFallbackFileIOAdapter` | `S3FallbackFileIOAdapter` | `extensions/iceberg/s3/src/main/java/.../S3FallbackFileIOAdapter.java` |
| `AzureInstructionsProviderPlugin` | `S3InstructionsProviderPlugin` | `extensions/iceberg/s3/src/main/java/.../S3InstructionsProviderPlugin.java` |
| `AzureInstructionsBasedClientFactory` | `S3InstructionsBasedAwsClientFactory` | `extensions/iceberg/s3/src/main/java/.../S3InstructionsBasedAwsClientFactory.java` |
| `IcebergToolsAzure` | `IcebergToolsS3` | `extensions/iceberg/s3/src/main/java/.../IcebergToolsS3.java` |
| `InjectAzureProperties` | `InjectAWSProperties` | `extensions/iceberg/src/main/java/.../InjectAWSProperties.java` |
