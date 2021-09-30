#include "Game.h"

#include <list>
#include <fstream>
#include <sstream>

#include <SDL.h>

#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h"

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
	Space* space;

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

	void loadMap(std::string fname);
	void loadMapObject(char character, int x, int y);
	int mapWidth;
	std::list<Tile*> tiles;

	float scrollX;
	void calculateScroll();
};
