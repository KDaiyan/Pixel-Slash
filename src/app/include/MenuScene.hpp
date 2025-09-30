#pragma once

#include <SFML/Graphics.hpp>
#include "GameScene.hpp"
#include "Scene.hpp"
#include "Label.hpp"
#include "Map.hpp"
#include "ButtonWidget.hpp"
#include "WidgetBuilder.hpp"

class MenuScene final : public Scene {
public:
    MenuScene();

private:
    void on_mouse_press(const MousePressEvent& event) override;
    void on_mouse_move(const MouseMovedEvent &event) override;
    static void on_click_play(const MousePressEvent&);
    static void on_click_settings(const MousePressEvent&) { /* lol no */ }
    static void on_click_exit(const MousePressEvent&);

    std::shared_ptr<ButtonWidget> m_playButton;
    std::shared_ptr<ButtonWidget> m_settingsButton;
    std::shared_ptr<ButtonWidget> m_quitButton;
    std::shared_ptr<Label> m_logo;
    std::shared_ptr<Map> m_background;
    sf::Clock clock;
};
