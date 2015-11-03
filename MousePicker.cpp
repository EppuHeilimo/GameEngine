#include "MousePicker.h"


MousePicker::MousePicker(Camera &cam, glm::mat4 &projection, InputHandler *input, Physics *physics)
{
	this->input = input;
	this->camera = &cam;
	this->projectionMatrix = projection;
	this->viewMatrix = MyMaths::createViewMatrix(*camera);
	this->physics = physics;
	currentRay = calculateMouseRay();
	glm::vec3 endVector = currentRay * 1000.0f;
	this->callback = new btCollisionWorld::ClosestRayResultCallback(btVector3(currentRay.x, currentRay.y, currentRay.z), btVector3(endVector.x, endVector.y, endVector.z));
}


MousePicker::~MousePicker()
{
}

void MousePicker::update(){
	/*
	currentRay = calculateMouseRay();
	glm::vec3 endVector = currentRay * 1000.0f;
	btCollisionWorld::ClosestRayResultCallback callback2(btVector3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z), btVector3(endVector.x, endVector.y, endVector.z));
	physics->getWorld()->rayTest(btVector3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z), btVector3(endVector.x, endVector.y, endVector.z), callback2);
	
	if (callback2.hasHit()){
		std::cout << "hit something" << std::endl;
		//(BulletObject*)callback->m_collisionObject->getUserPointer();
	}
	*/
	// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
	float mouseX = input->getMousePos().x;
	float mouseY = input->getMousePos().y;
	glm::vec4 lRayStart_NDC(
		((float)mouseX / (float)DisplayManager::getWidth() - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)mouseY / (float)DisplayManager::getHeight() - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
		);
	glm::vec4 lRayEnd_NDC(
		((float)mouseX / (float)DisplayManager::getWidth() - 0.5f) * 2.0f,
		((float)mouseY / (float)DisplayManager::getHeight() - 0.5f) * 2.0f,
		0.0,
		1.0f
		);
	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	glm::mat4 InverseProjectionMatrix = glm::inverse(projectionMatrix);

	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	this->viewMatrix = MyMaths::createViewMatrix(*camera);
	glm::mat4 InverseViewMatrix = glm::inverse(viewMatrix);

	glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera /= lRayStart_camera.w;
	glm::vec4 lRayStart_world = InverseViewMatrix       * lRayStart_camera; lRayStart_world /= lRayStart_world.w;
	glm::vec4 lRayEnd_camera = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera /= lRayEnd_camera.w;
	glm::vec4 lRayEnd_world = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world /= lRayEnd_world.w;


	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);
	currentRay = lRayDir_world;
	glm::vec3 endVector = lRayDir_world * 1000.0f;


	btCollisionWorld::ClosestRayResultCallback callback2(btVector3(currentRay.x, currentRay.y, currentRay.z), btVector3(endVector.x, endVector.y, endVector.z));
	physics->getWorld()->rayTest(btVector3(currentRay.x, currentRay.y, currentRay.z), btVector3(endVector.x, endVector.y, endVector.z), callback2);

	if (callback2.hasHit() && callback2.m_collisionObject->getUserPointer() != NULL){
		std::cout << "hit " << ((Entity*)callback2.m_collisionObject->getUserPointer())->id << std::endl;
	}
	//else
		//std::cout << std::endl;
	if (callback2.hasHit() && input->getKeysPointer()->at(SDL_BUTTON_LEFT)){
		((EntityInterface*)((Entity*)callback2.m_collisionObject->getUserPointer())->vPointer)->setPosition(endVector.x, endVector.y, endVector.z);
		btTransform t;
		t.setOrigin(btVector3(endVector.x, endVector.y, endVector.z));
		((Entity*)callback2.m_collisionObject->getUserPointer())->body->setWorldTransform(t);
	}
	// Faster way (just one inverse)
	//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;
}

glm::vec3 MousePicker::calculateMouseRay(){
	float mouseX = input->getMousePos().x;
	float mouseY = input->getMousePos().y;
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}
glm::vec3 MousePicker::toWorldCoords(glm::vec4 &eyeCoords){
	glm::mat4 invertedView = glm::inverse(viewMatrix); 
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	glm::normalize(mouseRay);
	return mouseRay;
}
glm::vec4 MousePicker::toEyeCoords(glm::vec4 &clipCoords){
	glm::mat4 invertedProjection = glm::inverse(projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}
glm::vec2 MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY){
	float x = (2.f * mouseX) / DisplayManager::getWidth() - 1.f;
	float y = (2.f * mouseY) / DisplayManager::getHeight() - 1.f;
	return glm::vec2(x, y);
}

