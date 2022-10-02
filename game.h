#pragma once

#include <stdio.h>
#include <vector>
#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class game
{
private:
	game() {};

	static game* s_pInstance;
	
	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	bool m_isRunning = false;
	int m_currentFrame = 0;

	std::vector<GameObject*> m_gameObjects;
	
public:
	~game() {};

	static game* Get()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool init(const char* title, int width, int height);
	void render();
	void update();
	void handleEvents();
	void cleanup();

	bool isRunning() { return m_isRunning; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }
};

