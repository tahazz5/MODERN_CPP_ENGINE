#pragma once

#include <cstddef>

namespace engine {

class MemoryPool {
public:
    explicit MemoryPool(std::size_t elementSize, std::size_t capacity);
    ~MemoryPool();
    void* allocate();
    void deallocate(void* ptr);

private:
    // internals...
};

} // namespace engine
