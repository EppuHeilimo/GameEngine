#pragma once
#include "TerrainShader.h"
#include <glm\glm.hpp>
#include <vector>
#include "Terrain.h"
#include "MyMaths.h"
#include "Light.h"
class TerrainRenderer
{
public:
	TerrainRenderer() {};
	TerrainRenderer(glm::mat4 &projection);
	~TerrainRenderer();
	void render(std::vector<Terrain*> &terrain);
	TerrainShader& getShader();
	void renderShadows(std::vector<Terrain*> &terrain, Light &light);
	
private:
	TerrainShader *shader;
	void prepareTerrain(Terrain *terrain);
	void prepareInstance(Terrain *terrain);
	void bindTextures(Terrain *terrain);
	void unbindTexturedModel();
	const float RED = 0.5444f;
	const float GREEN = 0.62f;
	const float BLUE = 0.69f;


};

