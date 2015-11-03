#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
class WaterShader : public ShaderProgram
{
public:
	WaterShader();
	~WaterShader();
	void loadTransform(glm::mat4&);
	void loadProjection(glm::mat4&);
	void loadViewMatrix(Camera &camera);
	void loadTextures();
	void loadMove(float f);
	void loadLights(std::vector<Light*> lights);
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	int location_transform;
	int location_viewMatrix;
	int location_projectionMatrix;
	int location_refractionTexture;
	int location_reflectionTexture;
	int location_dudv;
	int location_move;
	int location_cameraPos;
	int location_normalMap;
	int location_lightPosition;
	int location_lightColor;
	int location_depthMap;
};

