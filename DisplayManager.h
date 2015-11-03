#pragma once
#include <string>
#include <SDL\SDL.h>
#include <ctime>
#include <queue>
class DisplayManager
{
public:
	DisplayManager(int width, int height, const std::string& title);
	~DisplayManager();
	void update();
	static int getWidth();
	static int getHeight();
	bool hasClosed();
	float getFrameTime();
	SDL_Window* getWindowHandle(){ return window; }
private:
	float delta;
	long lastFrameTime;
	const static int width = 1440;
	const static int height = 900;
	SDL_Window* window;
	SDL_GLContext context;
	bool isClosed;
	float fpsCap = 16.6666f;//32.0; //in millseconds
	int framecount = 0;
	float time1 = 0;
};

