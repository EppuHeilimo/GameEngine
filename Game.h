#pragma once
#include <iostream>
#include "DisplayManager.h"
#include "glew/GL/glew.h"
#include "MasterRenderer.h"
#include "Vertex.h"
#include "Loader.h"
#include "MyMaths.h"
#include "glm\glm.hpp"
#include "RawModel.h"
#include <vector>
#include "TexturedModel.h"
#include "SDL/SDL.h"
#include <queue>
#include "ModelData.h"
#include "LocalPlayer.h"
#include "ObjLoader.h"
#include <map>
#include <thread>
#include "Light.h"
#include "Terrain.h"
#include "TerrainRenderer.h"
#include "InputHandler.h"
#include "TerrainTexturePack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Water.h"
#include "Renderer2D.h"
#include "GameTime.h"
#include <cmath>
#include "Physics.h"
#include "Entity.h"
#ifndef PI
#define PI 3.14159
#endif

class Game
{
public:



	Game(DisplayManager *display, InputHandler&);
	~Game();
	void initGame();

	void addEntity(int x, int z, glm::vec3 rotation, glm::vec3 scale, const std::string model);
	void addEntity(int x, int z, glm::vec3 rotation, glm::vec3 scale, const std::string model, int terrainNumber, int offsetY);
	void deleteEntity();
	void addPlayer();
	void addTerrain(float x, float z, float height, std::string blendMap, std::string heightMap, std::string texturePackName);
	void addTexturePack(std::string r, std::string g, std::string b, std::string background, std::string packName);
	void addWater(float x, float y, float z, glm::vec3 scale);

	void addGUI();
	void addLight();
	void addModel(std::string modelFile, std::string modelName);
	void addModel(std::string modelFile, std::string modelName, std::string modelTexture);
	void calcRenderTerrains(float range);
	int onTerrain(float x, float z);
	std::vector<Entity*>& getEntities(){ return entities; }
	std::vector<std::map<std::string, std::vector<EntityInterface*>>>& getAllEntities() { return allEntities; }
	Camera& getCamera(){ return *camera; }
	LocalPlayer& getPlayer(){ return *player; }
	std::vector<int>& getTerrainVector(){ return terrainVector; }
	std::vector<Terrain*>& getTerrains(){ return terrains; }
	std::vector<GuiTexture>& getGUI(){ return gui; }
	std::vector<Water*>& getWaters(){ return waters; }
	Physics* getPhysics(){ return physics; };
	float getDelta(){ return display->getFrameTime(); }
private:
	std::vector<int> terrainVector;
	std::vector<std::map<std::string, std::vector<EntityInterface*>>> allEntities;
	std::vector<Water*> waters;
	std::vector<GuiTexture> gui;
	std::map < std::string, std::vector<TexturedModel>> models;
	std::map < std::string, std::vector<ModelTexture*>> textures;
	std::vector<Terrain*> terrains;
	std::map < std::string, std::vector<TerrainTexturePack*>> TerrainTexturePacks;
	std::vector<Entity*> entities;
	int entityCount = 0;
	
	DisplayManager *display; 
	LocalPlayer *player;
	Camera *camera;
	Loader loader;
	EntityInterface *entity;
	TexturedModel *model;
	InputHandler *input;
	Physics *physics;





};

