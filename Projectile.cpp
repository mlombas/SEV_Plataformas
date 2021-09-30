#include "Projectile.h"

Projectile::Projectile(float x, float y, float vx, float vy, Game* game) : 
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game)
{ 
	this->vx = vx;
	this->vy = -1;
}

void Projectile::update() 
{
	//if(vy == 0) markForRemoval();
	vy -= 1;
}
