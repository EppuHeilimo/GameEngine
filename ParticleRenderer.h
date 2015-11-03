#pragma once
#include "ParticleShader.h"
#include <glm\gtc\matrix_transform.hpp>
#include "Camera.h"
#include "MyMaths.h"
class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();
	void setMatrices(glm::mat4& a_matProjection, Camera cam);
	void render(GLuint uiVAO[2], int, int);
private:
	glm::mat4 matProjection, matView;
	glm::vec3 vQuad1, vQuad2;
	ParticleShader *shader;
};

