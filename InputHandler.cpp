#include "InputHandler.h"


InputHandler::InputHandler(SDL_Window *window)
{
	this->window = window;
	keysPressed = new std::map<SDL_Keycode, bool>;
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_w, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_s, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_a, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_d, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_q, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_e, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F1, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F2, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F3, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F4, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F5, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F6, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F7, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F8, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F9, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F10, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F11, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_F12, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_SPACE, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_LSHIFT, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_LALT, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDLK_ESCAPE, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDL_BUTTON_LEFT, false));
	keysPressed->insert(std::pair<SDL_Keycode, bool>(SDL_BUTTON_RIGHT, false));

}


InputHandler::~InputHandler()
{
}


void InputHandler::poll(){
	
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type){
		case SDL_QUIT:
			closed = true;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE)
				closed = true;
			inputTrue(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputFalse(e.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
				inputTrue(SDL_BUTTON_LEFT);
			else if (e.button.button == SDL_BUTTON_RIGHT)
				inputTrue(SDL_BUTTON_RIGHT);
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
				inputFalse(SDL_BUTTON_LEFT);
			else if (e.button.button == SDL_BUTTON_RIGHT)
				inputFalse(SDL_BUTTON_RIGHT);
			break;
		case SDL_MOUSEMOTION:
			oldMouseX = mouseX;
			oldMouseY = mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			mouseMovement();
		//	std::cout << "x: " << mouseX << " y: " << mouseY << std::endl;
			
			break;
		}

	}
	if (!keysPressed->at(SDLK_LALT)){
		//centerMouse();
		SDL_ShowCursor(0);
	}
	else
		SDL_ShowCursor(1);

}

void InputHandler::centerMouse(){
	SDL_WarpMouseInWindow(window, DisplayManager::getWidth() / 2, DisplayManager::getHeight() / 2);
}

void InputHandler::mouseMovement(){
	dMouseX = DisplayManager::getWidth() - mouseX;
	dMouseY = DisplayManager::getWidth() - mouseY;
}

void InputHandler::inputTrue(SDL_Keycode key){
	try {
		keysPressed->at(key) = true;
	} catch (std::out_of_range){

	}
}

void InputHandler::inputFalse(SDL_Keycode key){
	try {
		keysPressed->at(key) = false;
	} catch (std::out_of_range){

	}
}

void InputHandler::mouseButtonDown() {
	
}
