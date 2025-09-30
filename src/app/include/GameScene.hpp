#pragma once

#include "CollisionMap.hpp"
#include "Constants.hpp"
#include "Scene.hpp"
#include "EntitySystem.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Label.hpp"
#include "SpawnPoints.hpp"
#include "Statistics.hpp"

class GameScene final : public Scene {
public:
    GameScene();

private:
    void on_key_press(const KeyPressEvent& event) override;
    void on_update(const UpdateEvent& event) override;
    void initialize_events() override;
    void handle_game_win() const;
    void add_coin();

    std::shared_ptr<Map> m_background;
    std::shared_ptr<Label> m_caveOutline;
    std::weak_ptr<Player> m_player;
    EntitySystem m_entitySystem;

    float m_coinTimeAccumulator {};
    size_t m_coinsSpawned {};
    Statistics m_statistics {Constants::mobCount, Constants::coinCapacity};
    std::vector<sf::Vector2f> m_coins { SpawnPoints::get_instance().get_coins() };
};
