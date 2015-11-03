#include "ModelData.h"


ModelData::ModelData(
	std::vector<float> vertices,
	std::vector<float> texCoords,
	std::vector<float> normals,
	std::vector<int> indices, 
	ModelTexture texture)
{
	this->vertices = vertices;
	this->texCoords = texCoords;
	this->normals = normals;
	this->indices = indices;
	this->texture = texture;
}

ModelData::ModelData(
	std::vector<glm::vec3> vertices,
	std::vector<glm::vec2> texCoords,
	std::vector<glm::vec3> normals,
	std::vector<unsigned int> indices)
{

	for (int i = 0; vertices.size(); i++){
		this->vertices.push_back(vertices[i].x);
		this->vertices.push_back(vertices[i].y);
		this->vertices.push_back(vertices[i].z);
	}

	for (int i = 0; texCoords.size(); i++){
		this->texCoords.push_back(texCoords[i].x);
		this->texCoords.push_back(texCoords[i].y);
	}

	for (int i = 0; normals.size(); i++){
		this->normals.push_back(normals[i].x);
		this->normals.push_back(normals[i].y);
		this->normals.push_back(normals[i].z);
	}

	for (int i = 0; indices.size(); i++){
		this->indices.push_back(indices[i]);
	}



}




ModelData::ModelData()
{

}

ModelData::~ModelData()
{
}
