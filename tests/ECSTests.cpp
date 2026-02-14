#include "ecs/World.hpp"

#include <iostream>

namespace {

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

bool testEntityLifecycleAndComponents() {
    engine::World world;

    auto e1 = world.createEntity();
    if (!world.isAlive(e1)) {
        return false;
    }

    world.addComponent<Position>(e1, Position{1.0f, 2.0f});
    auto* pos = world.getComponent<Position>(e1);

    if (pos == nullptr || pos->x != 1.0f || pos->y != 2.0f) {
        return false;
    }

    world.destroyEntity(e1);
    if (world.isAlive(e1)) {
        return false;
    }

    return world.getComponent<Position>(e1) == nullptr;
}

bool testReuseDestroyedEntityId() {
    engine::World world;

    auto e1 = world.createEntity();
    auto e2 = world.createEntity();
    world.destroyEntity(e1);

    auto e3 = world.createEntity();
    return e3.id == e1.id && e3.id != e2.id;
}

} // namespace

int main() {
    if (!testEntityLifecycleAndComponents()) {
        std::cerr << "testEntityLifecycleAndComponents failed\n";
        return 1;
    }

    if (!testReuseDestroyedEntityId()) {
        std::cerr << "testReuseDestroyedEntityId failed\n";
        return 1;
    }

    std::cout << "ECS tests passed\n";
    return 0;
}
