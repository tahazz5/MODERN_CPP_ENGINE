#include "render/Renderer.hpp"
#include <iostream>

namespace engine {

Renderer::Renderer(int width, int height, char clearChar)
    : width_(width), height_(height), buffer_(width * height), clearChar_(clearChar) {
    clear();
}

void Renderer::clear() {
    std::fill(buffer_.begin(), buffer_.end(), clearChar_);
}

void Renderer::setPixel(int x, int y, char c) {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        return;
    }
    buffer_[y * width_ + x] = c;
}

std::string Renderer::getBuffer() const {
    std::string out;
    out.reserve(buffer_.size() + height_); // include newlines
    for (int y = 0; y < height_; ++y) {
        out.append(buffer_.data() + y * width_, static_cast<std::size_t>(width_));
        if (y < height_ - 1) {
            out.push_back('\n');
        }
    }
    return out;
}

void Renderer::render() const {
    std::cout << getBuffer() << std::endl;
}

} // namespace engine
