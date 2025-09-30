#include "Coin.hpp"

#include "Constants.hpp"
#include "EntitySystem.hpp"
#include "Renderer.hpp"
#include "game-events/CoinCollectedEvent.hpp"

Coin::Coin(const sf::Vector2f& position, EventManager& eventManager)
    : Entity(position, sf::Vector2f{static_cast<float>(Constants::coinDimension), static_cast<float>(Constants::coinDimension)}, eventManager)
{
    const auto path = AssetHandler::get_path(Assets::Items::Coin);
    m_texture = sf::Texture{path.get()};

    const auto rect = sf::Rect<int>({static_cast<int>(Constants::coinDimension * spriteIterator), 0},
                                    {Constants::coinDimension, Constants::coinDimension});

    m_sprite = sf::Sprite(m_texture, rect);
    m_sprite->setPosition(position);
}

void Coin::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto& window = Renderer::instance().get_window();
    window.draw(*m_sprite);
}

void Coin::update(const UpdateEvent& event, EntitySystem& entitySystem) {
    const auto player = entitySystem.get_player_entity().lock();
    assert(player);

    if(player->does_collide(*this)) {
        m_eventManager.fire(CoinCollectedEvent{});
        entitySystem.remove_entity(this->shared_from_this());
        return;
    }

    if((updateCD += event.get_dt()) >= Constants::spriteUpdateTime) {
        updateCD = 0.f;
        spriteIterator = (spriteIterator + 1) % Constants::coinSpriteCount;

        const auto rect = sf::Rect<int>({static_cast<int>(Constants::coinDimension * spriteIterator), 0},
                                        {Constants::coinDimension, Constants::coinDimension});
        m_sprite = sf::Sprite(m_texture, rect);
    }

    m_sprite->setPosition(m_position);
}
