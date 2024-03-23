#include "graph.h"

#include <iostream>

int main() {
    tng::Graph graph;
    std::cout << "hello tiny-graph" << std::endl;

    std::shared_ptr<tng::GraphInputData> inputData(new tng::GraphInputData);
    inputData->gda = 1;
    inputData->gdb = 2;

    std::vector<std::vector<std::string>> config = {
        {"Node1"},
        {"Node2", "Node1"},
        {"Node3", "Node1"},
        {"Node4", "Node1"},
        {"Node5", "Node2", "Node3", "Node4"}
    };

    graph.setGraphInputData(inputData);
    graph.buildGraph(config);
    graph.run();
    std::shared_ptr<tng::GraphOutputData> outputData = graph.getGraphOutputData();
    if (outputData) {
        std::cout << "graph outputData: " << outputData->gdc << std::endl;
    } else {
        std::cout << "graph outputData is nullptr" << std::endl;
    }
    return 0;
}

