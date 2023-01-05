#include "Wall.h"
#include "Renderer.h"
#include "game.h"
#include "RectCollider.h"

Wall::Wall(const AssetLoader* pParams)
	: SDLGameObject(pParams, true, new RectCollider(m_position, 16, 16, 0, 0, false, "Wall"))
{
	m_pCollider->Update();
}

void Wall::draw()
{
	Renderer::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height);
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