#pragma once
class Terrain;
#include "EntityInterface.h"
#include "TexturedModel.h"
#include <map>
#include <SDL/SDL.h>
#include <cmath>
#include <iostream>
#include "DisplayManager.h"
#include <vector>
#include "Terrain.h"
#include <iostream>
#include "InputHandler.h"
#include "Physics.h"
class Physics;
#ifndef PI
#define PI 3.14159265;
#endif

class LocalPlayer : public EntityInterface
{
public:
	LocalPlayer(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, TexturedModel *model, InputHandler *input, int terrainNumber, Physics *physics);
	~LocalPlayer();
	void move(float DeltaSeconds, std::vector<Terrain*> &terrains);
	void checkInputs();
	int onTerrain(std::vector<Terrain*> &terrains);
	InputHandler* getInput() { return input; }
	int getTerrainNumber() { return terrainNumber; }

private:
	InputHandler *input;
	std::map<SDL_Keycode, bool> *keysPressed;
	int terrainNumber = -1;
	float forward_speed = 200;
	float strafe_speed = 150;
	float backward_speed = -150;
	float turn_speed = 3.14159265;
	float jump_power = 50;
	enum state { mFORWARD, mBACKWARD, mSTRAFELEFT, mSTRAFERIGHT, mSTOPPED };
	state pstate = mSTOPPED;
	float currentSpeedHorizontal = 0;
	float currentSpeedVertical = 0;
	float currentTurnSpeed = 0;
	float upwardsSpeed = 0;
	bool jumping = false;
	bool moved = false;
	void jump();
	const float TERRAIN_HEIGHT = 1;
	float gravity = -100;
	float terrainheight = 0;
	bool fly = false;
	Physics *physics;

};

