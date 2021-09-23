#include "Game.h"

#include <list>

#include <SDL.h>

#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(const SDL_Event& event);

private:
	Player* player;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	std::list<Enemy*> enemies;
	std::list<Projectile*> projectiles;

	Background* background;
	Actor* backgroundPoints;
	Text* textPoints;
	int points = 0;

	const unsigned int newEnemyCooldown = 110;
	unsigned int newEnemyTime = 0;

	void newEnemy();
};
