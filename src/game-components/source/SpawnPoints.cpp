#include "SpawnPoints.hpp"

#include <fstream>
#include "Constants.hpp"
#include "Random.hpp"

namespace {
    template <std::ranges::range Container>
    Container& parse_data(const std::filesystem::path& filePath, Container& container) {
        auto file = std::ifstream(filePath);
        if(!file) {
            std::perror("File failed to open");
        }

        auto json = nlohmann::json();
        file >> json;

        std::ranges::transform(json, std::inserter(container, container.end()), [&](const auto& entry) {
            return sf::Vector2f(entry["x"], entry["y"]);
        });

        return container;
    }
}

SpawnPoints& SpawnPoints::get_instance() {
    static SpawnPoints spawn_points;
    return spawn_points;
}

sf::Vector2f SpawnPoints::get_random_coin(std::vector<sf::Vector2f>& coins) {
    const auto index = Random::get(0, static_cast<int32_t>(coins.size()  - 1));
    const sf::Vector2f value = coins.at(index);
    coins.erase(coins.begin() + index);

    return value;
}

const std::vector<sf::Vector2f>& SpawnPoints::get_coins() const{
    return m_coinPositions;
}

const std::vector<sf::Vector2f>& SpawnPoints::get_mob_positions() const {
    return m_mobPositions;
}

const std::vector<std::pair<uint32_t, sf::Vector2f>>& SpawnPoints::get_pillars() const {
    return m_pillars;
}

SpawnPoints::SpawnPoints() {
    m_coinPositions = parse_data(Constants::coinPath.get(), m_coinPositions);
    m_mobPositions = parse_data(Constants::mobPath.get(), m_mobPositions);
    m_pillarPositions = parse_data(Constants::pillarPath.get(), m_pillarPositions);

    // Use the pillar heights and positions to create the pairs
    for (auto [h, pos] : std::views::zip(m_pillarHeights, m_pillarPositions)) {
        m_pillars.emplace_back(h, pos);
    }
}