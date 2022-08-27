cmake_minimum_required(VERSION 3.22)
project(PAFa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include(FetchContent)

find_package(biosoup 0.10.0 QUIET)
find_package(thread_pool 4.0.0 QUIET)
find_package(bioparser 3.0.13 QUIET)

if (NOT biosoup_FOUND)
    if (ram_install)
        message(FATAL_ERROR "Missing package biosoup!")
    endif ()

    FetchContent_Declare(
            biosoup
            GIT_REPOSITORY https://github.com/rvaser/biosoup
            GIT_TAG 0.10.0)

    FetchContent_GetProperties(biosoup)
    if (NOT biosoup_POPULATED)
        FetchContent_Populate(biosoup)
        add_subdirectory(
                ${biosoup_SOURCE_DIR}
                ${biosoup_BINARY_DIR}
                EXCLUDE_FROM_ALL)
    endif ()
endif ()

if (NOT thread_pool_FOUND)
    if (ram_install)
        message(FATAL_ERROR "Missing package thread_pool!")
    endif ()

    FetchContent_Declare(
            thread_pool
            GIT_REPOSITORY https://github.com/rvaser/thread_pool
            GIT_TAG 4.0.0)

    FetchContent_GetProperties(thread_pool)
    if (NOT thread_pool_POPULATED)
        FetchContent_Populate(thread_pool)
        add_subdirectory(
                ${thread_pool_SOURCE_DIR}
                ${thread_pool_BINARY_DIR}
                EXCLUDE_FROM_ALL)
    endif ()
endif ()

if (NOT bioparser_FOUND)
    FetchContent_Declare(
            bioparser
            GIT_REPOSITORY https://github.com/rvaser/bioparser
            GIT_TAG 3.0.13)

    FetchContent_GetProperties(bioparser)
    if (NOT bioparser_POPULATED)
        FetchContent_Populate(bioparser)
        add_subdirectory(
                ${bioparser_SOURCE_DIR}
                ${bioparser_BINARY_DIR}
                EXCLUDE_FROM_ALL)
    endif ()
endif ()

file(GLOB_RECURSE srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/**.cpp")
file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "include/**.h")
add_library(PAFa ${srcs} ${headers})
target_link_libraries(PAFa bioparser biosoup)

add_executable(PAFa_exe src/main.cpp)
target_link_libraries(PAFa_exe
        PAFa)
