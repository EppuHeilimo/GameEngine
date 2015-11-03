#include "DisplayManager.h"
#include <glew/GL/glew.h>
#include <iostream> 
#include <Windows.h>


DisplayManager::DisplayManager(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->width, this->height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	if (status != GLEW_OK){
		std::cerr << "Glew failed to initialize!\n";
	}
	lastFrameTime = SDL_GetTicks();
	isClosed = false;
	delta = (float)SDL_GetTicks();
	
	
}


DisplayManager::~DisplayManager()
{
	SDL_GL_DeleteContext(window);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void DisplayManager::update(){

	SDL_GL_SwapWindow(window);
	
	long currentFrameTime = SDL_GetTicks();
	delta = (float) (currentFrameTime - lastFrameTime); //delta in millseconds
	/*
	if (fpsCap > delta) {
		SDL_Delay(fpsCap - delta);
	} */
	
	framecount++;
	time1 += delta;
	if (time1 > 1000){
		std::string title = std::to_string(framecount);
		SDL_SetWindowTitle(window, title.c_str());
		framecount = 0;
		time1 = 0;
	}
	lastFrameTime = currentFrameTime;
	
}

bool DisplayManager::hasClosed(){
	return isClosed;
}

float DisplayManager::getFrameTime()
{
	{ return delta / 1000.0f; }
}

int DisplayManager::getWidth(){
	return width;
}

int DisplayManager::getHeight(){
	return height;
}
