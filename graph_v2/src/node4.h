#pragma once

#include "node.h"

namespace tng {

class Node4 : public Node {
public:
    Node4(const std::string& name) : Node(name) {}

    void run() override {
        std::cout << "Node4 run" << std::endl;
        for (size_t i = 0; i < m_inputFutures.size(); ++i) {
            m_inputFutures[i].wait();
        }
        std::cout << "Node4 wait succ" << std::endl;

        // something
        const std::shared_ptr<Node1OutputData>& input = DataCenter::getInstane()->node1OutputData;
        if (input) {
        std::shared_ptr<Node4OutputData>& output = DataCenter::getInstane()->node4OutputData;
        output.reset(new Node4OutputData);
        output->x = input->x + 4;
        std::cout << "Node4 x: " << output->x << " <- " << input->x << " + " << 4 << std::endl;
        } else {
            std::cout << "Node4 input is nullptr" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        m_outputPromise.set_value(m_name);
    }
};

}  // namespace tng
