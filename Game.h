#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Layer.h"
class Layer;

class Game
{
public:
	Game();
	void loop();
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool loopActive;

	//TODO: Make font manager
	TTF_Font* font;

	Layer* gameLayer;

	const unsigned int WIDTH = 480;
	const unsigned int HEIGHT = 320;

	void scale();

private:
	bool scaledToMax = false;
	float scaleLower = 1;
};

