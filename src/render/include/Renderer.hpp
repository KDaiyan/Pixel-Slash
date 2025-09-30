#pragma once

#include <SFML/Graphics.hpp>

class Renderer {
public:
    static Renderer& instance();
    sf::RenderWindow& get_window() { return m_window; }

private:
    sf::RenderWindow m_window;
    Renderer();
};
