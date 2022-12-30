#include "Wall.h"
#include "textureManager.h"
#include "game.h"
#include "RectCollider.h"

Wall::Wall(const AssetLoader* pParams)
	: SDLGameObject(pParams, true, new RectCollider(m_position, 16, 16, 0, 0, false, "wall"))
{
	m_pCollider->Update();
}

void Wall::draw()
{
	//m_pCollider->Debug();
	textureManager::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height, game::Instance()->getRenderer());
}

void Wall::update()
{
}

void Wall::cleanup()
{
}

void Wall::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
}