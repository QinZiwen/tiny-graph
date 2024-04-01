#include "graph.h"

#include <iostream>

#include "node_1.h"
#include "node_2.h"
#include "node_3.h"
#include "node_4.h"

namespace tng_v1 {

Graph::Graph() {
    std::cout << "Graph::Graph ..." << std::endl;
    m_dataCenter = std::shared_ptr<DataCenter>(new DataCenter);

    std::vector<std::string> config = {
        "Node1",
        "Node2:Node1",
        "Node3:Node1",
        "Node4:Node2:Node3"
    };

    setConfig(config);
}

bool Graph::setConfig(const std::vector<std::string>& config) {
    std::cout << "Graph::setConfig ... " << std::endl;

    m_config.clear();
    for (size_t i = 0; i < config.size(); ++i) {
        std::vector<std::string> stringList;
        if (!splitString(config[i], ":", stringList)) {
            std::cerr << "parse config err: " << config[i] << std::endl;
            return false;
        }
        m_config.emplace_back(std::move(stringList));
    }

    return true;
}

bool Graph::buildGraph() {
    std::cout << "Graph::buildGraph ..." << std::endl;

    // 1. 先构造输入节点
    for (const std::vector<std::string>& c : m_config) {
        if (c.size() == 1) {
            std::unique_ptr<Node> node = createNode(c[0]);
            std::promise<std::shared_ptr<DataCenter>> ipr;
            ipr.set_value(m_dataCenter);
            node->setInputData(ipr.get_future().share());
            m_nodes[c[0]] = std::move(node);
        }
    }

    // 2. 构造普通节点
    std::vector<std::string> c;
    while (findNotCreatedNodes(c)) {
        if (c.size() > 1) {
            auto it = m_nodes.find(c[0]);
            if (it == m_nodes.end()) {
                size_t i = 1;
                for (; i < c.size(); ++i) {
                    if (m_nodes.find(c[i]) == m_nodes.end()) {
                        break;
                    }
                }
                
                // 没有找到全部依赖的节点，则不创建这个节点，直到找到所有的依赖节点
                if (i != c.size()) {
                    continue;
                }

                std::unique_ptr<Node> node = createNode(c[0]);
                i = 1;
                for (; i < c.size(); ++i) {
                    auto depNode = m_nodes.find(c[i]);
                    node->setInputData(depNode->second->getOutputData());
                }
                m_nodes[c[0]] = std::move(node);
            }
        } else {
            break;
        }
    }
    return true;
}

std::shared_future<std::shared_ptr<DataCenter>> Graph::getEndNodeData() {
    // 1. 找到最后一个节点
    for (const std::vector<std::string>& c : m_config) {
        if (c.size() > 1) {
            const std::string& endNodeName = c[0];
            bool isEndNode = true;
            for (const std::vector<std::string>& ec : m_config) {
                if (!isEndNode) {
                    break;
                }

                if (ec.size() > 1 && endNodeName != ec[0]) {
                    for (size_t i = 1; i < ec.size(); ++i) {
                        if (ec[i] == endNodeName) {
                            isEndNode = false;
                            break;
                        }
                    }
                }
            }

            if (isEndNode) {
                // 2. 获取DataCenter
                return m_nodes[endNodeName]->getOutputData();
            }
        }
    }

    std::promise<std::shared_ptr<DataCenter>> dc;
    dc.set_value(std::shared_ptr<DataCenter>(new DataCenter));
    return dc.get_future().share();
}

void Graph::run() {
    for (auto& node : m_nodes) {
        m_thread.emplace_back(&Node::run, node.second.get());
    }

    for (auto& t : m_thread) {
        t.join();
    }
}

bool Graph::findNotCreatedNodes(std::vector<std::string>& c) {
    for (const std::vector<std::string>& con : m_config) {
        if (con.size() > 0) {
            if (m_nodes.find(con[0]) == m_nodes.end()) {
                c.assign(con.begin(), con.end());
                return true;
            }
        }
    }
    return false;
}

std::unique_ptr<Node> Graph::createNode(const std::string& depString) {
    std::unique_ptr<Node> node;
    if (depString == "Node1") {
        m_dataCenter->node1InputData = std::shared_ptr<Node1InputData>(new Node1InputData);
        m_dataCenter->node1InputData->a = m_graphInputData.gda;
        m_dataCenter->node1InputData->b = m_graphInputData.gdb;
        node = std::make_unique<Node1>();
    } else if (depString == "Node2") {
        node = std::make_unique<Node2>();
    } else if (depString == "Node3") {
        node = std::make_unique<Node3>();
    } else if (depString == "Node4") {
        node = std::make_unique<Node4>();
    }
    return node;
}

bool Graph::splitString(std::string depString, const std::string& token,
                  std::vector<std::string>& stringList) {
    for (std::string::size_type pos = depString.find(token);
            pos != std::string::npos;
            pos = depString.find(token)) {
        stringList.emplace_back(depString.substr(0, pos));
        depString = depString.substr(pos + 1);
    }

    if (!depString.empty()) {
        stringList.emplace_back(depString);
        // log
        std::cout << "[splitString]:";
        for (const auto& str : stringList) {
            std::cout << " " << str;
        }
        std::cout << std::endl;
        return true;
    } else {
        return false;
    }
}

void Graph::setGraphInputData(const GraphInputData& graphInputData) {
    std::cout << "Graph::setGraphInputData ..." << std::endl;
    m_graphInputData = graphInputData;
}

GraphOutputData Graph::getGraphOutputData() {
    std::shared_future<std::shared_ptr<DataCenter>> endNodeOutputData = getEndNodeData();
    GraphOutputData graphOutputData;
    if (endNodeOutputData.valid()) {
        endNodeOutputData.wait();
        std::shared_ptr<DataCenter> dataCenter = endNodeOutputData.get();
        graphOutputData.gdc = dataCenter->node4OutputData->f;
    }
    return graphOutputData;
}

}  // namespace tng_v1