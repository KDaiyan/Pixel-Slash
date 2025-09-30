#pragma once

#include <memory>
#include <vector>
#include <ranges>
#include "GameObject.hpp"
#include "event/EventManager.hpp"
#include "core-events/KeyPressEvent.hpp"
#include "core-events/KeyReleaseEvent.hpp"
#include "core-events/MouseMovedEvent.hpp"
#include "core-events/MousePressEvent.hpp"
#include "core-events/UpdateEvent.hpp"

class Scene {
public:
    virtual ~Scene() = default;
    virtual void on_key_press([[maybe_unused]] const KeyPressEvent& event) {}
    virtual void on_key_release([[maybe_unused]] const KeyReleaseEvent& event) {}
    virtual void on_mouse_press([[maybe_unused]] const MousePressEvent& event) {}
    virtual void on_mouse_move([[maybe_unused]] const MouseMovedEvent& event) {}
    virtual void on_update([[maybe_unused]] const UpdateEvent& event) {}
    virtual void initialize_events() {}
    void render();

protected:
    std::vector<std::weak_ptr<GameObject>> m_gameObjects;
    EventManager m_eventManager;

    template <typename... Object>
    requires (std::derived_from<typename Object::element_type, GameObject> && ...)
    void add_game_objects(const Object&... objects) {
        (m_gameObjects.emplace_back(objects), ...);

        // Prune once to be safe, don't have to check again during the sort
        std::erase_if(m_gameObjects, [](const std::weak_ptr<GameObject>& wptr) {
            return wptr.expired();
        });

        std::ranges::sort(m_gameObjects, [](const std::weak_ptr<GameObject>& a, const std::weak_ptr<GameObject>& b) {
            return a.lock()->get_render_priority() < b.lock()->get_render_priority();
        });
    }

};