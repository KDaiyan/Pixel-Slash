#include "GameScene.hpp"

#include "Pillar.hpp"
#include "Coin.hpp"
#include "Mob.hpp"
#include "Constants.hpp"
#include "CollisionMap.hpp"
#include "SpawnPoints.hpp"
#include "Game.hpp"
#include "ScoreScene.hpp"
#include "game-events/CoinCollectedEvent.hpp"
#include "game-events/GameWonEvent.hpp"
#include "game-events/MobKilledEvent.hpp"
#include "game-events/PlayerDiedEvent.hpp"

GameScene::GameScene()
    : m_entitySystem(m_eventManager)
{
    m_background = std::make_shared<Map>(Assets::Maps::Forest_Cave);
    m_caveOutline = std::make_shared<Label>(Assets::BackgroundObjects::Cave_Outline, sf::Vector2f{0, 0});

    m_entitySystem.set_player_entity(std::make_shared<Player>(sf::Vector2f{850.f, 500.f}, m_eventManager));
    m_player = m_entitySystem.get_player_entity();

    this->add_game_objects(m_background, m_caveOutline, m_player);

    m_entitySystem.add_collidable_objects(std::make_shared<CollisionMap>(Assets::BackgroundObjects::Cave_Outline));

    auto& mobs = SpawnPoints::get_instance().get_mob_positions();

    std::ranges::for_each(mobs, [this](const sf::Vector2f& position) {
        auto mob = std::make_shared<Mob>(*m_player.lock(), position, m_eventManager);
        this->add_game_objects(mob);
        m_entitySystem.add_entities(std::move(mob));
    });

    auto& pillars = SpawnPoints::get_instance().get_pillars();

    std::ranges::for_each(pillars, [this](const std::pair<uint32_t, sf::Vector2f> &pillarPair) {
        auto pillar = std::make_shared<Pillar>(pillarPair.first, pillarPair.second);
        this->add_game_objects(pillar);
        m_entitySystem.add_collidable_objects(std::move(pillar));
    });

    this->initialize_events();
}

void GameScene::on_key_press(const KeyPressEvent& event) {
    const auto scancode = event.get_scan_code();
    const auto& player = m_player.lock();

    if(!player) return;

    if(scancode == sf::Keyboard::Scan::Space) {
        player->jump();
    }
    else if (scancode == sf::Keyboard::Scan::M) {
        player->attack();
    }
}

void GameScene::on_update(const UpdateEvent& event) {
    // Create a new coin every few seconds
    const auto dt = event.get_dt();
    m_statistics.elapsedTime += dt;
    m_coinTimeAccumulator += dt;

    if(m_coinTimeAccumulator >= Constants::coinSpawnDelay && m_coinsSpawned < Constants::coinCapacity) {
        this->add_coin();
    }

    m_entitySystem.update(event);
}

void GameScene::initialize_events() {
    // Go straight to score scene if player dies
    m_eventManager.add<PlayerDiedEvent>([&](const PlayerDiedEvent &) {
        Game::push_scene(std::make_unique<ScoreScene>(m_statistics));
    });

    m_eventManager.add<GameWonEvent>([&](const GameWonEvent&) {
        m_statistics.winStatus = true;
        Game::push_scene(std::make_unique<ScoreScene>(m_statistics));
    });

    m_eventManager.add<MobKilledEvent>([&](const MobKilledEvent&) {
        m_statistics.mobsKilled++;
        this->handle_game_win();
    });

    m_eventManager.add<CoinCollectedEvent>([&](const CoinCollectedEvent&) {
        m_statistics.coinsCollected++;

        // spawn another coin right away unless all collected
        if(m_coinsSpawned < Constants::coinCapacity) {
            this->add_coin();
        }

        this->handle_game_win();
    });
}

void GameScene::add_coin() {
    const auto pos = SpawnPoints::get_random_coin(m_coins);
    auto coin = std::make_shared<Coin>(pos, m_eventManager);

    this->add_game_objects(coin);
    m_entitySystem.add_entities(std::move(coin));

    m_coinTimeAccumulator = 0.f;
    ++m_coinsSpawned;
}

void GameScene::handle_game_win() const {
    if(m_statistics.coinsCollected == m_statistics.coinsTotal && m_statistics.mobsKilled == m_statistics.mobsTotal) {
        m_eventManager.fire(GameWonEvent{});
    }
}
