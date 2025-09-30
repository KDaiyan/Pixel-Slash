#include "EntitySystem.hpp"

#include <bits/ranges_algo.h>

void EntitySystem::update(const UpdateEvent& event) {
    for(const auto& entity : m_entities) entity->update(event, *this);

    // Clear all the removed entities
    if(!m_eraseQueue.empty()) {
        std::erase_if(m_entities, [&](const std::shared_ptr<Entity>& entity) {
           return m_eraseQueue.contains(entity.get());
        });

        m_eraseQueue.clear();
    }
}

std::vector<std::shared_ptr<GameObject>> EntitySystem::get_collidableObjects() const {
    return m_collidableObjects;
}

void EntitySystem::set_player_entity(std::shared_ptr<Player>&& player) {
    m_player = std::move(player);
    m_entities.push_back(m_player);
}

std::weak_ptr<Player> EntitySystem::get_player_entity() const {
    return m_player;
}

void EntitySystem::remove_entity(const std::shared_ptr<Entity>& entity) {
    m_eraseQueue.insert(entity.get()); // Erase has to be done along with update (or we mess up start and end range of vector)
}

std::vector<std::weak_ptr<Mob>> EntitySystem::get_mobs() {
    // Get rid of all expired pointers before returning
    auto range = std::ranges::remove_if(m_mobs,
    [](const std::weak_ptr<Mob>& mob) { return mob.expired(); });

    m_mobs.erase(range.begin(), range.end());

    return m_mobs;
}