//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
package io.deephaven.auth.codegen.impl;

import io.deephaven.auth.AuthContext;
import io.deephaven.auth.ServiceAuthWiring;
import io.deephaven.proto.backplane.grpc.CreateDirectoryRequest;
import io.deephaven.proto.backplane.grpc.DeleteItemRequest;
import io.deephaven.proto.backplane.grpc.FetchFileRequest;
import io.deephaven.proto.backplane.grpc.ListItemsRequest;
import io.deephaven.proto.backplane.grpc.MoveItemRequest;
import io.deephaven.proto.backplane.grpc.SaveFileRequest;
import io.deephaven.proto.backplane.grpc.StorageServiceGrpc;
import io.grpc.ServerServiceDefinition;

/**
 * This interface provides type-safe authorization hooks for StorageServiceGrpc.
 */
public interface StorageServiceAuthWiring extends ServiceAuthWiring<StorageServiceGrpc.StorageServiceImplBase> {
    /**
     * Wrap the real implementation with authorization checks.
     *
     * @param delegate the real service implementation
     * @return the wrapped service implementation
     */
    default ServerServiceDefinition intercept(StorageServiceGrpc.StorageServiceImplBase delegate) {
        final ServerServiceDefinition service = delegate.bindService();
        final ServerServiceDefinition.Builder serviceBuilder =
                ServerServiceDefinition.builder(service.getServiceDescriptor());

        serviceBuilder.addMethod(ServiceAuthWiring.intercept(
                service, "ListItems", null, this::onMessageReceivedListItems));
        serviceBuilder.addMethod(ServiceAuthWiring.intercept(
                service, "FetchFile", null, this::onMessageReceivedFetchFile));
        serviceBuilder.addMethod(ServiceAuthWiring.intercept(
                service, "SaveFile", null, this::onMessageReceivedSaveFile));
        serviceBuilder.addMethod(ServiceAuthWiring.intercept(
                service, "MoveItem", null, this::onMessageReceivedMoveItem));
        serviceBuilder.addMethod(ServiceAuthWiring.intercept(
                service, "CreateDirectory", null, this::onMessageReceivedCreateDirectory));
        serviceBuilder.addMethod(ServiceAuthWiring.intercept(
                service, "DeleteItem", null, this::onMessageReceivedDeleteItem));

        return serviceBuilder.build();
    }

    /**
     * Authorize a request to ListItems.
     *
     * @param authContext the authentication context of the request
     * @param request the request to authorize
     * @throws io.grpc.StatusRuntimeException if the user is not authorized to invoke ListItems
     */
    void onMessageReceivedListItems(AuthContext authContext, ListItemsRequest request);

    /**
     * Authorize a request to FetchFile.
     *
     * @param authContext the authentication context of the request
     * @param request the request to authorize
     * @throws io.grpc.StatusRuntimeException if the user is not authorized to invoke FetchFile
     */
    void onMessageReceivedFetchFile(AuthContext authContext, FetchFileRequest request);

    /**
     * Authorize a request to SaveFile.
     *
     * @param authContext the authentication context of the request
     * @param request the request to authorize
     * @throws io.grpc.StatusRuntimeException if the user is not authorized to invoke SaveFile
     */
    void onMessageReceivedSaveFile(AuthContext authContext, SaveFileRequest request);

    /**
     * Authorize a request to MoveItem.
     *
     * @param authContext the authentication context of the request
     * @param request the request to authorize
     * @throws io.grpc.StatusRuntimeException if the user is not authorized to invoke MoveItem
     */
    void onMessageReceivedMoveItem(AuthContext authContext, MoveItemRequest request);

    /**
     * Authorize a request to CreateDirectory.
     *
     * @param authContext the authentication context of the request
     * @param request the request to authorize
     * @throws io.grpc.StatusRuntimeException if the user is not authorized to invoke CreateDirectory
     */
    void onMessageReceivedCreateDirectory(AuthContext authContext, CreateDirectoryRequest request);

    /**
     * Authorize a request to DeleteItem.
     *
     * @param authContext the authentication context of the request
     * @param request the request to authorize
     * @throws io.grpc.StatusRuntimeException if the user is not authorized to invoke DeleteItem
     */
    void onMessageReceivedDeleteItem(AuthContext authContext, DeleteItemRequest request);

    class AllowAll implements StorageServiceAuthWiring {
        public void onMessageReceivedListItems(AuthContext authContext, ListItemsRequest request) {}

        public void onMessageReceivedFetchFile(AuthContext authContext, FetchFileRequest request) {}

        public void onMessageReceivedSaveFile(AuthContext authContext, SaveFileRequest request) {}

        public void onMessageReceivedMoveItem(AuthContext authContext, MoveItemRequest request) {}

        public void onMessageReceivedCreateDirectory(AuthContext authContext,
                CreateDirectoryRequest request) {}

        public void onMessageReceivedDeleteItem(AuthContext authContext, DeleteItemRequest request) {}
    }

    class DenyAll implements StorageServiceAuthWiring {
        public void onMessageReceivedListItems(AuthContext authContext, ListItemsRequest request) {
            ServiceAuthWiring.operationNotAllowed();
        }

        public void onMessageReceivedFetchFile(AuthContext authContext, FetchFileRequest request) {
            ServiceAuthWiring.operationNotAllowed();
        }

        public void onMessageReceivedSaveFile(AuthContext authContext, SaveFileRequest request) {
            ServiceAuthWiring.operationNotAllowed();
        }

        public void onMessageReceivedMoveItem(AuthContext authContext, MoveItemRequest request) {
            ServiceAuthWiring.operationNotAllowed();
        }

        public void onMessageReceivedCreateDirectory(AuthContext authContext,
                CreateDirectoryRequest request) {
            ServiceAuthWiring.operationNotAllowed();
        }

        public void onMessageReceivedDeleteItem(AuthContext authContext, DeleteItemRequest request) {
            ServiceAuthWiring.operationNotAllowed();
        }
    }

    class TestUseOnly implements StorageServiceAuthWiring {
        public StorageServiceAuthWiring delegate;

        public void onMessageReceivedListItems(AuthContext authContext, ListItemsRequest request) {
            if (delegate != null) {
                delegate.onMessageReceivedListItems(authContext, request);
            }
        }

        public void onMessageReceivedFetchFile(AuthContext authContext, FetchFileRequest request) {
            if (delegate != null) {
                delegate.onMessageReceivedFetchFile(authContext, request);
            }
        }

        public void onMessageReceivedSaveFile(AuthContext authContext, SaveFileRequest request) {
            if (delegate != null) {
                delegate.onMessageReceivedSaveFile(authContext, request);
            }
        }

        public void onMessageReceivedMoveItem(AuthContext authContext, MoveItemRequest request) {
            if (delegate != null) {
                delegate.onMessageReceivedMoveItem(authContext, request);
            }
        }

        public void onMessageReceivedCreateDirectory(AuthContext authContext,
                CreateDirectoryRequest request) {
            if (delegate != null) {
                delegate.onMessageReceivedCreateDirectory(authContext, request);
            }
        }

        public void onMessageReceivedDeleteItem(AuthContext authContext, DeleteItemRequest request) {
            if (delegate != null) {
                delegate.onMessageReceivedDeleteItem(authContext, request);
            }
        }
    }
}
