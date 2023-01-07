#include "Collision.h"
#include "Vec2.h"
#include "CircleCollider.h"
#include "RectCollider.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
	{
		return true;
	}
	return false;
}

bool Collision::AABB(const SDL_Rect& recA, int x, int y)
{
	if (recA.x + recA.w >= x &&
		x + recA.w >= recA.x &&
		recA.y + recA.h >= y &&
		y + recA.h >= recA.y)
	{
		return true;
	}
	return false;
}

bool Collision::AABB(const Vec2& posA, const Vec2& posB, const int& widthA, const int& heightA, const int& widthB, const int& heightB)
{
	if (posA.x + widthA >= posB.x &&
		posB.x + widthB >= posA.x &&
		posA.y + heightA >= posB.y &&
		posB.y + heightB >= posA.y)
	{
		return true;
	}
	return false;
}

//bool Collision::Circle(const Vec2& posA, const int& radiusA, const Vec2& posB, const int& radiusB)
//{
//	int totalRadiusSquared = radiusA * radiusA + radiusB * radiusB;
//	if (totalRadiusSquared >= (posA - posB).LengthSq())
//	{
//		return true;
//	}
//	return false;
//}

bool Collision::Circle(const CircleCollider& self, const CircleCollider& other)
{
	int totalRadiusSquared = self.GetRadius() * self.GetRadius() + other.GetRadius() * other.GetRadius();

	// check if the circles are colliding, accounting for the offset
	if (totalRadiusSquared >= (self.GetPosition() + self.GetOffset() - other.GetPosition() - other.GetOffset()).LengthSq())
	{
		return true;
	}
	return false;
}

//bool Collision::CircleRect(const Vec2& circlePos, const int& circleRadius, const SDL_Rect& rect)
//{
//	int distX = abs(circlePos.x - rect.x - rect.w / 2);
//	int distY = abs(circlePos.y - rect.y - rect.h / 2);
//
//	if (distX > (rect.w / 2 + circleRadius)) { return false; }
//	if (distY > (rect.h / 2 + circleRadius)) { return false; }
//
//	if (distX <= (rect.w / 2)) { return true; }
//	if (distY <= (rect.h / 2)) { return true; }
//
//	int dx = distX - rect.w / 2;
//	int dy = distY - rect.h / 2;
//	return (dx * dx + dy * dy <= (circleRadius * circleRadius));
//}

bool Collision::CircleRect(const CircleCollider& circle, const RectCollider& rect)
{	
	int distX = fabs((circle.GetPosition().x + circle.GetOffset().x) - rect.GetX() - rect.GetWidth() / 2);
	int distY = fabs((circle.GetPosition().y + circle.GetOffset().y) - rect.GetY() - rect.GetHeight() / 2);

	if (distX > (rect.GetWidth() / 2 + circle.GetRadius())) { return false; }
	if (distY > (rect.GetHeight() / 2 + circle.GetRadius())) { return false; }

	if (distX <= (rect.GetWidth() / 2)) { return true; }
	if (distY <= (rect.GetHeight() / 2)) { return true; }

	int dx = distX - rect.GetWidth() / 2;
	int dy = distY - rect.GetHeight() / 2;
	return (dx * dx + dy * dy <= (circle.GetRadius() * circle.GetRadius()));
}