#include "GameLayer.h"

#include <iostream>

GameLayer::GameLayer(Game* game)
	: Layer(game)
{
	init();
}

void GameLayer::init() {
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	std::cout << "update GameLayer" << std::endl;
}

void GameLayer::draw() {
	SDL_RenderPresent(game->renderer); // Renderiza
}
