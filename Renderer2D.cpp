#include "Renderer2D.h"


Renderer2D::Renderer2D(Loader &loader)
{
	shader = new Shader2D();
	std::vector<float> positions;
	positions = { -0.3f, 0.3f, -0.3f, -0.3f, 0.3f, 0.3f, 0.3f, -0.3f };
	quad = loader.loadToVao(positions, 2);
}


Renderer2D::~Renderer2D()
{
	delete shader;
}

void Renderer2D::render(std::vector<GuiTexture> guis){
	shader->start();
	glBindVertexArray(quad.getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture gui : guis){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui.getTexture());
		glm::mat4 matrix = MyMaths::createTransformationMatrix(gui.getPosition(), gui.getScale());
		shader->loadTransform(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}