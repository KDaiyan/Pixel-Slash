#include "SpriteSet.hpp"

#include "Constants.hpp"
#include "Renderer.hpp"

SpriteSet::SpriteSet(const Asset& idleAsset, const Asset& walkAsset, const Asset& attackAsset, const Asset& damagedAsset, const Asset& deathAsset)
         : Renderable({}, {}, RenderPriority::Entity)
{
    //m_renderPriority = RenderPriority::Entity;

    std::array<std::tuple<Asset, sf::Texture&, std::span<std::optional<sf::Sprite>>>, 5> assetSpritePairs{{
        {idleAsset,   m_idleTexture,   m_idleSprites},
        {walkAsset,   m_walkTexture,   m_walkSprites},
        {attackAsset, m_attackTexture, m_attackSprites},
        {damagedAsset, m_damageTexture, m_damagedSprites},
        {deathAsset,  m_dyingTexture,  m_dyingSprites}
    }};

    for (auto& [asset, texture, spriteSpan] : assetSpritePairs) {
        const auto path = AssetHandler::get_path(asset);
        texture = sf::Texture(path.get());

        for(int i = 0; i < spriteSpan.size(); ++i) {
            auto rect = sf::Rect<int>({100 * i, 0}, {100, 100}); // Position at 0 0?
            spriteSpan[i] = sf::Sprite(texture, rect);
        }
    }

    m_targetSprite = m_idleSprites.at(0); // start at first idle frame
}

void SpriteSet::update(EntityState& state, const Direction direction, const sf::Vector2f& pos, std::optional<EntityState>& actionBuffer) {
    const EntityState entityState = actionBuffer.value_or(state);

    // Reset animation only if either:
    // Action buffer has a new, higher priority single action.
    // Action buffer is empty, but direction or state changed for continuous action
    const bool isNewBufferedAction = actionBuffer.has_value() && m_state != entityState;
    const bool isRegularStateChanged = !actionBuffer.has_value() && (m_state != entityState || m_direction != direction);

    if (isNewBufferedAction || isRegularStateChanged) {
        m_tickCount = 0;
        m_state = entityState;
        m_direction = direction;
    }

    const auto& sprites = m_spriteMap.at(entityState);
    size_t frameIndex = m_tickCount / Constants::updateFrequency;

    if (actionBuffer && frameIndex >= sprites.size()) {
        if(actionBuffer == EntityState::Dying) {
            state = EntityState::Dead;
        }

        actionBuffer.reset();
        return;
    }

    frameIndex %= sprites.size();

    if (m_tickCount++ % Constants::updateFrequency == 0) {
        m_targetSprite = sprites[frameIndex];
    }

    m_targetSprite->setPosition(pos);
}

void SpriteSet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto& window = Renderer::get_window();

    sf::Sprite spriteToDraw = *m_targetSprite;
    spriteToDraw.setPosition(spriteToDraw.getPosition() + Constants::spriteOffset);

    // flip the sprite if its facing left (right is default)
    if (m_direction == Direction::Left) {
        spriteToDraw.setScale({-1.f, 1.f}); // flip sprite on vertical axis

        auto bounds = spriteToDraw.getLocalBounds();
        spriteToDraw.setOrigin({bounds.size.x, 0.f});
    }

    window.draw(spriteToDraw);
}