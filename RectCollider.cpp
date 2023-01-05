#include "RectCollider.h"
#include "Collision.h"
#include "CircleCollider.h"
#include "game.h"
#include "Renderer.h"

RectCollider::RectCollider(Vec2& position, const int colliderWidth, const int colliderHeight, const int offsetX, const int offsetY, const bool isTrigger, const std::string tag)
	: Collider(isTrigger, ColliderType::Rect, tag), m_position(&position), m_width(colliderWidth), m_height(colliderHeight), m_offsetX(offsetX), m_offsetY(offsetY)
{
	m_rect.x = m_position->x - m_offsetX;
	m_rect.y = m_position->y - m_offsetY;
	m_rect.w = m_width;
	m_rect.h = m_height;
}

RectCollider::~RectCollider()
{
}

bool RectCollider::CheckCollision(const Collider& other) const
{
	switch (other.GetType())
	{
	case ColliderType::Rect:
		return Collision::AABB(m_rect, ((RectCollider&)other).GetRect());

	case ColliderType::Circle:
		return Collision::CircleRect((CircleCollider&) other, *this);
	}

	return false;
}

void RectCollider::Update()
{
	// Update the position of the rect centred on the position of the object
	m_rect.x = ((int)m_position->x + m_offsetX);
	m_rect.y = ((int)m_position->y + m_offsetY);
}

void RectCollider::Debug() const
{
	// Draw the rect
	SDL_SetRenderDrawColor(Renderer::getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::getRenderer(), &m_rect);
	SDL_SetRenderDrawColor(Renderer::getRenderer(), 0, 180, 180, 255);
}