#include "ParticleRenderer.h"


ParticleRenderer::ParticleRenderer()
{
	shader = new ParticleShader();
}


ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::setMatrices(glm::mat4& a_matProjection, Camera cam)
{
	matProjection = a_matProjection;
	matView = MyMaths::createViewMatrix(cam);
	glm::vec3 vUpVector(0.0, -1.0, 0.0);
	glm::vec3 vEye(0.0, 0.0, 0.0);
	glm::vec3 vView = vView - vEye;
	vView = glm::normalize(vView);
	vQuad1 = glm::cross(vView, vUpVector);

	vQuad1 = glm::normalize(vQuad1);
	vQuad2 = glm::cross(vView, vQuad1);
	vQuad2 = glm::normalize(vQuad2);
}

void ParticleRenderer::render(GLuint uiVAO[2], int iCurReadBuffer, int iNumParticles){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(0);

	glDisable(GL_RASTERIZER_DISCARD);
	shader->start();
	shader->loadProjection(matProjection);
	shader->loadView(matView);
	shader->loadQuad1(vQuad1);
	shader->loadQuad2(vQuad2);
	shader->loadTextures();

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glDisableVertexAttribArray(1); // Disable velocity, because we don't need it for rendering

	glDrawArrays(GL_POINTS, 0, iNumParticles);

	glDepthMask(1);
	glDisable(GL_BLEND);
}
