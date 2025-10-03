#include "ScoreScene.hpp"

#include <tuple>
#include <ranges>
#include "Game.hpp"
#include "MenuScene.hpp"
#include "WidgetBuilder.hpp"
#include "Renderer.hpp"

ScoreScene::ScoreScene(const Statistics& stats)
    : m_statistics(stats)
{
    m_background = std::make_shared<Map>(Assets::Maps::Shaded_Cave);
    m_scroll = std::make_shared<Label>(Assets::BackgroundObjects::Scroll, sf::Vector2f{673, 227});

    auto widgetBuilder = WidgetBuilder();

    m_homeButton = widgetBuilder.set_dimensions({120, 120})
                            .set_position({760, 607})
                            .set_texture(Assets::Icons::Home_Button)
                            .set_click_callback([this](const MousePressEvent& event) { on_click_home(event); })
                            .build<ButtonWidget>();

    m_replayButton = widgetBuilder.set_dimensions({120, 120})
                        .set_position({900, 607})
                        .set_texture(Assets::Icons::Replay_Button)
                        .set_click_callback([this](const MousePressEvent& event) { on_click_replay(event); })
                        .build<ButtonWidget>();

    m_exitButton = widgetBuilder.set_dimensions({120, 120})
                        .set_position({1040, 607})
                        .set_texture(Assets::Icons::Exit_Button)
                        .set_click_callback([this](const MousePressEvent& event) { on_click_exit(event); })
                        .build<ButtonWidget>();

    const auto mobKilledText = std::string("mobs:") + std::to_string(m_statistics.mobsKilled)
                                  + "/" + std::to_string(m_statistics.mobsTotal);

    m_mobKilledText = widgetBuilder.set_dimensions({315, 34})
                        .set_position({742, 414})
                        .set_font(Assets::Fonts::Quinque_Five)
                        .set_text(std::string_view{mobKilledText})
                        .set_text_size(33u)
                        .set_text_color(sf::Color{108, 69, 26}) // Brownish color
                        .build<TextBox>();

    const auto coinsCollectedText = std::string("coins:") + std::to_string(m_statistics.coinsCollected)
                                       + "/" + std::to_string(m_statistics.coinsTotal);

    m_coinsCollectedText = widgetBuilder.set_dimensions({436, 34})
                            .set_position({742, 515})
                            .set_font(Assets::Fonts::Quinque_Five)
                            .set_text(std::string_view{coinsCollectedText})
                            .set_text_size(33u)
                            .set_text_color(sf::Color{108, 69, 26}) // Brownish color
                            .build<TextBox>();

    const auto [statusText, statusColor, statusPos, statusDims] =
        m_statistics.winStatus
            ? std::tuple{"You win!", sf::Color(0,193,0), sf::Vector2f(777,317), sf::Vector2f(367,40)}
            : std::tuple{"You lose!", sf::Color(214,0,53), sf::Vector2f(752,317), sf::Vector2f(416,40)};

    m_gameResult = widgetBuilder.set_dimensions(statusDims)
                        .set_position(statusPos)
                        .set_font(Assets::Fonts::Quinque_Five)
                        .set_text(std::string_view{statusText})
                        .set_text_size(40u)
                        .set_text_color(statusColor)
                        .build<TextBox>();

    this->add_game_objects(m_background, m_scroll, m_homeButton, m_replayButton, m_exitButton, m_mobKilledText, m_coinsCollectedText, m_gameResult);
}

void ScoreScene::on_mouse_press(const MousePressEvent &event) {
    // Filter out all the valid button pointers, then check if they collide
    auto range = m_gameObjects
        | std::views::transform([](const std::weak_ptr<GameObject>& object) {
            return std::dynamic_pointer_cast<ButtonWidget>(object.lock());
        })
        | std::views::filter([](const std::shared_ptr<ButtonWidget>& button) {
            return button && button->does_mouse_collide();
        });

    // Use find_if to check only first collision (should not have multiple collisions unless anyway)
    std::ranges::find_if(range, [&](const std::shared_ptr<ButtonWidget>& button) {
        button->on_mouse_click_callback(event);
        return true;
    });
}

void ScoreScene::on_mouse_move(const MouseMovedEvent &event) {
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

void ScoreScene::on_click_home(const MousePressEvent&) {
    Game::clear_scenes();
    Game::push_scene(std::make_unique<MenuScene>());
}

void ScoreScene::on_click_replay(const MousePressEvent&) {
    Game::clear_scenes();
    Game::push_scene(std::make_unique<GameScene>());
}

void ScoreScene::on_click_exit(const MousePressEvent&) {
    auto& window = Renderer::get_window();
    window.close();
}