#include "Loader.h"
#include <iostream>
#include "ModelTexture.h"


Loader::Loader()
{

}

RawModel Loader::loadToVao(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices){
	GLuint vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	
	glBindVertexArray(0);
	return RawModel(vaoID, indices.size());
}

RawModel Loader::loadToVao(std::vector<float> positions, int dimensions)
{
	GLuint vaoID = createVAO();
	storeDataInAttributeList(0, dimensions, positions);
	glBindVertexArray(0);
	return RawModel(vaoID, positions.size() / dimensions);
}




void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> data){
	GLuint vboID = NULL;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(attributeNumber);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}



GLuint Loader::loadTexture(std::string fileName)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	GLuint texID;
	replacepng(fileName);
	if (!exists_test(fileName)){
		lodepng::load_file(png, "./res/white.png");
		unsigned error = lodepng::decode(image, width, height, png);

		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << " File: " << fileName << std::endl;

		/*int width, height, numComponents;
		unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

		if (data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl; */

		//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
		
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //GL_LINEAR_MIPMAP_NEAREST
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{	//load and decode
		lodepng::load_file(png, fileName);
		unsigned error = lodepng::decode(image, width, height, png);

		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << " File: " << fileName << std::endl;

		/*int width, height, numComponents;
		unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

		if (data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl; */

		//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);



		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
		//stbi_image_free(data);

		textures.push_back(texID);
		
	}
	return texID;
}

 RawImageData Loader::loadRawImageData(std::string fileName)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//load and decode
	lodepng::load_file(png, fileName);
	unsigned error = lodepng::decode(image, width, height, png);

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << " File: " << fileName << std::endl;


	return RawImageData(png, image, width, height);
}

std::vector<float> Loader::LoadHeightMap(std::string filename){
	std::vector<float> tmp;
	 SDL_Surface* img = SDL_LoadBMP(filename.c_str());
	 if (!img){
		 std::cerr << "Image is not loaded: " + filename + " at LoadBMP function!  \n SDL ERROR: " + SDL_GetError() + "\n";
		 return tmp;
	 }
	 
	 int size = img->h * img->h;
	 for (int i = 0; i < size; i++){
		Uint32 pixel = ((Uint32*)img->pixels)[i*img->pitch / 4 + i];
		Uint8 r, g, b;
		SDL_GetRGB(pixel, img->format, &r, &g, &b);
		tmp.push_back((float)r/255.0f);
	 }
	 return tmp;
 }


TextureData Loader::decodeTexture(std::string fileName)
{
	unsigned int width = NULL;
	unsigned int height = NULL;
	std::vector<unsigned char> png;
	std::vector<unsigned char> buffer;
	//load and decode
	lodepng::load_file(png, fileName);
	unsigned error = lodepng::decode(buffer, width, height, png);

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	TextureData data(buffer, width, height);
	return data;

}

GLuint Loader::loadCubeMap(std::vector<std::string> textureFiles)
{
	GLuint texID = NULL;
	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	for (int i = 0; i < textureFiles.size(); i++){
		TextureData data = decodeTexture(textureFiles.at(i));
		/*Right, left, top, bottom, back, front (REMEMBER ORDER WHEN IMPLEMENTING TEXTURE FILE LOCATIONS) */
		std::vector<unsigned char> vec = data.getBuffer();
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data.getWidth(), data.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &vec[0]);
	}
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	textures.push_back(texID);
	return texID;
}



std::vector<ModelData> Loader::loadCollada(std::string fileName)
{
	if (!meshes.empty()){
		meshes.clear();
	}
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_GenSmoothNormals | aiProcessPreset_TargetRealtime_Quality | aiProcess_Triangulate | aiProcess_FlipUVs); //aiProcess_GenSmoothNormals | aiProcess_Triangulate); //aiProcess_flipUVs

	if (!scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		std::cerr << "The file couldn't be opened" << fileName;
		std::cerr << importer.GetErrorString();
	}

	recursiveProcess(scene->mRootNode, scene);

	return meshes;
}



void Loader::recursiveProcess(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];	
		meshes.push_back(processMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++){
		recursiveProcess(node->mChildren[i], scene);
	}

}

ModelData Loader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<int> indices;
	std::vector<float> texcoords;
	std::vector<float> tangents;
	//get material color (NOT IN USE)
	aiColor4D col;
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &col);
	glm::vec3 defaultColor(col.r, col.g, col.b);

	//std::cout << 1;
	for (int i = 0; i < mesh->mNumVertices; i++){
		//positions

		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		//normals
		normals.push_back(mesh->mNormals[i].x);
		normals.push_back(mesh->mNormals[i].y);
		normals.push_back(mesh->mNormals[i].z);



		//Get tangents (NOT IN USE)
		if (mesh->mTangents){
			tangents.push_back(mesh->mTangents[i].x);
			tangents.push_back(mesh->mTangents[i].y);
			tangents.push_back(mesh->mTangents[i].z);
		}


		if (mesh->mTextureCoords[0]){
			texcoords.push_back(mesh->mTextureCoords[0][i].x);
			texcoords.push_back(mesh->mTextureCoords[0][i].y);
		}
		else {
			texcoords.push_back(0.0);
			texcoords.push_back(0.0);
		}
	}


	for (int i = 0; i < mesh->mNumFaces; i++){
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++){
			indices.push_back(face.mIndices[j]);
		}
	}

	ModelTexture temp;
	for (int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++){
		aiString str;
		std::string line = "./res/";
		
		mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
		line.append(str.C_Str());
		temp.setTexture(loadTexture(line));
		
	}

	return ModelData(vertices, texcoords, normals, indices, temp);

}

void Loader::bindIndicesBuffer(std::vector<int> indices){
	GLuint vboID = NULL;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}


Loader::~Loader()
{

	for (unsigned int i = 0; i < vaos.size(); i++){
		glDeleteVertexArrays(1, &vaos.at(i));
	}

	for (unsigned int i = 0; i < vbos.size(); i++){
		glDeleteBuffers(1, &vbos.at(i));
	}

	for (unsigned int i = 0; i < textures.size(); i++){
		glDeleteBuffers(1, &textures.at(i));
	}
	for (unsigned int i = 0; i < fbos.size(); i++){
		glDeleteFramebuffers(1, &fbos.at(i));
	}


}

GLuint Loader::createVAO(){
	GLuint vaoID = NULL;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}


