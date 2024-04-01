#include "graph.h"

#include <iostream>

int main() {
    tng_v1::Graph graph;
    std::cout << "hello tiny-graph" << std::endl;

    tng_v1::GraphInputData inputData;
    inputData.gda = 1;
    inputData.gdb = 2;

    graph.setGraphInputData(inputData);
    graph.buildGraph();
    graph.run();
    tng_v1::GraphOutputData outputData = graph.getGraphOutputData();
    std::cout << "graph outputData: " << outputData.gdc << std::endl;
    return 0;
}

