#pragma once
class LocalPlayer;
#include <glm/glm.hpp>
#include "LocalPlayer.h"
#include <cmath>
#include <iostream>

#ifndef PI
#define PI 3.14159265359
#endif

class Camera
{
public:
	Camera(LocalPlayer *player);
	~Camera();
	void move();
	void setPosition(glm::vec3 newpos) { position = newpos; }
	void setPitch(float pitch) { this->pitch = pitch; }
	void setYaw(float yaw) { this->yaw = yaw; }
	void setRoll(float roll) { this->roll = roll; }
	glm::vec3 getPosition() { return position; }
	float getPitch() { return pitch; }
	float getYaw() { return yaw; }
	float getRoll() { return roll; }
	void increasePosition(float dx, float dy, float dz);
	void invertCamera(){ this->pitch = -pitch; }
private:
	void calculatePitch();
	void calculateCameraPosition(float, float);
	void calculateAngleAroundPlayer();
	float calculateHorizontalDistance();
	float calculateVerticalDistance();
	glm::vec3 position = glm::vec3(0, 0, 0);
	float pitch = 0.2f;
	float distanceFromPlayer = 50;
	float angleAroundPlayer = 0;
	float yaw = 0;
	float roll = 0;
	LocalPlayer *player;

};

