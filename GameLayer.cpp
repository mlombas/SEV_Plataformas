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
	space = new Space(1);

	scrollX = 0;

	tiles.clear();

	background = new Background("res/fondo_2.png", game->WIDTH * .5, game->HEIGHT * .5, game);
	backgroundPoints = new Actor("res/icono_puntos.png", 
			game->WIDTH * 0.85, game->HEIGHT * 0.05, 24, 24, game);
	textPoints = new Text("hey", game->WIDTH * .95, game->HEIGHT * .05, game);

	enemies.clear();
	projectiles.clear();

	loadMap("res/0.txt");
}

int randomNumber(int min, int max) 
{
	return std::rand() % (max - min) + min + 1;
}

void GameLayer::update() 
{
	space->update();
	player->update();

	for(auto const &enemy : enemies) 
	{
		enemy->update();
		if(player->isOverlap(*enemy))
		{
			init();
			return;
		}
	}

	for(auto const &projectile : projectiles)
	{
		projectile->update();
		if(projectile->outsideScreen(scrollX)) projectile->markForRemoval();

		bool hit = false;
		for (auto const& enemy : enemies)
			if (projectile->isOverlap(*enemy))
			{
				hit = true;
				enemy->impacted();
			}

		if(hit) projectile->markForRemoval();
	}

	auto itP = projectiles.begin();
	while (itP != projectiles.end())
		if ((*itP)->isMarkedForRemoval())
		{
			space->removeDynamicActor(*itP);
			itP = projectiles.erase(itP);
		}
		else
			itP++;

	auto itE = enemies.begin();
	while (itE != enemies.end())
		if ((*itE)->isMarkedForRemoval())
		{
			space->removeDynamicActor(*itE);
			itE = enemies.erase(itE);
		}
		else
			itE++;

	textPoints->set(std::to_string(points));
}

void GameLayer::draw() 
{
	calculateScroll();

	background->draw(scrollX);

	for(auto const& tile : tiles) tile->draw(scrollX);

	for(auto const &enemy : enemies) enemy->draw(scrollX);
	for(auto const &projectile : projectiles) projectile->draw(scrollX);

	player->draw(scrollX);

	backgroundPoints->draw();
	textPoints->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::processControls() 
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) keysToControls(event);

	if(controlShoot)
	{
		Projectile* projectile = player->shoot();
		if(projectile != NULL) 
		{
			projectiles.push_back(projectile);
			space->addDynamicActor(projectile);
		}
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
	if (controlMoveY < 0) {
		player->jump();
	}
}

void GameLayer::keysToControls(const SDL_Event& event) 
{
	int code = event.key.keysym.sym;
	if (event.type == SDL_QUIT)
		game->loopActive = false;
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
			case SDLK_1:
				game->scale();
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

void GameLayer::loadMap(std::string fname)
{
	char character;
	std::string line;
	std::ifstream streamFile(fname.c_str());
	if (!streamFile.is_open()) {
		std::cout << "Falla abrir el fichero de mapa" << std::endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			std::istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				std::cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}
			
			std::cout << character << std::endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, int x, int y)
{
	switch (character) {
	case 'E': {
		Enemy* enemy = new Enemy(x, y, game);
		enemy->moveToFloor(x, y);
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
	}
	case '1': {
		player = new Player(x, y, game);
		player->moveToFloor(x, y);
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/bloque_tierra.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->moveToFloor(x, y);
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::calculateScroll()
{
	if (player->getX() > game->WIDTH * .3) 
		if (player->getX() - scrollX < game->WIDTH * .3)
			scrollX = player->getX() - game->WIDTH * .3;
	// limite derecha
	if(player->getX() < mapWidth - game->WIDTH * .7) 
		if (player->getX() - scrollX > game->WIDTH * .7) 
			scrollX = player->getX() - game->WIDTH * .7;
}
