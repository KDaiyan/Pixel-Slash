#include "Label.hpp"

#include "Renderer.hpp"
#include "AssetMap.hpp"

Label::Label(const Asset &asset, const sf::Vector2f& pos)
     : GameObject(RenderPriority::Background_Overlay)
{
    m_position = pos;
    const auto path = AssetHandler::get_path(asset);
    m_texture = sf::Texture(path.get());
    m_sprite = sf::Sprite(m_texture);
    m_sprite->setPosition(m_position);
}

sf::Sprite Label::get_sprite() const {
    return *m_sprite;
}

bool Label::does_collide(const GameObject& object) {
    const auto& bounds = this->get_bounds();
    return static_cast<bool>(bounds.findIntersection(object.get_bounds()));
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto& window = Renderer::instance().get_window();
    window.draw(*m_sprite);
}