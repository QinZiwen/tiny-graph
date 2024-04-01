#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "message.h"
#include "node.h"

namespace tng_v3 {

class Graph {
public:
    Graph();
    void setGraphInputData(std::shared_ptr<GraphInputData> graphInputData);
    std::shared_ptr<GraphOutputData> getGraphOutputData();
    
    /**
     * @brief Construct a graph based on config
     * 
     * @param config Config format: {"Node1", "Node2", "Node3"}. we will run Node1, Node2, Node3
     * @return true 
     * @return false 
     */
    bool buildGraph(const std::vector<std::string>& config);
    
    void run();

private:
    std::shared_ptr<GraphInputData> m_graphInputData;
    std::shared_ptr<GraphOutputData> m_graphOutputData;
    std::unordered_map<std::string, std::shared_ptr<Node>> m_nodes;
    std::shared_ptr<Conduit> m_conduit;
};

}  // namespace tng_v3