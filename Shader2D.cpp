#include "Shader2D.h"


Shader2D::Shader2D() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void Shader2D::getAllUniformLocations(){

	location_transform = getUniformLocation("transform");
	location_textureSampler = getUniformLocation("guiTexture");
}

void Shader2D::bindAttributes(){
	bindAttribute(0, "position");
}

std::string Shader2D::vertexfileLocation(){
	return "./res/2DVertexShader.txt";
}

std::string Shader2D::fragmentfileLocation(){
	return "./res/2DFragmentShader.txt";
}

void Shader2D::loadTransform(glm::mat4 &matrix){
	loadMatrix(location_transform, matrix);
}


void Shader2D::loadTextures()
{
	loadInt(location_textureSampler, 0);
}


Shader2D::~Shader2D()
{
	ShaderProgram::~ShaderProgram();
}
