#pragma once

#include "node.h"
#include "node1.h"
#include "node2.h"
#include "node3.h"
#include "node4.h"
#include "node5.h"

namespace tng {

class NodeFactory {
public:
    static std::shared_ptr<Node> createNode(const std::string& name) {
        if (name == "Node1") {
            return std::make_shared<Node1>(name);
        } else if (name == "Node2") {
            return std::make_shared<Node2>(name);
        } else if (name == "Node3") {
            return std::make_shared<Node3>(name);
        } else if (name == "Node4") {
            return std::make_shared<Node4>(name);
        } else if (name == "Node5") {
            return std::make_shared<Node5>(name);
        } else {
            return nullptr;
        }
    }
};

}  // namespace tng