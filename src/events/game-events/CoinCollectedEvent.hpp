#pragma once

#include "event/Event.hpp"

class CoinCollectedEvent final : public Event {
public:
    CoinCollectedEvent() = default;
};
