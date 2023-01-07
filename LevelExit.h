#pragma once

#include "SDLGameObject.h"

class LevelExit : public SDLGameObject
{
public:
	LevelExit(const AssetLoader* pParams);
	~LevelExit() {};

	void draw();
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};