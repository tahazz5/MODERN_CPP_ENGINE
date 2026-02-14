#pragma once

#include <chrono>

namespace engine {

class Timer {
public:
    Timer();
    void reset();
    float elapsed() const;

private:
    std::chrono::high_resolution_clock::time_point start_;
};

} // namespace engine
