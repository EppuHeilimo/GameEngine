#pragma once
#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <glm\glm.hpp>
#include "Camera.h"
#include "MyMaths.h"
#include "Light.h"
#include <string>
#include <sstream>
class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();
	void loadSkyColor(float r, float g, float b);
	void loadTransform(glm::mat4&);
	void loadTextures();
	void loadViewMatrix(Camera &camera);
	void loadProjectionMatrix(glm::mat4&);
	void loadLightSpace(glm::mat4&);
	void loadLights(std::vector<Light*> lights);
	void loadShine(float damper, float reflectivity);
	void loadShadowMap();
	void loadClipPlane(glm::vec4&);
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	//std::string VERTEX_FILE = "./res/vertexShader.txt";
	//std::string FRAGMENT_FILE = "./res/fragmentShader.txt";
	int location_skyColor;
	int location_transform;
	
	int location_viewMatrix;
	int location_projection;
	int location_lightPosition;
	int location_lightColor;
	int location_shineDamper;
	int location_reflectivity;
	int location_LightSpace;
	int location_shadowMap;
	int location_plane;
	int location_textureSampler;
	int location_textureSampler1;
	int location_textureSampler2;
	int location_textureSampler3;
};

