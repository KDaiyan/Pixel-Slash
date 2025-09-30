#pragma once

#include "SpriteSet.hpp"
#include "EntitySystem.hpp"
#include "LivingEntity.hpp"
#include "PathFinding.hpp"
#include "core-events/UpdateEvent.hpp"

class Player;

class Mob final : public LivingEntity {
public:
    Mob(Player& player, const sf::Vector2f& position, EventManager& eventManager);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(const UpdateEvent& event, EntitySystem& entitySystem) override;
    bool does_collide(const GameObject &object) override;

private:
    void attack();

    std::reference_wrapper<Player> m_player;
    float m_actionTimer {};

    SpriteSet m_spriteSet {
        Assets::Entity::Orc_Idle,
        Assets::Entity::Orc_Walk,
        Assets::Entity::Orc_Attack,
        Assets::Entity::Orc_Damaged,
        Assets::Entity::Orc_Death
    };
};