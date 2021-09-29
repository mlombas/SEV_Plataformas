#include "Projectile.h"

Projectile::Projectile(float x, float y, float vx, float vy, Game* game) : 
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game)
{ 
	this->vx = vx;
	this->vy = vy;
}

void Projectile::update() 
{
	x += vx;
}
