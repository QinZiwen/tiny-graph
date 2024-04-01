#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "data_center.h"
#include "node.h"

namespace tng_v2 {

class Graph {
public:
    void setGraphInputData(std::shared_ptr<GraphInputData> graphInputData);
    std::shared_ptr<GraphOutputData> getGraphOutputData();
    /**
     * @brief Construct a graph based on config
     * 
     * @param config Config format: {{"Node1"},{"Node2","Node1"},{"Node3","Node2"，"Node1"}}, 
     *               Node1 does not depend on other nodes
     *               Node2 depends on Node1
     *               Node3 depends on Node2 and Node1
     * @return true 
     * @return false 
     */
    bool buildGraph(std::vector<std::vector<std::string>> config);
    void run();

private:
    /**
     * @brief Have all dependent nodes been constructed
     * 
     * @param names Except for the first one, everything else depends on the name of the node
     * @return true satisfied
     * @return false 
     */
    bool allDependenciesSatisfied(const std::vector<std::string>& names);

    /**
     * @brief Get the names of Node dependent
     * 
     * @param config All dependencies
     * @param nodeDeps The names of Node dependent
     * @return true Successfully obtained the name of the dependent node
     * @return false 
     */
    bool getNodeDeps(const std::vector<std::vector<std::string>>& config, std::vector<std::string>& nodeDeps);

    /**
     * @brief Find the name of the output node
     * 
     * @param config All dependencies
     * @return std::string 
     */
    std::string findEndNodeName(const std::vector<std::vector<std::string>>& config);

    /**
     * @brief Randomly shuffle config
     * 
     * @param config 
     */
    void shuffleConfig(std::vector<std::vector<std::string>>& config);

    /**
     * @brief Check if config is a directed acyclic graph
     * 
     * @param config 
     * @return true 
     * @return false 
     */
    bool checkConfig(const std::vector<std::vector<std::string>>& config);

    /**
     * @brief Deep first search to check if config is a directed acyclic graph
     * 
     * @param config 
     * @param nodeName Nodes to be accessed soon
     * @param visitedNodes Nodes that have already been visited
     * @return true 
     * @return false 
     */
    bool visitConfigDFS(const std::vector<std::vector<std::string>>& config,
        const std::string& nodeName,
        std::unordered_set<std::string>& visitedNodes);

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> m_nodes;
    std::shared_future<std::string> m_graphOutputFuture;
};

}  // namespace tng_v2