#pragma once

#include <cstdint>

namespace engine {

using EntityID = std::uint32_t;

struct Entity {
    EntityID id;
    std::uint64_t generation = 0;
};

} // namespace engine
