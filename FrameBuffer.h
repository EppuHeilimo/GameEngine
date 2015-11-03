#pragma once
#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include "GuiTexture.h"
#include "DisplayManager.h"
#include <iostream>
class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(int width, int height);
	~FrameBuffer();
	void createFrameBuffer(int width, int height);
	void createTextureAttachment();
	void createDepthTextureAttachment();
	void createDepthBufferAttachment();
	void bindFrameBuffer();
	void unbindFrameBuffer();
	inline int getFbo() { return fbo; }
	inline int getColorTexture() { return colorTexture; }
	inline int getDepthTexture() { return depthTexture; }
	inline int getDepthBuffer() { return depthBuffer; }
	void createWaterDepthTextureAttachment();
private:
	int width;
	int height;
	GLuint fbo;
	GLuint colorTexture;
	GLuint depthTexture;
	GLuint depthBuffer;
};

