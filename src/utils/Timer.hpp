#pragma once

#include <chrono>

namespace engine {

class Timer {
public:
    Timer();
    void reset();
    float elapsed() const;

private:
    std::chrono::steady_clock::time_point start_;
};

} // namespace engine
