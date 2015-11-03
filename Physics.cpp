#include "Physics.h"



Physics::Physics(DisplayManager *display)
{
	this->display = display;
	this->collConfig = new btDefaultCollisionConfiguration();
	this->dispatcher = new btCollisionDispatcher(collConfig);
	this->overlappingPairCache = new btDbvtBroadphase();
	this->solver = new btSequentialImpulseConstraintSolver();
	this->dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collConfig);
	dynamicsWorld->setGravity(btVector3(0, -9.82, 0));
	debug = new MyDebug();
	dynamicsWorld->setDebugDrawer(debug);
	
	dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
}


Physics::~Physics()
{
	delete debug;
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	
	delete dispatcher;
	delete collConfig;

	for (int i = 0; i < Entities.size(); i++){
		//dynamicsWorld->removeCollisionObject(bulletObjects[i]->body);
		btMotionState* motionState = Entities[i]->body->getMotionState();
		btCollisionShape* collShape = Entities[i]->body->getCollisionShape();
		
		delete Entities[i]->body;
		delete motionState;
		delete collShape;
	}
}

void Physics::addTerrainHeightMap(Terrain *terrain) {
	mTriMesh = new btTriangleMesh();
	int size = terrain->getTerrainVertices().size();
	std::vector<float> vertices = terrain->getTerrainVertices();
	btVector3 v1, v2, v3;
	for (int i = 0; i < size / 9; i++) {
		v1.setX( vertices.at(i) );
		v1.setY(vertices.at(i + 1));
		v1.setZ(vertices.at(i + 2));
		v2.setX(vertices.at(i + 3));
		v2.setY(vertices.at(i + 4));
		v2.setZ(vertices.at(i + 5));
		v3.setX(vertices.at(i + 6));
		v3.setY(vertices.at(i + 7));
		v3.setZ(vertices.at(i + 8));
		mTriMesh->addTriangle(v1, v2, v3);
	}
	btCollisionShape *terrainShape;
	terrainShape = new btBvhTriangleMeshShape(mTriMesh, true);
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(terrain->getX(), 0, terrain->getZ()));
	btDefaultMotionState* groundMS = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMS, terrainShape, btVector3(0, 0, 0));
	btRigidBody *body = new btRigidBody(groundRigidBodyCI);
	Entities.push_back(new Entity(Entities.size(), terrain, body, EntityType::TERRAIN));
	body->setUserPointer(Entities[Entities.size() - 1]);
	dynamicsWorld->addRigidBody(body);


}

void Physics::addSphere(float rad, float x, float y, float z, float mass){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	btSphereShape* sphere = new btSphereShape(rad);
	btMotionState* motion = new btDefaultMotionState(t);
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0){
		sphere->calculateLocalInertia(mass, inertia);
	}

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
	btRigidBody *body = new btRigidBody(info);
	dynamicsWorld->addRigidBody(body);
	void* asd;
	Entities.push_back(new Entity(Entities.size(), asd, body, EntityType::STATIC));
	body->setUserPointer(Entities[Entities.size() - 1]);
	//body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
}

void Physics::addStaticBox(float width, float height, float depth, float x, float y, float z, float mass, void* c){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	btBoxShape* box = new btBoxShape(btVector3(width/2.0f, height/2.0f, depth/2.0f));	
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0){
		box->calculateLocalInertia(mass, inertia);
	}
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);
	btRigidBody *body = new btRigidBody(info);
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	body->setRollingFriction(1);
	body->setFriction(1);
	Entities.push_back(new Entity(Entities.size(), c, body, EntityType::STATIC));
	body->setUserPointer(Entities[Entities.size() - 1]);
	dynamicsWorld->addRigidBody(body);
	

	

}

void Physics::addPlayer(float width, float height, float depth, float x, float y, float z, float mass, void* c){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	btBoxShape* box = new btBoxShape(btVector3(width / 2.0, height / 2.0, depth / 2.0));
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0){
		box->calculateLocalInertia(mass, inertia);
	}
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);
	btRigidBody *body = new btRigidBody(info);
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	Entities.push_back(new Entity(Entities.size(), c, body, EntityType::PLAYER));
	body->setUserPointer(Entities[Entities.size() - 1]);
	dynamicsWorld->addRigidBody(body);
	
	player = body;
}

void Physics::updatePlayer(float x, float y, float z){

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	player->setWorldTransform(t);
}


void Physics::update(){

	dynamicsWorld->stepSimulation(display->getFrameTime());
	dynamicsWorld->debugDrawWorld();
	for (Entity* object : Entities) {
		if (object->vPointer == nullptr)
			continue;
		float x = object->body->getWorldTransform().getOrigin().getX();
		float y = object->body->getWorldTransform().getOrigin().getY();
		float z = object->body->getWorldTransform().getOrigin().getZ();
		((EntityInterface*)object->vPointer)->setPosition(x, y, z);
	}

}