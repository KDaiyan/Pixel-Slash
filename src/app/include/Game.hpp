#pragma once

#include <deque>
#include "Scene.hpp"

namespace Game {
    void begin();
    void push_scene(std::unique_ptr<Scene>&& scene);
    void pop_back_scene();
    void clear_scenes();

    inline std::deque<std::unique_ptr<Scene>> g_scenes;
}