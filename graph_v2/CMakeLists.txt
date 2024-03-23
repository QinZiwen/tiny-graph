include_directories(./ src)

file(GLOB_RECURSE SRC "src/*.cpp" )
message(STATUS "graph_v2 source files: ${SRC}")
add_library(graph_v2 SHARED ${SRC})

add_executable(main_graph_v2 main.cpp)
target_link_libraries(main_graph_v2 graph_v2)