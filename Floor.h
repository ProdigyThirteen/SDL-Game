#pragma once
#include "SDLGameObject.h"
class Floor : public SDLGameObject
{
public:
	Floor(const AssetLoader* pParams);
	void draw();
	void update();
	void cleanup() override;
};

