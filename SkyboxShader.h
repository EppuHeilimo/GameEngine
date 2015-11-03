#pragma once
#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <glm\glm.hpp>
#include "Camera.h"
#include "MyMaths.h"
class SkyboxShader : public ShaderProgram
{
public:
	SkyboxShader();
	~SkyboxShader();
	void loadSkyColor(float r, float g, float b);
	void loadTextures();
	void loadViewMatrix(Camera &camera);
	void loadProjectionMatrix(glm::mat4&);
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	int location_skyColor;
	int location_textureSampler;
	int location_viewMatrix;
	int location_projection;
};


