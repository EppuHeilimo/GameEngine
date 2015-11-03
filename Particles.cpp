#include "Particles.h"


Particles::Particles(glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float mass, float radius, float lifeTime, float type)
{
	this->position = position;
	this->velocity = velocity;
	this->color = color;
	this->mass = mass;
	this->radius = radius;
	this->lifeTime = lifeTime;
	this->type = type;
}



Particles::~Particles()
{
}
