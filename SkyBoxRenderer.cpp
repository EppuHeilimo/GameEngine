#include "SkyBoxRenderer.h"

SkyBoxRenderer::SkyBoxRenderer(Loader &loader, glm::mat4 &projection)
{
	/*Right, left, top, bottom, back, front (REMEMBER ORDER WHEN IMPLEMENTING TEXTURE FILE LOCATIONS) */
//	TEXTURE_FILES.push_back("./res/plain_sky_right.png");
//	TEXTURE_FILES.push_back("./res/plain_sky_left.png");
//	TEXTURE_FILES.push_back("./res/plain_sky_top.png");
//	TEXTURE_FILES.push_back("./res/plain_sky_back.png");
//	TEXTURE_FILES.push_back("./res/plain_sky_front.png");
//	TEXTURE_FILES.push_back("./res/plain_sky_back.png");
	TEXTURE_FILES.push_back("./res/eveningleft.png");
	TEXTURE_FILES.push_back("./res/eveningright.png");
	TEXTURE_FILES.push_back("./res/eveningup.png");
	TEXTURE_FILES.push_back("./res/eveningdown.png");
	TEXTURE_FILES.push_back("./res/eveningfront.png");
	TEXTURE_FILES.push_back("./res/eveningback.png");

	vertices = {
		-SIZE, SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,

		-SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, -SIZE, SIZE,

		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,

		-SIZE, -SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE,

		-SIZE, SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE, -SIZE,

		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE };

	cube = loader.loadToVao(vertices, 3);
	texture = loader.loadCubeMap(TEXTURE_FILES);
	shader.start();
	shader.loadProjectionMatrix(projection);
	shader.stop();
}



SkyBoxRenderer::~SkyBoxRenderer()
{
}

void SkyBoxRenderer::render(Camera &camera, float RED, float GREEN, float BLUE)
{

	shader.start();
	shader.loadViewMatrix(camera); 
	glBindVertexArray(cube.getVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	shader.loadTextures();
	shader.loadSkyColor(RED, GREEN, BLUE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.stop();

}
