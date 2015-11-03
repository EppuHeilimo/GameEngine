#pragma once
#include "Particles.h"
#include <vector>
#include <glm\glm.hpp>
#include "ShaderProgram.h"
#include <glew\GL\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParticleRenderer.h"
#include "Camera.h"
#include "Loader.h"

class Particle
{
public:
	glm::vec3 vPosition;
	glm::vec3 vVelocity;
	glm::vec3 vColor;
	float fLifeTime;
	float fSize;
	int type;
};

class ParticleSystem : public ShaderProgram
{
public:
	ParticleSystem();
	~ParticleSystem();
	bool initializeParticles();
	void updateParticles(float timePassed);
	void clearAll();
	bool releaseSystem();
	int getNumParticles();
	void RenderParticles(glm::mat4& projection, Camera cam, float delta);
	void SetGeneratorProperties(glm::vec3 a_vGenPosition, glm::vec3 a_vGenVelocityMin, glm::vec3 a_vGenVelocityMax, glm::vec3 a_vGenGravityVector, glm::vec3 a_vGenColor, float a_fGenLifeMin, float a_fGenLifeMax, float a_fGenSize, float fEvery, int a_iNumToGenerate);
private:
	void renderComplete();
	void bindAttributes();
	void getAllUniformLocations();
	std::string vertexfileLocation();
	std::string geometryFileLocation();
	bool init;
	GLuint uiTransformFeedbackBuffer;

	GLuint uiParticleBuffer[2];
	GLuint uiVAO[2];

	GLuint uiQuery;
	GLuint uiTexture;
	int iCurReadBuffer;
	int iNumParticles;
	std::vector<Particle> particleVec;
	glm::vec3 genPosition;
	glm::vec3 genVelocityMin, genVelocityRange;
	glm::vec3 genGravity;
	glm::vec3 genColor;
	float grandf(float fMin, float fAdd);
	float fElapsedTime;
	float fNextGenerationTime;

	float genLifeMin, genLifeRange;
	float genSize;
	int numToGen;
	int textureid;
	int location_timePassed;
	int location_genPosition;
	int location_genVelocityMin;
	int location_genVelocityRange;
	int location_genColor;
	int location_genGravityVector;
	int location_genLifeMin;
	int location_genLifeRange;
	int location_genSize;
	int location_numToGenerate;
	int location_randomSeed;
	Loader loader;
	ParticleRenderer renderer;
};

