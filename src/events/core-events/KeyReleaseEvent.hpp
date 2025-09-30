#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "event/Event.hpp"

namespace Key = sf::Keyboard;

class KeyReleaseEvent final : public Event {
public:
    explicit KeyReleaseEvent(const Key::Scancode key) : m_scanCode(key) {}
    [[nodiscard]] const Key::Scancode& get_scan_code() const { return m_scanCode; }

private:
    Key::Scancode m_scanCode;
};

