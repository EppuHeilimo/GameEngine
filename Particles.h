#pragma once
#include <glm\glm.hpp>
class Particles
{
public:
	Particles(glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float mass, float radius, float lifeTime, float type);
	Particles();
	~Particles();
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 color;
	float mass;
	float radius;
	float lifeTime;
	float type;
};

