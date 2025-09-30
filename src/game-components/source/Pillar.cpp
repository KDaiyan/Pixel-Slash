#include "Pillar.hpp"

#include "Constants.hpp"

Pillar::Pillar(const uint32_t height, const sf::Vector2f& position)
      : GameObject(RenderPriority::Background_Object),
        m_height(height)
{
    const float bodyHeight = static_cast<float>(height) * Constants::pillarDimension;
    const float totalHeight = bodyHeight + Constants::pillarHeadHeight;

    m_dimensions = sf::Vector2f{Constants::pillarDimension, totalHeight};
    m_position = position;

    const auto pillarPath = AssetHandler::get_path(Assets::BackgroundObjects::Pillar);
    const auto headPath = AssetHandler::get_path(Assets::BackgroundObjects::Pillar_Head);

    m_pillarTexture = sf::Texture(pillarPath.get());
    m_pillarTexture.setRepeated(true); // Repeat the texture so it can be stacked
    m_headTexture = sf::Texture(headPath.get());

    m_pillarSprite = sf::Sprite(m_pillarTexture);
    m_pillarSprite->setTextureRect({
        {0, 0}, {static_cast<int>(Constants::pillarDimension), static_cast<int>(bodyHeight)}
    });
    m_pillarSprite->setPosition(m_position);

    m_headSprite = sf::Sprite(m_headTexture);
    m_headSprite->setPosition({m_position.x, m_position.y - Constants::pillarHeadHeight});
}

bool Pillar::does_collide(const GameObject& object) {
    const auto pillarBounds = m_headSprite->getGlobalBounds(); // Only the pillar head is collidable
    return static_cast<bool>(object.get_bounds().findIntersection(pillarBounds));
}

bool Pillar::does_collide(const sf::FloatRect& rect) {
    const auto pillarBounds = m_headSprite->getGlobalBounds(); // Only the pillar head is collidable
    return static_cast<bool>(rect.findIntersection(pillarBounds));
}

void Pillar::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    auto& window = Renderer::instance().get_window();
    window.draw(*m_pillarSprite);
    window.draw(*m_headSprite);
}

