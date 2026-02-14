#include "World.hpp"

namespace engine {

Entity World::createEntity() {
    EntityID id;

    if (!freeIds_.empty()) {
        id = freeIds_.front();
        freeIds_.pop();
    } else {
        id = nextId_++;
        if (id >= alive_.size()) {
            alive_.resize(static_cast<std::size_t>(id) + 1, false);
        }
    }

    alive_[id] = true;
    return Entity{id};
}

void World::destroyEntity(Entity e) {
    if (!isAlive(e)) {
        return;
    }

    alive_[e.id] = false;
    freeIds_.push(e.id);
}

bool World::isAlive(Entity e) const {
    return e.id < alive_.size() && alive_[e.id];
}

} // namespace engine
