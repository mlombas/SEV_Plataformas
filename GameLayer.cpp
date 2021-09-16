#include "GameLayer.h"

#include <iostream>

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
	int nEnemies = 3;
	for(int n = 0; n < nEnemies; n++)
		enemies.push_back(new Enemy(WIDTH - 50, HEIGHT / nEnemies * n + 50, game));
}

void GameLayer::update() 
{
	std::cout << "update GameLayer" << std::endl;

	player->update();

	for(auto const &enemy : enemies) enemy->update();
}

void GameLayer::draw() 
{
	background->draw();

	for(auto const &enemy : enemies) enemy->draw();

	player->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::processControls() 
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) keysToControls(event);

	if(controlShoot)
	{
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
