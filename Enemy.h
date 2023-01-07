#pragma once
#include "Character.h"
#include "CircleCollider.h"
#include "Renderer.h"
#include "Player.h"
#include <memory>

class Enemy : public Character
{
private:
	Vec2 m_lastSafeLocation;

	void setRotation(Vec2* target);
	void setTexture();
	
public:
	Enemy(const AssetLoader* pParams);
	~Enemy();
	void draw() override;
	void update();
	void cleanup() override;
	void onCollision(std::shared_ptr<SDLGameObject> pOther) override;
};

