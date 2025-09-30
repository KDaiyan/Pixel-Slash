#include "Player.hpp"

#include <iostream>
#include <ranges>
#include <bits/ranges_algo.h>
#include "EntitySystem.hpp"
#include "Constants.hpp"
#include "Mob.hpp"
#include "game-events/PlayerDiedEvent.hpp"

namespace {
    std::optional<std::reference_wrapper<Mob>> get_target_mob(const std::vector<std::weak_ptr<Mob>>& enemies, const Player& player, const Direction direction) {
        if(enemies.empty()) return std::nullopt;

        const auto playerPos = player.get_position();

        auto range = enemies
            | std::views::transform([](auto& wPtr) { return wPtr.lock(); })
            | std::views::filter([](auto const& sPtr) { return static_cast<bool>(sPtr); });

        const auto it = std::ranges::find_if(range, [&](const std::shared_ptr<Mob>& mob) {
            const auto mobPos = mob->get_position();
            const float distanceX = mobPos.x - playerPos.x;
            const float distanceY = mobPos.y - playerPos.y;

            const bool isValidAttack = std::abs(distanceX) < Constants::playerAttackRange
                                     && std::abs(distanceY) < Constants::HeightMarginError;
            const bool isDirectionAligned = (direction == Direction::Right && distanceX > 0)
                                          || (direction == Direction::Left && distanceX < 0);

            return isValidAttack && isDirectionAligned;
        });

        if(it != std::ranges::end(range)) {
            return std::ref(**it);
        }
        return std::nullopt;
    }
}


Player::Player(const sf::Vector2f& position, EventManager& eventManager, const uint32_t health)
      : LivingEntity(position, Constants::entityDimensions, health, eventManager)
{
    constexpr auto entityWidth = static_cast<uint32_t>(Constants::entityDimensions.x);
    constexpr auto entityHeight = static_cast<uint32_t>(Constants::entityDimensions.y);

    if(const auto image = sf::Image({entityWidth, entityHeight}); m_texture.loadFromImage(image)) {
        m_sprite = sf::Sprite(m_texture);
    }

    assert(m_sprite);
    m_sprite->setPosition(position);
}

void Player::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    m_spriteSet.draw(target, states);
}

void Player::apply_velocity(const sf::Vector2f& velocity) {
    m_velocity += velocity;
}

void Player::jump() {
    if(!m_isMidAir) {
        apply_velocity({0.f, -750.f});
    }
}

void Player::attack() {
    if(m_isAttackOnCD) return;

    // set attack cooldowns and play attack animation
    this->add_action(EntityState::Attack);

    if(const auto targetMob = get_target_mob(m_enemies, *this, m_direction)) {
        targetMob.value().get().damage();
    }

    m_isAttackOnCD = true;
    this->reset_attack_cooldown();
}

bool Player::does_collide(const GameObject &object) {
    const auto& bounds = this->get_bounds();
    return static_cast<bool>(bounds.findIntersection(object.get_bounds()));
}

void Player::update(const UpdateEvent& event, EntitySystem& entitySystem) {
    const float dt = event.get_dt();
    const auto& collidableObjects = entitySystem.get_collidableObjects();

    m_enemies = entitySystem.get_mobs();

    if(m_health <= 0 && m_state == EntityState::Dead) {
        m_eventManager.fire(PlayerDiedEvent{m_position});
        entitySystem.remove_entity(this->shared_from_this());
        return;
    }

    // Evaluate attack CD
    if(m_isAttackOnCD) {
        m_attackCooldown -= dt;
        if (m_attackCooldown <= 0.f) {
            m_isAttackOnCD = false;
            m_attackCooldown = 0.f;
        }
    }

    this->evaluate_collisions(dt, collidableObjects);
    this->evaluate_horizontal_movement();
    m_spriteSet.update(m_state, m_direction, m_sprite->getPosition(), m_actionBuffer);
}

// SFML recommends using real-time keyboard input over events for smooth movement here
void Player::evaluate_horizontal_movement() {
    const auto set_movement = [&](const float velocity, const Direction direction, const EntityState state) {
        m_velocity.x = velocity;
        m_direction = direction;
        if (!m_actionBuffer) m_state = state;
    };

    if (isKeyPressed(sf::Keyboard::Scan::A)) {
        set_movement(-Constants::horizontalVelocity, Direction::Left, EntityState::Walking);
    }
    else if (isKeyPressed(sf::Keyboard::Scan::D)) {
        set_movement(Constants::horizontalVelocity, Direction::Right, EntityState::Walking);
    }
    else {
        set_movement(0.f, m_direction, EntityState::Idle);
    }
}

void Player::evaluate_collisions(const float dt, std::span<const std::shared_ptr<GameObject>> collidableObjects) {
    m_velocity.y += Constants::gravity * dt;
    sf::Vector2f nextPosition = m_position;

    auto testRect = this->get_bounds();

    // Horizontal movement
    nextPosition.x += m_velocity.x * dt;
    testRect.position = nextPosition;

    if (std::ranges::any_of(collidableObjects, [&](const auto& obj) { return obj->does_collide(testRect); })) {
        nextPosition.x = m_position.x;
        m_velocity.x = 0.f;
    }

    // Clamp horizontal movement so player can't walk out of map
    const float clampedX = std::clamp(
        nextPosition.x,
        Constants::mapBounds.position.x,
        Constants::mapBounds.position.x + Constants::mapBounds.size.x - 5.f
    );

    if (clampedX != nextPosition.x) {
        nextPosition.x = clampedX;
        m_velocity.x = 0.f;
    }

    // Vertical movement
    nextPosition.y += m_velocity.y * dt;
    testRect.position = nextPosition;

    m_isMidAir = true;

    if (std::ranges::any_of(collidableObjects, [&](const auto& obj) { return obj->does_collide(testRect); })) {
        nextPosition.y = m_position.y;
        m_velocity.y = 0.f;
        m_isMidAir = false;
    }

    const float clampedY = std::clamp(
        nextPosition.y,
        Constants::mapBounds.position.y,
        Constants::mapBounds.position.y + Constants::mapBounds.size.y
    );
    if (clampedY != nextPosition.y) {
        nextPosition.y = clampedY;
        m_velocity.y = 0.f;
        m_isMidAir = false;
    }

    this->set_position(nextPosition);
}

void Player::reset_attack_cooldown() {
    m_attackCooldown = Constants::attackCooldown;
}