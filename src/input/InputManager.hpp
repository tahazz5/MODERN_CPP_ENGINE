#pragma once

#include <unordered_set>

namespace engine {

// Platform-independent state; a window or terminal backend supplies events.
class InputManager {
public:
    void init();
    void update(); // Begin a frame before supplying events.
    void keyPress(int key);
    void keyRelease(int key);
    bool isKeyPressed(int key) const;
    bool wasKeyPressed(int key) const;
    bool wasKeyReleased(int key) const;
    void mouseButtonPress(int button);
    void mouseButtonRelease(int button);
    bool isMouseButtonPressed(int button) const;
    void setMousePosition(double x, double y);
    void getMousePosition(double& x, double& y) const;
private:
    std::unordered_set<int> keys_, pressed_, released_, buttons_;
    double mouseX_ = 0, mouseY_ = 0;
};
}

using InputManager = engine::InputManager;
