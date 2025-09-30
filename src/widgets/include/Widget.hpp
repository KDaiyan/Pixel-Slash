#pragma once

#include <SFML/Graphics.hpp>
#include "Renderable.hpp"
#include "GameObject.hpp"
#include "core-events/MousePressEvent.hpp"
#include "core-events/MouseReleaseEvent.hpp"
#include "core-events/KeyPressEvent.hpp"
#include "core-events/KeyReleaseEvent.hpp"

class Widget : public GameObject {
public:
    Widget() : GameObject(RenderPriority::Button) {}
    void set_dimensions(const sf::Vector2f& dimensions) { m_dimensions = dimensions; }
    [[nodiscard]] sf::Vector2f get_dimensions() const { return m_dimensions; }
    void set_position(const sf::Vector2f& position) { m_position = position; }
    [[nodiscard]] sf::Vector2f get_position() const { return m_position; }
    ~Widget() override = default;

protected:
    virtual void on_mouse_click_callback(const MousePressEvent& mouse_press_event) {}
    virtual void on_mouse_release_callback(const MouseReleaseEvent& mouse_release_event) {}
    virtual void on_key_pressed_callback(const KeyPressEvent& key_press_event) {}
    virtual void on_key_release_callback(const KeyReleaseEvent& key_release_event) {}
    virtual void set_hover_state(const bool state) {}
};
