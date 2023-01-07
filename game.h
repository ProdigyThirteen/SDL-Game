#pragma once

#include <memory>
#include <stdio.h>
#include <vector>

#include "SDL.h"
#include "Config.h"
#include "Renderer.h"
#include "Player.h"
#include "SDLGameObject.h"

class game
{
private:
	game() {};
	
	//void loadTextures();
	//void loadSounds();
	void loadAssets();
	//void createObjects();

	static game* s_pInstance;
	
	// Game window and view
	SDL_Window* m_pWindow = nullptr;
	//SDL_Renderer* m_pRenderer = nullptr;
	Vec2 m_CameraPos = Vec2(0, 0);

	bool m_isRunning = false;
	bool m_hasWon = false;
	int m_currentFrame = 0;
	int m_enemiesRemaining = 0;

	// Delta time
	int m_lastTime = 0;
	int m_currentTime = 0;
	float m_deltaTime = 0.0f;

	// Game objects
	std::vector<std::shared_ptr<SDLGameObject>> m_gameObjects; // Main game object vector
	std::vector<std::shared_ptr<SDLGameObject>> m_newObjects;  // Vector for new objects to be added to the main vector
	std::vector<std::shared_ptr<SDLGameObject>> m_deadObjects; // Vector for objects to be removed from the main vector
	
public:
	~game() {};

	static game* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool init();
	bool setup();
	void render();
	void update();
	void handleEvents();
	void cleanup(); // For ending the game
	void partialCleanup(); // For resetting the game
	void tick();
	void gameOver();

	// Getters
	bool isRunning() { return m_isRunning; }
	Vec2 getCameraPos() { return m_CameraPos; }
	void setCameraPos(Vec2 pos) { m_CameraPos = pos; }
	float getDeltaTime() { return m_deltaTime; }
	std::vector<std::shared_ptr<SDLGameObject>> getGameObjects() { return m_gameObjects; }
	std::shared_ptr<SDLGameObject> getPlayer();
	bool hasWon() { return m_hasWon; }
	
	// Object management
	void addObject(std::shared_ptr<SDLGameObject> obj);
	void removeObject(std::shared_ptr<SDLGameObject> obj);

	// Misc
	int getEnemiesRemaining() { return m_enemiesRemaining; }
	void setEnemiesRemaining(int num) { m_enemiesRemaining = num; }
	
};

