#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Vec2.h"

SDLGameObject::SDLGameObject(const AssetLoader* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_framesOfAnimation(pParams->getFramesOfAnimation())
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw()
{
	textureManager::Get()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, game::Get()->getRenderer());
}

void SDLGameObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}