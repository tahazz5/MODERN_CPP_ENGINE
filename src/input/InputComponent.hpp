#pragma once
#include <string>
#include <unordered_set>

namespace engine {
class InputComponent {
public:
    void keyPress(const std::string& key) { keys_.insert(key); }
    void keyRelease(const std::string& key) { keys_.erase(key); }
    bool isKeyPressed(const std::string& key) const { return keys_.contains(key); }
private:
    std::unordered_set<std::string> keys_;
};
}
using InputComponent = engine::InputComponent;
