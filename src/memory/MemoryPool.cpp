#include "MemoryPool.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <new>

namespace engine {

MemoryPool::MemoryPool(std::size_t elementSize, std::size_t capacity)
    : elementSize_(std::max(elementSize, sizeof(FreeNode))),
      slotSize_(elementSize_),
      capacity_(capacity),
      used_(0),
      storage_(slotSize_ * capacity_),
      freeList_(nullptr) {
    if (capacity_ == 0) {
        return;
    }

    auto* base = reinterpret_cast<std::byte*>(storage_.data());
    for (std::size_t i = 0; i < capacity_; ++i) {
        auto* node = reinterpret_cast<FreeNode*>(base + (i * slotSize_));
        node->next = freeList_;
        freeList_ = node;
    }
}

void* MemoryPool::allocate() {
    if (freeList_ == nullptr) {
        return nullptr;
    }

    FreeNode* node = freeList_;
    freeList_ = freeList_->next;
    ++used_;
    return node;
}

void MemoryPool::deallocate(void* ptr) {
    if (ptr == nullptr) {
        return;
    }

    assert(ownsPointer(ptr) && "Pointer must belong to this pool.");

    auto* node = static_cast<FreeNode*>(ptr);
    node->next = freeList_;
    freeList_ = node;

    if (used_ > 0) {
        --used_;
    }
}

bool MemoryPool::ownsPointer(void* ptr) const noexcept {
    const auto* begin = storage_.data();
    const auto* end = storage_.data() + storage_.size();
    const auto* p = static_cast<std::byte*>(ptr);

    if (p < begin || p >= end) {
        return false;
    }

    const auto offset = static_cast<std::size_t>(p - begin);
    return (offset % slotSize_) == 0;
}

} // namespace engine
