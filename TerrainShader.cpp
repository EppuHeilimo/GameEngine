#include "TerrainShader.h"


TerrainShader::TerrainShader() : ShaderProgram(vertexfileLocation(), fragmentfileLocation())
{
	bindAttributes();
	getAllUniformLocations();
}

void TerrainShader::getAllUniformLocations(){
	location_shadowMap = getUniformLocation("shadowMap");
	location_skyColor = getUniformLocation("skyColor");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_transform = getUniformLocation("transformationMatrix");
	location_projection = getUniformLocation("projectionMatrix");
	location_backgroundTexture = getUniformLocation("backgroundTexture");
	location_rTexture = getUniformLocation("rTexture");
	location_gTexture = getUniformLocation("gTexture");
	location_bTexture = getUniformLocation("bTexture");
	location_blendMap = getUniformLocation("blendMap");
	location_plane = getUniformLocation("plane");
	
	location_LightSpace = getUniformLocation("lightSpaceMatrix");
	for (int i = 0; i < max_lights; i++) {
		std::stringstream line;
		line << "lightPosition[" << i << "]";
		location_LightPosition[i] = getUniformLocation(line.str());
		line.str("");
		line.clear();
		line << "lightColor[" << i << "]";
		location_LightColor[i] = getUniformLocation(line.str());
		line.str("");
		line.clear();
		line << "attenuation[" << i << "]";
		location_Attenuation[i] = getUniformLocation(line.str());
		line.str("");
		line.clear();
	} 
}

void TerrainShader::loadLightSpace(glm::mat4& matrix){
	loadMatrix(location_LightSpace, matrix);
}

void TerrainShader::bindAttributes(){
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void TerrainShader::connectTextureUnits(){
	loadInt(location_rTexture, 0);
	loadInt(location_bTexture, 1);
	loadInt(location_gTexture, 2);
	loadInt(location_backgroundTexture, 3);
	loadInt(location_blendMap, 4);
}

void TerrainShader::loadClipPlane(glm::vec4& clipPlane){
	loadVector4f(location_plane, clipPlane);
}

void TerrainShader::loadShadowMap() {
	loadInt(location_shadowMap, 5);
}

void TerrainShader::loadTransform(glm::mat4 &matrix){
	loadMatrix(location_transform, matrix);
}

void TerrainShader::loadShine(float damper, float reflectivity){
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadLights(std::vector<Light*> lights) {
	for (int i = 0; i < lights.size(); i++){
		if (i < lights.size()){
			loadVector3f(location_LightPosition[i], lights[i]->getPosition());
			loadVector3f(location_LightColor[i], lights[i]->getColor());
			loadVector3f(location_Attenuation[i], lights[i]->getAttenuation());
		}
		else {
			loadVector3f(location_Attenuation[i], glm::vec3(1, 0, 0));
			loadVector3f(location_LightPosition[i], glm::vec3(0, 0, 0));
			loadVector3f(location_LightColor[i], glm::vec3(0, 0, 0));
		}
	}
}

std::string TerrainShader::vertexfileLocation(){
	return "./res/terrainVertex.txt";
}

std::string TerrainShader::fragmentfileLocation(){
	return "./res/terrainFragment.txt";
}

void TerrainShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r, g, b));
}

void TerrainShader::loadTextures()
{
	
}

void TerrainShader::loadViewMatrix(Camera &camera)
{
	glm::mat4 viewMatrix = MyMaths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4& projection)
{
	loadMatrix(location_projection, projection);
}

TerrainShader::~TerrainShader()
{
	ShaderProgram::~ShaderProgram();
}

