#pragma once
#include "Collider.h"

class RectCollider : public Collider
{
private:
	SDL_Rect m_rect;
	Vec2* m_position;
	const int m_width;
	const int m_height;
	const int m_offsetX;
	const int m_offsetY;
	

public:
	RectCollider(Vec2& position, const int colliderWidth, const int colliderHeight, const int offsetX, const int offsetY, const bool isTrigger, const std::string tag);

	~RectCollider();

	bool CheckCollision(const Collider& other) const override;
	void Update() override;
	void Debug() const override;

	inline SDL_Rect& GetRect() { return m_rect; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline int GetX() const { return m_rect.x; }
	inline int GetY() const { return m_rect.y; }
};