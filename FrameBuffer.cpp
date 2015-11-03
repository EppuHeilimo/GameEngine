#include "FrameBuffer.h"


FrameBuffer::FrameBuffer()
{

}

	FrameBuffer::FrameBuffer(int width, int height)
	{
		createFrameBuffer(width, height);
//		createDepthBufferAttachment();
//		createTextureAttachment();
		createDepthTextureAttachment();
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			std::cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\nFramebuffer failed to generate! 0\n";
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	}

	FrameBuffer::~FrameBuffer()
	{
		if (fbo != NULL)
			glDeleteFramebuffers(1, &fbo);
		if (colorTexture != NULL)
			glDeleteTextures(1, &colorTexture);
		if (depthBuffer != NULL)
			glDeleteRenderbuffers(1, &depthBuffer);
		if (depthTexture != NULL)
			glDeleteTextures(1, &depthTexture);
	}

	void FrameBuffer::createFrameBuffer(int width, int height){
		this->width = width;
		this->height = height;
		glGenFramebuffers(1, &fbo);
	
	}

	void FrameBuffer::createTextureAttachment(){
		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,  0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			std::cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\nFramebuffer failed to generate! 1\n";
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		

	}
	void FrameBuffer::createDepthTextureAttachment(){
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glDrawBuffer(GL_NONE);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			std::cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\nFramebuffer failed to generate! 2\n";
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	}

	void FrameBuffer::createWaterDepthTextureAttachment(){
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			std::cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\nFramebuffer failed to generate! 2\n";
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void FrameBuffer::createDepthBufferAttachment(){
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			std::cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\nFramebuffer failed to generate! 3\n";
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::bindFrameBuffer( ){
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glViewport(0, 0, width, height);
	}

	void FrameBuffer::unbindFrameBuffer(){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, DisplayManager::getWidth(), DisplayManager::getHeight());
	}
