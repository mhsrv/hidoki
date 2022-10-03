cmake_minimum_required(VERSION 3.22)
project(hidoki)

add_executable(test test.cpp)
target_link_libraries(test PUBLIC hidoki)