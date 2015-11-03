#include <iostream>
#include "DisplayManager.h"
#include "glew/GL/glew.h"
#include "MasterRenderer.h"
#include "Loader.h"
#include "glm\glm.hpp"
#include <vector>
#include "Light.h"
#include "InputHandler.h"
#include "Renderer2D.h"
#include "GameTime.h"
#include "Game.h"
#include "ParticleShader.h"
#include "ParticleSystem.h"
#include "Physics.h"
#include "MousePicker.h"
#include "bt\btBulletCollisionCommon.h"

bool callBackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2);

int main(int argc, char** argv){
	gContactAddedCallback = callBackFunc;
	DisplayManager *display = new DisplayManager(1440, 900, "Game");
	Loader loader;
	InputHandler input(display->getWindowHandle());
	Game *game = new Game(display, input);
	MasterRenderer renderer(loader, *game);
	Renderer2D render2D(loader);
	Light *sun = new Light(glm::vec3(-1000.0f, 500.0f, 1000.0f), glm::vec3(1, 0.9, 0.2), glm::vec3(1.0f, 0.0f, 0.0f));
	std::vector<Light*> lights;
	lights.push_back(sun);
	GameTime gametime(display, 5.0f, 5.0f, 5.0f, 5.0f);
	MousePicker mousePick(game->getCamera(), renderer.getProjection(), &input, game->getPhysics());
	ParticleSystem particle;
	particle.SetGeneratorProperties(
		glm::vec3(-45.0f, 45.5f, -40.0f), // Where the particles are generated
		glm::vec3(-5, 0, -5), // Minimal velocity
		glm::vec3(5, 20, 5), // Maximal velocity
		glm::vec3(0, -5, 0), // Gravity force applied to particles
		glm::vec3(0.0f, 0.5f, 1.0f), // Color (light blue)
		1.5f, // Minimum lifetime in seconds
		3.0f, // Maximum lifetime in seconds
		10.0f, // Rendered size
		0.02f, // Spawn every 0.05 seconds
		30); // And spawn 30 particles 
	
	
	while(!input.hasClosed()){		
		game->getCamera().move();
		game->calcRenderTerrains(900);
		
		renderer.render(game->getPlayer(), game->getAllEntities(), game->getCamera(), 
			lights, game->getTerrains(), game->getGUI(), game->getWaters(), game->getTerrainVector(), particle);

		game->getPhysics()->update();
		render2D.render(game->getGUI());
		mousePick.update();
		display->update();
		input.poll();
		game->getPlayer().move(display->getFrameTime(), game->getTerrains());
		gametime.updateTime();	

	}
	delete game;
	delete sun;
	delete display;
	return 0;
}


bool callBackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2){
	std::cout << ((Entity*)obj2->getCollisionObject()->getUserPointer())->id << " collided with " << ((Entity*)obj1->getCollisionObject()->getUserPointer())->id << std::endl;
	return false;
}

