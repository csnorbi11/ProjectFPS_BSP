#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>
#include "Texture.hpp"


struct Particle {
	glm::vec3 position{};
	glm::vec2 size{};
	glm::vec3 velocity{};
	glm::vec3 acceleration{};
	float duration = 0;
	const float livingTime = 0;
	bool isAlive = false;
	Texture* texture = nullptr;
};


#endif // !PARTICLE_HPP
