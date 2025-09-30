#pragma once

#include "Entity.hpp"

class Coin final : public Entity {
public:
    explicit Coin(const sf::Vector2f& position, EventManager& eventManager);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(const UpdateEvent& event, EntitySystem& entitySystem) override;

private:
    size_t spriteIterator {};
    float updateCD {};
};
