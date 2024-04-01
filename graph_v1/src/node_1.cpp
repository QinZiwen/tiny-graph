#include "node_1.h"

#include <iostream>

namespace tng_v1 {

Node1::Node1() {
    std::cout << "Node1::Node1 ..." << std::endl;
    m_dataCenterOutput = m_outputDataCenter.get_future().share();
}

void Node1::run() {
    std::cout << "Node1::run ..." << std::endl;

    for (const auto& dci : m_dataCenterInput) {
        if (dci.valid()) {
            dci.wait();
        }
    }

    if (m_dataCenterInput.size() > 0) {
        std::shared_ptr<DataCenter> dataCenter = m_dataCenterInput[0].get();
        std::shared_ptr<Node1InputData> inputData = dataCenter->node1InputData;
        if (inputData) {
            if (dataCenter->node1OutputData == nullptr) {
                dataCenter->node1OutputData = std::shared_ptr<Node1OutputData>(new Node1OutputData);
            }
            dataCenter->node1OutputData->c += inputData->a + inputData->b;
            std::cout << "Node1 c: " << dataCenter->node1OutputData->c
                      << " | a: " << inputData->a
                      << " b: " << inputData->b << std::endl;
        }
        
        m_outputDataCenter.set_value(dataCenter);
    }
}

}  // namespace tng_v1