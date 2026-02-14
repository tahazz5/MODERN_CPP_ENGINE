#pragma once

#include "MemoryPool.hpp"

namespace engine {

template<typename T>
class ObjectPool {
public:
    ObjectPool(std::size_t capacity);
    ~ObjectPool();

    T* acquire();
    void release(T* obj);

private:
    MemoryPool pool_;
};

} // namespace engine
