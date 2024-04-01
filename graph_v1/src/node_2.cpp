#include "node_2.h"

#include <iostream>

namespace tng_v1 {

Node2::Node2() {
    std::cout << "Node2::Node2 ..." << std::endl;
    m_dataCenterOutput = m_outputDataCenter.get_future().share();
}

void Node2::run() {
    std::cout << "Node2::run ..." << std::endl;

    for (const auto& dci : m_dataCenterInput) {
        if (dci.valid()) {
            dci.wait();
        }
    }

    if (m_dataCenterInput.size() > 0) {
        std::shared_ptr<DataCenter> dataCenter = m_dataCenterInput[0].get();
        std::shared_ptr<Node1OutputData> inputData = dataCenter->node1OutputData;
        if (inputData) {
            if (dataCenter->node2OutputData == nullptr) {
                dataCenter->node2OutputData = std::shared_ptr<Node2OutputData>(new Node2OutputData);
            }
            dataCenter->node2OutputData->c += inputData->c + 10;
            std::cout << "Node2 c: " << dataCenter->node2OutputData->c
                      << " | c: " << inputData->c << std::endl;
        }
        
        m_outputDataCenter.set_value(dataCenter);
    }
}

}  // namespace tng_v1