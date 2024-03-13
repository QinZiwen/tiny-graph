#pragma once

#include <vector>

namespace tng {

struct Node1InputData {
    int a = 0;
    int b = 0;
};

struct Node1OutputData {
    int c = 0;
};

struct Node2OutputData {
    int c = 0;
};

struct Node3OutputData {
    int d = 0;
    int e = 0;
};

struct Node4OutputData {
    int f = 0;
};

struct DataCenter {
    std::shared_ptr<Node1InputData> node1InputData = nullptr;
    std::shared_ptr<Node1OutputData> node1OutputData = nullptr;
    std::shared_ptr<Node2OutputData> node2OutputData = nullptr;
    std::shared_ptr<Node3OutputData> node3OutputData = nullptr;
    std::shared_ptr<Node4OutputData> node4OutputData = nullptr;
};

class Node {
public:
    virtual ~Node() = default;
    
    virtual void setInputData(std::shared_future<std::shared_ptr<DataCenter>> dataCenter) {  m_dataCenterInput.push_back(dataCenter); }
    virtual std::shared_future<std::shared_ptr<DataCenter>> getOutputData() { return m_dataCenterOutput; }
    virtual void run() = 0;

protected:
    std::vector<std::shared_future<std::shared_ptr<DataCenter>>> m_dataCenterInput;
    std::shared_future<std::shared_ptr<DataCenter>> m_dataCenterOutput;
};

}  // namespace tng