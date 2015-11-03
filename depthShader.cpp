#include "depthShader.h"


DepthShader::DepthShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void DepthShader::getAllUniformLocations(){

	location_LightSpace = getUniformLocation("lightSpaceMatrix");
	location_Transform = getUniformLocation("transform");
}

void DepthShader::bindAttributes(){
	bindAttribute(0, "position");
}

std::string DepthShader::vertexfileLocation(){
	return "./res/depthShader.txt";
}

std::string DepthShader::fragmentfileLocation(){
	return "./res/EmptyFragment.txt";
}

void DepthShader::loadLightSpace(glm::mat4& matrix){
	loadMatrix(location_LightSpace, matrix);
}

void DepthShader::loadTransform(glm::mat4& matrix){
	loadMatrix(location_Transform, matrix);
}

DepthShader::~DepthShader()
{
	ShaderProgram::~ShaderProgram();
}
