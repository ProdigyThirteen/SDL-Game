#pragma once

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
private:
	int m_lifeTime = 0;
	const int m_maxLifeTime = 100;

	// Used to prevent self damage and multiple instances of damage
	bool m_canDamagePlayer = false;
	
public:
	Bullet(const AssetLoader* pParams, bool canDamagePlayer);
	~Bullet();

	void draw() override;
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
	bool CanDamagePlayer() { return m_canDamagePlayer; }
	void SetCanDamagePlayer(bool canDamagePlayer) { m_canDamagePlayer = canDamagePlayer; }
};