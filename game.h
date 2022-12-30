#pragma once

#include <memory>
#include <stdio.h>
#include <vector>

#include "SDL.h"
#include "Config.h"
#include "TextureManager.h"
#include "Player.h"
#include "SDLGameObject.h"

class game
{
private:
	game() {};

	const char* TITLE = "Game";
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	
	void loadTextures();
	void createObjects();

	static game* s_pInstance;
	
	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	bool m_isRunning = false;
	int m_currentFrame = 0;

	// Game objects
	std::vector<std::shared_ptr<SDLGameObject>> m_gameObjects; // Main game object vector
	std::vector<std::shared_ptr<SDLGameObject>> m_newObjects;  // Vector for new objects to be added to the main vector
	std::vector<std::shared_ptr<SDLGameObject>> m_deadObjects; // Vector for objects to be removed from the main vector
	
public:
	~game() {};

	static game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool init();
	void render();
	void update();
	void handleEvents();
	void cleanup();

	bool isRunning() { return m_isRunning; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }

	void addObject(std::shared_ptr<SDLGameObject> obj);
	void removeObject(std::shared_ptr<SDLGameObject> obj);
	std::vector<std::shared_ptr<SDLGameObject>> getGameObjects() { return m_gameObjects; }
};

