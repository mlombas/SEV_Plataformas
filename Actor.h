#pragma once

#include <string>

#include "Game.h"

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height, Game* game); 
	~Actor();

	virtual void update();
	virtual void draw() const;

	bool isOverlap(const Actor&) const;
	bool outsideScreen() const;

protected:
	SDL_Texture* texture;

	float x;
	float y;

	float vx;
	float vy;

	int width;
	int height;

	Game* game; // referencia al juego

private:
	int fileWidth;
	int fileHeight;
};
