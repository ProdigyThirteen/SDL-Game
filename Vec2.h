#pragma once

#include <math.h>
#include <iostream>

struct Vec2
{
	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}

	float x;
	float y;
	//void setX(float x) { this->x = x; }
	//void setY(float y) { this->y = y; }
	//float getX() { return x; }
	//float getY() { return y; }

	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}

	Vec2 operator*(float rhs) const
	{
		return Vec2(x * rhs, y * rhs);
	}

	Vec2 operator/(float rhs) const
	{
		return Vec2(x / rhs, y / rhs);
	}

	Vec2& operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2& operator*=(float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vec2& operator/=(float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	float Length() const
	{
		return (float)sqrt(x * x + y * y);
	}

	float LengthSq() const
	{
		return x * x + y * y;
	}

	Vec2& Normalize()
	{
		return *this /= Length();
	}

	Vec2 GetNormalized() const
	{
		return *this / Length();
	}

	float Dot(const Vec2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	float Cross(const Vec2& rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	float AngleBetween(const Vec2& rhs) const
	{
		float lenProduct = Length() * rhs.Length();

		if (lenProduct < 1.0e-8f)
			lenProduct = 1.0e-8f;

		float d = Dot(rhs) / lenProduct;

		if (d < -1.0f)
			d = -1.0f;
		if (d > 1.0f)
			d = 1.0f;

		return (float)acos(d);
	}

	float Distance(const Vec2& rhs) const
	{
		return (*this - rhs).Length();
	}

	float DistanceSq(const Vec2& rhs) const
	{
		return (*this - rhs).LengthSq();
	}

	Vec2& Rotate(float angle)
	{
		float cs = (float)cos(angle);
		float sn = (float)sin(angle);

		return *this = Vec2(x * cs - y * sn, x * sn + y * cs);
	}
};