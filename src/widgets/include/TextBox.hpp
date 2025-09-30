#pragma once

#include "Widget.hpp"

class TextBox final : public Widget {
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void set_text(const std::string_view text) { m_text = text; }
    void set_text_size(const uint32_t size) { m_textSize = size; }
    void set_font(const sf::Font& font) { m_font = font; }
    void set_color(const sf::Color color) { m_color = color; }
    void construct_text();

private:
    std::optional<sf::Text> m_textObject;
    std::string_view m_text;
    uint32_t m_textSize {};
    sf::Font m_font;
    sf::Color m_color;
};
