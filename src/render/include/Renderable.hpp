#pragma once

#include <SFML/Graphics.hpp>
#include "RenderPriority.hpp"

class Renderable : public sf::Drawable {
public:
    Renderable() = delete;
    [[nodiscard]] RenderPriority get_render_priority() const { return m_renderPriority; }
    [[nodiscard]] virtual sf::FloatRect get_bounds() const { return {m_position, m_dimensions}; }

protected:
    Renderable(const sf::Vector2f& position, const sf::Vector2f& dimensions, const RenderPriority renderPriority)
        : m_position(position), m_dimensions(dimensions), m_renderPriority(renderPriority) {}

    sf::Vector2f m_position;  // Top left position
    sf::Vector2f m_dimensions;  // Base x Height
    RenderPriority m_renderPriority {};
};
