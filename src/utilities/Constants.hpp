#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstdint>
#include "FilePath.hpp"

namespace Constants {
    /// Generics
    inline constexpr uint8_t alphaThreshold = 10;
    inline constexpr size_t updateFrequency = 5;
    inline constexpr float HeightMarginError = 5.f;
    inline constexpr float tileSize = 16.f;

    /// Mob
    inline constexpr float mobAttackCooldown = 1.5f;
    inline constexpr float mobAttackRange = 50.f;
    inline constexpr float mobSpeed = 100.f;
    inline constexpr uint32_t mobHealth = 3u;

    /// Player
    inline constexpr float playerAttackRange = 80.f;
    inline constexpr float attackCooldown = 0.5f;
    inline constexpr float targetRange = 300.f;
    inline constexpr float horizontalVelocity = 200.f;

    /// Entity
    inline constexpr float spriteUpdateTime = 1.f / 8.f;
    inline constexpr float gravity = 980.f;
    inline constexpr float refreshDuration = 0.2f;

    /// Coin
    inline constexpr int32_t coinDimension = 48;
    inline constexpr float coinSpawnDelay = 10.f;
    inline constexpr size_t coinSpriteCount = 5;

    /// Pillar
    inline constexpr float pillarDimension = 50.f;
    inline constexpr float pillarHeadHeight = 8.f;

    /// Game specific
    inline constexpr uint32_t coinCapacity = 10u;
    inline constexpr uint32_t mobCount = 3u;
    inline constexpr uint32_t rainCount = 300u;

    /// Vector constants
    inline constexpr sf::Vector2f spriteOffset {-35.f, -23.f};
    inline constexpr sf::Vector2f entityDimensions {30.f, 55.f};
    inline constexpr sf::Vector2f screenDimensions {1920.f, 1080.f};
    inline constexpr sf::FloatRect mapBounds {{0.f, 0.f}, screenDimensions};

    /// File Paths
    inline FilePath coinPath {"data/coins.json"};
    inline FilePath mobPath {"data/mobs.json"};
    inline FilePath pillarPath {"data/pillars.json"};
}
