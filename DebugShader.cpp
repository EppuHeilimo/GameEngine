#include "DebugShader.h"


DebugShader::DebugShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void DebugShader::getAllUniformLocations(){

	location_transform = getUniformLocation("transform");
	location_view = getUniformLocation("view");
	location_projection = getUniformLocation("projection");
}

void DebugShader::bindAttributes(){
	bindAttribute(0, "position");
}

std::string DebugShader::vertexfileLocation(){
	return "./res/debugShaderVertex.txt";
}

std::string DebugShader::fragmentfileLocation(){
	return "./res/debugShaderFragment.txt";
}

void DebugShader::loadProjection(glm::mat4& projection){
	loadMatrix(location_projection, projection);
}

void DebugShader::loadTransform(glm::mat4 &matrix){
	loadMatrix(location_transform, matrix);
}

void DebugShader::loadView(Camera &cam){
	glm::mat4 view = MyMaths::createViewMatrix(cam);
	loadMatrix(location_projection, view);
}

void DebugShader::loadTextures()
{
	loadInt(location_textureSampler, 0);
}


DebugShader::~DebugShader()
{
	ShaderProgram::~ShaderProgram();
}

