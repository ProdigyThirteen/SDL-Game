#include "LevelExit.h"

#include "game.h"
#include "Renderer.h"
#include "RectCollider.h"

LevelExit::LevelExit(const AssetLoader* pParams)
	: SDLGameObject(pParams, true, new RectCollider(m_position, 32, 32, 0, 0, true, "LevelExit"), "LevelExit")
{
	m_pCollider->Update();
}

void LevelExit::draw()
{
	//m_pCollider->Debug();
	Renderer::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height);
}

void LevelExit::update()
{
}

void LevelExit::cleanup()
{
}

void LevelExit::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
}