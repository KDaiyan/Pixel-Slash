#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include "Entity.hpp"
#include "Player.hpp"
#include "GameObject.hpp"
#include "core-events/UpdateEvent.hpp"
#include "event/EventManager.hpp"

class Entity;
class Mob;
class Player;

class EntitySystem {
public:
    explicit EntitySystem(EventManager& manager) : m_eventManager(manager) {}

    void update(const UpdateEvent& event);

    void add_collidable_objects(auto&&... objects) {
        (m_collidableObjects.push_back(std::move(objects)), ...);
    }

    void add_entities(const auto&&... entities) {
        auto add_entity = [&](auto entity) {
            if (auto mob = std::dynamic_pointer_cast<Mob>(entity)) {
                m_mobs.push_back(mob);
            }
            m_entities.push_back(std::move(entity));
        };

        (add_entity(entities), ...);
    }

    void remove_entity(const std::shared_ptr<Entity>& entity);

    void set_player_entity(std::shared_ptr<Player>&& player);

    [[nodiscard]] std::weak_ptr<Player> get_player_entity() const;
    [[nodiscard]] std::vector<std::shared_ptr<GameObject>> get_collidableObjects() const;
    [[nodiscard]] std::vector<std::weak_ptr<Mob>> get_mobs();

private:
    EventManager& m_eventManager;
    std::shared_ptr<Player> m_player;
    std::vector<std::weak_ptr<Mob>> m_mobs;
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<GameObject>> m_collidableObjects;
    std::unordered_set<Entity*> m_eraseQueue;
};
