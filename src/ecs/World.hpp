#pragma once

#include "ComponentStorage.hpp"
#include "Entity.hpp"

#include <queue>
#include <vector>

namespace engine {

class World {
public:
    Entity createEntity();
    void destroyEntity(Entity e);
    bool isAlive(Entity e) const;

    template<typename Component>
    void addComponent(Entity e, const Component& component) {
        if (isAlive(e)) {
            components_.add<Component>(e.id, component);
        }
    }

    template<typename Component>
    void removeComponent(Entity e) {
        components_.remove<Component>(e.id);
    }

    template<typename Component>
    Component* getComponent(Entity e) {
        if (!isAlive(e)) {
            return nullptr;
        }
        return components_.get<Component>(e.id);
    }

private:
    EntityID nextId_ = 0;
    std::queue<EntityID> freeIds_;
    std::vector<bool> alive_;
    ComponentStorage components_;
};

} // namespace engine
