#pragma once
#include "bt\btBulletDynamicsCommon.h"
#include "bt\btBulletCollisionCommon.h"
#include "DisplayManager.h"
#include <vector>
#include <iostream>
#include "EntityInterface.h"
#include "LocalPlayer.h"
#include "Entity.h"
#include "MyDebug.h"
#include "Terrain.h"
class MyDebug;

class Physics
{
public:

	Physics(DisplayManager *display);
	~Physics();
	btDefaultCollisionConfiguration* collConfig;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	void update();
	DisplayManager *display;


	std::vector<Entity*>& getBulletObjects(){ return Entities; }
	
	void addSphere(float rad, float x, float y , float z, float mass);
	void addStaticBox(float width, float height, float depth, float x, float y, float z, float mass, void* c);
	void addTerrainHeightMap(Terrain *terrain);
	void addPlayer(float width, float height, float depth, float x, float y, float z, float mass, void* c);
	void updatePlayer(float x, float y, float z);
	btRigidBody *player;
	btDiscreteDynamicsWorld* getWorld(){ return dynamicsWorld; }

	std::vector<Entity*> Entities;
	MyDebug *debug;

	btTriangleMesh *mTriMesh;
};

