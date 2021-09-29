#pragma once

#include "Actor.h"
#include "Animation.h"


class Enemy : public Actor
{
public:
	enum class State
	{
		MOVING,
		DYING,
		DEAD
	};

public:
	Enemy(float x, float y, Game* game);
	virtual void draw() const override;
	void update();
	void impacted();

private:
	State state;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation;
};
