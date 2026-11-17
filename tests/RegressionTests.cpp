#include "ecs/World.hpp"
#include "ecs/Components.hpp"
#include "ecs/RenderSystem.hpp"
#include "input/InputComponent.hpp"
#include "input/InputManager.hpp"
#include "memory/ObjectPool.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

void check(bool condition) { if (!condition) throw std::runtime_error("Regression check failed"); }
struct alignas(64) Tracked {
    static inline int live = 0;
    Tracked() { ++live; }
    ~Tracked() { --live; }
};
struct Throws { Throws() { throw std::runtime_error("construction"); } };
int main() {
    try {
        engine::World world;
        auto old = world.createEntity();
        world.addComponent<engine::Position>(old, {1, 1});
        world.addComponent<engine::Sprite>(old, {'X'});
        world.destroyEntity(old);
        auto current = world.createEntity();
        check(current.id == old.id && !world.isAlive(old));
        check(!world.getComponent<engine::Position>(current));
        world.addComponent<engine::Position>(current, {2, 0});
        world.removeComponent<engine::Position>(old);
        world.destroyEntity(old);
        check(world.isAlive(current) && world.getComponent<engine::Position>(current));
        engine::Renderer renderer(3, 2, '.');
        engine::RenderSystem system(world, renderer);
        system.update(0);
        check(renderer.getBuffer() == "...\n...");
        world.addComponent<engine::Sprite>(current, {'@'});
        system.update(0);
        check(renderer.getBuffer() == "..@\n...");
        renderer.setPixel(-1, 0, '!');
        renderer.setPixel(3, 0, '!');
        check(renderer.getBuffer() == "..@\n...");
        bool rejected = false;
        try { engine::Renderer invalid(-1, 2); } catch (const std::invalid_argument&) { rejected = true; }
        check(rejected);
        {
            engine::ObjectPool<Tracked> pool(3);
            for (int i = 0; i < 3; ++i) {
                auto* object = pool.acquire();
                check(object && reinterpret_cast<std::uintptr_t>(object) % alignof(Tracked) == 0);
            }
            check(!pool.acquire() && Tracked::live == 3);
        }
        check(Tracked::live == 0);
        engine::ObjectPool<Throws> throwing(1);
        try { throwing.acquire(); } catch (const std::runtime_error&) {}
        check(throwing.used() == 0);
        engine::MemoryPool memory(9, 3);
        auto* slot = memory.allocate();
        check(reinterpret_cast<std::uintptr_t>(slot) % alignof(std::max_align_t) == 0);
        memory.deallocate(slot);
        rejected = false;
        try { memory.deallocate(slot); } catch (const std::invalid_argument&) { rejected = true; }
        check(rejected && memory.used() == 0);
        engine::InputManager input;
        input.keyPress('w'); input.keyPress('w');
        check(input.isKeyPressed('w') && input.wasKeyPressed('w'));
        input.update();
        check(input.isKeyPressed('w') && !input.wasKeyPressed('w'));
        input.keyRelease('w');
        check(!input.isKeyPressed('w') && input.wasKeyReleased('w'));
        input.mouseButtonPress(1);
        input.setMousePosition(2, 4);
        double x, y;
        input.getMousePosition(x, y);
        check(x == 2 && y == 4 && input.isMouseButtonPressed(1));
        input.init();
        check(!input.wasKeyReleased('w') && !input.isMouseButtonPressed(1));
        engine::InputComponent controls;
        controls.keyPress("jump"); check(controls.isKeyPressed("jump"));
        controls.keyRelease("jump"); check(!controls.isKeyPressed("jump"));
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n'; return 1;
    }
    std::cout << "Regression tests passed\n";
}
