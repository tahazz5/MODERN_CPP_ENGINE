#pragma once

#include "System.hpp"
#include "World.hpp"
#include "render/Renderer.hpp"
#include "Components.hpp"

namespace engine {

class RenderSystem : public System {
public:
    RenderSystem(World& world, Renderer& renderer)
        : world_(world), renderer_(renderer) {}

    void update(float /*dt*/) override {
        renderer_.clear();
        // draw all entities that have both Position and Sprite
        world_.forEach<Position>([&](Entity e, Position& pos) {
            auto* sprite = world_.getComponent<Sprite>(e);
            if (sprite) {
                renderer_.setPixel(pos.x, pos.y, sprite->glyph);
            }
        });
    }

private:
    World& world_;
    Renderer& renderer_;
};

} // namespace engine
