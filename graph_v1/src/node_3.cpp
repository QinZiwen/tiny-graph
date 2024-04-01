#include "node_3.h"

#include <iostream>

namespace tng_v1 {

Node3::Node3() {
    std::cout << "Node3::Node3 ..." << std::endl;
    m_dataCenterOutput = m_outputDataCenter.get_future().share();
}

void Node3::run() {
    std::cout << "Node3::run ..." << std::endl;

    for (const auto& dci : m_dataCenterInput) {
        if (dci.valid()) {
            dci.wait();
        }
    }

    if (m_dataCenterInput.size() > 0) {
        std::shared_ptr<DataCenter> dataCenter = m_dataCenterInput[0].get();
        std::shared_ptr<Node1OutputData> inputData = dataCenter->node1OutputData;
        if (inputData) {
            if (dataCenter->node3OutputData == nullptr) {
                dataCenter->node3OutputData = std::shared_ptr<Node3OutputData>(new Node3OutputData);
            }
            dataCenter->node3OutputData->d = inputData->c + 10;
            dataCenter->node3OutputData->e = inputData->c + 20;
            std::cout << "Node3 c: " << dataCenter->node3OutputData->d
                      << " e: " << dataCenter->node3OutputData->e
                      << " | c: " << inputData->c << std::endl;
        }
        
        m_outputDataCenter.set_value(dataCenter);
    }
}

}  // namespace tng_v1