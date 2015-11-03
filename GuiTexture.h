#pragma once
#include <glm\glm.hpp>
class GuiTexture
{
public:
	GuiTexture(int tex, glm::vec2 position, glm::vec2 scale);
	~GuiTexture();
	GuiTexture() {};
	int getTexture() { return texture; }
	glm::vec2 getPosition() { return position; }
	glm::vec2 getScale() { return scale; }
private:
	glm::vec2 position;
	glm::vec2 scale;
	int texture;
};

