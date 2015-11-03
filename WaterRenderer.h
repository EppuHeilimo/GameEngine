#pragma once
#include "RawModel.h"
#include "WaterShader.h"
#include "Loader.h"
#include <glm\glm.hpp>
#include "Water.h"
#include "Camera.h"
class WaterRenderer
{
public:
	WaterRenderer(Loader &loader, glm::mat4 &projection);
	~WaterRenderer();
	void render(std::vector<Water*> &water, Camera &camera, std::vector<Light*> &lights);
	WaterShader* getShader() { return shader; }
private:
	RawModel quad;
	WaterShader *shader;

};

