#include "conduit.h"

namespace tng_v3 {

void Conduit::publishTopic(const std::string& topic) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callbackMap.find(topic) == m_callbackMap.end()) {
        std::cout << "[Conduit::publishTopic] Publish topic: " << topic << std::endl;
        m_callbackMap[topic].push_back(std::make_shared<CallbackFunction>());
    }
}

bool Conduit::subscribeTopic(const std::string& topic, std::shared_ptr<CallbackFunction> callback) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "[Conduit::subscribeTopic] Subscribe topic: " << topic << std::endl;
    if (m_callbackMap.find(topic) != m_callbackMap.end()) {
        m_callbackMap[topic].push_back(callback);
        return true;
    } else {
        std::cout << "[Conduit::subscribeTopic] This topic was not found: " << topic << std::endl;
        return false;
    }
}

bool Conduit::sendData(const std::string& topic, std::shared_ptr<Message> msg) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "[Conduit::sendData] Send data to topic: " << topic << std::endl;
    if (m_callbackMap.find(topic) != m_callbackMap.end()) {
        msg->topic = topic;
        for (auto& callback : m_callbackMap[topic]) {
            (*callback)(msg);
        }
        return true;
    } else {
        std::cout << "[Conduit::sendData] This topic was not found: " << topic << std::endl;
        return false;
    }
}

}  // namespace tng_v3