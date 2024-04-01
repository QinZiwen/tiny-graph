#pragma once

#include "message.h"

namespace tng_v3 {

class CallbackFunction {
public:
    virtual ~CallbackFunction() = default;
    virtual void callback(std::shared_ptr<Message> msg) {}
    void operator()(std::shared_ptr<Message> msg) {
        callback(msg);
    }
};

}  // namespace tng_v3