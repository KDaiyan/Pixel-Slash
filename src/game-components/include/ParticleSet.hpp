#pragma once

#include <vector>
#include "Particle.hpp"
#include "ParticleSpread.hpp"
#include "GameObject.hpp"

class ParticleSet final : public GameObject {
public:
    ParticleSet(const Particle& base_particle, size_t count, const sf::Vector2f& particle_spread = ParticleSpread::None);
    [[nodiscard]] std::vector<Particle>& get_particles() { return m_particles; }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<Particle> m_particles;
};