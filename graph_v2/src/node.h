#pragma once

#include <iostream>
#include <string>
#include <future>
#include <vector>

#include "data_center.h"

namespace tng {

class Node {
public:
    Node(const std::string& name) : m_name(name) {
        m_outputFuture = m_outputPromise.get_future().share();
    }

    virtual ~Node() = default;

    void setInputFuture(std::shared_future<std::string> inputFuture) { m_inputFutures.push_back(inputFuture); }
    std::shared_future<std::string> getOutputFuture() { return m_outputFuture; }
    virtual void run() = 0;

protected:
    std::string m_name;
    std::vector<std::shared_future<std::string>> m_inputFutures;
    std::promise<std::string> m_outputPromise;
    std::shared_future<std::string> m_outputFuture;
};

}  // namespace tng