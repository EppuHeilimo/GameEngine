#pragma once
#include <glm\glm.hpp>
#include "FrameBuffer.h"
#include "MyMaths.h"
class Water
{
public:
	Water(float x, float height, float z, glm::vec3 scale, Loader &loader, DisplayManager *display);
	~Water();
	float getHeight(){ return height; }
	glm::vec2 getPos(){ return glm::vec2(x, z); }
	glm::vec3 getScale() { return scale; }
	glm::mat4 getModelMatrix() { return modelMatrix; }
	int getDUDV(){ return dudvID; }
	float getMove (){ return moveFactor; }
	int getNormalMap(){ return normalMap; }
	FrameBuffer* getRefraction() { return &refractionBuffer; }
	FrameBuffer* getReflection() { return &reflectionBuffer; }
	void increaseMoveFactor();
private:
	glm::vec3 scale;
	float height;
	float x, z;
	FrameBuffer reflectionBuffer;
	FrameBuffer refractionBuffer;
	int dudvID; 
	int normalMap;
	glm::mat4 modelMatrix;
	DisplayManager *display;
	float wave_speed = 0.06f;
	float moveFactor = 0;
	
};

