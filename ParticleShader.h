#pragma once
#include <glm\glm.hpp>
#include <string>
#include "ShaderProgram.h"
class ParticleShader : public ShaderProgram
{
public:
	ParticleShader();
	~ParticleShader();

	void loadLightSpace(glm::mat4&);
	void loadTransform(glm::mat4&);
	void loadProjection(glm::mat4& projection);
	void loadView(glm::mat4&);
	void loadQuad1(glm::vec3&);
	void loadQuad2(glm::vec3&);
	void loadTextures();
private:
	void getAllUniformLocations() override;
	void bindAttributes() override;
	std::string vertexfileLocation();
	std::string fragmentfileLocation();
	std::string geometryfileLocation();
	int location_gsampler;
	int location_view;
	int location_projection;
	int location_quad1;
	int location_quad2;
};

