#pragma once

#include "node.h"
#include "node1.h"
#include "node2.h"
#include "node3.h"
#include "node4.h"
#include "node5.h"
#include "conduit.h"

namespace tng_v3 {

class NodeFactory {
public:
    static std::shared_ptr<Node> createNode(const std::string& name, std::shared_ptr<Conduit> conduit) {
        if (name == "Node1") {
            return std::make_shared<Node1>(name, conduit);
        } else if (name == "Node2") {
            return std::make_shared<Node2>(name, conduit);
        } else if (name == "Node3") {
            return std::make_shared<Node3>(name, conduit);
        } else if (name == "Node4") {
            return std::make_shared<Node4>(name, conduit);
        } else if (name == "Node5") {
            return std::make_shared<Node5>(name, conduit);
        } else {
            return nullptr;
        }
    }
};

}  // namespace tng_v3