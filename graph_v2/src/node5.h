#pragma once

#include "node.h"

namespace tng_v2 {

class Node5 : public Node {
public:
    Node5(const std::string& name) : Node(name) {}

    void run() override {
        std::cout << "Node5 run" << std::endl;
        for (size_t i = 0; i < m_inputFutures.size(); ++i) {
            m_inputFutures[i].wait();
        }
        std::cout << "Node5 wait succ" << std::endl;

        // something
        std::shared_ptr<Node5OutputData> output = DataCenter::getInstane()->node5OutputData;
        output.reset(new Node5OutputData);
        output->x = 0;
        for (size_t i = 0; i < m_inputFutures.size(); ++i) {
            std::string name = m_inputFutures[i].get();
            if (name == "Node2") {
                const std::shared_ptr<Node2OutputData>& input = DataCenter::getInstane()->node2OutputData;
                if (input) {
                    output->x += input->x + 5;
                    std::cout << "Node5 | Node2 x: " << output->x << " <- " << input->x << " + " << 5 << std::endl;
                } else {
                    std::cout << "Node5 | node2 input is nullptr" << std::endl;
                }
            } else if (name == "Node3") {
                const std::shared_ptr<Node3OutputData>& input = DataCenter::getInstane()->node3OutputData;
                if (input) {
                    output->x += input->x + 5;
                    std::cout << "Node5 | Node3 x: " << output->x << " <- " << input->x << " + " << 5 << std::endl;
                } else {
                    std::cout << "Node5 | node3 input is nullptr" << std::endl;
                }
            } else if (name == "Node4") {
                const std::shared_ptr<Node4OutputData>& input = DataCenter::getInstane()->node4OutputData;
                if (input) {
                output->x += input->x + 5;
                std::cout << "Node5 | Node4 x: " << output->x << " <- " << input->x << " + " << 5 << std::endl;
                } else {
                    std::cout << "Node5 | node4 input is nullptr" << std::endl;
                }
            } else {
                std::cout << "Node5 dose not support " << name << std::endl;
            }
        }

        std::shared_ptr<GraphOutputData>& graphOutput = DataCenter::getInstane()->graphOutputData;
        graphOutput.reset(new GraphOutputData);
        graphOutput->gdc = output->x;
        std::cout << "Node5 graphOutput: " << graphOutput->gdc << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        m_outputPromise.set_value(m_name);
    }
};

}  // namespace tng_v2
