#include "Game.h"

#include <list>

#include <SDL.h>

#include "Player.h"
#include "Background.h"
#include "Enemy.h"

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(const SDL_Event& event);

	Player* player;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	std::list<Enemy*> enemies;

	Background* background;
};
