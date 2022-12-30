#pragma once
#include "Collider.h"
#include <iostream>
#include <memory>

#include "SDLGameObject.h"

class CircleCollider : public Collider
{
private:
	Vec2* m_position;
	int m_radius;
	const Vec2 offset = Vec2(0, 0);

public:
	CircleCollider(Vec2& position, int radius, const bool isTrigger, const std::string tag);
	CircleCollider(Vec2& position, int radius, const int offsetX, const int offsetY, const bool isTrigger, const std::string tag);

	~CircleCollider();

	bool CheckCollision(const Collider& other) const override;
	void Update() override;
	void Debug() const override;

	inline Vec2 GetPosition() const { return *m_position; }
	inline int GetRadius() const { return m_radius; }
	inline Vec2 GetOffset() const { return offset; }
};

