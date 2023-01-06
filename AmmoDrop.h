#pragma once

#include "SDLGameObject.h"

class AmmoDrop : public SDLGameObject
{
public:
	AmmoDrop(const AssetLoader* pParams);
	~AmmoDrop();

	void draw() override;
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};