#include "ecs/World.hpp"
#include "ecs/Components.hpp"
#include "ecs/RenderSystem.hpp"
#include "render/Renderer.hpp"

#include <iostream>

namespace {

bool testSimpleRender() {
    engine::World world;
    engine::Renderer renderer(3, 2, '.');
    engine::RenderSystem renderSys(world, renderer);

    auto e = world.createEntity();
    world.addComponent<engine::Position>(e, {1, 0});
    world.addComponent<engine::Sprite>(e, {'X'});

    renderSys.update(0.0f);

    std::string expected = ".X.\n...";
    return renderer.getBuffer() == expected;
}

} // namespace

int main() {
    if (!testSimpleRender()) {
        std::cerr << "testSimpleRender failed\n";
        return 1;
    }

    std::cout << "Rendering tests passed\n";
    return 0;
}
