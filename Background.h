#pragma once

#include "Actor.h"

#include <string>

class Background : public Actor
{
public:
	Background(std::string filename, float x, float y, Game* game);
	void draw(float scrollX = 0) const override;
};
