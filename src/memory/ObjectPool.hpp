#pragma once

#include "MemoryPool.hpp"

#include <new>
#include <utility>

namespace engine {

template<typename T>
class ObjectPool {
public:
    explicit ObjectPool(std::size_t capacity)
        : pool_(sizeof(T), capacity) {}

    ~ObjectPool() = default;

    template<typename... Args>
    T* acquire(Args&&... args) {
        void* memory = pool_.allocate();
        if (memory == nullptr) {
            return nullptr;
        }
        return new (memory) T(std::forward<Args>(args)...);
    }

    void release(T* obj) {
        if (obj == nullptr) {
            return;
        }
        obj->~T();
        pool_.deallocate(static_cast<void*>(obj));
    }

    std::size_t used() const noexcept { return pool_.used(); }
    std::size_t capacity() const noexcept { return pool_.capacity(); }

private:
    MemoryPool pool_;
};

} // namespace engine
