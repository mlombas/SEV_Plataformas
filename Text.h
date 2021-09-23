#pragma once

#include <string>

#include "Game.h"

class Text 
{
public:
	Text(std::string content, float x, float y, Game* game);
	void draw() const;
	void set(std::string content);

private:
	std::string content; // texto
	int x;
	int y;
	int width;
	int height;
	Game* game; // referencia al juego
};
