#include "Background.h"

Background::Background(std::string filename, float x, float y, Game* game) 
	: Actor(filename, x, y, game->WIDTH, game->HEIGHT, game) 
{
}

void Background::draw(float scrollX) const
{
	Actor::draw();
}
