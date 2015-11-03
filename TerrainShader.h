#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include <string>
#include "MyMaths.h"
#include <glm\glm.hpp>
#include <vector>
#include "Light.h"
#include <sstream>
class TerrainShader : public ShaderProgram
{
public:
	TerrainShader();
	~TerrainShader();
	void loadSkyColor(float r, float g, float b);
	void loadTextures();
	void loadViewMatrix(Camera &camera);
	void loadProjectionMatrix(glm::mat4&);
	void loadTransform(glm::mat4 &matrix);
	void connectTextureUnits();
	void loadShine(float damper, float reflectivity);
	void loadLights(std::vector<Light*> lights);
	void loadLightSpace(glm::mat4& matrix);
	void loadShadowMap();
	void loadClipPlane(glm::vec4& clipPlane);
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	int location_skyColor;
	int location_viewMatrix;
	int location_projection;
	int location_transform;
	int location_shineDamper;
	int location_reflectivity;
	int location_backgroundTexture;
	int location_rTexture;
	int location_gTexture;
	int location_bTexture;
	int location_blendMap;
	int max_lights = 1;
	int location_LightPosition[4];
	int location_LightColor[4];
	int location_Attenuation[4];
	int location_LightSpace;
	int location_shadowMap;
	int location_plane;
};

