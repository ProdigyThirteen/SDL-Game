#include <stdio.h>
#include "Game.h"
#include <random>
#include <time.h>

const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

int main(int, char**)
{	
	Uint32 frameStart, frameTime;

	// Seed random
	srand(time(NULL));

	printf("Attempting init...\n");
	if (game::Instance()->init())
	{
		printf("Init success!\n");
		while (game::Instance()->isRunning())
		{
			frameStart = SDL_GetTicks();
			game::Instance()->handleEvents();
			game::Instance()->update();
			game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			
			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((DELAY_TIME - frameTime));
			}
		}		
	}


	game::Instance()->cleanup();
	
	return 0;
}