#include "Renderer.hpp"

Renderer& Renderer::instance() { // Change from singleton to RAII when possible
    static Renderer renderer;
    return renderer;
}

Renderer::Renderer() {
    m_window.create(sf::VideoMode({1920u, 1080u}), "Pixel Slash");
    m_window.setFramerateLimit(60u);
    m_window.setKeyRepeatEnabled(false);
}
