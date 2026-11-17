#include "ecs/RenderSystem.hpp"
#include "input/InputManager.hpp"
#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    const bool interactive = argc == 2 && std::string(argv[1]) == "--interactive";
    if (argc > 1 && !interactive) {
        std::cerr << "Usage: ModernCppEngineApp [--interactive]\n";
        return 1;
    }
    engine::World world;
    engine::Renderer renderer(20, 8, '.');
    engine::RenderSystem rendering(world, renderer);
    engine::InputManager input;
    const auto player = world.createEntity();
    world.addComponent<engine::Position>(player, {10, 4});
    world.addComponent<engine::Sprite>(player, {'@'});
    std::cout << "Modern C++ Engine — ASCII demo\n";
    do {
        rendering.update(0.0f);
        renderer.render();
        if (!interactive) break;
        std::cout << "z/w: haut, s: bas, q/a: gauche, d: droite, x: quitter (puis Entrée)\n";
        std::string command;
        if (!std::getline(std::cin, command) || command == "x") break;
        input.update();
        for (char key : command) input.keyPress(key);
        auto* position = world.getComponent<engine::Position>(player);
        position->x += input.isKeyPressed('d') - (input.isKeyPressed('a') || input.isKeyPressed('q'));
        position->y += input.isKeyPressed('s') - (input.isKeyPressed('w') || input.isKeyPressed('z'));
        position->x = std::clamp(position->x, 0, renderer.width() - 1);
        position->y = std::clamp(position->y, 0, renderer.height() - 1);
        for (char key : command) input.keyRelease(key);
    } while (true);
}
