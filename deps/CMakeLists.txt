cmake_minimum_required(VERSION 3.22)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/)

include(FetchContent)
FetchContent_Declare(
        io
        GIT_REPOSITORY https://github.com/mhsrv/io
        GIT_TAG master
)
FetchContent_MakeAvailable(io)

FetchContent_Declare(
        utils
        GIT_REPOSITORY https://github.com/mhsrv/utils
        GIT_TAG master
)
FetchContent_MakeAvailable(utils)
