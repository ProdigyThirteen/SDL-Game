#include "GameObject.h"

void GameObject::load(int x, int y, int width, int height, std::string textureID)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;

	m_currentCol = 1;
	m_currentFrame = 1;
}

void GameObject::draw(SDL_Renderer* pRenderer)
{
	textureManager::Get()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentCol, m_currentFrame, pRenderer);
}

void GameObject::update()
{
	m_x += 1;
}