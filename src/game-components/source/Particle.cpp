#include "Particle.hpp"

#include "Renderer.hpp"

Particle::Particle(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color color, const float speed)
        : Renderable(position, size, RenderPriority::Background_Object)
{
    m_shape.setSize(size);
    m_shape.setFillColor(color);
    set_position(position);
    m_speed = speed;
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto& window = Renderer::get_window();
    window.draw(m_shape);
}
