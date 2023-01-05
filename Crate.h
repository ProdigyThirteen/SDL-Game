#pragma once

#include "SDLGameObject.h"

class Crate : public SDLGameObject
{
public:
	Crate(const AssetLoader* pParams);

	void draw();
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};