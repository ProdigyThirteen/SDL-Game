#pragma once

#include <math.h>

class Vec2
{
private:
	float x;
	float y;
	
public:
	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	float getX() { return x; }
	float getY() { return y; }

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
		return sqrt(x * x + y * y);
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

};