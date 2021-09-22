#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Layer.h"
class Layer;

#define WIDTH 480
#define HEIGHT 320

class Game
{
public:
	Game();
	void loop();
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool loopActive;

	Layer* gameLayer;

	void scale();
	bool scaledToMax = false;
	float scaleLower = 1;
};

