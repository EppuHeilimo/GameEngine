#pragma once
#include <vector>
#include <string>
#include <glew/GL/glew.h>
#include "RawModel.h"
#include "SkyboxShader.h"
#include "Loader.h"
#include <glm/glm.hpp>
#include "Camera.h"
class SkyBoxRenderer
{
public:
	SkyBoxRenderer();
	SkyBoxRenderer(Loader &loader, glm::mat4 &projection);
	~SkyBoxRenderer();
	void render(Camera &camera, float RED, float GREEN, float BLUE);
	
private:
	const float SIZE = 1000.0f;

	/* ALWAYS THIS ORDER */
	std::vector<std::string> TEXTURE_FILES;

	RawModel cube;
	GLuint texture;
	SkyboxShader shader;


	std::vector<float> vertices;
};

