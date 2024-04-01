#include "node_4.h"

#include <iostream>

namespace tng_v1 {

Node4::Node4() {
    std::cout << "Node4::Node4 ..." << std::endl;
    m_dataCenterOutput = m_outputDataCenter.get_future().share();
}

void Node4::run() {
    std::cout << "Node4::run ..." << std::endl;

    for (const auto& dci : m_dataCenterInput) {
        if (dci.valid()) {
            dci.wait();
        }
    }

    if (m_dataCenterInput.size() > 0) {
        std::shared_ptr<DataCenter> dataCenter = m_dataCenterInput[0].get();

        if (dataCenter->node4OutputData == nullptr) {
            dataCenter->node4OutputData = std::shared_ptr<Node4OutputData>(new Node4OutputData);
        }

        std::shared_ptr<Node2OutputData> inputData2 = dataCenter->node2OutputData;
        if (inputData2) {
            dataCenter->node4OutputData->f += inputData2->c + 10;
            std::cout << "Node4 f: " << dataCenter->node4OutputData->f
                        << " | c: " << inputData2->c << std::endl;
        }

        std::shared_ptr<Node3OutputData> inputData3 = dataCenter->node3OutputData;
        if (inputData3) {
            dataCenter->node4OutputData->f += inputData3->d + inputData3->e + 100;
            std::cout << "Node4 f: " << dataCenter->node4OutputData->f
                        << " | d: " << inputData3->d
                        << " e: " << inputData3->e << std::endl;
        }

        m_outputDataCenter.set_value(dataCenter);
    }
}

}  // namespace tng_v1