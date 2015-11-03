#pragma once
#include <glm\glm.hpp>
#include "Camera.h"
#include "MyMaths.h"
#include "InputHandler.h"
#include "DisplayManager.h"
#include "Physics.h"
#include "Entity.h"
class MousePicker
{
public:

	MousePicker(Camera &cam, glm::mat4 &projection, InputHandler *input, Physics *physics);
	~MousePicker();
	glm::vec3 getCurrentRay(){ return currentRay; }
	void update();
private:
	glm::vec3 calculateMouseRay();
	glm::vec3 toWorldCoords(glm::vec4 &eyeCoords);
	glm::vec4 toEyeCoords(glm::vec4 &clipCoords);
	glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);

	glm::vec3 currentRay;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Camera *camera;
	InputHandler *input;
	Physics *physics;
	btCollisionWorld::ClosestRayResultCallback *callback;
};

