#include <stdio.h>

#include "game.h"

game* g_game = 0;

int main(int, char**)
{	
	g_game = new game();

	g_game->init("Game", 1280, 720);

	while (g_game->isRunning())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	g_game->cleanup();
	
	return 0;
}