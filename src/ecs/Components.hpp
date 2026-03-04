#pragma once

namespace engine {

// basic components to support simple rendering/demo

struct Position {
    int x = 0;
    int y = 0;
};

struct Sprite {
    char glyph = '#';
};

} // namespace engine
