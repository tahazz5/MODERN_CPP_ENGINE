#pragma once

#include <iostream>

namespace engine {

inline void log(const std::string& msg) {
    std::cout << "[Debug] " << msg << std::endl;
}

} // namespace engine
