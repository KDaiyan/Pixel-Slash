#pragma once

#include "GameObject.hpp"
#include "Renderer.hpp"
#include "AssetMap.hpp"

class Pillar final : public GameObject {
public:
    Pillar(uint32_t height, const sf::Vector2f& position);
    bool does_collide(const GameObject &object) override;
    bool does_collide(const sf::FloatRect &rect) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    uint32_t m_height;
    sf::Texture m_pillarTexture;
    sf::Texture m_headTexture;
    std::optional<sf::Sprite> m_pillarSprite;
    std::optional<sf::Sprite> m_headSprite;
};
