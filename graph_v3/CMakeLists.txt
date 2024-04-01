include_directories(./ src)

file(GLOB_RECURSE SRC "src/*.cpp" )
message(STATUS "graph_v3 source files: ${SRC}")
add_library(graph_v3 SHARED ${SRC})

add_executable(main_graph_v3 main.cpp)
target_link_libraries(main_graph_v3 graph_v3)