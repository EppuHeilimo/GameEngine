#include "RawImageData.h"


RawImageData::RawImageData(std::vector<unsigned char> png, std::vector<unsigned char> image, unsigned width, unsigned height)
{
	this->png = png;
	this->image = image;
	this->width = width;
	this->height = height;
}


RawImageData::~RawImageData()
{
}
