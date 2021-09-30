#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game) 
	: Actor("res/enemigo.png", x, y, 36, 40, game) 
{
	vx = -1;

	state = State::MOVING;

	aDying = new Animation(
			"res/enemigo_morir.png",
		   	width, height,
			280, 40, 6, 8,
		   	false, game
			);
	aMoving = new Animation(
			"res/enemigo_movimiento.png",
		   	width, height, 
			108, 40, 6, 3,
		   	game
			);
	animation = aMoving;
}

void Enemy::update()
{
	switch(state) {
		case State::MOVING:
			animation = aMoving;
			break;
		case State::DYING:
			animation = aDying;
			break;
	}
	bool endAnim = animation->update();
	if (endAnim && state == State::DYING)
	{
		state = State::DEAD;
		markForRemoval();
	}
} 

void Enemy::impacted() {
	state = State::DYING;
}

void Enemy::draw(float scrollX) const
{
	animation->draw(x - scrollX, y);
}
