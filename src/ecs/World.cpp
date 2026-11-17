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
            generations_.resize(alive_.size(), 0);
        }
    }

    alive_[id] = true;
    return Entity{id, generations_[id]};
}

void World::destroyEntity(Entity e) {
    if (!isAlive(e)) {
        return;
    }

    components_.removeAll(e.id);
    alive_[e.id] = false;
    ++generations_[e.id];
    freeIds_.push(e.id);
}

bool World::isAlive(Entity e) const {
    return e.id < alive_.size() && alive_[e.id] && generations_[e.id] == e.generation;
}

} // namespace engine
