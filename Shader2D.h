#pragma once
#include "ShaderProgram.h"
class Shader2D : public ShaderProgram
{
public:
	Shader2D();
	~Shader2D();
	void loadTransform(glm::mat4&);
	void loadTextures();
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	int location_transform;
	int location_textureSampler;


};

