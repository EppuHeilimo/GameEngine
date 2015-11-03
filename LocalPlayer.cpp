#include "LocalPlayer.h"


LocalPlayer::LocalPlayer(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, TexturedModel *model, InputHandler *input, int terrainNumber, Physics *physics)
	: EntityInterface(position, rotation, scale, model, terrainNumber)
{
	this->physics = physics;
	this->input = input;
	physics->addPlayer(10, 10, 10, position.x, position.y, position.z, 0, this);
}

LocalPlayer::~LocalPlayer()
{

}

void LocalPlayer::move(float deltaseconds, std::vector<Terrain*> &terrains)
{

	moved = false;
	checkInputs();
	EntityInterface::increaseRotation(0, currentTurnSpeed * deltaseconds, 0);
	
	//Entity::increaseRotation(0, input->getMouseDif().y * -0.1, 0);

	float distanceHorizontal = currentSpeedHorizontal * deltaseconds;
	float distanceVertical = currentSpeedVertical * deltaseconds;

	if (currentSpeedHorizontal != 0){
		float dx = (float)(distanceHorizontal * sin(EntityInterface::getRotation().y));
		float dz = (float)(distanceHorizontal * cos(EntityInterface::getRotation().y));
		EntityInterface::increasePosition(dx, 0, dz);
		moved = true;
	}

	if (currentSpeedVertical != 0){
		float dx = (float)(distanceVertical * sin(EntityInterface::getRotation().y + (PI / 2)));
		float dz = (float)(distanceVertical * cos(EntityInterface::getRotation().y + (PI / 2)));
		EntityInterface::increasePosition(dx, 0, dz);
		moved = true;
	}

	if (!fly)
		upwardsSpeed += gravity * deltaseconds;
	EntityInterface::increasePosition(0, upwardsSpeed * deltaseconds, 0);
	if (terrainNumber != -1)
		terrainheight = terrains[terrainNumber]->getHeightOfTerrain(getPosition().x, getPosition().z);
	else
		terrainheight = TERRAIN_HEIGHT;
	if (EntityInterface::getPosition().y < terrainheight && !fly){ //){
		upwardsSpeed = 0;
		jumping = false;
		EntityInterface::setEntityYposition(terrainheight);
	}
	onTerrain(terrains);
	physics->updatePlayer(getPosition().x, getPosition().y, getPosition().z);
	

}

void LocalPlayer::checkInputs()
{ 
	if (input->getKeysPointer()->at(SDLK_w)){
		currentSpeedHorizontal = forward_speed;
	}
	
	else if (input->getKeysPointer()->at(SDLK_s)){
		currentSpeedHorizontal = backward_speed;
	}

	else
		currentSpeedHorizontal = 0;

	if (input->getKeysPointer()->at(SDLK_d)){
		currentSpeedVertical = -strafe_speed;
	}

	else if (input->getKeysPointer()->at(SDLK_a)){
		currentSpeedVertical = strafe_speed;
	}

	else
		currentSpeedVertical = 0;

	if (input->getKeysPointer()->at(SDLK_q)){
		currentTurnSpeed = turn_speed;
	}

	else if (input->getKeysPointer()->at(SDLK_e)){
		currentTurnSpeed = -turn_speed;
	}
	else 
		currentTurnSpeed = 0;
	if (input->getKeysPointer()->at(SDLK_SPACE)){
		if (!fly)
			jump();
		else
			this->upwardsSpeed = jump_power;
	}

	if (fly && input->getKeysPointer()->at(SDLK_LSHIFT)){
		this->upwardsSpeed = -jump_power;
	}
	else if (fly && !input->getKeysPointer()->at(SDLK_SPACE)){
		this->upwardsSpeed = 0;
	}
	

	if (input->getKeysPointer()->at(SDLK_F5)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (input->getKeysPointer()->at(SDLK_F6)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (input->getKeysPointer()->at(SDLK_F7)){
		fly = !fly;
		std::cout << "x: " << getPosition().x << " y: " << getPosition().y << " z: " << getPosition().z << "\n";
		std::cout << "yaw: " << getRotation().y << "\n";
	}

	if (input->getKeysPointer()->at(SDL_BUTTON_RIGHT)) {
		glm::vec2 temp = input->getMouseDif();
		increaseRotation(0, temp.x * -0.01, 0);//angleAroundPlayer -= temp.x * 0.005;
	}

	
	
}


int LocalPlayer::onTerrain(std::vector<Terrain*> &terrains)
{
	for (int i = 0; i < terrains.size(); i++) {
		if (getPosition().x > terrains[i]->getX() &&
			getPosition().z > terrains[i]->getZ() &&
			getPosition().x < terrains[i]->getX() + terrains[i]->getSize() &&
			getPosition().z < terrains[i]->getZ() + terrains[i]->getSize())
		{
			terrainNumber = i;
		//	std::cout << i << std::endl;
			return i;
		}
	}
	terrainNumber = -1;
	//std::cout << terrainNumber << std::endl;
	return -1;
}

void LocalPlayer::jump()
{
	if (!jumping){
		this->upwardsSpeed = jump_power;
		jumping = true;
	}
}
