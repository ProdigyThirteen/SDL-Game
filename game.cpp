#include "SDL.h" // SDL_Init, SDL_CreateWindow, SDL_CreateRenderer, SDL_SetRenderDrawColor, SDL_RenderClear, SDL_RenderPresent, SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Quit
#include "Game.h"
#include "Config.h" // SCREEN_WIDTH, SCREEN_HEIGHT
#include "Renderer.h" // loadTexture
#include "InputHandler.h" // Input events
#include "MapLoader.h" // loadMap
#include <iostream>

game* game::s_pInstance = nullptr;

bool game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s", SDL_GetError());
		return false;
	}
	
	if (!(m_pWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
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
	
	loadTextures();

	//if (!MapLoader::loadMap("levels/test.png"))
	if (!MapLoader::loadMap("levels/benchmark.png"))
	{
		printf("Error loading map\n");
		return false;
	}
	 
	printf("Total objects: %I64d\n", m_newObjects.size());
	
	m_isRunning = true;
	return true;
}

void game::loadTextures()
{
	Renderer::loadTexture("assets/player/rifle.png", "playerIdle", m_pRenderer, 1);
	Renderer::loadTexture("assets/player/rifle_shooting.png", "playerShooting", m_pRenderer, 2);
	Renderer::loadTexture("assets/world/Wall.png", "wall", m_pRenderer, 1);
	Renderer::loadTexture("assets/world/Floor.png", "floor", m_pRenderer, 1);
	Renderer::loadTexture("assets/BulletProjectile.png", "bullet", m_pRenderer, 1);
}

void game::addObject(std::shared_ptr<SDLGameObject> obj)
{
	m_newObjects.push_back(obj);
}

void game::removeObject(std::shared_ptr<SDLGameObject> obj)
{
	m_deadObjects.push_back(obj);
}

void game::cleanup()
{
	printf("Running cleanup...\n");
	m_isRunning = false;
	inputHandler::cleanup();
	
	// Clear all vectors
	m_gameObjects.clear();
	m_newObjects.clear();
	m_deadObjects.clear();
	
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
	// Update delta time
	tick();
	
	// Update objects
	for (auto& go : m_gameObjects)
	{
		go->update();
		go->checkCollisions();
	}

	// Remove objects
	for (auto& go : m_deadObjects)
	{
		m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), go), m_gameObjects.end());
	}

	m_deadObjects.clear();

	// Add objects
	for (auto& go : m_newObjects)
	{
		m_gameObjects.push_back(go);
	}

	m_newObjects.clear();
	

	inputHandler::update();

	if (inputHandler::isKeyDown(SDL_SCANCODE_ESCAPE))
		m_isRunning = false;
	
}

void game::render()
{
	SDL_RenderClear(m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer, 0, 180, 180, 255);

	for (auto& obj : m_gameObjects)
	{
		obj->draw();
	}

	SDL_RenderPresent(m_pRenderer);
}

void game::tick()
{
	// Calculate delta time
	m_lastTime = m_currentTime;
	m_currentTime = SDL_GetTicks();
	m_deltaTime = (m_currentTime - m_lastTime) / 1000.0f;
}