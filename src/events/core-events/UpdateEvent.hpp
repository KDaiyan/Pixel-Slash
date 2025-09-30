#pragma once

#include "event/Event.hpp"

class UpdateEvent final : public Event {
public:
    explicit UpdateEvent(const float dt) : m_dt(dt) {}
    [[nodiscard]] const float& get_dt() const { return m_dt; }

private:
    float m_dt;
};
