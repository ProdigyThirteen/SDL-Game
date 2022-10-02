#include <stdio.h>

#include "Game.h"

game* g_game = nullptr;

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