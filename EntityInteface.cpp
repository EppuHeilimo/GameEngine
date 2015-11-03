#include "EntityInterface.h"
#include "MyMaths.h"


EntityInterface::EntityInterface(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, TexturedModel *model, int terrainNumber)
{
	this->terrainNumber = terrainNumber;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->model = model;
	transformation = MyMaths::createTransformationmatrix(position, rotation.x, rotation.y, rotation.z, scale);
}

EntityInterface::EntityInterface(const EntityInterface &entity){

}

EntityInterface::EntityInterface()
{
	delete model;
}

void EntityInterface::increasePosition(float dx, float dy, float dz){
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void EntityInterface::increaseRotation(float rx, float ry, float rz){
	this->rotation.x += rx;
	this->rotation.y += ry;
	this->rotation.z += rz;
	if (this->rotation.x > 2 * 3.14 || this->rotation.x < 2 * -3.14)
		this->rotation.x = 0;
	if (this->rotation.y > 2 * 3.14 || this->rotation.y < 2 * -3.14)
		this->rotation.y = 0;
	if (this->rotation.z > 2 * 3.14 || this->rotation.z < 2 * -3.14)
		this->rotation.z = 0;
}


EntityInterface::~EntityInterface()
{
}
