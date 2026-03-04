#pragma once

#include <string>
#include <vector>

namespace engine {

class Renderer {
public:
    Renderer(int width, int height, char clearChar = ' ');

    void clear();
    void setPixel(int x, int y, char c);
    std::string getBuffer() const;
    void render() const; // print to stdout

    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
    std::vector<char> buffer_;
    char clearChar_;
};

} // namespace engine
