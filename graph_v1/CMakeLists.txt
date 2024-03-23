include_directories(./ src)

file(GLOB_RECURSE SRC "src/*.cpp" )
message(STATUS "graph_v1 source files: ${SRC}")
add_library(graph_v1 SHARED ${SRC})

add_executable(main_graph_v1 main.cpp)
target_link_libraries(main_graph_v1 graph_v1)