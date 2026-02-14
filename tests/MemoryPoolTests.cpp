#include "memory/MemoryPool.hpp"
#include "memory/ObjectPool.hpp"

#include <iostream>

namespace {

bool testMemoryPoolCapacityAndReuse() {
    engine::MemoryPool pool(sizeof(int), 2);

    void* first = pool.allocate();
    void* second = pool.allocate();
    void* third = pool.allocate();

    if (first == nullptr || second == nullptr || third != nullptr || pool.used() != 2u) {
        return false;
    }

    pool.deallocate(first);
    if (pool.used() != 1u) {
        return false;
    }

    void* recycled = pool.allocate();
    return recycled == first && pool.used() == 2u;
}

struct TestObject {
    explicit TestObject(int v)
        : value(v) {
        ++liveCount;
    }

    ~TestObject() {
        --liveCount;
    }

    int value;
    static inline int liveCount = 0;
};

bool testObjectPoolLifecycle() {
    engine::ObjectPool<TestObject> pool(1);
    auto* obj = pool.acquire(42);

    if (obj == nullptr || obj->value != 42 || TestObject::liveCount != 1) {
        return false;
    }

    pool.release(obj);
    return TestObject::liveCount == 0;
}

} // namespace

int main() {
    if (!testMemoryPoolCapacityAndReuse()) {
        std::cerr << "testMemoryPoolCapacityAndReuse failed\n";
        return 1;
    }

    if (!testObjectPoolLifecycle()) {
        std::cerr << "testObjectPoolLifecycle failed\n";
        return 1;
    }

    std::cout << "MemoryPool tests passed\n";
    return 0;
}
