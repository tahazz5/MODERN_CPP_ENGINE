#pragma once

#include "Entity.hpp"
#include "ComponentStorage.hpp"

namespace engine {

class World {
public:
    Entity createEntity();
    void destroyEntity(Entity e);

    // systems, component storage etc.
};

} // namespace engine
