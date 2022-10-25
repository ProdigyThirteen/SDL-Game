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

	void setRotation();
	void setTexture();

	
public:
	Player(const AssetLoader* pParams);

	void draw();
	void update();
	void cleanup();
};