#pragma once
#include <glm\glm.hpp>
#include "ModelTexture.h"
class TerrainTexturePack
{
public:
	TerrainTexturePack(int rTexture,
		int gTexture,
		int bTexture,
		int backGroundTexture);
	TerrainTexturePack(ModelTexture *rTexture, ModelTexture *gTexture, ModelTexture *bTexture, ModelTexture *backgroundTexture );
	TerrainTexturePack() {};

	~TerrainTexturePack();
	glm::vec3 getTexturePack(){ return glm::vec3(rTexture, gTexture, bTexture); }
	int getBackground() { return backGroundTexture; }

private:

	int rTexture;
	int bTexture;
	int gTexture;
	int backGroundTexture;
	ModelTexture *mrTexture;
	ModelTexture *mgTexture;
	ModelTexture *mbTexture;
	ModelTexture *mBackgroundTexture;


};

