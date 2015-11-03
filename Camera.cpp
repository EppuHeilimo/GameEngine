#include "Camera.h"


Camera::Camera(LocalPlayer *player)
{
	this->player = player;
	position = player->getPosition();
}

Camera::~Camera()
{

}

void Camera::move()
{
	//calculateAngleAroundPlayer();
	calculatePitch();
	float horizontalDistance = calculateHorizontalDistance();
	float verticalDistance = calculateVerticalDistance();
	calculateCameraPosition(horizontalDistance, verticalDistance);
	this->yaw = 3.14159265 - ((player->getRotation().y) + angleAroundPlayer);

}

void Camera::increasePosition(float dx, float dy, float dz){
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Camera::calculateCameraPosition(float hDistance, float vDistance)
{
	float theta = player->getRotation().y + this->angleAroundPlayer;
	float offsetZ = (float)(hDistance * cos(theta));
	float offsetX = (float)(vDistance * sin(theta));
	this->position.z = player->getPosition().z - offsetZ;
	this->position.x = player->getPosition().x - offsetX;
	this->position.y = player->getPosition().y + vDistance;

}

void Camera::calculateAngleAroundPlayer() {
	if (player->getInput()->getKeysPointer()->at(SDL_BUTTON_RIGHT)) {
		glm::vec2 temp = player->getInput()->getMouseDif();
		player->increaseRotation(0, temp.x * -0.005, 0);//angleAroundPlayer -= temp.x * 0.005;
	}
}

void Camera::calculatePitch() {
	

}

float Camera::calculateHorizontalDistance()
{
	return (float)(distanceFromPlayer * pitch); // cos(pitch));// * 3.14159265 / 180));
}

float Camera::calculateVerticalDistance()
{
	return (float)(distanceFromPlayer * pitch); // sin(pitch)); // 3.14159265 / 180));
}


