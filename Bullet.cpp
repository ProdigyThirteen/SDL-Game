#include "Bullet.h"
#include "CircleCollider.h"
#include "Renderer.h"
#include "game.h"


Bullet::Bullet(const AssetLoader* pParams, bool canDamagePlayer) 
	: SDLGameObject(pParams, false, new CircleCollider(m_position, 4, 2, 2, false, "Bullet"), "Bullet"), m_canDamagePlayer(canDamagePlayer)
{
	m_pCollider->Update();
	m_friction = 0;
	m_maxSpeed = 1000;
	m_speed = 1000;
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	//m_pCollider->Debug();
	Renderer::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height);
}

void Bullet::update()
{
	SDLGameObject::update();
	m_pCollider->Update();

	m_lifeTime++;
	if (m_lifeTime > m_maxLifeTime)
	{
		game::Instance()->removeObject(shared_from_this());
	}
}

void Bullet::cleanup()
{
}

void Bullet::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
	if (pOther->getCollider().GetTag() == "Wall")
	{
		game::Instance()->removeObject(shared_from_this());
	}

	if (pOther->getCollider().GetTag() == "Enemy")
	{
		pOther->onCollision(shared_from_this());
		game::Instance()->removeObject(shared_from_this());
	}
}