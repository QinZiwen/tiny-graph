#pragma once

#include "node.h"

namespace tng_v2 {

class Node3 : public Node {
public:
    Node3(const std::string& name) : Node(name) {}

    void run() override {
        std::cout << "Node3 run" << std::endl;
        for (size_t i = 0; i < m_inputFutures.size(); ++i) {
            m_inputFutures[i].wait();
        }
        std::cout << "Node3 wait succ" << std::endl;

        // something
        const std::shared_ptr<Node1OutputData>& input = DataCenter::getInstane()->node1OutputData;
        if (input) {
        std::shared_ptr<Node3OutputData>& output = DataCenter::getInstane()->node3OutputData;
        output.reset(new Node3OutputData);
        output->x = input->x + 3;
        std::cout << "Node3 x: " << output->x << " <- " << input->x << " + " << 3 << std::endl;
        } else {
            std::cout << "Node2 input is nullptr" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        m_outputPromise.set_value(m_name);
    }
};

}  // namespace tng_v2
