#include "Scene.hpp"

#include "CollisionMap.hpp"
#include "Renderer.hpp"

void Scene::render() {
    auto& window = Renderer::instance().get_window();
    window.clear();

    std::erase_if(m_gameObjects, [&](const std::weak_ptr<GameObject>& wptr) { return wptr.expired(); });

    std::ranges::for_each(m_gameObjects, [&](const std::weak_ptr<GameObject>& wp) {
        if(const auto object = wp.lock()) window.draw(*object);
    });

    window.display();
}