#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"
#include "Entity.hpp"
#include "Direction.hpp"

class PathFinding {
public:
    [[nodiscard]] static Direction get_direction(const Entity& mob, const Entity& player, std::span<const std::shared_ptr<GameObject>> collidableObjects);

private:
    static bool is_blocked(const sf::Vector2i& pos, std::span<const std::shared_ptr<GameObject>> collidableObjects);
};