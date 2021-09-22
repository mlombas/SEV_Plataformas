#include "Actor.h"
#include "Projectile.h"

class Player :
	public Actor
{
public:
	Player(float x, float y, Game* game);

	void update() override;

	Projectile* shoot();

	void moveX(float x);
	void moveY(float y);

private:
	const unsigned int shootCadence = 30;
	unsigned int shootTime = 0;
};
