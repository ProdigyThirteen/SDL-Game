#include "Floor.h"
#include "textureManager.h"
#include "game.h"

Floor::Floor(const AssetLoader* pParams)
	: SDLGameObject(pParams, true)
{}

void Floor::draw()
{
	textureManager::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height, game::Instance()->getRenderer());
}

void Floor::update()
{
}

void Floor::cleanup()
{
}