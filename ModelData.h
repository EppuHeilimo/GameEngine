#pragma once
#include <glm\glm.hpp>
#include "Vertex.h"
#include <vector>
#include "ModelTexture.h"
class ModelData
{
public:
	ModelData(std::vector<float> vertices,
	std::vector<float> texCoords,
	std::vector<float> normals,
	std::vector<int> indices,
	ModelTexture texture);

	ModelData(std::vector<glm::vec3> vertices,
		std::vector<glm::vec2> texCoords,
		std::vector<glm::vec3> normals,
		std::vector<unsigned int> indices);
	
	std::vector<float> getVertices(){ return vertices; }
	std::vector<float> getTexCoords(){ return texCoords; }
	std::vector<float> getNormals(){ return normals; }
	std::vector<int> getIndices(){ return indices; }
	ModelTexture getTextures(){ return texture; }
	~ModelData();
	ModelData();
private:
	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	ModelTexture texture;
};

