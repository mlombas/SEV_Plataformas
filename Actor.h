#pragma once

#include <string>

#include "Game.h"

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height, Game* game); 

	virtual void draw();

protected:
	SDL_Texture* texture;

	float x;
	float y;

	float vx;
	float vy;

	int width;
	int height;
	int fileWidth;
	int fileHeight;

	Game* game; // referencia al juego
};
