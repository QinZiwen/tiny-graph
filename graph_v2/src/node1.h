#pragma once

#include "node.h"

namespace tng_v2 {

class Node1 : public Node {
public:
    Node1(const std::string& name) : Node(name) {}

    void run() override {
        std::cout << "Node1 run" << std::endl;
        for (size_t i = 0; i < m_inputFutures.size(); ++i) {
            m_inputFutures[i].wait();
        }
        std::cout << "Node1 wait succ" << std::endl;

        // something
        const std::shared_ptr<GraphInputData>& input = DataCenter::getInstane()->graphInputData;
        if (input) {
            std::shared_ptr<Node1OutputData>& output = DataCenter::getInstane()->node1OutputData;
            output.reset(new Node1OutputData);
            output->x = input->gda + input->gdb;
            std::cout << "Node1 x: " << output->x << " <- " << input->gda << " + " << input->gdb << std::endl;
        } else {
            std::cout << "Node1 input is nullptr" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        m_outputPromise.set_value(m_name);
    }
};

}  // namespace tng_v2
