#pragma once
#include <glew\GL\glew.h>
#include "Shader2D.h"
#include "RawModel.h"
#include "Loader.h"
#include <vector>
#include "TexturedModel.h"
#include "MyMaths.h"
#include "GuiTexture.h"
class Renderer2D
{
public:
	Renderer2D(Loader &loader);
	~Renderer2D();
	void render(std::vector<GuiTexture> guis);
	Shader2D* getShader() { return shader; }
private:
	Shader2D *shader;
	RawModel quad;

};

