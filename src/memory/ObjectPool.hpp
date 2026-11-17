#pragma once

#include "MemoryPool.hpp"

#include <new>
#include <utility>
#include <unordered_set>
#include <stdexcept>

namespace engine {

template<typename T>
class ObjectPool {
public:
    explicit ObjectPool(std::size_t capacity)
        : pool_(sizeof(T), capacity, alignof(T)) {}

    ~ObjectPool() { for (auto* object : live_) object->~T(); }

    template<typename... Args>
    T* acquire(Args&&... args) {
        void* memory = pool_.allocate();
        if (memory == nullptr) {
            return nullptr;
        }
        T* object = nullptr;
        try {
            object = new (memory) T(std::forward<Args>(args)...);
            live_.insert(object);
            return object;
        } catch (...) {
            if (object) object->~T();
            pool_.deallocate(memory);
            throw;
        }
    }

    void release(T* obj) {
        if (obj == nullptr) {
            return;
        }
        if (!live_.erase(obj)) throw std::invalid_argument("Object is not live in this pool");
        obj->~T();
        pool_.deallocate(static_cast<void*>(obj));
    }

    std::size_t used() const noexcept { return pool_.used(); }
    std::size_t capacity() const noexcept { return pool_.capacity(); }

private:
    MemoryPool pool_;
    std::unordered_set<T*> live_;
};

} // namespace engine
