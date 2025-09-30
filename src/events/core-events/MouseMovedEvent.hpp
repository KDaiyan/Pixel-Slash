#pragma once

#include "event/Event.hpp"

class MouseMovedEvent final : public Event {
public:
    explicit MouseMovedEvent(const sf::Vector2i& pos) : m_position(pos) {}
    [[nodiscard]] const sf::Vector2i& get_position() const { return m_position; }

private:
    sf::Vector2i m_position;
};