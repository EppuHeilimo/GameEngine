#pragma once
#include <SDL\SDL.h>
#include <map>
#include <iostream>
#include <glm\glm.hpp>
#include "DisplayManager.h"

class InputHandler
{
public:
	InputHandler(SDL_Window *window);
	~InputHandler();
	void poll();
	bool hasClosed() { return closed; }
	std::map<SDL_Keycode, bool>* getKeysPointer() { return keysPressed; }
	glm::vec2 getMouseDif() { return glm::vec2(dMouseX, dMouseY); }
	glm::vec2 getMouseOld() { return glm::vec2(oldMouseX, oldMouseY); }
	glm::vec2 getMousePos() { return glm::vec2(mouseX, mouseY); }
	void centerMouse();
private:
	SDL_Window *window;
	bool closed = false;
	std::map<SDL_Keycode, bool> *keysPressed;
	void inputTrue(SDL_Keycode);
	void inputFalse(SDL_Keycode);
	void mouseButtonDown();
	void mouseMovement();
	int oldMouseX = 0;
	int oldMouseY = 0;
	int mouseX = 0;
	int mouseY = 0;
	int dMouseX = 0;
	int dMouseY = 0;
};

