#include "TextureData.h"



TextureData::TextureData(std::vector<unsigned char> buffer, int width, int height)
{
	this->buffer = buffer;
	this->width = width;
	this->height = height;
}

TextureData::~TextureData()
{

}
