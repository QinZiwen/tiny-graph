#pragma once

#include "node.h"

namespace tng {

class Node2 : public Node {
public:
    Node2(const std::string& name) : Node(name) {}

    void run() override {
        std::cout << "Node2 run" << std::endl;
        for (size_t i = 0; i < m_inputFutures.size(); ++i) {
            m_inputFutures[i].wait();
        }
        std::cout << "Node2 wait succ" << std::endl;

        // something
        const std::shared_ptr<Node1OutputData>& input = DataCenter::getInstane()->node1OutputData;
        if (input) {
        std::shared_ptr<Node2OutputData>& output = DataCenter::getInstane()->node2OutputData;
        output.reset(new Node2OutputData);
        output->x = input->x + 2;
        std::cout << "Node2 x: " << output->x << " <- " << input->x << " + " << 2 << std::endl;
        } else {
            std::cout << "Node2 input is nullptr" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        m_outputPromise.set_value(m_name);
    }
};

}  // namespace tng
