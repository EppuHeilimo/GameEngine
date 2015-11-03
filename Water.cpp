#include "Water.h"


Water::Water(float x, float height, float z, glm::vec3 scale, Loader &loader, DisplayManager *display)
{
	this->display = display;
	modelMatrix = MyMaths::createTransformationmatrix(glm::vec3(x, height, z), 0, 0, 0,
		scale);
	this->x = x;
	this->z = z;
	this->height = height;
	this->scale = scale;
	reflectionBuffer.createFrameBuffer(1024, 1024);
	reflectionBuffer.createTextureAttachment();
	reflectionBuffer.createDepthBufferAttachment();

	refractionBuffer.createFrameBuffer(1024, 1024);
	refractionBuffer.createTextureAttachment();
	refractionBuffer.createWaterDepthTextureAttachment();
	dudvID = loader.loadTexture("./res/waterDUDV.png");
	normalMap  = loader.loadTexture("./res/matchingNormalMap.png");
}


Water::~Water()
{
}

void Water::increaseMoveFactor(){
	moveFactor += wave_speed * display->getFrameTime();
	if (moveFactor >= 1.0f)
		moveFactor = 0.0f;

}
