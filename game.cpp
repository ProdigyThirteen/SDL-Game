#include "SDL.h" // SDL_Init, SDL_CreateWindow, SDL_CreateRenderer, SDL_SetRenderDrawColor, SDL_RenderClear, SDL_RenderPresent, SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Quit
#include "SDL_image.h" // IMG_Init, IMG_Quit
#include "SDL_ttf.h" // TTF_Init, TTF_Quit
#include "SDL_mixer.h" // Mix_Init, Mix_Quit
#include "Game.h"
#include "Config.h" // SCREEN_WIDTH, SCREEN_HEIGHT
#include "Renderer.h" // loadTexture
#include "InputHandler.h" // Input events
#include "MapLoader.h" // loadMap
#include "UI.h"
#include "Sounds.h"
#include "Utils.h"
#include <iostream>
#include <random>

game* game::s_pInstance = nullptr;

bool game::init()
{
	// SDL Init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("SDL_Init Error: %s", SDL_GetError());
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}
	
	if (!(m_pWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	// Renderer init
	if (!Renderer::init(m_pWindow))
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("Error initializing renderer\n");
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}
	
	// IMG Init
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	
	if (initted != flags)
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("IMG_Init Error: %s", IMG_GetError());
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	// Text init
	if (TTF_Init() != 0)
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("TTF_Init Error: %s", TTF_GetError());
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	// UI Init
	if (!UI::init())
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("Error initializing UI\n");
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	// Sound init
	if (!Sounds::init())
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("Error initializing sounds\n");
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	// Input init
	if (!inputHandler::init())
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("Error initializing input handler\n");
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	// Game setup
	loadAssets();

	// Load a random level
	int choice = rand() % 2;

	switch (choice)
	{
	case 0:
		if (!MapLoader::loadMap("levels/2.png"))
		{
			Utils::SetConsoleColour(Utils::ConsoleColour::RED);
			printf("Error loading map\n");
			Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
			return false;
		}
		break;

	case 1:
		if (!MapLoader::loadMap("levels/2.png"))
		{
			Utils::SetConsoleColour(Utils::ConsoleColour::RED);
			printf("Error loading map\n");
			Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
			return false;
		}
		break;

	default:
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("Error loading map\n");
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}
	
	m_isRunning = true;
	return true;
}

void game::loadAssets()
{
	// Textures
	Renderer::loadTexture("assets/player/rifle.png", "playerIdle");
	Renderer::loadTexture("assets/player/rifle_shooting.png", "playerShooting", 2);
	Renderer::loadTexture("assets/enemy/pistol_idle.png", "enemyIdle");
	Renderer::loadTexture("assets/enemy/pistol_shooting.png", "enemyShooting", 2);
	Renderer::loadTexture("assets/world/Wall.png", "wall");
	Renderer::loadTexture("assets/world/Floor.png", "floor");
	Renderer::loadTexture("assets/world/crate.png", "crate");
	Renderer::loadTexture("assets/BulletProjectile.png", "bullet");
	Renderer::loadTexture("assets/Machinegun.png", "gun");
	Renderer::loadTexture("assets/ui/Bullet.png", "ui_bullet");
	Renderer::loadTexture("assets/ui/Heart.png", "ui_heart");

	// Sounds
	Sounds::loadSound("assets/sounds/gunshot.mp3", "gunshot");

	// Fonts
	UI::loadFont("assets/fonts/NotoMono-Regular.ttf", 32);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~OBJECT MANAGEMENT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void game::addObject(std::shared_ptr<SDLGameObject> obj)
{
	m_newObjects.push_back(obj);
}

void game::removeObject(std::shared_ptr<SDLGameObject> obj)
{
	m_deadObjects.push_back(obj);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~CORE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
	for (auto& obj : m_gameObjects)
	{
		obj->update();
		obj->checkCollisions();
	}

	// Remove dead objects
	for (auto& obj : m_deadObjects)
	{
		m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), obj), m_gameObjects.end());
	}

	m_deadObjects.clear();

	// Add new objects
	for (auto& obj : m_newObjects)
	{
		m_gameObjects.push_back(obj);
	}

	m_newObjects.clear();
	

	inputHandler::update();
	if (inputHandler::isKeyDown(SDL_SCANCODE_ESCAPE))
		m_isRunning = false;
	
}

void game::render()
{
	Renderer::clear();
	Renderer::setDrawColor(0, 180, 180, 255);

	for (auto& obj : m_gameObjects)
	{
		obj->draw();
	}
	
	Renderer::present();
}

void game::tick()
{
	// Calculate delta time
	m_lastTime = m_currentTime;
	m_currentTime = SDL_GetTicks();
	m_deltaTime = (m_currentTime - m_lastTime) / 1000.0f;
}

void game::cleanup()
{
	printf("Running cleanup...\n");
	m_isRunning = false;

	// Clean up static classes
	Renderer::cleanup();
	inputHandler::cleanup();
	UI::cleanup();
	Sounds::cleanup();

	// Clear all vectors
	m_gameObjects.clear();
	m_newObjects.clear();
	m_deadObjects.clear();

	// Clean up SDL modules
	SDL_DestroyWindow(m_pWindow);
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~GETTERS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

std::shared_ptr<SDLGameObject> game::getPlayer()
{
	// Find player in game objects
	for (auto& obj : m_gameObjects)
	{
		if (obj->getTag() == "Player")
			return obj;
	}
	
	return nullptr;
}