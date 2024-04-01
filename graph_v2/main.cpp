#include "graph.h"

#include <iostream>

int main() {
    tng_v2::Graph graph;
    std::cout << "hello tiny-graph" << std::endl;

    std::vector<std::vector<std::string>> config = {
        {"Node1"},
        {"Node2", "Node1"},
        {"Node3", "Node1"},
        {"Node4", "Node1"},
        {"Node5", "Node2", "Node3", "Node4"}
    };

    if (graph.buildGraph(config)) {
        std::shared_ptr<tng_v2::GraphInputData> inputData(new tng_v2::GraphInputData);
        inputData->gda = 1;
        inputData->gdb = 2;
        
        graph.setGraphInputData(inputData);
        graph.run();
        std::shared_ptr<tng_v2::GraphOutputData> outputData = graph.getGraphOutputData();
        if (outputData) {
            std::cout << "graph outputData: " << outputData->gdc << std::endl;
        } else {
            std::cout << "graph outputData is nullptr" << std::endl;
        }
    }
    return 0;
}

