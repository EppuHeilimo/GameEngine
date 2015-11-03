
#pragma once
#include <glm\glm.hpp>
#include "TexturedModel.h"
class EntityInterface
{
public:
	EntityInterface(glm::vec3, glm::vec3 rotation, glm::vec3, TexturedModel *model, int terrainNumber);
	EntityInterface(const EntityInterface &entity);
	EntityInterface();
	~EntityInterface();
	void setEntityYposition(float y) { position.y = y; }
	void increasePosition(float dx, float dy, float dz);
	inline void setPosition(float x, float y, float z) { position = glm::vec3(x, y, z); }
	void increaseRotation(float rx, float ry, float rz);
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getScale() { return scale; }
	inline int getTerrainNumber(){ return terrainNumber; }
	glm::mat4& getTransform(){ return transformation; }
	TexturedModel* getTexturedModel() { return model; }
private:
	int terrainNumber;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 transformation;
	int textureIndex = 0;
	TexturedModel *model = new TexturedModel();

};

