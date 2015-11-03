#include "ParticleShader.h"


ParticleShader::ParticleShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation(), geometryfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void ParticleShader::getAllUniformLocations(){

}

void ParticleShader::bindAttributes(){
	bindAttribute(0, "position");
}

std::string ParticleShader::vertexfileLocation(){
	return "./res/particleVertex.txt";
}

std::string ParticleShader::fragmentfileLocation(){
	return "./res/particleFragment.txt";
}

std::string ParticleShader::geometryfileLocation(){
	return "./res/particleGeometry.txt";
}

void ParticleShader::loadProjection(glm::mat4& projection)
{
	loadMatrix(location_projection, projection);
}

void ParticleShader::loadView(glm::mat4 &view){
	loadMatrix(location_view, view);
}

void ParticleShader::loadQuad1(glm::vec3 &quad){
	loadVector3f(location_quad1, quad);
}

void ParticleShader::loadQuad2(glm::vec3 &quad){
	loadVector3f(location_quad2, quad);
}

void ParticleShader::loadTextures(){
	loadInt(location_gsampler, 0);
}



ParticleShader::~ParticleShader()
{
	ShaderProgram::~ShaderProgram();
}
