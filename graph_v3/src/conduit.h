#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <mutex>

#include "callback_function.h"
#include "message.h"

namespace tng_v3 {

/**
 * @brief 1. 可以通过Conduit声明一个topic，或者订阅一个topic
 *        2. 可以通过Conduit发送数据
 *        3. 可以通过Conduit接收数据
 */
class Conduit {
public:
    void publishTopic(const std::string& topic);
    bool subscribeTopic(const std::string& topic, std::shared_ptr<CallbackFunction> callback);
    bool sendData(const std::string& topic, std::shared_ptr<Message> msg);

private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<CallbackFunction>>> m_callbackMap;
    std::mutex m_mutex;
};

}  // namespace tng_v3