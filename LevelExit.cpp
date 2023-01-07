#include "LevelExit.h"

#include "game.h"
#include "Renderer.h"
#include "RectCollider.h"

LevelExit::LevelExit(const AssetLoader* pParams)
	: SDLGameObject(pParams, true, new RectCollider(m_position, 32, 32, 32, 32, false, "LevelExit"), "LevelExit")
{
}

void LevelExit::draw()
{
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