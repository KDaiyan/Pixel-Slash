#pragma once

#include <concepts>
#include <functional>
#include "Widget.hpp"
#include "ButtonWidget.hpp"
#include "AssetList.hpp"
#include "TextBox.hpp"

class WidgetBuilder {
public:
    WidgetBuilder& set_dimensions(const sf::Vector2f& dimensions);
    WidgetBuilder& set_position(const sf::Vector2f& position);
    WidgetBuilder& set_texture(const Asset& asset);
    WidgetBuilder& set_text(std::string_view text);
    WidgetBuilder& set_font(const Asset& asset);
    WidgetBuilder& set_text_size(uint32_t size);
    WidgetBuilder& set_text_color(sf::Color color);
    WidgetBuilder& set_click_callback(const std::function<void(MousePressEvent)>& callback);

    template <typename WidgetType> requires std::derived_from<WidgetType, Widget>
    std::shared_ptr<WidgetType> build() {
        auto widget = std::make_shared<WidgetType>();
        widget->set_dimensions(*m_dimensions);
        widget->set_position(*m_position);
        this->configure(widget);
        this->reset_members();

        return widget;
    }

private:
    template <typename T>
    static void configure(const std::shared_ptr<T>&) {}
    void configure(const std::shared_ptr<ButtonWidget>& widget) const;
    void configure(const std::shared_ptr<TextBox>& widget) const;
    void reset_members();

    std::optional<sf::Texture> m_texture;
    std::optional<sf::Vector2f> m_position;
    std::optional<sf::Vector2f> m_dimensions;
    std::optional<sf::Font> m_font;
    std::optional<std::string_view> m_text;
    std::optional<uint32_t> m_textSize;
    std::optional<sf::Color> m_textColor;
    std::optional<std::function<void(MousePressEvent)>> m_clickCallback;
};
