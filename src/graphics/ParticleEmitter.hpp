#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "Particle.hpp"
#include <vector>

class ParticleEmitter {
public:
	ParticleEmitter() = default;
	~ParticleEmitter() = default;

private:
	std::vector<Particle> particles{};
};


#endif