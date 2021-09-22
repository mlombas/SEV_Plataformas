#include <cmath>
#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) 
{
}

void Player::update()
{
	x += vx;
	y += vy;

	shootTime = std::min(shootTime + 1, shootCadence);
}

Projectile* Player::shoot() 
{
	if(shootTime == shootCadence)
	{
		shootTime = 0;
		return new Projectile(x, y, game);
	}

	return NULL;
}

void Player::moveX(float axis) 
{
	vx = axis * 3;
}

void Player::moveY(float axis) 
{
	vy = axis * 3;
}
