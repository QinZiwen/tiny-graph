#pragma once

#include "node.h"

namespace tng_v3 {

class Node4 : public Node {
public:
    Node4(const std::string& name, std::shared_ptr<Conduit> conduit) : Node(name, conduit) {
        publishTopic("Node4_res");
    }

    ~Node4() = default;

    virtual void run() override {
        std::cout << "Node4 run" << std::endl;
        subscribeTopic("Node1_res");
        
        {
            std::unique_lock lk(m_mtx);
            m_cv.wait(lk);
            m_msg->node4OutputData.x = m_msg->node1OutputData.x + 5;
            std::cout << "Node4 " << m_msg->node4OutputData.x << " <- " << m_msg->node1OutputData.x << " + " << 5 << std::endl;
            sendData("Node4_res", m_msg);
        }
    }

    virtual void callback(std::shared_ptr<Message> msg) override {
        std::lock_guard lk(m_mtx);
        m_msg = msg;
        std::cout << "Node4 callback msg topic: " << msg->topic << std::endl;
        m_cv.notify_all();
    }

private:
    std::shared_ptr<Message> m_msg;
};

}  // namespace tng_v3