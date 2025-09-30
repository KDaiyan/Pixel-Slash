#pragma once

#include <cstdint>

struct Statistics {
    Statistics(const uint32_t mobs, const uint32_t coins) : mobsTotal(mobs), coinsTotal(coins) {}

    float elapsedTime {};
    uint32_t mobsKilled {};
    uint32_t mobsTotal {};
    uint32_t coinsCollected {};
    uint32_t coinsTotal {};
    bool winStatus {};
};
