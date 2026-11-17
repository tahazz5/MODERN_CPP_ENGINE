#include "MemoryPool.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <new>
#include <stdexcept>

namespace engine {
MemoryPool::MemoryPool(std::size_t elementSize, std::size_t capacity, std::size_t alignment)
    : elementSize_(std::max(elementSize, sizeof(FreeNode))), slotSize_(0),
      capacity_(capacity), used_(0), alignment_(std::max(alignment, alignof(std::max_align_t))),
      storage_(nullptr), allocated_(), freeList_(nullptr) {
    if (alignment == 0 || (alignment & (alignment - 1)) != 0)
        throw std::invalid_argument("Alignment must be a power of two");
    const auto max = std::numeric_limits<std::size_t>::max();
    if (elementSize_ > max - (alignment_ - 1)) throw std::length_error("Pool slot too large");
    slotSize_ = (elementSize_ + alignment_ - 1) & ~(alignment_ - 1);
    if (capacity_ > max / slotSize_) throw std::length_error("Pool too large");
    allocated_.resize(capacity_, false);
    if (!capacity_) return;
    storage_ = static_cast<std::byte*>(::operator new(slotSize_ * capacity_, std::align_val_t(alignment_)));
    for (std::size_t i = 0; i < capacity_; ++i) {
        auto* node = new (storage_ + i * slotSize_) FreeNode{freeList_};
        freeList_ = node;
    }
}
MemoryPool::~MemoryPool() { ::operator delete(storage_, std::align_val_t(alignment_)); }
void* MemoryPool::allocate() {
    if (!freeList_) return nullptr;
    auto* node = freeList_;
    freeList_ = node->next;
    allocated_[(reinterpret_cast<std::byte*>(node) - storage_) / slotSize_] = true;
    ++used_;
    return node;
}
void MemoryPool::deallocate(void* ptr) {
    if (!ptr) return;
    if (!ownsPointer(ptr)) throw std::invalid_argument("Pointer does not belong to pool");
    const auto index = (static_cast<std::byte*>(ptr) - storage_) / slotSize_;
    if (!allocated_[index]) throw std::invalid_argument("Pool slot already released");
    allocated_[index] = false;
    freeList_ = new (ptr) FreeNode{freeList_};
    --used_;
}
bool MemoryPool::ownsPointer(void* ptr) const noexcept {
    if (!storage_ || !ptr) return false;
    const auto start = reinterpret_cast<std::uintptr_t>(storage_);
    const auto address = reinterpret_cast<std::uintptr_t>(ptr);
    return address >= start && address - start < slotSize_ * capacity_
        && (address - start) % slotSize_ == 0;
}
}
