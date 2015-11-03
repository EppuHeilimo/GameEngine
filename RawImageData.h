#pragma once
#include <vector>
class RawImageData
{
public:
	RawImageData(std::vector<unsigned char> png, std::vector<unsigned char> image, unsigned width, unsigned height);
	~RawImageData();
	std::vector<unsigned char> getPng() { return png; }
	std::vector<unsigned char> getDecodedImage() { return image; }
	unsigned getHeight(){ return height; }
	unsigned getWidth(){ return width; }
private:
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	unsigned width, height;
};

