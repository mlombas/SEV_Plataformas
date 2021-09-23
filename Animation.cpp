#include "Animation.h"

#include <iostream>

Animation::Animation(
	std::string filename, float actorWidth, float actorHeight, 
	float fileWidth, float fileHeight,
	int updateFrecuence, int totalFrames,
   	Game* game
) :
	Animation(
		filename, actorWidth, actorHeight,
	   	fileWidth, fileHeight,
	   	updateFrecuence, totalFrames,
	   	true,
	   	game
	)
{}
Animation::Animation(
	std::string filename, float actorWidth, float actorHeight, 
	float fileWidth, float fileHeight,
	int updateFrecuence, int totalFrames,
	bool loop,
   	Game* game
) :
	actorWidth(actorWidth), actorHeight(actorHeight),
	fileWidth(fileWidth), fileHeight(fileHeight),
	updateFrecuence(updateFrecuence), totalFrames(totalFrames),
	updateTime(0), currentFrame(0),
	loop(loop),
	game(game)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	frameWidth = fileWidth / totalFrames;
	frameHeigt = fileHeight;

	source.x = 0;
	source.y = 0;
	source.w = frameWidth; 
	source.h = frameHeigt; 
}

//TODO: fix the blink
bool Animation::update() 
{
	if(updateTime++ > updateFrecuence)
	{
		if(currentFrame++ >= totalFrames)
		{ 
			currentFrame = 0;
			if(!loop) return true;
		}
		updateTime = 0;
	}

	source.x = currentFrame * frameWidth;
	return false;
}

void Animation::draw(float x, float y) {
	SDL_Rect destination;
	destination.x = x - actorWidth / 2;
	destination.y = y - actorHeight / 2;
	destination.w = actorWidth;
	destination.h = actorHeight;

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}
