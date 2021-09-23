#include "Text.h"

#include <string>

Text::Text(std::string content, float x, float y, Game* game) :
	content(content),
	x(x),
	y(y),
	game(game)
{}

void Text::draw() const
{
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect;
	rect.x = x - surface->w/2;
	rect.y = y - surface->h/2;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void Text::set(std::string content) 
{
	this->content = content;
}
