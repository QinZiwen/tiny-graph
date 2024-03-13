#pragma once

#include <future>

#include "node.h"

namespace tng {

class Node3 : public Node {
public:
    Node3();
    virtual void run() override;

private:
    std::promise<std::shared_ptr<DataCenter>> m_outputDataCenter;
};

}  // namespace tng