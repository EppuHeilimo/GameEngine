#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 Attenuation)
{
	this->position = position;
	this->color = color;
	this->Attenuation = Attenuation;
	frameBuffer = new FrameBuffer(2048, 2048);
	shadowShader = new DepthShader();
}


Light::~Light()
{
	delete shadowShader;
	delete frameBuffer;
}

glm::vec3 Light::getColor()
{
	return color;
}

glm::vec3 Light::getPosition()
{
	return position;
}
