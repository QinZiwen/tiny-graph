cmake_minimum_required(VERSION 3.15)
project(tiny-graph)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE "Debug")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
endif()

add_subdirectory(graph_v1)