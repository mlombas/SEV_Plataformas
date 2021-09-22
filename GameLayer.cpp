#include "GameLayer.h"

#include <cstdlib>
#include <iostream>
#include "Actor.h"

GameLayer::GameLayer(Game* game)
	: Layer(game)
{
	init();
}

void GameLayer::init() 
{
	player = new Player(50, 50, game);
	background = new Background("res/fondo.png", WIDTH * .5, HEIGHT * .5, game);

	enemies.clear();
	newEnemy();

	projectiles.clear();
}

//TODO refine
void GameLayer::newEnemy() 
{
	int rX = (std::rand() % (600-500)) + 1 + 500;
	int rY = (std::rand() % (300-60)) + 1 + 60;
	enemies.push_back(new Enemy(rX, rY, game));
	newEnemyTime = 0;
}

void GameLayer::update() 
{
	if(newEnemyTime++ >= newEnemyCooldown)
		newEnemy();

	std::cout << "update GameLayer" << std::endl;

	player->update();

	for(auto const &enemy : enemies) 
	{
		std::cout << "update enemy" << std::endl;
		enemy->update();
		if(player->isOverlap(*enemy))
		{
			init();
			return;
		}
	}

	auto itP = projectiles.begin();
	while(itP != projectiles.end())
	{
		(*itP)->update();
		bool hit = false;

		auto itE = enemies.begin();
		while (itE != enemies.end())
			if ((*itP)->isOverlap(**itE))
			{
				hit = true;
				itE = enemies.erase(itE);
			}
			else itE++;

		if (hit) itP = projectiles.erase(itP);
		else itP++;
	}
}

void GameLayer::draw() 
{
	background->draw();

	for(auto const &enemy : enemies) enemy->draw();
	for(auto const &projectile : projectiles) projectile->draw();

	player->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::processControls() 
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) keysToControls(event);

	if(controlShoot)
	{
		Projectile* projectile = player->shoot();
		if(projectile != NULL) projectiles.push_back(projectile);
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}
}

void GameLayer::keysToControls(const SDL_Event& event) 
{
	int code = event.key.keysym.sym;
	if (event.type == SDL_KEYDOWN) 
	{
		switch (code) 
		{
			case SDLK_d: // derecha
				controlMoveX = 1;
				break;
			case SDLK_a: // izquierda
				controlMoveX = -1;
				break;
			case SDLK_w: // arriba
				controlMoveY = -1;
				break;
			case SDLK_s: // abajo
				controlMoveY = 1;
				break;
			case SDLK_SPACE: // dispara
				controlShoot = true;
				break;
			case SDLK_ESCAPE:
				game->loopActive = false;
				break;
		}
	}
	if (event.type == SDL_KEYUP) 
	{
		switch (code) 
		{
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
}
