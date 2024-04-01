#include "graph.h"

int main() {
    tng_v3::Graph graph;
    std::shared_ptr<tng_v3::GraphInputData> inputData = std::make_shared<tng_v3::GraphInputData>();
    inputData->gda = 1;
    inputData->gdb = 2;
    graph.setGraphInputData(inputData);

    std::vector<std::string> config = {"Node1", "Node2", "Node3", "Node4", "Node5"};
    if (graph.buildGraph(config)) {
        graph.run();
    }
    return 0;
}