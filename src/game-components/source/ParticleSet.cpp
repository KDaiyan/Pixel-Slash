#include "ParticleSet.hpp"

#include <bits/ranges_algo.h>
#include <ranges>
#include "Random.hpp"

ParticleSet::ParticleSet(const Particle& base_particle, const size_t count, const sf::Vector2f& particle_spread)
           : GameObject(RenderPriority::Background_Object)
{
    const auto &base_pos = base_particle.get_position();
    m_particles.reserve(count);

    // so modern so convoluted
    std::ranges::for_each(std::views::iota(0u, count), [&](auto) {
        auto particle = base_particle;

        const sf::Vector2f offset{
            Random::get(-particle_spread.x, particle_spread.x),
            Random::get(-particle_spread.y, particle_spread.y)
        };

        sf::Vector2f new_pos = base_pos + offset;

        // Wrap around out-of-bound particles
        new_pos.x = std::fmod(new_pos.x + 1920.f, 1920.f);
        new_pos.y = std::fmod(new_pos.y + 1080.f, 1080.f);

        particle.set_position(new_pos);

        m_particles.emplace_back(std::move(particle));
    });
}

void ParticleSet::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    for(const auto& particle : m_particles) particle.draw(target, states);
}
