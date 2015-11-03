#include "ModelTexture.h"


ModelTexture::ModelTexture(GLuint newtexture)
{
	this->textureID = newtexture;
}

ModelTexture::ModelTexture(){

}


ModelTexture::~ModelTexture()
{
}

void ModelTexture::setNumberOfRows(int numberOfRows) {
	this->numberOfRows = numberOfRows;
}
int ModelTexture::getNumberOfRows() {
	return numberOfRows;
}

void ModelTexture::setUseFakeLightning(bool useFakeLightning) {
	this->useFakeLightning = useFakeLightning;
}

bool ModelTexture::isUseFakeLightning() {
	return useFakeLightning;
}

void ModelTexture::setHasTransparency(bool hasTransparency) {
	this->hasTransparency = hasTransparency;
}

bool ModelTexture::isHasTransparency() {
	return hasTransparency;
}

float ModelTexture::getShineDamper() {
	return shineDamper;
}

void ModelTexture::setTexture(GLuint newtexture) {
	this->textureID = newtexture;
}

void ModelTexture::setShineDamper(float shineDamper) {
	this->shineDamper = shineDamper;
}

void ModelTexture::setReflectivity(float reflectivity) {
	this->reflectivity = reflectivity;
}

float ModelTexture::getReflectivity() {
	return reflectivity;
}

GLuint ModelTexture::getTextureID()
{
	return textureID;
}

