#pragma once

#include "Actor.h"

class Projectile :
	public Actor
{
public:
	Projectile(float x, float y, float vx, float vy, Game* game);
	void update() override;
};
