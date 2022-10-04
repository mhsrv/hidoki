cmake_minimum_required(VERSION 3.22)
project(hidoki)

add_library(hidoki_base INTERFACE)
target_link_libraries(hidoki_base INTERFACE async utils)
target_include_directories(hidoki_base INTERFACE lib)

add_library(hidoki_host STATIC lib/scope.h src/scope.cpp lib/host_service_container.h src/host_service_container.cpp lib/host.h src/host.cpp)
target_link_libraries(hidoki_host PUBLIC hidoki_base)

add_library(hidoki SHARED lib/interface/example.h lib/example_service.h src/example_service.cpp)
target_link_libraries(hidoki PUBLIC hidoki_base hidoki_host)