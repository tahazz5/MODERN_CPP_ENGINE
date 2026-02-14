#pragma once

#include <cstdint>

namespace engine {

using EntityID = std::uint32_t;

struct Entity {
    EntityID id;
};

} // namespace engine
