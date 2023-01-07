#pragma once

#include "SDLGameObject.h"

class Character : public SDLGameObject
{
protected:
	const int m_bulletOffset = 12; // Distance from player to spawn bullet
	int m_fireRate = 8; // How many frames between each bullet
	int m_fireRateCounter = 0;
	const bool m_isEnemy = false;

	int m_maxHealth = 10;
	int m_health = m_maxHealth;
	bool m_isDead = false;

	void Shoot(Vec2 target, int bulletSpeed, bool canDamagePlayer);
	
	
public:
	Character(const AssetLoader* pParams, bool isEnemy, Collider* pCollider, const std::string tag);
	~Character();
	
};

