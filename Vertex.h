#include "glm\glm.hpp"

#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z);
	~Vertex();
	glm::vec3 getPosition() { return position; }
private:
	 glm::vec3 position;
};

