#pragma once

#include "event/Event.hpp"

class PlayerDiedEvent final : public Event {
public:
    explicit PlayerDiedEvent(const sf::Vector2f& pos) : m_playerPos(pos) {}
    [[nodiscard]] sf::Vector2f get_player_pos() const { return m_playerPos; }

private:
    sf::Vector2f m_playerPos;
};