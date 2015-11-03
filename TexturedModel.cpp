#include "TexturedModel.h"


TexturedModel::TexturedModel(RawModel model, ModelTexture texture, std::string modelName)
{
	this->modelName = modelName;
	this->textures.push_back(texture);
	this->Model.push_back( model );
}

TexturedModel::TexturedModel(std::vector<RawModel> model, std::vector<ModelTexture> textures, std::string modelName)
{
	this->modelName = modelName;
	this->textures = textures;
	this->Model = model;
}



TexturedModel::TexturedModel()
{

}

TexturedModel::~TexturedModel()
{
}
