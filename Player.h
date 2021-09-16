#include "Actor.h"

class Player :
	public Actor
{
public:
	Player(float x, float y, Game* game);

	void update();

	void moveX(float x);
	void moveY(float y);
};
