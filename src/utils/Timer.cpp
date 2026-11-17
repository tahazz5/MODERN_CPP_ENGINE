#include "Timer.hpp"

namespace engine {

Timer::Timer()
    : start_(std::chrono::steady_clock::now()) {}

void Timer::reset() {
    start_ = std::chrono::steady_clock::now();
}

float Timer::elapsed() const {
    const auto now = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - start_);
    return duration.count();
}

} // namespace engine
