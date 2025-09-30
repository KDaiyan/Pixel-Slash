#pragma once

#include "GameObject.hpp"
#include "AssetList.hpp"

class Map final : public GameObject {
public:
    explicit Map(const Asset &asset);
    sf::Sprite get_sprite() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::Texture m_texture;
    std::optional<sf::Sprite> m_sprite;
};