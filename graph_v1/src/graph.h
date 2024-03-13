#pragma once

#include <vector>
#include <string>
#include <future>
#include <memory>
#include <unordered_map>
#include <thread>

#include "node.h"

namespace tng {

struct GraphInputData {
    int gda;
    int gdb;
};

struct GraphOutputData {
    int gdc;
};

class Graph {
public:
    Graph();
    void setGraphInputData(const GraphInputData& graphInputData);
    GraphOutputData getGraphOutputData();
    bool buildGraph();
    void run();
 
private:
    std::unique_ptr<Node> createNode(const std::string& depString);
    bool findNotCreatedNodes(std::vector<std::string>& c);
    std::shared_future<std::shared_ptr<DataCenter>> getEndNodeData();

    /**
     * @brief Set the Config
     * 
     * @param config fromat: {"node:dependent node:dependent node", "node:dependent node:dependent node"}
     * @return true 解析config成功
     * @return false 
     */
    bool setConfig(const std::vector<std::string>& config);

    /**
     * @brief 根据指定字符切分字符串，可以根据分隔符将字符传切分为多个子字符串
     * 
     * @param [in] depString 待切分的字符串
     * @param [in] token 分隔符
     * @param [out] stringList 切分后的字符串列表
     * @return 切分是否成功
     */
    bool splitString(std::string depString, const std::string& token,
                     std::vector<std::string>& stringList);

private:
    std::unordered_map<std::string, std::unique_ptr<Node>> m_nodes;
    std::shared_ptr<DataCenter> m_dataCenter;
    GraphInputData m_graphInputData;

    std::vector<std::vector<std::string>> m_config;
    std::vector<std::thread> m_thread;
};

}  // namespace tng
