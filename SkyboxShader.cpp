#include "SkyboxShader.h"


SkyboxShader::SkyboxShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void SkyboxShader::getAllUniformLocations(){
	location_skyColor = getUniformLocation("skyColor");
	location_textureSampler = getUniformLocation("cubeMap");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_projection = getUniformLocation("projectionMatrix");
}

void SkyboxShader::bindAttributes(){
	bindAttribute(0, "position");
}

std::string SkyboxShader::vertexfileLocation(){
	return "./res/skyboxVertex.txt";
}

std::string SkyboxShader::fragmentfileLocation(){
	return "./res/skyboxFragment.txt";
}

void SkyboxShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r, g, b));
}

void SkyboxShader::loadTextures()
{
	loadInt(location_textureSampler, 0);
}

void SkyboxShader::loadViewMatrix(Camera &camera)
{
	//MyMaths math;
	glm::mat4 viewMatrix = MyMaths::createViewMatrix(camera);
	viewMatrix[3][0] = 0.0;
	viewMatrix[3][1] = 0.0;
	viewMatrix[3][2] = 0.0;
	loadMatrix(location_viewMatrix, viewMatrix);
}

void SkyboxShader::loadProjectionMatrix(glm::mat4& projection)
{
	loadMatrix(location_projection, projection);
}

SkyboxShader::~SkyboxShader()
{
	ShaderProgram::~ShaderProgram();
}

