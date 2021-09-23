#pragma once

#include <string>
#include "Game.h"

class Animation
{
	public:
		Animation(
				std::string filename,
			   	float actorWidth, float actorHeight,
				float fileWidth, float fileHeight,
				int updateFrecuence, int totalFrames,
			   	Game* game
				);
		Animation(
				std::string filename,
			   	float actorWidth, float actorHeight,
				float fileWidth, float fileHeight,
				int updateFrecuence, int totalFrames,
				bool loop,
			   	Game* game
				);
		bool update();
		void draw(float x, float y);

private:
		bool loop;

		int actorWidth;
		int actorHeight;
		int fileWidth;
		int fileHeight;
		int currentFrame;
		int totalFrames;
		Game* game;

		SDL_Texture* texture; 
		SDL_Rect source; 
		float frameWidth;
		float frameHeigt;
		int updateFrecuence = 0;
		int updateTime = 0;
		
};
