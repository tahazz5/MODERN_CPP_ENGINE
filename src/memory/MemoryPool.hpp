#pragma once

#include <cstddef>
#include <vector>

namespace engine {

class MemoryPool {
public:
    explicit MemoryPool(std::size_t elementSize, std::size_t capacity);
    ~MemoryPool() = default;

    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    MemoryPool(MemoryPool&&) = delete;
    MemoryPool& operator=(MemoryPool&&) = delete;

    void* allocate();
    void deallocate(void* ptr);

    std::size_t capacity() const noexcept { return capacity_; }
    std::size_t used() const noexcept { return used_; }
    std::size_t elementSize() const noexcept { return elementSize_; }

private:
    struct FreeNode {
        FreeNode* next;
    };

    std::size_t elementSize_;
    std::size_t slotSize_;
    std::size_t capacity_;
    std::size_t used_;
    std::vector<std::byte> storage_;
    FreeNode* freeList_;

    bool ownsPointer(void* ptr) const noexcept;
};

} // namespace engine
