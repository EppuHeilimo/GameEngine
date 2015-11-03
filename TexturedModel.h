#pragma once
#include "RawModel.h"
#include "modelTexture.h"
#include <string>
class TexturedModel
{
public:
	TexturedModel(RawModel model, ModelTexture texture, std::string modelName);
	TexturedModel(std::vector<RawModel> model, std::vector<ModelTexture> texture, std::string modelName);
	
	TexturedModel();
	~TexturedModel();
	std::vector<RawModel>& getRawModel(){
		return Model;
	}
	std::vector<ModelTexture>* getTexture(){
		return &textures;
	}
	std::string& getModelName(){
		return modelName;
	}

private:
	std::vector<ModelTexture> textures;
	std::vector<RawModel> Model;
	
	std::string modelName;
};

