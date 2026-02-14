#pragma once

#include <cstddef>

namespace engine {

class PoolResource {
public:
    PoolResource(void* ptr, std::size_t size);
    ~PoolResource();

    PoolResource(const PoolResource&) = delete;
    PoolResource& operator=(const PoolResource&) = delete;

    PoolResource(PoolResource&& other) noexcept;
    PoolResource& operator=(PoolResource&& other) noexcept;

    void* data() const;
    std::size_t size() const;

private:
    void* data_;
    std::size_t size_;
};

} // namespace engine
