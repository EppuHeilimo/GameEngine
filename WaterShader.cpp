#include "WaterShader.h"


WaterShader::WaterShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void WaterShader::getAllUniformLocations(){

	location_transform = getUniformLocation("transform");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_projectionMatrix = getUniformLocation("projection");
	location_reflectionTexture = getUniformLocation("reflectionTexture");
	location_refractionTexture = getUniformLocation("refractionTexture");
	location_dudv = getUniformLocation("dudv");
	location_move = getUniformLocation("moveFactor");
	location_cameraPos = getUniformLocation("cameraPos");
	location_normalMap = getUniformLocation("normalMap");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_depthMap = getUniformLocation("depthMap");
}

void WaterShader::bindAttributes(){
	bindAttribute(0, "position");
}

std::string WaterShader::vertexfileLocation(){
	return "./res/waterVertex.txt";
}

std::string WaterShader::fragmentfileLocation(){
	return "./res/waterFragment.txt";
}

void WaterShader::loadMove(float f){
	loadFloat(location_move, f);
}

void WaterShader::loadLights(std::vector<Light*> lights)
{
	loadVector3f(location_lightPosition, lights[0]->getPosition());
	loadVector3f(location_lightColor, lights[0]->getColor()); 
}


void WaterShader::loadTransform(glm::mat4 &matrix){
	loadMatrix(location_transform, matrix);
}

void WaterShader::loadProjection(glm::mat4& projection)
{
	loadMatrix(location_projectionMatrix, projection);
}

void WaterShader::loadViewMatrix(Camera &camera)
{
	//MyMaths math;
	glm::mat4 viewMatrix = MyMaths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
	loadVector3f(location_cameraPos, camera.getPosition());
}


void WaterShader::loadTextures()
{
	loadInt(location_reflectionTexture, 0);
	loadInt(location_refractionTexture, 1);
	loadInt(location_dudv, 2);
	loadInt(location_normalMap, 3);
	loadInt(location_depthMap, 4);
}


WaterShader::~WaterShader()
{
	ShaderProgram::~ShaderProgram();
}