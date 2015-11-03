#include "Terrain.h"


Terrain::Terrain(float gridX, float gridZ, float max_height, Loader &loader, TerrainTexturePack *texturePack,ModelTexture *blendMap, std::string heightMapFile)
{
	this->blendMap = blendMap;
	this->max_height = max_height;
	this->x = gridX * size;
	this->z = gridZ * size;
	this->texturePack = texturePack;
	transform = MyMaths::createTransformationmatrix(glm::vec3(x, 0, z), 0, 0, 0, glm::vec3(1, 1, 1));
	model = generateTerrain(loader, heightMapFile);
}


Terrain::~Terrain()
{

}

float Terrain::getHeightOfTerrain(float worldX, float worldZ){
	float terrainX = worldX - this->x;
	float terrainZ = worldZ - this->z;
	float gridSquareSize = size / ((float)heights.size() - 1);
	int gridX = (int)floor(terrainX / gridSquareSize);
	int gridZ = (int)floor(terrainZ / gridSquareSize);
	if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0) {
		return 0;
	}
	float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
	float answer;
	if (xCoord <= (1 - zCoord)){
		answer = MyMaths::barryCentric(glm::vec3(0, heights[gridX][gridZ], 0), glm::vec3(1,
			heights[gridX + 1][gridZ], 0), glm::vec3(0,
			heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	else {
		answer = MyMaths::barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(1,
			heights[gridX + 1][gridZ + 1], 1),  glm::vec3(0,
			heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	return answer;
}



float Terrain::getHeight(int x, int y){
	if (x < 0 || x >= vertex_count || y < 0 || y >= vertex_count){
		return 0;
	}
	float height = nHeightMap[y * vertex_count + x] * max_height;
	return height;
}

void Terrain::processHeightMap(RawImageData &heightMap){
	int imagesize = heightMap.getDecodedImage().size() / 4;
	std::vector<unsigned char> tmp = heightMap.getDecodedImage();
	for (int i = 0; i < imagesize; i++) {
		nHeightMap.push_back(tmp[i * 4] / 255.0f);
	}
}

RawModel Terrain::generateTerrain(Loader &loader, std::string heightMapFile){
	RawImageData heightMap = loader.loadRawImageData(heightMapFile);

	processHeightMap(heightMap); 

	vertex_count = heightMap.getHeight();
	heights.resize(vertex_count, std::vector<float>(vertex_count, 0));
	
	std::vector<float> normals;
	std::vector<float> textureCoords;
	std::vector<int> indices;
	for (int i = 0; i < vertex_count; i++) {
		for (int j = 0; j < vertex_count; j++){
			vertices.push_back((float)j / ((float)vertex_count - 1) * size);
			float height = getHeight(j, i);
			heights[j][i] = height;
			vertices.push_back( height );
			vertices.push_back((float)i / ((float)vertex_count - 1) * size);
			glm::vec3 normal = calculateNormal(j, i);
			normals.push_back( normal.x );
			normals.push_back( normal.y );
			normals.push_back( normal.z );
			textureCoords.push_back((float)j / ((float)vertex_count - 1));
			textureCoords.push_back((float)i / ((float)vertex_count - 1));
		}
	}

	for (int gz = 0; gz < vertex_count - 1; gz++){
		for (int gx = 0; gx < vertex_count - 1; gx++){
			int topLeft = (gz*vertex_count) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*vertex_count) + gx;
			int bottomRight = bottomLeft + 1;
			indices.push_back( topLeft );
			indices.push_back( bottomLeft );
			indices.push_back( topRight );
			indices.push_back( topRight );
			indices.push_back( bottomLeft );
			indices.push_back( bottomRight );
		}
	}

	return loader.loadToVao(vertices, textureCoords, normals, indices);
}


glm::vec3 Terrain::calculateNormal(int x, int z){
	float heightL = getHeight(x - 1, z);
	float heightR = getHeight(x + 1, z);
	float heightD = getHeight(x, z - 1);
	float heightU = getHeight(x, z + 1);
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	glm::normalize(normal);
	return normal;

}