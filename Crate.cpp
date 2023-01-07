#include "Crate.h"
#include "Renderer.h"
#include "game.h"
#include "RectCollider.h"

Crate::Crate(const AssetLoader* pParams)
	: SDLGameObject(pParams, true, new RectCollider(m_position, 16, 16, 0, 0, false, "Crate"), "Crate")
{
	m_pCollider->Update();
}

void Crate::draw()
{
	Renderer::draw(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height);
}

void Crate::update()
{
}

void Crate::cleanup()
{
}

void Crate::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
}