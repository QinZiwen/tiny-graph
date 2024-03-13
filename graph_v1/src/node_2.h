#pragma once

#include <future>

#include "node.h"

namespace tng {

class Node2 : public Node {
public:
    Node2();
    virtual void run() override;

private:
    std::promise<std::shared_ptr<DataCenter>> m_outputDataCenter;
};

}  // namespace tng