#pragma once

#include "GameObject.hpp"
#include "core-events/UpdateEvent.hpp"
#include "event/EventManager.hpp"

class EntitySystem;

class Entity : public GameObject, public std::enable_shared_from_this<Entity> {
public:
    Entity(const sf::Vector2f& position, const sf::Vector2f& dimensions, EventManager& eventManager);
    [[nodiscard]] bool does_collide(const GameObject& object) override;
    [[nodiscard]] sf::Vector2f get_position() const;
    virtual void update(const UpdateEvent& event, EntitySystem& entitySystem) {}
    void set_position(const sf::Vector2f& pos);

protected:
    sf::Texture m_texture;
    std::optional<sf::Sprite> m_sprite;
    EventManager& m_eventManager;
};