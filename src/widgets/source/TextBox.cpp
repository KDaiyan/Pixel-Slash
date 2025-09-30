#include "TextBox.hpp"

#include "Renderer.hpp"

void TextBox::construct_text() {
    m_textObject = sf::Text{m_font, m_text.data(), m_textSize};
    m_textObject->setFillColor(m_color);
    m_textObject->setPosition(m_position);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto& window = Renderer::instance().get_window();
    window.draw(*m_textObject);
}

