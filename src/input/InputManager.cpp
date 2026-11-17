#include "InputManager.hpp"

namespace engine {
void InputManager::init() { keys_.clear(); buttons_.clear(); update(); mouseX_ = mouseY_ = 0; }
void InputManager::update() { pressed_.clear(); released_.clear(); }
void InputManager::keyPress(int key) { if (keys_.insert(key).second) pressed_.insert(key); }
void InputManager::keyRelease(int key) { if (keys_.erase(key)) released_.insert(key); }
bool InputManager::isKeyPressed(int key) const { return keys_.contains(key); }
bool InputManager::wasKeyPressed(int key) const { return pressed_.contains(key); }
bool InputManager::wasKeyReleased(int key) const { return released_.contains(key); }
void InputManager::mouseButtonPress(int button) { buttons_.insert(button); }
void InputManager::mouseButtonRelease(int button) { buttons_.erase(button); }
bool InputManager::isMouseButtonPressed(int button) const { return buttons_.contains(button); }
void InputManager::setMousePosition(double x, double y) { mouseX_ = x; mouseY_ = y; }
void InputManager::getMousePosition(double& x, double& y) const { x = mouseX_; y = mouseY_; }
}
