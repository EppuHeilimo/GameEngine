#pragma once
#include "ShaderProgram.h"
class DepthShader : public ShaderProgram
{
public:
	DepthShader();
	~DepthShader();

	void loadLightSpace(glm::mat4&);
	void loadTransform(glm::mat4&);
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	int location_LightSpace;
	int location_model;
	int location_Transform;

};

