#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include "MenuScene.hpp"
#include "Renderer.hpp"
#include "core-events/KeyPressEvent.hpp"
#include "core-events/KeyReleaseEvent.hpp"
#include "core-events/MouseMovedEvent.hpp"

namespace Game {

void begin() {
    Renderer::init();

    auto& window = Renderer::get_window();
    auto clock = sf::Clock();

    // Create all callbacks
    const auto onClose = [&](const sf::Event::Closed&){
        window.close();
    };

    const auto onUpdate = [&](const float dt) {
        g_scenes.front()->on_update(UpdateEvent{dt});
    };

    const auto onKeyPressed = [&](const sf::Event::KeyPressed& keyPressed){
        g_scenes.front()->on_key_press(KeyPressEvent{keyPressed.scancode});
    };

    const auto onKeyRelease = [&](const sf::Event::KeyReleased& keyReleased) {
        g_scenes.front()->on_key_release(KeyReleaseEvent{keyReleased.scancode});
    };

    const auto onMousePress = [&](const sf::Event::MouseButtonPressed& mousePressed) {
        g_scenes.front()->on_mouse_press(MousePressEvent{mousePressed.button, mousePressed.position});
    };

    const auto onMouseMove = [&](const sf::Event::MouseMoved& mouseMoved) {
        g_scenes.front()->on_mouse_move(MouseMovedEvent{mouseMoved.position});
    };

    // Initialize the main menu scene
    push_scene(std::make_unique<MenuScene>());

    while(window.isOpen()) {
        window.handleEvents(onClose, onKeyPressed, onKeyRelease, onMousePress, onMouseMove);

        const auto dt = clock.restart().asSeconds();
        onUpdate(dt);

        g_scenes.front()->render();
    }
}

void push_scene(std::unique_ptr<Scene>&& scene) {
    g_scenes.push_front(std::move(scene));
}

void pop_back_scene() {
    g_scenes.pop_back();
}

void clear_scenes() {
    g_scenes.clear();
}

}