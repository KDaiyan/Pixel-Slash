#include "CollisionMap.hpp"

#include <bits/ranges_algo.h>

#include "AssetMap.hpp"
#include "Label.hpp"
#include "Constants.hpp"
#include "Renderer.hpp"

CollisionMap::CollisionMap(const Asset& asset)
            : GameObject(RenderPriority::Background_Overlay)
{
    const auto path = AssetHandler::get_path(asset);
    const auto image = sf::Image{path.get()};
    const auto [width, height] = image.getSize();
    constexpr auto tileSize = static_cast<uint32_t>(Constants::tileSize);

    // iterate through the pixels inside the tile to make sure none are opaque
    auto tileHasOpaque = [&](const uint32_t x, const uint32_t y) {
        for (uint32_t j = 0; j < tileSize && y + j < height; ++j) {
            for (uint32_t i = 0; i < tileSize && x + i < width; ++i) {
                if (image.getPixel({x + i, y + j}).a > Constants::alphaThreshold) {
                    return true;
                }
            }
        }
        return false;
    };

    // iterate through tiles and add all opaque tiles
    for (uint32_t y = 0; y < height; y += tileSize) {
        for (uint32_t x = 0; x < width; x += tileSize) {
            if (tileHasOpaque(x, y)) {
                m_collidableElements.emplace_back(sf::FloatRect{
                    {static_cast<float>(x), static_cast<float>(y)},
                    {Constants::tileSize, Constants::tileSize}
                });
            }
        }
    }
}

bool CollisionMap::does_collide(const GameObject &object) {
    return std::ranges::any_of(m_collidableElements, [&](const sf::FloatRect& rect) {
        return static_cast<bool>(rect.findIntersection(object.get_bounds()));
    });
}

bool CollisionMap::does_collide(const sf::FloatRect &rect) {
    return std::ranges::any_of(m_collidableElements, [&](const sf::FloatRect& rectangle) {
        return static_cast<bool>(rect.findIntersection(rectangle));
    });
}

void CollisionMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto& window = Renderer::instance().get_window();

    // Only used for debugging, this does a lot of expensive operations
    std::ranges::for_each(m_collidableElements, [&](const sf::FloatRect& rect) {
        auto shape = sf::RectangleShape{rect.size};
        shape.setPosition(rect.position);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(1.f);

        window.draw(shape);
    });
}