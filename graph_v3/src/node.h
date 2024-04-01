#pragma once

#include <condition_variable>
#include <iostream>
#include <string>
#include <future>
#include <vector>
#include <mutex>
#include <exception>

#include "conduit.h"

namespace tng_v3 {

class Node : public CallbackFunction, public std::enable_shared_from_this<Node> {
public:
    Node(const std::string& name, std::shared_ptr<Conduit> conduit) : m_name(name), m_conduit(conduit) {}
    virtual ~Node() = default;

    void publishTopic(const std::string& topic) {
        std::cout << "[Node::publishTopic] topic: " << topic << std::endl;
        m_conduit->publishTopic(topic);
    }

    bool subscribeTopic(const std::string& topic) {
        std::cout << "[Node::subscribeTopic] topic: " << topic << std::endl;
        try {
            return m_conduit->subscribeTopic(topic, this->shared_from_this());
        } catch (std::exception& e) {
            std::cout << "[Node::subscribeTopic] exception: " << e.what() << std::endl;
            return false;
        }
    }

    bool sendData(const std::string& topic, std::shared_ptr<Message> msg) {
        std::cout << "[Node::sendData] topic: " << topic << std::endl;
        return m_conduit->sendData(topic, msg);
    }

    // virtual void run() = 0;
    virtual void run() {}
    virtual void callback(std::shared_ptr<Message> msg) override {}

protected:
    std::string m_name;
    std::shared_ptr<Conduit> m_conduit;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};

}  // namespace tng_v3