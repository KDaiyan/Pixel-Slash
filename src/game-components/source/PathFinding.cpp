#include "PathFinding.hpp"

#include <bits/ranges_algo.h>
#include "Pillar.hpp"
#include "Constants.hpp"

Direction PathFinding::get_direction(const Entity& mob, const Entity& player, const std::span<const std::shared_ptr<GameObject>> collidableObjects) {
    const auto mobPos = mob.get_position();
    const auto playerPos = player.get_position();

    const auto mobTile = sf::Vector2i(static_cast<int32_t>(mobPos.x / Constants::tileSize), static_cast<int32_t>(mobPos.y / Constants::tileSize));
    const auto playerTile = sf::Vector2i(static_cast<int32_t>(playerPos.x / Constants::tileSize), static_cast<int32_t>(playerPos.y / Constants::tileSize));

    if (mobTile.x < playerTile.x) {
        sf::Vector2i next(mobTile.x + 1, mobTile.y);
        if (!is_blocked(next, collidableObjects)) {
            return Direction::Right;
        }
    }
    else if (mobTile.x > playerTile.x) {
        sf::Vector2i next(mobTile.x - 1, mobTile.y);
        if (!is_blocked(next, collidableObjects)) {
            return Direction::Left;
        }
    }

    return Direction::Left; // Random default (cases are handled outside)
}

bool PathFinding::is_blocked(const sf::Vector2i& pos, std::span<const std::shared_ptr<GameObject>> collidableObjects) {
    sf::FloatRect testArea(
        sf::Vector2f(static_cast<float>(pos.x) * Constants::tileSize, static_cast<float>(pos.y) * Constants::tileSize),
        sf::Vector2f(Constants::tileSize, Constants::tileSize)
    );

    return std::ranges::any_of(collidableObjects, [&](const auto& obj) {
        if (std::dynamic_pointer_cast<Pillar>(obj)) {
            return false; // Pillar dimensions is technically entire pillar, hence collision from objects side is true
        }

        return obj->does_collide(testArea);
    });
}