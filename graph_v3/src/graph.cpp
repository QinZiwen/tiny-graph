#include "graph.h"

#include "node_factory.h"

namespace tng_v3 {

Graph::Graph() {
    m_conduit.reset(new Conduit);
}

void Graph::setGraphInputData(std::shared_ptr<GraphInputData> graphInputData) {
    m_graphInputData = graphInputData;
}

std::shared_ptr<GraphOutputData> Graph::getGraphOutputData() {
    return m_graphOutputData;
}

bool Graph::buildGraph(const std::vector<std::string>& config) {
    std::cout << "[Graph::buildGraph] config size: " << config.size() << std::endl;
    for (const auto& cfg : config) {
        std::cout << "[Graph::buildGraph] cfg: " << cfg << std::endl;
        std::shared_ptr<Node> node= NodeFactory::createNode(cfg, m_conduit);
        if (node) {
            m_nodes[cfg] = node;
        }
    }
    return true;
}
    
void Graph::run() {
    m_conduit->publishTopic("Graph_input");

    std::vector<std::thread> threads;
    for (auto& node : m_nodes) {
        std::cout << "[Graph::run] name: " << node.first << std::endl;
        threads.emplace_back(&Node::run, node.second.get());
    }

    for (size_t i = 0; i < threads.size();) {
        if (threads[i].joinable()) {
            std::cout << "[Graph::run] joinable: " << i << std::endl;
            ++i;
        } else {
            std::cout << "[Graph::run] thread sleep: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::shared_ptr<Message> msg(new Message);
    msg->graphInputData = *m_graphInputData;
    m_conduit->sendData("Graph_input", msg);

    for (auto& t : threads) {
        t.join();
    }
}

}  // namespace tng_v3