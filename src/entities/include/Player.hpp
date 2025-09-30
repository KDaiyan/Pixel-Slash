#pragma once

#include "LivingEntity.hpp"
#include "SpriteSet.hpp"

class Mob;
class EntitySystem;

class Player final : public LivingEntity {
public:
    Player(const sf::Vector2f& position, EventManager& eventManager, uint32_t health = 10u);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void apply_velocity(const sf::Vector2f& velocity);
    void jump();
    void attack();
    void reset_attack_cooldown();
    bool does_collide(const GameObject& object) override;
    void update(const UpdateEvent& event, EntitySystem& entitySystem) override;

private:
    void evaluate_horizontal_movement();
    void evaluate_collisions(float dt, std::span<const std::shared_ptr<GameObject>> collidableObjects);

    std::vector<std::weak_ptr<Mob>> m_enemies;
    bool m_isAttackOnCD = false;

    SpriteSet m_spriteSet {
        Assets::Entity::Soldier_Idle,
        Assets::Entity::Soldier_Walk,
        Assets::Entity::Soldier_Attack,
        Assets::Entity::Soldier_Damaged,
        Assets::Entity::Soldier_Death
    };

};