#include "LivingEntity.hpp"

namespace {
    // Priority goes Death -> Damaged -> Attack
    int32_t get_priority(const EntityState state) {
        switch (state) {
            case EntityState::Dying:   return 3;
            case EntityState::Damaged: return 2;
            case EntityState::Attack:  return 1;
            default:                   std::unreachable();
        }
    }
}

LivingEntity::LivingEntity(const sf::Vector2f& position, const sf::Vector2f& dimensions, const uint32_t health, EventManager& eventManager)
    : Entity(position, dimensions, eventManager),
      m_health(health) {}

void LivingEntity::damage() {
    if(m_health > 1) {
        this->add_action(EntityState::Damaged);
    }
    else if (m_health == 1) {
        this->add_action(EntityState::Dying);
    }
    m_health--;
}

void LivingEntity::add_action(const EntityState state) {
    assert(state == EntityState::Attack || state == EntityState::Damaged || state == EntityState::Dying);

    if(m_actionBuffer) {
        if (get_priority(state) > get_priority(m_actionBuffer.value())) {
            m_actionBuffer = state;
        }
    } else {
        m_actionBuffer = state;
    }
}