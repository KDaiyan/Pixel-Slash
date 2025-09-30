#pragma once

#include "Scene.hpp"
#include "Statistics.hpp"
#include "Map.hpp"
#include "Label.hpp"
#include "ButtonWidget.hpp"
#include "TextBox.hpp"

class ScoreScene final : public Scene {
public:
    explicit ScoreScene(const Statistics& stats);

private:
    void on_mouse_press(const MousePressEvent& event) override;
    void on_mouse_move(const MouseMovedEvent& event) override;
    static void on_click_home(const MousePressEvent&);
    static void on_click_replay(const MousePressEvent&);
    static void on_click_exit(const MousePressEvent&);

    std::shared_ptr<Map> m_background;
    std::shared_ptr<Label> m_scroll;
    std::shared_ptr<ButtonWidget> m_homeButton;
    std::shared_ptr<ButtonWidget> m_replayButton;
    std::shared_ptr<ButtonWidget> m_exitButton;
    std::shared_ptr<TextBox> m_mobKilledText;
    std::shared_ptr<TextBox> m_coinsCollectedText;
    std::shared_ptr<TextBox> m_gameResult;

    Statistics m_statistics;
};
