#include "AmmoDrop.h"
#include "game.h"
#include "RectCollider.h"

AmmoDrop::AmmoDrop(const AssetLoader* pParams)
	: SDLGameObject(pParams, true, new RectCollider(m_position, 16, 16, 0, 0, true, "AmmoDrop"), "Ammo")
{
	m_pCollider->Update();
	m_friction = 0;
	m_maxSpeed = 1000;
	m_speed = 1000;
}

AmmoDrop::~AmmoDrop()
{
}

void AmmoDrop::draw()
{
	//m_pCollider->Debug();
	Renderer::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height);
}

void AmmoDrop::update()
{
	SDLGameObject::update();
	m_pCollider->Update();
}

void AmmoDrop::cleanup()
{
}

void AmmoDrop::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
	// Ammo is static object so collisions will never be checked, handled on player side
}