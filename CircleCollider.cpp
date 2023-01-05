#include "CircleCollider.h"
#include "Collision.h"
#include "RectCollider.h"
#include "Renderer.h"
#include "game.h"
#include "Utils.h"

CircleCollider::CircleCollider(Vec2& position, int radius, const bool isTrigger, const std::string tag)
	: Collider(isTrigger, ColliderType::Circle, tag), m_position(&position), m_radius(radius)
{}

CircleCollider::CircleCollider(Vec2& position, int radius, const int offsetX, const int offsetY, const bool isTrigger, const std::string tag)
	: Collider(isTrigger, ColliderType::Circle, tag), m_position(&position), m_radius(radius), offset(offsetX, offsetY)
{}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::CheckCollision(const Collider& other) const
{
	switch (other.GetType())
	{
	case ColliderType::Rect:
		return Collision::CircleRect(*this, (RectCollider&)other);
		
	case ColliderType::Circle:
		return Collision::Circle(*this, (CircleCollider&)other);

	default:
		return false;
	}

	return false;
}

void CircleCollider::Update()
{
}

void CircleCollider::Debug() const
{
	SDL_SetRenderDrawColor(Renderer::getRenderer(), 255, 0, 0, 255);
	Utils::DrawCircle(Renderer::getRenderer(), (int)m_position->x + offset.x - game::Instance()->getCameraPos().x, (int)m_position->y + offset.y - game::Instance()->getCameraPos().y, m_radius);
	SDL_SetRenderDrawColor(Renderer::getRenderer(), 0, 180, 180, 255);
}