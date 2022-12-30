#include "Bullet.h"
#include "CircleCollider.h"
#include "textureManager.h"
#include "game.h"


Bullet::Bullet(const AssetLoader* pParams) 
	: SDLGameObject(pParams, false, new CircleCollider(m_position, 4, 0, 0, false, "bullet"))
{
	m_pCollider->Update();
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	//m_pCollider->Debug();
	textureManager::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height, game::Instance()->getRenderer());
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
	if (pOther->getCollider().GetTag() == "wall")
	{
		game::Instance()->removeObject(shared_from_this());
	}
}