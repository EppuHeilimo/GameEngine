#include "GuiTexture.h"


GuiTexture::GuiTexture(int tex, glm::vec2 position, glm::vec2 scale)
{
	this->texture = tex;
	this->position = position;
	this->scale = scale;
}


GuiTexture::~GuiTexture()
{

}
