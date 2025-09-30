#pragma once

#include <functional>
#include "Widget.hpp"

class ButtonWidget final : public Widget {
public:
    void set_hover_state(bool state) override;
    void on_mouse_click_callback(const MousePressEvent& mouse_press_event) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void set_click_callback(const std::function<void(MousePressEvent)>& callback) { m_clickCallback = callback; }
    void set_texture(const sf::Texture& texture) { m_texture = texture; }
    void set_texture_and_sprite(const sf::Texture& texture);
    bool does_mouse_collide() const;

private:
    sf::Texture m_texture;
    std::optional<sf::Sprite> m_sprite;
    bool m_highlighted = false;
    std::function<void(MousePressEvent)> m_clickCallback;
};
