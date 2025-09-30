#pragma once

#include <nlohmann/json.hpp>
#include <SFML/System/Vector2.hpp>

class SpawnPoints {
public:
    [[nodiscard]] static SpawnPoints& get_instance();
    [[nodiscard]] const std::vector<sf::Vector2f>& get_mob_positions() const;
    [[nodiscard]] const std::vector<std::pair<uint32_t, sf::Vector2f>>& get_pillars() const;
    [[nodiscard]] const std::vector<sf::Vector2f>& get_coins() const;
    [[nodiscard]] static sf::Vector2f get_random_coin(std::vector<sf::Vector2f>& coins);

private:
    SpawnPoints();

    std::vector<sf::Vector2f> m_coinPositions {};
    std::vector<sf::Vector2f> m_mobPositions {};
    std::vector<sf::Vector2f> m_pillarPositions {};
    std::vector<uint32_t> m_pillarHeights {6, 9, 5}; // pretend like this is not hard-coded (it's 3 numbers give me a break)
    std::vector<std::pair<uint32_t, sf::Vector2f>> m_pillars {};
};