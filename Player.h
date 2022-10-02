#pragma once

#include <string>
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
	Player(const AssetLoader* pParams);

	void draw();
	void update();
	void clean();
};