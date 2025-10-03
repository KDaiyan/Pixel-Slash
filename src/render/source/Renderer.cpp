#include "Renderer.hpp"

namespace {
    sf::RenderWindow window;
}

namespace Renderer {
    void init() {
        window.create(sf::VideoMode{{1920u, 1080u}}, "Pixel Slash");
        window.setFramerateLimit(60u);
        window.setKeyRepeatEnabled(false);
    }

    sf::RenderWindow& get_window() { return window; }
}