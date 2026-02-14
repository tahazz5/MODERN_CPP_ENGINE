#include "PoolResource.hpp"

#include <utility>

namespace engine {

PoolResource::PoolResource(void* ptr, std::size_t size)
    : data_(ptr), size_(size) {}

PoolResource::~PoolResource() = default;

PoolResource::PoolResource(PoolResource&& other) noexcept
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

PoolResource& PoolResource::operator=(PoolResource&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;
    return *this;
}

void* PoolResource::data() const {
    return data_;
}

std::size_t PoolResource::size() const {
    return size_;
}

} // namespace engine
