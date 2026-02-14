#pragma once

#include <cstddef>

namespace engine {

class PoolResource {
public:
    PoolResource(void* ptr, std::size_t size);
    ~PoolResource();

    void* data() const;
    std::size_t size() const;

private:
    void* data_;
    std::size_t size_;
};

} // namespace engine
