#pragma once
#include "ShaderProgram.h"
#include "MyMaths.h"
class DebugShader : public ShaderProgram
{
public:
	DebugShader();
	~DebugShader();
	void loadTransform(glm::mat4&);
	void loadTextures();
	void loadView(Camera &cam);
	void loadProjection(glm::mat4& projection);
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	int location_transform;
	int location_projection;
	int location_view;
	int location_textureSampler;

};

