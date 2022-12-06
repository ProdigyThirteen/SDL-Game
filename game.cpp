#include <stdio.h>
#include <vector>
#include "SDL.h"

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"

game* game::s_pInstance = 0;

bool game::init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s", SDL_GetError());
		return false;
	}
	
	if (!(m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN)))
	{
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		return false;
	}

	if(!(m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED)))
	{
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		return false;
	}

	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	
	if (initted != flags)
	{
		printf("IMG_Init Error: %s", IMG_GetError());
		return false;
	}

	inputHandler::init();
	
	//textureManager::Get()->loadTexture("assets/player/rifle.png", "playerIdle", m_pRenderer);
	//textureManager::Get()->loadTexture("assets/player/rifle_shooting.png", "playerShooting", m_pRenderer);
	textureManager::loadTexture("assets/player/rifle.png", "playerIdle", m_pRenderer);
	textureManager::loadTexture("assets/player/rifle_shooting.png", "playerShooting", m_pRenderer);

	m_gameObjects.push_back(new Player(new AssetLoader(0, 0, 48, 48, "playerIdle", 2)));
	
	
	m_isRunning = true;
	return true;
}

void game::cleanup()
{
	printf("Running cleanup...\n");
	
	m_isRunning = false;
	inputHandler::cleanup();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void game::handleEvents()
{
	//inputHandler::update();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			inputHandler::onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputHandler::onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			inputHandler::onMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			inputHandler::onKeyDown(event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			inputHandler::onKeyUp(event.key.keysym.scancode);
			break;
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
	for (auto& go : m_gameObjects)
	{
		go->update();
	}

	inputHandler::update();

	if (inputHandler::isKeyDown(SDL_SCANCODE_ESCAPE))
		m_isRunning = false;

	if (inputHandler::onKeyDown(SDL_SCANCODE_W))
		printf("W is pressed\n");
	if (inputHandler::onKeyUp(SDL_SCANCODE_W))
		printf("W is released\n");
	
}

void game::render()
{
	SDL_RenderClear(m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer, 0, 180, 180, 255);

	for (auto& go : m_gameObjects)
	{
		go->draw();
	}

	SDL_RenderPresent(m_pRenderer);
}

