#include "Game.h"

#include <iostream>
#include <string>

Game::Game() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error SDL_Init" << SDL_GetError() << std::endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) 
	{
		std::cout << "Error Window y Renderer" << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(window, "Juego de Navecitas");
	// Escalado de imágenes de calidad 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	loopActive = true; // bucle activo
	loop();
}

void Game::loop() 
{
	int initTick; // ms de inicio loop
	int endTick; // ms de fin de loop
	int differenceTick; // fin - inicio
	while (loopActive) 
	{
		initTick = SDL_GetTicks();

		// Controles
		// Actualizar elementos
		// Dibujar

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < (1000 / 30)) 
		{
			SDL_Delay((1000 / 30) - differenceTick);
		}
	}
}
