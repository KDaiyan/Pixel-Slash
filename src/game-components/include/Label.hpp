#pragma once

#include "GameObject.hpp"
#include "AssetList.hpp"

class Label final : public GameObject {
public:
    Label(const Asset &asset, const sf::Vector2f& pos);
    sf::Sprite get_sprite() const;
    bool does_collide(const GameObject& object) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::Texture m_texture;
    std::optional<sf::Sprite> m_sprite;
};