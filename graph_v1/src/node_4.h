#pragma once

#include <future>

#include "node.h"

namespace tng_v1 {

class Node4 : public Node {
public:
    Node4();
    virtual void run() override;

private:
    std::promise<std::shared_ptr<DataCenter>> m_outputDataCenter;
};

}  // namespace tng_v1