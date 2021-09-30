#pragma once

#include <string>

#include "Game.h"

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height, Game* game); 
	~Actor();

	virtual void update();
	virtual void draw(float scrollX = 0) const;

	bool isOverlap(const Actor&) const;
	bool outsideScreen(float scrollX = 0) const;

	void markForRemoval();
	bool isMarkedForRemoval();

	void moveToFloor(float x, float y);

public:
	float x;
	float y;

	float vx;
	float vy;

	int width;
	int height;

	bool collisionDown;

protected:
	SDL_Texture* texture;

	bool removal = false;

	Game* game; // referencia al juego

private:
	int fileWidth;
	int fileHeight;
};


