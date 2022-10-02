#pragma once

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

#include "textureManager.h"

class game
{
private:
	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	bool m_isRunning = false;

	int m_screenWidth = 0;
	int m_screenHeight = 0;
	int m_currentFrame = 0;
	const int framesOfAnimation = 4; // how many frames per sprite sheet
	
public:
	game();
	~game();

	void init(const char* title, int width, int height);
	void cleanup();
	void handleEvents();
	void update();
	void render();

	bool isRunning() { return m_isRunning; }
};

