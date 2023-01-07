#pragma once

#include <string>
#include "Character.h"

enum playerStateEnum
{
	IDLE,
	SHOOTING
};

class Player : public Character
{
private:
	int m_playerState = IDLE;

	Vec2 m_lastSafeLocation;

	void setRotation();
	void setTexture();

	// Gun variables
	const int m_maxAmmo = 99;
	int m_ammo = 2000;
	
public:
	Player(const AssetLoader* pParams);

	void draw();
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};