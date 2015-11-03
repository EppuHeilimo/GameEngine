#include <iostream>
#include "MyDebug.h"


using std::cout;
using std::endl;

#include <stdio.h>
MyDebug::MyDebug(){
	shader = new DebugShader();
}
MyDebug::~MyDebug(){
	delete shader;
}

void MyDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	shader->start();
	glBegin(GL_LINES);
	glVertex3f(from.getX(), from.getY(), from.getZ());
	glVertex3f(to.getX(), to.getY(), to.getZ());
	glEnd();
	shader->stop();
	/*
	vertices.push_back(from.getX());
	vertices.push_back(from.getY());
	vertices.push_back(from.getZ());
	vertices.push_back(to.getX());
	vertices.push_back(to.getY());
	vertices.push_back(to.getZ());
	*/
}

void MyDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

}

void MyDebug::reportErrorWarning(const char* warningString)
{

}

void MyDebug::draw3dText(const btVector3& location, const char* textString)
{

}


void MyDebug::draw(glm::vec3 &transform, Camera &cam, glm::mat4 &projection){
	RawModel model = loader.loadToVao(vertices, 3);
	//glDisable(GL_DEPTH_TEST);
	shader->start();
	shader->loadTransform(MyMaths::createTransformationmatrix(transform, 0, 0, 0, glm::vec3(0,0,0)));
	shader->loadView(cam);
	shader->loadProjection(projection);
	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, model.getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
	//glEnable(GL_DEPTH_TEST);
	vertices.clear();
}
