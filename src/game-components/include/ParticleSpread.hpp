#pragma once

#include "Constants.hpp"

struct ParticleSpread {
    static constexpr sf::Vector2f Small {10.f, 10.f};
    static constexpr sf::Vector2f Large {30.f, 30.f};
    static constexpr sf::Vector2f None {0.f, 0.f};
    static constexpr sf::Vector2f Random {Constants::screenDimensions}; // Random means range of entire screen
};
