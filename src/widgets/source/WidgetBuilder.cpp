#include "WidgetBuilder.hpp"

#include "AssetMap.hpp"

WidgetBuilder& WidgetBuilder::set_dimensions(const sf::Vector2f& dimensions) {
    m_dimensions = dimensions;
    return *this;
}

WidgetBuilder& WidgetBuilder::set_position(const sf::Vector2f& position) {
    m_position = position;
    return *this;
}

WidgetBuilder& WidgetBuilder::set_texture(const Asset& asset) {
    const auto path = AssetHandler::get_path(asset);
    m_texture = sf::Texture{path.get()};
    return *this;
}

WidgetBuilder& WidgetBuilder::set_text(std::string_view text) {
    m_text = text;
    return *this;
}

WidgetBuilder& WidgetBuilder::set_font(const Asset& asset) {
    const auto path = AssetHandler::get_path(asset);
    const auto font = sf::Font{path.get()};

    m_font = font;
    return *this;
}

WidgetBuilder& WidgetBuilder::set_text_size(const uint32_t size) {
    m_textSize = size;
    return *this;
}

void WidgetBuilder::configure(const std::shared_ptr<ButtonWidget>& widget) const {
    widget->set_click_callback(m_clickCallback.value());
    widget->set_texture_and_sprite(m_texture.value());
}

void WidgetBuilder::configure(const std::shared_ptr<TextBox>& widget) const {
    widget->set_font(m_font.value());
    widget->set_text_size(m_textSize.value());
    widget->set_text(m_text.value());
    widget->set_color(m_textColor.value());
    widget->construct_text();
}

WidgetBuilder& WidgetBuilder::set_text_color(const sf::Color color) {
    m_textColor = color;
    return *this;
}

WidgetBuilder& WidgetBuilder::set_click_callback(const std::function<void(MousePressEvent)>& callback) {
    m_clickCallback = callback;

    return *this;
}

void WidgetBuilder::reset_members() {
    m_clickCallback.reset();
    m_texture.reset();
    m_position.reset();
    m_dimensions.reset();
    m_font.reset();
    m_text.reset();
    m_textSize.reset();
    m_textColor.reset();
}