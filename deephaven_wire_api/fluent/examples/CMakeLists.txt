cmake_minimum_required(VERSION 3.16)
project(examples)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Werror)

find_package(Boost 1.71 REQUIRED)
FIND_PACKAGE(Arrow REQUIRED PATHS /home/kosak/arrowlocal/usr/local/lib/cmake/arrow)
FIND_PACKAGE(ArrowFlight REQUIRED PATHS /home/kosak/arrowlocal/usr/local/lib/cmake/arrow)
FIND_PACKAGE(gRPC REQUIRED)
FIND_PACKAGE(Protobuf REQUIRED)
find_package(Threads REQUIRED)

add_executable(examples
        add_drop_example.cc
        add_drop_example.h
        aggregates_example.cc
        aggregates_example.h
        date_time_filter_example.cc
        date_time_filter_example.h
        drop_columns_example.cc
        drop_columns_example.h
        get_data_example.cc
        get_data_example.h
        head_and_tail_example.cc
        head_and_tail_example.h
        filter_example.cc
        filter_example.h
        join_example.cc
        join_example.h
        lastby_example.cc
        lastby_example.h
        main.cc
        merge_tables_example.cc
        merge_tables_example.h
        new_table_example.cc
        new_table_example.h
        select_example.cc
        select_example.h
        snapshot_example.cc
        snapshot_example.h
        sort_example.cc
        sort_example.h
        string_filter_example.cc
        string_filter_example.h
        table_cleanup_example.cc
        table_cleanup_example.h
        table_snapshot_example.cc
        table_snapshot_example.h
        time_table_example.cc
        time_table_example.h
        ungroup_example.cc
        ungroup_example.h
        validation_example.cc
        validation_example.h
        view_example.cc
        view_example.h
        )
target_include_directories(examples PUBLIC "..")
target_include_directories(examples BEFORE PUBLIC ${Boost_INCLUDE_DIRS})
include_directories("../openapi")

add_subdirectory("../openapi" "libopenapi")
target_link_libraries(examples openapi)
target_link_libraries(examples arrow_flight_static)
target_link_libraries(examples arrow_static)
target_link_libraries(examples protobuf)
target_link_libraries(examples gRPC::grpc++)
# target_link_libraries(examples OpenSSL::SSL)
target_link_libraries(examples Threads::Threads)
