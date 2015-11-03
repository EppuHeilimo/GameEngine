#pragma once
#include <glm/glm.hpp>
#include <glew\GL\glew.h>
#include "DepthShader.h"
#include "FrameBuffer.h"
class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color, glm::vec3 Attenuation);
	~Light();
	glm::vec3 getColor();
	void setPosition(glm::vec3 val) { position = val; }
	glm::vec3 getPosition();
	glm::vec3 getAttenuation() { return Attenuation; }
	void setColor(glm::vec3 val) { color = val; }
	FrameBuffer* getFrameBuffer() { return frameBuffer; }
	inline DepthShader* getShadowShader() { return shadowShader; }
private:
	DepthShader *shadowShader;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 Attenuation;
	FrameBuffer *frameBuffer;
	
};

/*	inline void setFbo(GLuint fbo){ this->fbo = fbo; }
	inline void setdepthMap(GLuint depthMap){ this->depthMap = depthMap; }
	inline GLuint getFbo() { return fbo; }
	inline GLuint getDepthMap() { return depthMap; }*/