#include "Game.h"


Game::Game(DisplayManager *display, InputHandler &input)
{
	this->display = display;
	this->input = &input;
	physics = new Physics(display);
	initGame();
}

void Game::initGame(){
	
	addWater(500, 25, -500, glm::vec3(350, 1, 400));
	
	addTexturePack("mud2", "snowpath", "snowdirt", "Snow", "winter");
	addTexturePack("mud2", "desert_tiled", "sandHard", "Sand", "desert");
	addTexturePack("mud2", "sandHard", "grassFlowers", "grass2", "plains");
	addTerrain(0.0f, 0.0f, 80.0f, "blendMap", "heightmap", "plains");
	addTerrain(-1.0f, -1.0f, 80.0f, "blendMap", "heightmap", "desert");
	addTerrain(-1.0f, 0.0f, 80.0f, "blendMap", "heightMap2", "winter");
	addTerrain(0.0f, -1.0f, 80.0f, "blendMapLake", "heightmapLake", "plains");
	addTerrain(1.0f, 1.0f, 80.0f, "blendMap", "heightmap", "desert");
	addTerrain(-2.0f, -2.0f, 80.0f, "blendMap", "heightmap", "desert");
	addTerrain(-2.0f, -1.0f, 80.0f, "blendMap", "heightmap", "desert");
	addTerrain(-1.0f, -2.0f, 80.0f, "blendMap", "heightmap", "desert");
	addTerrain(1.0f, 0.0f, 80.0f, "blendMap", "heightmap", "desert");
	allEntities.resize(terrains.size());
	addModel("block2.obj", "block", "block.png");
	addModel("tree.obj", "treeModel", "tree.png");
	addModel("Tree2A.3ds", "tree2");
	int random = 0;
	int random2 = 0;
	srand(time(NULL));
	for (int i = 0; i < 100; i++){
		random = rand() % 900 + 1;
		random2 = rand() % 900 + 1;
		int terrain = onTerrain(random, random2);
		addEntity(random, random2, glm::vec3(-1.6f, 0.0f, -1.6f), glm::vec3(300.0f, 300.0f, 300.0f), "tree2", terrain, 33);
	} 
	int terrain = onTerrain(450.0f, -865.0f);
	addEntity(450.0f, -865.0f, glm::vec3(-1.6f, 0.0f, -1.6f), glm::vec3(300.0f, 300.0f, 300.0f), "tree2", terrain, 33);
	addEntity(440.0f, -865.0f, glm::vec3(-1.6f, 0.0f, -1.6f), glm::vec3(300.0f, 300.0f, 300.0f), "tree2", terrain, 33);
	addEntity(430.0f, -865.0f, glm::vec3(-1.6f, 0.0f, -1.6f), glm::vec3(300.0f, 300.0f, 300.0f), "tree2", terrain, 33);
	terrain = onTerrain(806.0f, -460.0f);
	player = new LocalPlayer(glm::vec3(806.0f, terrains[terrain]->getHeightOfTerrain(806.0f, -460.0f), -460.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(2, 2, 2), &models.at("tree2").at(0), input, terrain, physics);

	camera = new Camera(player);
	std::map<std::string, std::vector<TexturedModel>>::iterator it = models.begin();
	std::map<std::string, std::vector<TexturedModel>>::iterator itend = models.end();


		
} 

void Game::addWater(float x, float y, float z, glm::vec3 scale){
	entityCount++;
	Water *water = new Water(x, y, z, scale, loader, display);
	physics->addStaticBox(scale.x, scale.y, scale.z, x, y, z, 0, water);
	waters.push_back(water);
}

void Game::addEntity(int x, int z, glm::vec3 rotation, glm::vec3 scale, std::string model){
	int terrain = onTerrain(x, z);
	float terrainHeight = terrains.at(terrain)->getHeightOfTerrain(x, z);
	
	allEntities.at(terrain).at(model).push_back(new EntityInterface(glm::vec3(x, terrains.at(terrain)->getHeightOfTerrain(x, z), z), rotation, scale, &models[model].at(0), terrain));
	physics->addStaticBox(20, 20, 20, x, terrainHeight, z, 0, allEntities.at(terrain).at(model).back());
}

void Game::addEntity(int x, int z, glm::vec3 rotation, glm::vec3 scale, std::string model, int terrainNumber, int offsetY){
	entityCount++;
	float terrainHeight = terrains.at(terrainNumber)->getHeightOfTerrain(x, z);
	terrainHeight += offsetY;
	allEntities.at(terrainNumber).at(model).push_back(new EntityInterface(glm::vec3(x, terrainHeight, z), rotation, scale, &models[model].at(0), terrainNumber));
	physics->addStaticBox(20, 20, 20, x, terrainHeight, z, 0, allEntities.at(terrainNumber).at(model).back());
	
}

void Game::addTerrain(float x, float z, float height, std::string blendMap, std::string heightMap, std::string texturePackName){
	ModelTexture *blendMapfile = new ModelTexture(loader.loadTexture("./res/" + blendMap + ".png"));
	Terrain *terrain = new Terrain(x, z, height, loader, TerrainTexturePacks.at(texturePackName).front(), blendMapfile, "./res/" + heightMap + ".png");
	//physics->addTerrainHeightMap(terrain);
	terrains.push_back(terrain);
}

void Game::addTexturePack(std::string r, std::string g, std::string b, std::string background, std::string packName){
	ModelTexture *rTexture = new ModelTexture(loader.loadTexture("./res/" + r + ".png"));
	ModelTexture *gTexture = new ModelTexture(loader.loadTexture("./res/" + g + ".png"));
	ModelTexture *bTexture = new ModelTexture(loader.loadTexture("./res/" + b + ".png"));
	ModelTexture *backgroundTexture = new ModelTexture(loader.loadTexture("./res/" + background + ".png"));
	TerrainTexturePack *texturePack = new TerrainTexturePack(rTexture, gTexture, bTexture, backgroundTexture);
	TerrainTexturePacks[packName].push_back(texturePack);

}

void Game::addModel(std::string modelFile, std::string modelName){
	std::vector<ModelData> data = loader.loadCollada("./res/" + modelFile); //load meshes vector
	std::vector<RawModel> model; //the whole scene of meshes
	std::vector<ModelTexture> textures; //different mesh textures
	for (int i = 0; i < data.size(); i++){
		RawModel meshid = loader.loadToVao(data[i].getVertices(), data[i].getTexCoords(), data[i].getNormals(), data[i].getIndices());
		model.push_back(meshid); 
		textures.push_back(data[i].getTextures());
	}
	models[modelName].push_back(TexturedModel(model, textures, modelName)); //new texturedmodel which is basically a scene

	for (int i = 0; i < allEntities.size(); i++){
		allEntities.at(i)[modelName];
	}
		

}

void Game::addModel(std::string modelFile, std::string modelName, std::string textureFile){
	std::vector<ModelData> data = loader.loadCollada("./res/" + modelFile);
	for (int i = 0; i < data.size(); i++){
		RawModel model = loader.loadToVao(data[i].getVertices(), data[i].getTexCoords(), data[i].getNormals(), data[i].getIndices());

		models[modelName].push_back(TexturedModel(model, loader.loadTexture("./res/" + textureFile), modelName));
	}

	for (int i = 0; i < allEntities.size(); i++){
		allEntities.at(i)[modelName];
	}
}


Game::~Game()
{
	delete physics;
	for (int i = 0; i < terrains.size(); i++)
		delete terrains[i];
	for (int i = 0; i < waters.size(); i++)
		delete waters[i];
	std::map < std::string, std::vector<TerrainTexturePack*>>::iterator it = TerrainTexturePacks.begin();
	std::map < std::string, std::vector<TerrainTexturePack*>>::iterator itend = TerrainTexturePacks.end();
	for (; it != itend; ++it){
		for (int i = 0; i < it->second.size(); i++)
			delete it->second[i];
	}
	delete player;
	for (int i = 0; i < allEntities.size(); i++){
		std::map<std::string, std::vector<EntityInterface*>>::iterator it = allEntities.at(i).begin();
		std::map<std::string, std::vector<EntityInterface*>>::iterator itend = allEntities.at(i).end();
		for (; it != itend; ++it){
			for (int j = 0; j < it->second.size(); j++) {
				delete it->second.at(j);
			}
		}
	}

}




void Game::calcRenderTerrains(float range){
	

	float px = player->getPosition().x;
	float pz = player->getPosition().z;
	float rx = px + range;
	float lx = px - range;
	float uz = pz + range;
	float dz = pz - range;
	

/*Z 
  ^ rx,dz---------px,dz---------lx,dz
  |  |							  |
  |  |							  |
  |  |							  |
  |  |							  |
  |rx,pz		 player		    lx,pz 0
  |  |							  |
  |  |							  |
  |  |							  |
  |  |							  |
  |	rx,uz--------px,uz---------lx,uz
   ----------------------------> X
	*/
	
	terrainVector.clear();

	int terrain1 = onTerrain(lx, uz);
	int terrain2 = onTerrain(rx, uz);
	int terrain3 = onTerrain(lx, dz);
	int terrain4 = onTerrain(rx, dz);
	int terrain5 = onTerrain(px, uz);
	int terrain6 = onTerrain(px, dz);

	int terrain7 = onTerrain(lx, pz);
	int terrain8 = onTerrain(rx, pz);

	terrainVector.push_back(terrain1);
	terrainVector.push_back(terrain2);
	terrainVector.push_back(terrain3);
	terrainVector.push_back(terrain4);
	terrainVector.push_back(terrain5);
	terrainVector.push_back(terrain6);
	terrainVector.push_back(terrain7);
	terrainVector.push_back(terrain8);



	if (terrain3 == 1){

	}
	int first = -1;
	int second = -1;
	int third = -1;
	int fourth = -1;
	int fifth = -1;
	int sixth = -1;
	int seventh = -1;
	int eight = -1;
	int ninth = player->getTerrainNumber();
	int size = terrainVector.size();
	std::vector<int> temp;
	for (int i = 0; i < size; i++){
		if (terrainVector[i] == -1){
			continue;
		}
		if (terrainVector[i] == first || terrainVector[i] == second || terrainVector[i] == third || terrainVector[i] == fourth
			|| terrainVector[i] == fifth || terrainVector[i] == sixth || terrainVector[i] == seventh || terrainVector[i] == eight){
			continue;
		}
		if (first == -1){
			first = terrainVector[i];
			continue;
		}
		if (second == -1){
			second = terrainVector[i];
			continue;
		}
		if (third == -1){
			third = terrainVector[i];
			continue;
		}
		if (fourth == -1){
			fourth = terrainVector[i];
			continue;
		}
		if (fifth == -1){
			fifth = terrainVector[i];
			continue;
		}
		if (sixth == -1){
			sixth = terrainVector[i];
			continue;
		}
		if (seventh == -1){
			seventh = terrainVector[i];
			continue;
		}
		if (eight == -1){
			eight = terrainVector[i];
			continue;
		}

	}
	if (terrainVector.size() != 4){

	}
	terrainVector.clear();

	if (first != -1 ){
		terrainVector.push_back(first);
	}
	if (second != -1 && second != first){
		terrainVector.push_back(second);
	}
	if (third != -1 && third != first && third != second){
		terrainVector.push_back(third);
	}
	if (fourth != -1 && fourth != first && fourth != second && fourth != third){
		terrainVector.push_back(fourth);
	}
	if (fifth != -1 && fifth != fourth && fifth != third && fifth != second && fifth != first){
		terrainVector.push_back(fifth);
	}
	if (sixth != -1){
		terrainVector.push_back(sixth);
	}
	if (seventh != -1){
		terrainVector.push_back(seventh);
	}
	if (eight != -1){
		terrainVector.push_back(eight);
	}
	if (ninth != -1){
		terrainVector.push_back(ninth);
	}




}


int Game::onTerrain(float x, float z){
	int size = terrains.size();
	Terrain** arr = &terrains[0];
	for (int i = 0; i < size; i++) {
		if (x > arr[i]->getX() &&
			z > arr[i]->getZ() &&
			x < arr[i]->getX() + arr[i]->getSize() &&
			z < arr[i]->getZ() + arr[i]->getSize())
		{
			//	std::cout << i << std::endl;
			return i;
		}
	}
	//std::cout << terrainNumber << std::endl;
	return -1;
}
