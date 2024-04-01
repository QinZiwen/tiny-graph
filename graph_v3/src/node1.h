#pragma once

#include "node.h"

namespace tng_v3 {

class Node1 : public Node {
public:
    Node1(const std::string& name, std::shared_ptr<Conduit> conduit) : Node(name, conduit) {
        publishTopic("Node1_res");
    }

    ~Node1() = default;

    virtual void run() override {
        std::cout << "Node1 run" << std::endl;
        subscribeTopic("Graph_input");
        
        {
            std::unique_lock lk(m_mtx);
            m_cv.wait(lk);
            m_msg->node1OutputData.x = m_msg->graphInputData.gda + m_msg->graphInputData.gdb;
            std::cout << "Node1 " << m_msg->node1OutputData.x << " <- " << m_msg->graphInputData.gda
                      << " + " << m_msg->graphInputData.gdb << std::endl;
            sendData("Node1_res", m_msg);
        }
    }

    virtual void callback(std::shared_ptr<Message> msg) override {
        std::lock_guard lk(m_mtx);
        m_msg = msg;
        std::cout << "Node1 callback msg topic: " << msg->topic << std::endl;
        m_cv.notify_all();
    }

private:
    std::shared_ptr<Message> m_msg;
};

}  // namespace tng_v3