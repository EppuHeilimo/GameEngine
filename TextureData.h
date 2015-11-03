#pragma once
#include <vector>
class TextureData
{
public:
	TextureData(std::vector<unsigned char> buffer, int width, int height);
	~TextureData();
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	std::vector<unsigned char> getBuffer(){ return buffer; }
private:
	int width;
	int height;
	std::vector<unsigned char> buffer;
};

