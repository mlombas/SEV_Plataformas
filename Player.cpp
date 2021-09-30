#include <cmath>
#include <algorithm>
#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) 
{
	onAir = false;

	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
			320, 40, 6, 8, game);
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
			320, 40, 6, 8, game);
	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
			320, 40, 6, 8, game);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
			320, 40, 6, 8, game);
	aShootingRight = new Animation("res/jugador_disparando_derecha.png", 
			width, height, 160, 40, 6, 4, false, game);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png",  
			width, height,160, 40, 6, 4, false, game);
	animation = aIdleRight;
}

void Player::update()
{
	onAir = !collisionDown;

	shootTime = std::min(shootTime + 1, shootCadence);

	if(currentState != State::SHOOTING)
	{
		//I do this because floats and precision errors
		if(vx * vx < 1e-12) currentState = State::IDLE;
		else
		{
			currentState = State::MOVING;
			if(vx > 0) orientation = Orientation::RIGHT;
			else orientation = Orientation::LEFT;
		}
	}
	
	switch (currentState)
	{
	case State::SHOOTING:
		animation = orientation == Orientation::RIGHT ?
			aShootingRight : aShootingLeft;
		break;
	case State::MOVING:
		animation = orientation == Orientation::RIGHT ?
			aRunningRight : aRunningLeft;
		break;
	case State::IDLE:
		animation = orientation == Orientation::RIGHT ?
			aIdleRight : aIdleLeft;
		break;
	}
	
	bool finish = animation->update();
	if(finish) currentState = State::MOVING;
}

void Player::draw(float scrollX) const
{
	animation->draw(x - scrollX, y);
}

Projectile* Player::shoot() 
{
	if(shootTime == shootCadence)
	{
		shootTime = 0;

		currentState = State::SHOOTING;
		return new Projectile(
				x, y,
				//Invert shooting direction if player is looking at the other way
			   	20 * (int(orientation == Orientation::RIGHT) * 2 - 1), 20,
			   	game);
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

void Player::jump() 
{
	if(!onAir)
	{
		vy = -16;
		onAir = false;
	}
}

float Player::getX() { return x; }
float Player::getY() { return y; }
