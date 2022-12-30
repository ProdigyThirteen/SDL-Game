#pragma once

#include <string>
#include "SDLGameObject.h"

enum playerStateEnum
{
	IDLE,
	SHOOTING
};

class Player : public SDLGameObject
{
private:
	int m_playerState = IDLE;

	Vec2 m_lastSafeLocation;

	void setRotation();
	void setTexture();

	// Gun variables
	const int m_bulletOffset = 10; // Distance from player to spawn bullet
	const int m_fireRate = 10; // How many frames between each bullet
	int m_fireRateCounter = 0;
	const int m_bulletSpeed = 10; 
	
public:
	Player(const AssetLoader* pParams);

	void draw();
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};