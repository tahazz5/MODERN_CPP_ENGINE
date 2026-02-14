#pragma once

#include <vector>
#include <cstdint>

namespace engine {

template<typename T>
class SparseSet {
public:
    void insert(std::uint32_t id, const T& value);
    void remove(std::uint32_t id);
    T* get(std::uint32_t id);

private:
    std::vector<T> dense_;
    std::vector<std::uint32_t> sparse_;
};

} // namespace engine
