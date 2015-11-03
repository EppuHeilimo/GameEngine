#include "TerrainTexturePack.h"


TerrainTexturePack::TerrainTexturePack(int rTexture,
	int gTexture,
	int bTexture,
	int backGroundTexture)
{
	
	this->rTexture = rTexture;
	this->gTexture = gTexture;
	this->bTexture = bTexture;
	this->backGroundTexture = backGroundTexture;

}

TerrainTexturePack::TerrainTexturePack(ModelTexture *rTexture, ModelTexture *gTexture, ModelTexture *bTexture, ModelTexture *backgroundTexture){
	this->mrTexture = rTexture;
	this->mgTexture = gTexture;
	this->mbTexture = bTexture;
	this->mBackgroundTexture = backgroundTexture;
	this->rTexture = mrTexture->getTextureID();
	this->gTexture = mgTexture->getTextureID();
	this->bTexture = mbTexture->getTextureID();
	this->backGroundTexture = mBackgroundTexture->getTextureID();
}


TerrainTexturePack::~TerrainTexturePack()
{
}
