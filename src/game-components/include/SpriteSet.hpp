#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Direction.hpp"
#include "Renderable.hpp"
#include "EntityState.hpp"
#include "AssetMap.hpp"

class SpriteSet final : public Renderable {
public:
    SpriteSet(const Asset& idleAsset, const Asset& walkAsset, const Asset& attackAsset, const Asset& damagedAsset, const Asset& deathAsset);
    void update(EntityState& state, Direction direction, const sf::Vector2f& pos, std::optional<EntityState>& actionBuffer);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::optional<sf::Sprite> m_targetSprite;
    EntityState m_state = EntityState::Idle;
    Direction m_direction = Direction::Right;

    sf::Texture m_idleTexture;
    sf::Texture m_walkTexture;
    sf::Texture m_attackTexture;
    sf::Texture m_damageTexture;
    sf::Texture m_dyingTexture;

    // Probably not ideal to have fixed number of sprites in a class like this
    // but the sprites used all share this same trend and array is simpler
    std::array<std::optional<sf::Sprite>, 6> m_idleSprites;
    std::array<std::optional<sf::Sprite>, 8> m_walkSprites;
    std::array<std::optional<sf::Sprite>, 6> m_attackSprites;
    std::array<std::optional<sf::Sprite>, 4> m_damagedSprites;
    std::array<std::optional<sf::Sprite>, 4> m_dyingSprites;

    std::unordered_map<EntityState, std::span<const std::optional<sf::Sprite>>> m_spriteMap = {
        {EntityState::Idle, m_idleSprites},
        {EntityState::Walking, m_walkSprites},
        {EntityState::Attack, m_attackSprites},
        {EntityState::Damaged, m_damagedSprites},
        {EntityState::Dying, m_dyingSprites}
    };

    size_t m_tickCount {};
};