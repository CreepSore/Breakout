#pragma once
#include <string>

struct EventArgs {
    std::string eventName;

    EventArgs(std::string eventName = "unknown") {
        this->eventName = eventName;
    }
};
