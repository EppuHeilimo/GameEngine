#pragma once
#include "RawModel.h"
#include "ModelTexture.h"
#include "Loader.h"
#include <vector>
#include <glm\glm.hpp>
#include "MyMaths.h"
#include "TerrainTexturePack.h"
#include <string>
#include <cmath>
class Terrain
{
public:
	Terrain(float gridX, float gridZ, float max_height, Loader &loader, TerrainTexturePack *texturePack, ModelTexture *blendMap, std::string heightMapFile);
	~Terrain();
	RawModel getModel(){ return model; }
	TerrainTexturePack* getTexture(){ return texturePack; }
	glm::mat4 getTransform(){ return transform; }
	float getHeight(int, int);
	ModelTexture* getBlendMap() { return blendMap; }
	std::vector < std::vector<float> > getHeights() { return heights; }
	inline float& getX() { return x; }
	inline float& getZ() { return z; }
	inline float& getSize() { return size; }
	float getHeightOfTerrain(float worldX, float worldZ);
	std::vector<float>& getTerrainVertices() { return vertices; }
	
private:
	void processHeightMap(RawImageData&);
	glm::vec3 calculateNormal(int x, int z);
	float realSize = 0;
	float size = 1000;
	float vertex_count = 128;
	float max_pixel_color = 256 * 256 * 256;
	float max_height = 60;
	float x;
	float z;
	std::vector<float> vertices;
	RawModel model;
	TerrainTexturePack *texturePack;
	glm::mat4 transform;
	ModelTexture *blendMap;
	std::vector < std::vector<float> > heights;
	RawModel generateTerrain(Loader &loader, std::string heightMapFile);
	std::vector<float> nHeightMap;


};

