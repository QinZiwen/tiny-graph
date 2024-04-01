#pragma once

#include <unordered_set>

#include "node.h"

namespace tng_v3 {

class Node5 : public Node {
public:
    Node5(const std::string& name, std::shared_ptr<Conduit> conduit) : Node(name, conduit) {
        m_subscribeTopics = {"Node2_res", "Node3_res", "Node4_res"};
        publishTopic("Node5_res");
    }

    ~Node5() = default;

    virtual void run() override {
        std::cout << "Node5 run" << std::endl;
        for (const auto& topic : m_subscribeTopics) {
            subscribeTopic(topic);
        }

        {
            std::unique_lock lk(m_mtx);
            m_cv.wait(lk, [&]() -> bool {
                for (const auto& topic : m_subscribeTopics) {
                    if (m_msgTopics.find(topic) == m_msgTopics.end()) {
                        return false;
                    }
                }
                return true;
            });
            m_msg->node5OutputData.x = m_msg->node4OutputData.x + m_msg->node3OutputData.x + m_msg->node2OutputData.x;
            std::cout << "Node5 " << m_msg->node5OutputData.x << " <- " << m_msg->node4OutputData.x
                      << " + " << m_msg->node3OutputData.x
                      << " + " << m_msg->node2OutputData.x << std::endl;
            sendData("Node5_res", m_msg);
        }
    }

    virtual void callback(std::shared_ptr<Message> msg) override {
        std::lock_guard lk(m_mtx);
        m_msg = msg;
        m_msgTopics.emplace(msg->topic);
        std::cout << "Node5 callback msg topic: " << msg->topic << std::endl;
        m_cv.notify_all();
    }

private:
    std::shared_ptr<Message> m_msg;
    std::vector<std::string> m_subscribeTopics;
    std::unordered_set<std::string> m_msgTopics;
};

}  // namespace tng_v3