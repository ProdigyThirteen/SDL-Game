#include "SDL.h"
#include "Config.h"
#include "Game.h"
#include "UI.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"

game* game::s_pInstance = 0;

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
	createObjects();
	
	m_isRunning = true;
	return true;
}

void game::loadTextures()
{
	textureManager::loadTexture("assets/player/rifle.png", "playerIdle", m_pRenderer, 1);
	textureManager::loadTexture("assets/player/rifle_shooting.png", "playerShooting", m_pRenderer, 2);
	textureManager::loadTexture("assets/world/Wall.png", "wall", m_pRenderer, 1);
	textureManager::loadTexture("assets/world/Floor.png", "floor", m_pRenderer, 1);
	textureManager::loadTexture("assets/BulletProjectile.png", "bullet", m_pRenderer, 1);
}

void game::createObjects()
{
	const int adjustedWidth = SCREEN_WIDTH / 16;
	const int adjustedHeight = SCREEN_HEIGHT / 16;
	// Create floor
	for (int i = 0; i < adjustedWidth; i++)
	{
		for (int j = 0; j < adjustedHeight; j++)
		{
			addObject(std::make_shared<Floor>(new AssetLoader(i * 16, j * 16, 16, 16, "floor")));
		}
	}

	// Create walls
	for (int i = 0; i < adjustedWidth; i++)
	{
		addObject(std::make_shared<Wall>(new AssetLoader(i * 16, 0, 16, 16, "wall")));
		addObject(std::make_shared<Wall>(new AssetLoader(i * 16, SCREEN_HEIGHT - 16, 16, 16, "wall")));
	}

	for (int i = 0; i < adjustedHeight; i++)
	{
		addObject(std::make_shared<Wall>(new AssetLoader(0, i * 16, 16, 16, "wall")));
		addObject(std::make_shared<Wall>(new AssetLoader(SCREEN_WIDTH - 16, i * 16, 16, 16, "wall")));
	}

	
	addObject(std::make_shared<Player>(new AssetLoader(100, 100, 48, 48, "playerIdle")));
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
	// Update objects
	for (auto& go : m_gameObjects)
	{
		go->checkCollisions();
		go->update();
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

	for (auto& go : m_gameObjects)
	{
		go->draw();
	}

	SDL_RenderPresent(m_pRenderer);
}

