#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
class Camera;
#include "Camera.h"


class MyMaths
{
public:
	MyMaths();
	~MyMaths();
	static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
	static glm::mat4 createViewMatrix(Camera &camera);
	static glm::mat4 createTransformationmatrix(glm::vec3 translation, float rx, float ry, float rz, glm::vec3 scale);
	static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
};

