#pragma once

#include "Renderable.hpp"

class GameObject : public Renderable {
public:
    GameObject() = delete;

    GameObject(const sf::Vector2f& pos, const sf::Vector2f& dimensions, const RenderPriority renderPriority)
        : Renderable(pos, dimensions, renderPriority) {}

    // For builder type objects, position and dimension are initialized later
    explicit GameObject(const RenderPriority renderPriority)
        : Renderable({0,0}, {0,0}, renderPriority) {}

    virtual bool does_collide(const GameObject& object) { return false; }

    virtual bool does_collide(const sf::FloatRect& rect) {
        const auto& bounds = this->get_bounds();
        return static_cast<bool>(bounds.findIntersection(rect));
    }
};
