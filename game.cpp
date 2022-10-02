#include "game.h"

game::game()
{
}

game::~game()
{
}

void game::init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s", SDL_GetError());
		return;
	}
	
	if (!(m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN)))
	{
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		return;
	}

	if(!(m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED)))
	{
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		return;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		printf("IMG_Init Error: %s", IMG_GetError());
		return;
	}

	textureManager::Get()->loadTexture("assets/player/walk/down.png", "walk", m_pRenderer);
	
	m_screenWidth = width;
	m_screenHeight = height;
	m_isRunning = true;
}

void game::cleanup()
{
	m_isRunning = false;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;

		default:
			break;
		}
	}
}

void game::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % framesOfAnimation));
}

void game::render()
{
	SDL_RenderClear(m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer, 0, 180, 180, 255);
	
	textureManager::Get()->drawFrame("walk", 100, 100, 64, 64, 1, m_currentFrame, m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}

