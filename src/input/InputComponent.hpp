// InputComponent.hpp
#ifndef INPUT_COMPONENT_HPP
#define INPUT_COMPONENT_HPP

#include <string>
#include <unordered_map>

class InputComponent {
public:
    InputComponent();
    ~InputComponent();

    void keyPress(const std::string& key);
    void keyRelease(const std::string& key);
    bool isKeyPressed(const std::string& key);

private:
    std::unordered_map<std::string, bool> keyStates;
};

#endif // INPUT_COMPONENT_HPP
