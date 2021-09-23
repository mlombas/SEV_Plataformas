#include "Actor.h"
#include "Projectile.h"
#include "Animation.h"

enum class State
{
	IDLE,
	MOVING,
	JUMPING,
	DYING,
	DEAD,
	SHOOTING
};

enum class Orientation
{
	LEFT,
	RIGHT
};

class Player :
	public Actor
{
public:
	Player(float x, float y, Game* game);

	void update() override;
	void draw() const override;

	Projectile* shoot();

	void moveX(float x);
	void moveY(float y);

private:
	const unsigned int shootCadence = 30;
	unsigned int shootTime = 0;

	State currentState = State::IDLE;
	Orientation orientation = Orientation::RIGHT;

	Animation* animation;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aShootingRight;
	Animation* aShootingLeft;
};
