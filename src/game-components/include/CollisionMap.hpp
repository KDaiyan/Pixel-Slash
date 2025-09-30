#pragma once

#include "GameObject.hpp"
#include "AssetList.hpp"

class CollisionMap final : public GameObject {
public:
    explicit CollisionMap(const Asset& asset);
    bool does_collide(const GameObject &object) override;
    bool does_collide(const sf::FloatRect &rect) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<sf::FloatRect> m_collidableElements;
};
