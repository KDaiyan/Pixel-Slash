#pragma once

#include <SFML/Window/Mouse.hpp>
#include "event/Event.hpp"

namespace Mouse = sf::Mouse;

class MousePressEvent final : public Event {
public:
    MousePressEvent(const Mouse::Button button, const sf::Vector2i& pos) : m_button(button), m_position(pos) {}
    [[nodiscard]] const Mouse::Button& get_button() const { return m_button; }
    [[nodiscard]] const sf::Vector2i& get_position() const { return m_position; }

private:
    Mouse::Button m_button;
    sf::Vector2i m_position;
};
