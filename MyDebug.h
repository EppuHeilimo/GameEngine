#pragma once
#include <iostream>
#include <glew\GL\glew.h>
#include "bt\btBulletCollisionCommon.h"
#include <vector>
#include "Loader.h"
#include "RawModel.h"
#include "DebugShader.h"
#include "MyMaths.h"
class DebugShader;

class MyDebug : public btIDebugDraw
{
public:
	MyDebug();
	~MyDebug();

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	virtual void reportErrorWarning(const char* warningString);

	virtual void draw3dText(const btVector3& location, const char* textString);

	virtual void setDebugMode(int debugMode) { m_debugMode = debugMode; }

	int getDebugMode() const { return m_debugMode; }

	std::vector<float> vertices;
	std::vector<float> colors;

	void draw(glm::vec3 &transform, Camera &cam, glm::mat4 &projection);
	Loader loader;
	DebugShader *shader;


	int m_debugMode;
};

