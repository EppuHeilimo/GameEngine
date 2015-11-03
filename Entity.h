#pragma once
#include "bt\btBulletCollisionCommon.h"
#include "EntityInterface.h"
enum EntityType {
	STATIC,
	WATER,
	PLAYER,
	DYNAMIC,
	TERRAIN,
	FRUSTRUM
};

class Entity
{
public:
	EntityType type;
	int id;
	bool hitByMouse;
	void setPickedByMouse(bool b) { hitByMouse = b; }
	void* vPointer;
	btRigidBody* body;
	Entity(int i, void* c, btRigidBody* body, EntityType type);
	~Entity();
};

