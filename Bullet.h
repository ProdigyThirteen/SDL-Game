#pragma once

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
private:
	int m_lifeTime = 0;
	int m_maxLifeTime = 100;
	
public:
	Bullet(const AssetLoader* pParams);
	~Bullet();

	void draw() override;
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};