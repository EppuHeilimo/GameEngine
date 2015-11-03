#include "Entity.h"


Entity::Entity(int id, void* ePointer, btRigidBody* body, EntityType type)
{
	this->type = type;
	this->id = id;
	this->vPointer = ePointer;
	this->hitByMouse = false;
	this->body = body;
}


Entity::~Entity()
{
	if (vPointer != NULL)
		delete vPointer;
}
