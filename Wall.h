#pragma once

#include "SDLGameObject.h"

class Wall : public SDLGameObject
{
public:
	Wall(const AssetLoader* pParams);

	void draw();
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};