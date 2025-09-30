#pragma once

#include "Renderable.hpp"

class Particle final : public Renderable {
public:
    Particle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color, float speed);
    // Particle() = default;
    void set_position(const sf::Vector2f& pos) { m_position = pos; m_shape.setPosition(m_position); }
    sf::Vector2f get_position() const { return m_position; }
    void set_speed(const float speed) { m_speed = speed; }
    float get_speed() const { return m_speed; }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_shape;
    float m_speed{};
};