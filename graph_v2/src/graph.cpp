#include "graph.h"

#include <random>
#include <algorithm>

#include "node_factory.h"

namespace tng {

void Graph::setGraphInputData(std::shared_ptr<GraphInputData> graphInputData) {
    DataCenter::getInstane()->graphInputData = graphInputData;
}

std::shared_ptr<GraphOutputData> Graph::getGraphOutputData() {
    if (m_graphOutputFuture.valid()) {
        m_graphOutputFuture.wait();
        return DataCenter::getInstane()->graphOutputData;
    } else {
        return nullptr;
    }
}

bool Graph::buildGraph(std::vector<std::vector<std::string>> config) {
    // 1. 先构造输入节点； 2. 构造其他节点
    std::promise<std::string> graphInPromise;
    graphInPromise.set_value("graph input");
    std::vector<std::string> nodeDeps;
    while (getNodeDeps(config, nodeDeps)) {
        if (nodeDeps.size() == 1) {
            std::shared_ptr<Node> node = NodeFactory::createNode(nodeDeps[0]);
            if (node) {
                node->setInputFuture(graphInPromise.get_future().share());
                m_nodes[nodeDeps[0]] = node;
            }
        } else {
            if (allDependenciesSatisfied(nodeDeps)) {
                std::shared_ptr<Node> node = NodeFactory::createNode(nodeDeps[0]);
                for (size_t i = 1; i < nodeDeps.size(); ++i) {
                    std::shared_ptr<Node> depNode = m_nodes[nodeDeps[i]];
                    std::shared_future<std::string> depFuture = depNode->getOutputFuture();
                    // std::cout << "depFuture valid: " << depFuture.valid() << std::endl;
                    node->setInputFuture(depFuture);
                }
                m_nodes[nodeDeps[0]] = node;
            } else {
                // 打乱config中元素的顺序
                // std::random_device rd;
                // std::mt19937 g(rd());
                // std::shuffle(config.begin(), config.end(), g);
                shuffleConfig(config);
            }
        }
    }

    std::string endNodeName = findEndNodeName(config);
    if (m_nodes.find(endNodeName) != m_nodes.end()) {
        std::shared_ptr<Node> depNode = m_nodes[endNodeName];
        m_graphOutputFuture = depNode->getOutputFuture();
    }

    return true;
}

bool Graph::allDependenciesSatisfied(const std::vector<std::string>& names) {
    for (size_t i = 1; i < names.size(); ++i) {
        if (m_nodes.find(names[i]) == m_nodes.end()) {
            return false;
        }
    }
    return true;
}

bool Graph::getNodeDeps(const std::vector<std::vector<std::string>>& config, std::vector<std::string>& nodeDeps) {
    for (const auto& deps : config) {
        if (deps.size() > 0) {
            if (m_nodes.find(deps[0]) == m_nodes.end()) {
                nodeDeps.assign(deps.begin(), deps.end());
                return true;
            }
        }
    }

    return false;
}

void Graph::run() {
    std::vector<std::thread> threads;
    for (auto& node : m_nodes) {
        threads.emplace_back(&Node::run, node.second.get());
    }

    for (auto& t : threads) {
        t.join();
    }
}

std::string Graph::findEndNodeName(const std::vector<std::vector<std::string>>& config) {
    for (const auto& deps : config) {
        if (deps.size() > 1) {
            std::string endName = deps[0];
            bool found = false;
            for (const auto& otherDeps : config) {
                if (otherDeps.size() > 1) {
                    for (size_t i = 1; i < otherDeps.size(); ++i) {
                        if (otherDeps[i] == endName) {
                            found = true;
                            break;
                        }
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                return endName;
            }
        }
    }

    return "";
}

void Graph::shuffleConfig(std::vector<std::vector<std::string>>& config) {
    typedef typename std::vector<std::vector<std::string>>::difference_type diff_t;
    typedef std::uniform_int_distribution<diff_t> distr_t;
    typedef typename distr_t::param_type param_t;
 
    distr_t D;
    std::random_device rd;
    std::mt19937 g(rd());
    auto first = config.begin();
    auto last = config.end();
    for (diff_t i = last - first - 1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[D(g, param_t(0, i))]);
    }
}

} // namespace tng