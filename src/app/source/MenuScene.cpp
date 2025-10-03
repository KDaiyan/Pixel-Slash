#include "MenuScene.hpp"

#include "WidgetBuilder.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

MenuScene::MenuScene() {
    m_background = std::make_shared<Map>(Assets::Maps::Start_Menu);
    m_logo = std::make_shared<Label>(Assets::Icons::Logo, sf::Vector2f{470, 20});

    auto widgetBuilder = WidgetBuilder();

    m_playButton = widgetBuilder.set_dimensions({400, 100})
                                .set_position({760, 470})
                                .set_texture(Assets::Icons::Play_Button)
                                .set_click_callback([this](const MousePressEvent& event) { on_click_play(event); })
                                .build<ButtonWidget>();

    m_settingsButton = widgetBuilder.set_dimensions({655, 100})
                                    .set_position({635, 620})
                                    .set_texture(Assets::Icons::Settings_Button)
                                    .set_click_callback([this](const MousePressEvent& event) { on_click_settings(event); })
                                    .build<ButtonWidget>();

    m_quitButton = widgetBuilder.set_dimensions({400, 100})
                                .set_position({760, 770})
                                .set_texture(Assets::Icons::Quit_Button)
                                .set_click_callback([this](const MousePressEvent& event) { on_click_exit(event); })
                                .build<ButtonWidget>();

    this->add_game_objects(m_playButton, m_settingsButton, m_quitButton, m_logo, m_background);
}

void MenuScene::on_mouse_press(const MousePressEvent& event) {
    // Filter out all the valid button pointers, then check if they collide
    auto collidingButtons = m_gameObjects
        | std::views::transform([](const std::weak_ptr<GameObject>& object) {
            return std::dynamic_pointer_cast<ButtonWidget>(object.lock());
        })
        | std::views::filter([](const std::shared_ptr<ButtonWidget>& button) {
            return button && button->does_mouse_collide();
        });

    // Use find_if to check only first collision (should not have multiple collisions anyway)
    std::ranges::find_if(collidingButtons, [&](const std::shared_ptr<ButtonWidget>& button) {
        button->on_mouse_click_callback(event);
        return true;
    });
}

void MenuScene::on_mouse_move(const MouseMovedEvent& event) {
    // Filter out all valid button pointers
    auto buttons = m_gameObjects
        | std::views::transform([](const std::weak_ptr<GameObject>& object) {
            return std::dynamic_pointer_cast<ButtonWidget>(object.lock());
        })
        | std::views::filter([](const std::shared_ptr<ButtonWidget>& button) {
            return static_cast<bool>(button);
        });

    // For each of them, set highlight effect if collides
    std::ranges::for_each(buttons, [&](const std::shared_ptr<ButtonWidget>& button) {
        const auto doesCollide = button->does_mouse_collide();
        button->set_hover_state(doesCollide);
    });
}


void MenuScene::on_click_play(const MousePressEvent&) {
    Game::push_scene(std::make_unique<GameScene>());
}

void MenuScene::on_click_exit(const MousePressEvent&) {
    auto& window = Renderer::get_window();
    window.close();
}
