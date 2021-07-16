cmake_minimum_required(VERSION 3.16)
project(openapi)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Werror)

find_package(Boost 1.67 REQUIRED)
FIND_PACKAGE(Arrow REQUIRED PATHS /home/kosak/arrowlocal/usr/local/lib/cmake/arrow)
FIND_PACKAGE(ArrowFlight REQUIRED PATHS /home/kosak/arrowlocal/usr/local/lib/cmake/arrow)

set(SRC_FILES
    core/deserializer.cc
    core/deserializer.h
    core/protocol_base_classes.cc
    core/protocol_base_classes.h
    core/serializer.cc
    core/serializer.h
    core/server.cc
    core/server.h
    core/callbacks.h

    lowlevel/custom/custom_shared_objects.cc
    lowlevel/custom/custom_shared_objects.h
    lowlevel/generated/dhserver_notifications.cc
    lowlevel/generated/dhserver_notifications.h
    lowlevel/generated/dhserver_requests.cc
    lowlevel/generated/dhserver_requests.h
    lowlevel/generated/dhworker_notifications.cc
    lowlevel/generated/dhworker_notifications.h
    lowlevel/generated/dhworker_requests.cc
    lowlevel/generated/dhworker_requests.h
    lowlevel/generated/shared_objects.cc
    lowlevel/generated/shared_objects.h
    lowlevel/util/deserializer_adapter.h
    lowlevel/util/serializer_adapter.h
    lowlevel/util/server_callbacks.h
    lowlevel/dhserver.cc
    lowlevel/dhserver.h
    lowlevel/dhworker.cc
    lowlevel/dhworker.h
    lowlevel/dhworker_session.cc
    lowlevel/dhworker_session.h

    highlevel/data/column_data.cc
    highlevel/data/column_data.h
    highlevel/data/column_data_holder.cc
    highlevel/data/column_data_holder.h
    highlevel/data/dbdatetime.cc
    highlevel/data/dbdatetime.h
    highlevel/data/deephaven_constants.cc
    highlevel/data/deephaven_constants.h
    highlevel/impl/boolean_expression_impl.cc
    highlevel/impl/boolean_expression_impl.h
    highlevel/impl/columns_impl.cc
    highlevel/impl/columns_impl.h
    highlevel/impl/datetime_expression_impl.cc
    highlevel/impl/datetime_expression_impl.h
    highlevel/impl/expression_impl.cc
    highlevel/impl/expression_impl.h
    highlevel/impl/numeric_expression_impl.cc
    highlevel/impl/numeric_expression_impl.h
    highlevel/impl/string_expression_impl.cc
    highlevel/impl/string_expression_impl.h
    highlevel/impl/aggregate_impl.cc
    highlevel/impl/aggregate_impl.h
    highlevel/impl/apply_aggregates_operation.cc
    highlevel/impl/apply_aggregates_operation.h
    highlevel/impl/client_impl.cc
    highlevel/impl/client_impl.h
    highlevel/impl/query_scope_impl.cc
    highlevel/impl/query_scope_impl.h
    highlevel/impl/query_table_impl.cc
    highlevel/impl/query_table_impl.h
    highlevel/impl/worker_session_impl.cc
    highlevel/impl/worker_session_impl.h
    highlevel/util/demo_constants.cc
    highlevel/util/demo_constants.h
    highlevel/util/print_utils.cc
    highlevel/util/print_utils.h
    highlevel/columns.cc
    highlevel/columns.h
    highlevel/expressions.cc
    highlevel/expressions.h
    highlevel/openapi.cc
    highlevel/openapi.h

    proto/barrage.grpc.pb.cc
    proto/barrage.grpc.pb.h
    proto/barrage.pb.cc
    proto/barrage.pb.h
    proto/console.grpc.pb.cc
    proto/console.grpc.pb.h
    proto/console.pb.cc
    proto/console.pb.h
        proto/flight.grpc.pb.cc
        proto/flight.grpc.pb.h
        proto/flight.pb.cc
        proto/flight.pb.h
        proto/session.grpc.pb.cc
        proto/session.grpc.pb.h
        proto/session.pb.cc
        proto/session.pb.h
        proto/table.grpc.pb.cc
        proto/table.grpc.pb.h
        proto/table.pb.cc
        proto/table.pb.h

    utility/escape_utils.cc
    utility/escape_utils.h
    utility/executor.cc
    utility/executor.h
    utility/utility.cc
    utility/utility.h
    )

add_library(openapi ${SRC_FILES})
target_link_libraries(openapi arrow_flight_static)
target_link_libraries(openapi arrow_static)
target_include_directories(openapi BEFORE PUBLIC ${Boost_INCLUDE_DIRS})
include_directories(".")
cmake_minimum_required(VERSION 3.16)
