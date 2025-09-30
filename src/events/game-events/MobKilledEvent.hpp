#pragma once

#include "event/Event.hpp"

class MobKilledEvent final : public Event {
public:
    MobKilledEvent() = default;
};
