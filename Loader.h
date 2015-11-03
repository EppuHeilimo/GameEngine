#include <vector>
#include <glew\GL\glew.h>
#include "RawModel.h"
#include "lodepng.h"
#include "stbimage.h"
#include "ModelData.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "TextureData.h"
#include <vector>
#include <glm/glm.hpp>
#include "RawImageData.h"
#include "SDL\SDL.h"
#include <fstream>
#include <iostream>

#pragma once
class Loader
{
public:
	Loader();
	~Loader();
	RawModel loadToVao(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices);
	RawModel loadToVao(std::vector<float> positions, int dimensions);
	GLuint createVAO();
	GLuint loadTexture(std::string fileName);
	TextureData decodeTexture(std::string fileName);
	std::vector<ModelData> loadCollada(std::string fileName);
	GLuint loadCubeMap(std::vector<std::string> textureFiles);
	RawImageData loadRawImageData(std::string fileName);
	std::vector<float> LoadHeightMap(std::string filename);
	GLuint createFrameBuffer();
	GLuint createDepthMap(GLuint fbo);
private:
	void bindIndicesBuffer(std::vector<int>);
	void storeDataInAttributeList(int, int, std::vector<float>);
	std::vector<GLuint> vaos;
	std::vector<GLuint> fbos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
	void recursiveProcess(aiNode* node, const aiScene* scene);
	ModelData processMesh(aiMesh* mesh, const aiScene* scene);
	inline bool exists_test(const std::string& name) {
		if (FILE *file = fopen(name.c_str(), "r")) {
			fclose(file);
			return true;
		}
		else {
			return false;
		}
	}
	inline std::string replacepng(std::string& file){
		std::string temp;
		if (file.find(".JPG") != std::string::npos)
			temp = file.replace(file.find(".JPG"), 4, ".png");
		else if (file.find(".jpg") != std::string::npos)
			temp = file.replace(file.find(".jpg"), 4, ".png");
		else if (file.find(".dds") != std::string::npos)
			temp = file.replace(file.find(".dds"), 4, ".png");
		std::cout << file << "\n";
		return temp;
	}
	std::vector<ModelTexture> texturesTemp;
	std::vector<ModelData> meshes;
	
	
};

