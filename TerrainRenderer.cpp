#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(glm::mat4 &projection)
{
	shader = new TerrainShader();
	this->shader->start();
	this->shader->loadProjectionMatrix(projection);
	this->shader->connectTextureUnits();
	this->shader->stop();
}


TerrainRenderer::~TerrainRenderer()
{
	delete shader;
}


TerrainShader& TerrainRenderer::getShader(){
	return *shader;
}

void TerrainRenderer::render(std::vector<Terrain*> &terrain){
	
	for (int i = 0; i < terrain.size(); i++){
		prepareTerrain(terrain[i]);
		prepareInstance(terrain[i]);
		glDrawElements(GL_TRIANGLES, terrain[i]->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
	
}

void TerrainRenderer::renderShadows(std::vector<Terrain*> &terrain, Light &light){
	for (int i = 0; i < terrain.size(); i++){
		glBindVertexArray(terrain[i]->getModel().getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		light.getShadowShader()->loadTransform(terrain[i]->getTransform());
		glDrawElements(GL_TRIANGLES, terrain[i]->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
}



void TerrainRenderer::prepareTerrain(Terrain *terrain){
	
	glBindVertexArray(terrain->getModel().getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindTextures(terrain);
	
}

void TerrainRenderer::prepareInstance(Terrain *terrain){
	shader->loadTransform(terrain->getTransform());
}

void TerrainRenderer::bindTextures(Terrain *terrain){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexture()->getTexturePack().r);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexture()->getTexturePack().g);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexture()->getTexturePack().b);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexture()->getBackground());
	//glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap()->getTextureID());
	//glGenerateMipmap(GL_TEXTURE_2D);

}
void TerrainRenderer::unbindTexturedModel(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}
