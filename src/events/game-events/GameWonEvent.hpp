#pragma once

#include "event/Event.hpp"

class GameWonEvent final : public Event {
public:
    GameWonEvent() = default;
};