#include "StaticShader.h"


StaticShader::StaticShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}



void StaticShader::getAllUniformLocations(){
	location_skyColor = getUniformLocation("skyColor");
	location_transform = getUniformLocation("transform");

	location_viewMatrix = getUniformLocation("viewMatrix");
	location_projection = getUniformLocation("projection");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_LightSpace = getUniformLocation("lightSpaceMatrix");
	location_shadowMap = getUniformLocation("shadowMap");
	location_textureSampler = getUniformLocation("textureSampler");

}

void StaticShader::bindAttributes(){
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

std::string StaticShader::vertexfileLocation(){
	return "./res/vertexShader.txt";
}

std::string StaticShader::fragmentfileLocation(){
	return "./res/fragmentShader.txt";
}

void StaticShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r, g, b));
}

void StaticShader::loadTransform(glm::mat4 &matrix){
	loadMatrix(location_transform, matrix);
}


void StaticShader::loadShine(float damper, float reflectivity){
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);

}

void StaticShader::loadClipPlane(glm::vec4& clip){
	loadVector4f(location_plane, clip);
}

void StaticShader::loadLightSpace(glm::mat4& matrix){
	loadMatrix(location_LightSpace, matrix);
}


void StaticShader::loadTextures()
{
	loadInt(location_textureSampler, 1);
}

void StaticShader::loadShadowMap() {
	loadInt(location_shadowMap, 0);
}

void StaticShader::loadViewMatrix(Camera &camera)
{
	//MyMaths math;
	glm::mat4 viewMatrix = MyMaths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4& projection)
{
	loadMatrix(location_projection, projection);
}

void StaticShader::loadLights(std::vector<Light*> lights)
{
	loadVector3f(location_lightPosition, lights[0]->getPosition());
	loadVector3f(location_lightColor, lights[0]->getColor());
}

StaticShader::~StaticShader()
{
	ShaderProgram::~ShaderProgram();
}
