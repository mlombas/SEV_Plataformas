#pragma once

#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	virtual void draw() const override;
	void update();

	Animation* aMoving;
	Animation* animation;
};
