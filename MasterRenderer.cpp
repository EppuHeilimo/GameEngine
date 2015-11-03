#include "MasterRenderer.h"


MasterRenderer::MasterRenderer(Loader &loader, Game &game)
{
	this->game = &game;
	this->loader = &loader;
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glCullFace(GL_BACK);
	glEnable(GL_CLIP_DISTANCE0);
	//glFinish();
	shader = new StaticShader;
	createProjectionMatrix();
	terrainRenderer		= new TerrainRenderer(projectionMatrix);
	skyboxRenderer		= new SkyBoxRenderer(loader, projectionMatrix);
	render2D			= new Renderer2D(loader);
	waterRenderer		= new WaterRenderer(loader, projectionMatrix);
	shader->loadProjectionMatrix(projectionMatrix);
}


MasterRenderer::~MasterRenderer()
{
	delete terrainRenderer;
	delete skyboxRenderer;
	delete shader;
	delete render2D;
}

void MasterRenderer::createProjectionMatrix()
{
	
	float aspectRatio = (float)DisplayManager::getWidth() / (float)DisplayManager::getHeight();
	float y_scale = (float)((1.0f / tan((FOV / 2.0f) * 3.14159265 / 180.0)) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustrum_length = FAR_PLANE - NEAR_PLANE;

	projectionMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);

}

void MasterRenderer::prepare(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(RED, GREEN, BLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat4 MasterRenderer::transformation(LocalPlayer &player)
{
	return MyMaths::createTransformationmatrix(player.getPosition(), player.getRotation().x, player.getRotation().y, player.getRotation().z, player.getScale());
}

glm::mat4 MasterRenderer::transformation(EntityInterface *entity)
{
	return MyMaths::createTransformationmatrix(entity->getPosition(), entity->getRotation().x, entity->getRotation().y, entity->getRotation().z, entity->getScale());
}

void MasterRenderer::renderTerrain(std::vector<Terrain*> &terrain){
	terrainRenderer->render(terrain);
}

glm::mat4 MasterRenderer::shadowPrepare(Light &light, LocalPlayer &player){
	glm::mat4 lightProjection = glm::ortho(-250.0f, 250.0f, -250.0f, 250.0f, NEAR_PLANE, FAR_PLANE);
	light.setPosition(glm::vec3(player.getPosition().x - 250.0f, player.getPosition().y + 250.0f, player.getPosition().z + 250.0f));
	glm::mat4 lightView = glm::lookAt(light.getPosition(), player.getPosition(), glm::vec3(0.0f, -1.0f, 0.0f));
	return lightProjection * lightView;
}

void MasterRenderer::renderTerrainShadows(std::vector<Terrain*> &terrain, Light &light){
	terrainRenderer->renderShadows(terrain, light);
}

void MasterRenderer::renderShadows(LocalPlayer &player, std::vector<std::map<std::string, std::vector<EntityInterface*>>>& entities, std::vector<Light*> &lights, std::vector<Terrain*> &terrain, std::vector<int>& entityNumbers){
	for (int j = 0; j < lights.size(); j++) {
		glm::mat4 lightSpaceMatrix = shadowPrepare(*lights[j], player);
		lights[j]->getShadowShader()->start();
		lights[j]->getShadowShader()->loadLightSpace(lightSpaceMatrix);
		lights[j]->getFrameBuffer()->bindFrameBuffer();
		glClear(GL_DEPTH_BUFFER_BIT);


		TexturedModel *modelPlayer = player.getTexturedModel();
		lights[j]->getShadowShader()->loadTransform(transformation(player));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		for (int mesh = 0; mesh < modelPlayer->getRawModel().size(); mesh++){
			glBindVertexArray(modelPlayer->getRawModel()[mesh].getVaoID());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, modelPlayer->getTexture()->at(mesh).getTextureID());
			glDrawElements(GL_TRIANGLES, modelPlayer->getRawModel()[mesh].getVertexCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	
		for (int i = 0; i < entityNumbers.size(); i++){
			std::map<std::string, std::vector<EntityInterface*>>::iterator it = entities.at(entityNumbers.at(i)).begin();
			std::map<std::string, std::vector<EntityInterface*>>::iterator itend = entities.at(entityNumbers.at(i)).end();
			for (; it != itend; ++it){
				if (!it->second.empty()){
					TexturedModel *model = it->second.front()->getTexturedModel();
					glEnableVertexAttribArray(0);
					glEnableVertexAttribArray(1);
					glEnableVertexAttribArray(2);
					for (int mesh = 0; mesh < model->getRawModel().size(); mesh++){
						RawModel rawmodel = model->getRawModel()[mesh];
						glBindVertexArray(rawmodel.getVaoID());
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, model->getTexture()->at(mesh).getTextureID());//.getTextureID());
						int size = it->second.size(); //extract size for optimization, otherwise we call size() for every single object
						std::vector<EntityInterface*> temp = it->second;
						for (int i = 0; i < size; i++){
							lights[j]->getShadowShader()->loadTransform(temp.at(i)->getTransform());
							glDrawElements(GL_TRIANGLES, rawmodel.getVertexCount(), GL_UNSIGNED_INT, 0);
						}
						glBindVertexArray(0);
					}
					glDisableVertexAttribArray(0);
					glDisableVertexAttribArray(1);
					glDisableVertexAttribArray(2);

				}
			}
		}

		shader->stop();

		lights[j]->getFrameBuffer()->unbindFrameBuffer();

	}
	
	
}

void MasterRenderer::render(LocalPlayer &player, std::vector<std::map<std::string, std::vector<EntityInterface*>>> &entities, Camera &camera,
	std::vector<Light*> &lights, std::vector<Terrain*> &terrain, std::vector<GuiTexture> &guis, std::vector<Water*> &waters, std::vector<int>& entityNumbers, ParticleSystem& particle){
	
	glCullFace(GL_FRONT);
	renderShadows(player, entities, lights, terrain, entityNumbers);
	glCullFace(GL_BACK);
	glm::mat4 lightSpaceMatrix = shadowPrepare(*lights[0], player);

	float dist = 2 * (camera.getPosition().y - waters[0]->getHeight());
	for (int i = 0; i < 3; i++){
		if (i == 0){
			waters[0]->getRefraction()->bindFrameBuffer();
		}
		else if (i == 1){
			waters[0]->getReflection()->bindFrameBuffer();
			
			camera.increasePosition(0.0f, -dist, 0.0f);
			camera.invertCamera();
		}
		prepare();
		skyboxRenderer->render(camera, RED, GREEN, BLUE);

		terrainRenderer->getShader().start();
		if (i == 0){
			terrainRenderer->getShader().loadClipPlane(glm::vec4(0.0f, -1.0f, 0.0f, waters[0]->getHeight()));
		}
		else if (i == 1)
			terrainRenderer->getShader().loadClipPlane(glm::vec4(0.0f, 1.0f, 0.0f, -waters[0]->getHeight() + 1.5f));
		else
			terrainRenderer->getShader().loadClipPlane(glm::vec4(0.0f, -1.0f, 0.0, 100000.0f));
		terrainRenderer->getShader().loadSkyColor(RED, GREEN, BLUE);
		terrainRenderer->getShader().loadLightSpace(lightSpaceMatrix);
		terrainRenderer->getShader().loadLights(lights);
		terrainRenderer->getShader().loadViewMatrix(camera);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, lights[0]->getFrameBuffer()->getDepthTexture());
		terrainRenderer->getShader().loadShadowMap();
		renderTerrain(terrain);
		terrainRenderer->getShader().stop();


		shader->start();

		if (i == 0)
			shader->loadClipPlane(glm::vec4(0.0f, 1.0f, 0.0f, -waters[0]->getHeight()));
		else if (i == 1)
			shader->loadClipPlane(glm::vec4(0.0f, -1.0f, 0.0f, waters[0]->getHeight() + 1.5f));
		else
			shader->loadClipPlane(glm::vec4(0.0, -1.0, 0.0, 100000));
	
		renderPlayer(player, camera, lights, lightSpaceMatrix);
		renderEntities(entities, lights, lightSpaceMatrix, entityNumbers);

		shader->stop();

		if ( i == 0){
			waters[0]->getRefraction()->unbindFrameBuffer();
		}
		else if (i == 1){
			waters[0]->getReflection()->unbindFrameBuffer();
			camera.increasePosition(0.0f, dist, 0.0f);
			camera.invertCamera();
		}
	}
	
	particle.RenderParticles(projectionMatrix, camera, game->getDelta());
	waterRenderer->render(waters, camera, lights);
	//game->getPhysics()->debug->draw(glm::vec3(0, 0, 0), camera, projectionMatrix);


}
void MasterRenderer::renderPlayer(LocalPlayer& player, Camera& cam, std::vector<Light*>& lights, glm::mat4& lightSpaceMatrix){
	TexturedModel *model = player.getTexturedModel();
	shader->loadSkyColor(RED, GREEN, BLUE);
	shader->loadTransform(transformation(player));
	shader->loadViewMatrix(cam);
	shader->loadProjectionMatrix(projectionMatrix);
	shader->loadLights(lights);
	shader->loadLightSpace(lightSpaceMatrix);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lights[0]->getFrameBuffer()->getDepthTexture());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	for (int mesh = 0; mesh < model->getRawModel().size(); mesh++){
		glBindVertexArray(model->getRawModel()[mesh].getVaoID());
		shader->loadShine(model->getTexture()->at(mesh).getShineDamper(), player.getTexturedModel()->getTexture()->at(mesh).getReflectivity());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, model->getTexture()->at(mesh).getTextureID());//.getTextureID());
		shader->loadTextures();
		shader->loadShadowMap();
		glDrawElements(GL_TRIANGLES, model->getRawModel()[mesh].getVertexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void MasterRenderer::renderEntities(std::vector<std::map<std::string, std::vector<EntityInterface*>>> &entities, std::vector<Light*>& lights, glm::mat4& lightSpaceMatrix, std::vector<int>& entityNumbers){
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 0; i < entityNumbers.size(); i++){
		std::map<std::string, std::vector<EntityInterface*>>::iterator it = entities.at(entityNumbers.at(i)).begin();
		std::map<std::string, std::vector<EntityInterface*>>::iterator itend = entities.at(entityNumbers.at(i)).end();
		for (; it != itend; ++it){
			if (it->second.empty()) {
				continue;
			}			
			TexturedModel *model = it->second.front()->getTexturedModel();
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			for (int mesh = 0; mesh < model->getRawModel().size(); mesh++){
				RawModel rawmodel = model->getRawModel()[mesh];
				glBindVertexArray(rawmodel.getVaoID());
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, lights[0]->getFrameBuffer()->getDepthTexture());
				shader->loadShadowMap();

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, model->getTexture()->at(mesh).getTextureID());
					
				shader->loadTextures();
				int size = it->second.size(); //extract size for optimization, otherwise we call size() for every single object
				std::vector<EntityInterface*> temp = it->second;
				for (int i = 0; i < size; i++){
					shader->loadTransform(transformation(it->second.at(i)));//temp.at(i)->getTransform());
					//shader->loadTransform(transformation(temp.at(i)));
					glDrawElements(GL_TRIANGLES, rawmodel.getVertexCount(), GL_UNSIGNED_INT, 0);
				}
				glBindVertexArray(0);

			}
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);								
		}
	}
	glDisable(GL_ALPHA);
	glEnable(GL_CULL_FACE);
}

