#pragma once
#include <vector>
#include <glew/GL/glew.h>
class ModelTexture
{
public:
	ModelTexture(GLuint texture);
	ModelTexture();
	~ModelTexture();
	void setNumberOfRows(int numberOfRows);
	int getNumberOfRows();
	void setUseFakeLightning(bool useFakeLightning);
	bool isUseFakeLightning();
	void setHasTransparency(bool hasTransparency);
	bool isHasTransparency();
	float getShineDamper();
	void setTexture(GLuint texture);
	void setShineDamper(float shineDamper);
	void setReflectivity(float reflectivity);
	float getReflectivity();
	GLuint getTextureID();
	

private:
	float shineDamper = 1;
	float reflectivity = 0;
	int numberOfRows = 1;
	bool hasTransparency = false;
	bool useFakeLightning = false;
	GLuint textureID;
};

