#include "Map.hpp"

#include "Renderer.hpp"
#include "AssetMap.hpp"

Map::Map(const Asset& asset)
   : GameObject(RenderPriority::Background)
{
    const auto path = AssetHandler::get_path(asset);

    m_texture = sf::Texture(path.get());
    m_sprite = sf::Sprite(m_texture);
    m_sprite->setPosition(m_position);
}

sf::Sprite Map::get_sprite() const {
    return *m_sprite;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto& window = Renderer::get_window();
    window.draw(*m_sprite);
}