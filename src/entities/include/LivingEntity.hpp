#pragma once

#include "Entity.hpp"
#include "EntityState.hpp"
#include "SpriteSet.hpp"

class LivingEntity : public Entity {
public:
    LivingEntity(const sf::Vector2f& position, const sf::Vector2f& dimensions, uint32_t health, EventManager& eventManager);
    void damage();

protected:
    void add_action(EntityState state);

    std::optional<EntityState> m_actionBuffer; // For non-persisting actions like swing, damage, and death
    EntityState m_state = EntityState::Idle;
    Direction m_direction = Direction::Right;
    bool m_isMidAir = true;
    float m_attackCooldown {};
    uint32_t m_health;
    sf::Vector2f m_velocity;
};
