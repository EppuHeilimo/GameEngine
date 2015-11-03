#include "WaterRenderer.h"


WaterRenderer::WaterRenderer(Loader &loader, glm::mat4 &projection)
{
	std::vector<float> vertices = {-1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1};
	quad = loader.loadToVao(vertices, 2);
	this->shader = new WaterShader();
	shader->start();
	shader->loadProjection(projection);
	shader->stop();
}


WaterRenderer::~WaterRenderer()
{
	delete shader;
}


void WaterRenderer::render(std::vector<Water*> &water, Camera &camera, std::vector<Light*> &lights){
	shader->start();
	shader->loadViewMatrix(camera);
	shader->loadLights(lights);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(quad.getVaoID());
	glEnableVertexAttribArray(0);
	for (int i = 0; i < water.size(); i++){
		water[i]->increaseMoveFactor();
		shader->loadMove(water[i]->getMove());
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, water[i]->getReflection()->getColorTexture());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, water[i]->getRefraction()->getColorTexture());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, water[i]->getDUDV());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, water[i]->getNormalMap());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, water[i]->getRefraction()->getDepthTexture());
		shader->loadTextures();
		shader->loadTransform(water[i]->getModelMatrix());
		glDrawArrays(GL_TRIANGLES, 0, quad.getVertexCount());

	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
	glDisable(GL_BLEND);
}
