#include "ButtonWidget.hpp"

#include "Renderer.hpp"

void ButtonWidget::set_hover_state(const bool state) {
    m_highlighted = state;

    if (m_highlighted) {
        m_sprite->setColor(sf::Color(255, 255, 255, 180));
    } else {
        m_sprite->setColor(sf::Color::White);
    }
}

void ButtonWidget::on_mouse_click_callback(const MousePressEvent& mouse_press_event) {
    m_clickCallback(mouse_press_event);
}

void ButtonWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto& window = Renderer::get_window();
    window.draw(*m_sprite);
}

void ButtonWidget::set_texture_and_sprite(const sf::Texture& texture) {
    m_texture = texture;
    m_sprite = sf::Sprite{m_texture};
    m_sprite->setPosition(m_position);
}

bool ButtonWidget::does_mouse_collide() const {
    if(!m_sprite) return false;

    const auto& window = Renderer::get_window();
    const auto mouse_world_pos = window.mapPixelToCoords(Mouse::getPosition(window));

    return m_sprite->getGlobalBounds().contains(mouse_world_pos);
}
