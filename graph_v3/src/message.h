#pragma once

#include <string>

namespace tng_v3 {

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

struct Message {
    GraphInputData graphInputData;
    GraphOutputData graphOutputData;
    Node1OutputData node1OutputData;
    Node2OutputData node2OutputData;
    Node3OutputData node3OutputData;
    Node4OutputData node4OutputData;
    Node5OutputData node5OutputData;

    std::string topic;
};

}  // namespace tng_v3