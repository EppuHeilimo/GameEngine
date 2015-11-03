#pragma once
#include <glew\GL\glew.h>
#include "StaticShader.h"
#include "Vertex.h"
#include <glm\glm.hpp>
#include "RawModel.h"
#include "TexturedModel.h"
#include "Camera.h"
#include "DisplayManager.h"
#include <math.h>
#include "SkyBoxRenderer.h"
#include "Loader.h"
#include "EntityInterface.h"
#include "LocalPlayer.h"
#include <map>
#include "Light.h"
#include "TerrainRenderer.h"
#include "Terrain.h"
#include "Renderer2D.h"
#include "WaterRenderer.h"
class Game;
#include "Game.h"
#include "ParticleSystem.h"




#ifndef PI
#define PI 3.14159265;
#endif

class MasterRenderer
{
public:
	MasterRenderer(Loader &loader, Game &game);
	~MasterRenderer();
	glm::mat4 transformation(LocalPlayer &player);
	glm::mat4 transformation(EntityInterface *entity);

	void render( EntityInterface&, Camera &camera);
	void render(LocalPlayer&, std::vector<std::map<std::string, std::vector<EntityInterface*>>> &entities, Camera &camera,
		std::vector<Light*> &lights, std::vector<Terrain*> &terrain, std::vector<GuiTexture> &guis, std::vector<Water*> &waters, std::vector<int>&, ParticleSystem& particle);
	void renderShadows(LocalPlayer &player, std::vector<std::map<std::string, std::vector<EntityInterface*>>> &entities, std::vector<Light*> &lights, std::vector<Terrain*> &terrain, std::vector<int>&);
	void renderTerrain(std::vector<Terrain*> &terrain);
	glm::mat4 shadowPrepare(Light &light, LocalPlayer &player);
	void renderTerrainShadows(std::vector<Terrain*> &terrain, Light &light);
	glm::mat4& getProjection() { return projectionMatrix; }
	
private:
	void createProjectionMatrix();
	void prepare();
	StaticShader* shader;
//	const float RED = 0.5444f;
//	const float GREEN = 0.62f;
//	const float BLUE = 0.69f;
	const float RED = 0.9944f;
	const float GREEN = 0.62f;
	const float BLUE = 0.29f;
	float FOV = 45.0f;
	void renderPlayer(LocalPlayer& player, Camera& cam, std::vector<Light*>& lights, glm::mat4& lightSpaceMatrix);
	void renderEntities(std::vector<std::map<std::string, std::vector<EntityInterface*>>> &entities, std::vector<Light*>& lights, glm::mat4& lightSpaceMatrix, std::vector<int>& entityNumbers);
	
	const float NEAR_PLANE = 1.f;
	const float FAR_PLANE = 2000;
	TerrainRenderer *terrainRenderer;
	glm::mat4 projectionMatrix;
	SkyBoxRenderer *skyboxRenderer;
	Renderer2D *render2D;
	WaterRenderer  *waterRenderer;
	Loader *loader;
	Game *game;
};

