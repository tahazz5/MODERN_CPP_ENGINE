#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <unordered_map>
#include <GLFW/glfw3.h>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void init();
    void update();

    bool isKeyPressed(int key);
    bool isMouseButtonPressed(int button);
    void getMousePosition(double &x, double &y);

private:
    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> mouseButtonStates;
    double mouseX, mouseY;
};

#endif // INPUTMANAGER_HPP