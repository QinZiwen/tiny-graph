#pragma once

#include <memory>

namespace tng {

struct GraphInputData {
    int gdb;
    int gda;
};

struct GraphOutputData {
    int gdc;
};

struct Node1OutputData {
    int x;
};

struct Node2OutputData {
    int x;
};

struct Node3OutputData {
    int x;
};

struct Node4OutputData {
    int x;
};

struct Node5OutputData {
    int x;
};

struct DataCenter {
public:
    static DataCenter* getInstane() {
        static DataCenter instance;
        return &instance;
    }

    // data segment
    std::shared_ptr<GraphInputData> graphInputData = nullptr;
    std::shared_ptr<GraphOutputData> graphOutputData = nullptr;
    std::shared_ptr<Node1OutputData> node1OutputData = nullptr;
    std::shared_ptr<Node2OutputData> node2OutputData = nullptr;
    std::shared_ptr<Node3OutputData> node3OutputData = nullptr;
    std::shared_ptr<Node4OutputData> node4OutputData = nullptr;
    std::shared_ptr<Node5OutputData> node5OutputData = nullptr;

private:
    DataCenter() = default;
};

}  // namespace tng