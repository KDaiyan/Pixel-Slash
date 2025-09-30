#include "Entity.hpp"

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& dimensions, EventManager& eventManager)
      : GameObject(position, dimensions, RenderPriority::Entity),
        m_eventManager(eventManager) {}

bool Entity::does_collide(const GameObject& object) {
    const auto& bounds = this->get_bounds();
    return static_cast<bool>(bounds.findIntersection(object.get_bounds()));
}

sf::Vector2f Entity::get_position() const {
    return m_position;
}

void Entity::set_position(const sf::Vector2f& pos) { m_position = pos; m_sprite->setPosition(m_position); }