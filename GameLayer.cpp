#include "GameLayer.h"

#include <iostream>

GameLayer::GameLayer(Game* game)
	: Layer(game)
{
	init();
}

void GameLayer::init() {
	player = new Player(50, 50, game);
	background = new Background("res/fondo.png", WIDTH * .5, HEIGHT * .5, game);
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	std::cout << "update GameLayer" << std::endl;
}

void GameLayer::draw() {
	background->draw();
	player->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}
