#include "Enemy.h"
#include "CircleCollider.h"
#include "Renderer.h"
#include "Player.h"
#include "game.h"

Enemy::Enemy(const AssetLoader* pParams)
	: Character(pParams, true, new CircleCollider(m_position, 8, 24, 24, false, "Enemy"), "Enemy")
{
	m_friction = 10;
	m_maxSpeed = 45;
	m_speed = 30;
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
	m_pCollider->Debug();
	Renderer::drawRot(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height, m_rotation);
}

void Enemy::update()
{
	// Check health
	if (m_health <= 0)
	{
		m_isDead = true;
	}
	
	if (!m_isDead)
	{
		m_lastSafeLocation = m_position;
		SDLGameObject::update();
		m_pCollider->Update();

		m_fireRateCounter++;
	
		// TODO: Clean this up, magic number "24,24" is the player's positional offset
		Vec2 playerPos = game::Instance()->getPlayer()->getPosition() + Vec2(24, 24);
		setRotation(&playerPos);

		Vec2 distToPlayer = playerPos - m_position;
	
		if (m_fireRateCounter >= m_fireRate && distToPlayer.Length() < 200)
		{
			m_fireRateCounter = 0;
			//Shoot(playerPos, 400, true);
		}
		// If the enemy is too far away from the player, move towards them
		else if (distToPlayer.Length() > 200)
		{
			m_acceleration = distToPlayer.Normalize() * m_speed;
		}
	}
	else
	{
		game::Instance()->removeObject(shared_from_this());
	}


}

void Enemy::cleanup()
{
}

void Enemy::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
	if (pOther->getTag() == "Bullet")
	{
		m_health -= 1;
		printf("Enemy health = %i\n", m_health);
	}

	if (pOther->getTag() == "Player")
	{
		m_lastSafeLocation = m_position;
	}

	if (pOther->getTag() == "Wall" || 
		pOther->getTag() == "Player" || 
		pOther->getTag() == "Crate")
	{
		m_position = m_lastSafeLocation;
	}
}

void Enemy::setRotation(Vec2* target)
{
	Vec2* vec = target;
	float x = vec->x - (m_position.x + m_width / 2);
	float y = vec->y - (m_position.y + m_height / 2);
	m_rotation = (float)(atan2(y, x) * 180 / M_PI);
}

void Enemy::setTexture()
{
}