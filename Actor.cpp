#include "Actor.h"

Actor::Actor(std::string filename, float x, float y, int width, int height, Game* game) :
	vx(0), 
	vy(0)
{
	this->game = game;

	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	// lo que mide el fichero
	this->fileWidth = width;
	this->fileHeight = height;

	// posición
	this->x = x;
	this->y = y;

	// lo que va a medir en el juego
	this->width = width;
	this->height = height;
}

bool Actor::isOverlap(const Actor& actor) const
{
	bool overlap = true;

	// &= is a bitwise operator but with bools it works the same
	overlap &= actor.x - actor.width / 3 <= x + width / 2;
	overlap &= actor.x + actor.width / 2 >= x - width / 2;
	overlap &= actor.y + actor.height / 2 >= y - height / 2;
	overlap &= actor.y - actor.height / 2 <= y + height / 2;
	return overlap;
}

void Actor::update() {}

void Actor::draw() const
{
	// Recorte en el fichero de la imagen
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; // texture.width;
	source.h = fileHeight; // texture.height;

	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - int(width / 2);
	destination.y = y - int(height / 2);
	destination.w = width;
	destination.h = height;
	// Modificar para que la referencia sea el punto central

	SDL_RenderCopyEx(game->renderer, 
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

bool Actor::outsideScreen() const
{
	return x + width/2 < 0 || x - width/2 > game->WIDTH ||
		y + height/2 < 0 || y - height/2 > game->HEIGHT;
}
