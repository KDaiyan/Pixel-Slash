#include "Mob.hpp"

#include <cmath>
#include "Renderer.hpp"
#include "Constants.hpp"
#include "game-events/MobKilledEvent.hpp"

namespace {
    EntityState evaluate_action_state(const sf::Vector2f& mobPosition, const sf::Vector2f& playerPosition) {
        const auto [mob_x, mob_y] = mobPosition;
        const auto [player_x, player_y] = playerPosition;

        const float verticalDiff = std::abs(player_y - mob_y);
        const float distance = std::hypot(mob_x - player_x, mob_y - player_y);

        if (verticalDiff > Constants::HeightMarginError) {
            return EntityState::Idle;
        }
        if (distance <= Constants::mobAttackRange) {
            return EntityState::Attack;
        }
        if (distance <= Constants::targetRange) {
            return EntityState::Walking;
        }
        return EntityState::Idle;
    }

    sf::Vector2f get_dir_vector(const Direction direction) {
        switch (direction) {
            case Direction::Left:  return {-1.f, 0.f};
            case Direction::Right: return { 1.f, 0.f};
            case Direction::Up:    return { 0.f,-1.f};
            case Direction::Down:  return { 0.f, 1.f};
        }
        std::unreachable();
    }
}


Mob::Mob(Player& player, const sf::Vector2f& position, EventManager& eventManager)
   : LivingEntity(position, Constants::entityDimensions, Constants::mobHealth, eventManager),
     m_player(player)
{
    constexpr auto entityWidth = static_cast<uint32_t>(Constants::entityDimensions.x);
    constexpr auto entityHeight = static_cast<uint32_t>(Constants::entityDimensions.y);

    if(const auto image = sf::Image({entityWidth, entityHeight}); m_texture.loadFromImage(image)) {
        m_sprite = sf::Sprite(m_texture);
    }

    m_sprite->setPosition(position);
}

void Mob::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    m_spriteSet.draw(target, states);
}

void Mob::attack() {
    // Attack and play attack animation
    auto& player = m_player.get();

    // Look at the player if not already (if player jumps behind mob, it doesn't change facing direction)
    m_direction = [&] {
        const auto playerPos = m_player.get().get_position();
        const float distance = playerPos.x - m_position.x;
        return distance < 0.f ? Direction::Left : Direction::Right;
    }();

    player.damage();
    player.reset_attack_cooldown();
}

bool Mob::does_collide(const GameObject &object) {
    const auto& bounds = this->get_bounds();
    return static_cast<bool>(bounds.findIntersection(object.get_bounds()));
}

void Mob::update(const UpdateEvent& event, EntitySystem& entitySystem) {
    const auto& collidableObjects = entitySystem.get_collidableObjects();
    const auto dt = event.get_dt();

    m_actionTimer += dt;
    m_attackCooldown -= dt;

    // Check if the mob is dead before anything else
    if(m_health <= 0 && m_state == EntityState::Dead) {
        m_eventManager.fire(MobKilledEvent{});
        entitySystem.remove_entity(this->shared_from_this());
        return;
    }

    if (m_actionTimer >= Constants::refreshDuration) {
        m_state = evaluate_action_state(m_position, m_player.get().get_position());
        if (m_state == EntityState::Walking) {
            m_direction = PathFinding::get_direction(*this, m_player, collidableObjects);
        }
        m_actionTimer = 0.f;
    }

    // Chase Action
    if (m_state == EntityState::Walking) {
        const auto updatedPos = m_position + get_dir_vector(m_direction) * (Constants::mobSpeed * dt);
        this->set_position(updatedPos);
    }
    // Attack Action
    else if(m_state == EntityState::Attack && m_attackCooldown <= 0.f) {
        this->attack();
        m_attackCooldown = Constants::mobAttackCooldown;
    }

    m_spriteSet.update(m_state, m_direction, m_sprite->getPosition(), m_actionBuffer);
}