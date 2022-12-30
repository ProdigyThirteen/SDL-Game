#pragma once

#include <SDL.h>
#include "Vec2.h"
#include "CircleCollider.h"
#include "RectCollider.h"

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const SDL_Rect& recA, int x, int y);
	static bool AABB(const Vec2& posA, const Vec2& posB, const int& widthA, const int& heightA, const int& widthB, const int& heightB);

	//static bool Circle(const Vec2& posA, const int& radiusA, const Vec2& posB, const int& radiusB);
	static bool Circle(const CircleCollider& self, const CircleCollider& other);

	//static bool CircleRect(const Vec2& circlePos, const int& circleRadius, const SDL_Rect& rect);
	static bool CircleRect(const CircleCollider& circle, const RectCollider& rect);
};