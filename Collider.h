#pragma once

#include <SDL.h>
#include "Vec2.h"
#include <iostream>

enum ColliderType
{
	Rect,
	Circle
};

class Collider
{
private:
	const bool m_bIsTrigger;
	const ColliderType m_type;
	const std::string m_tag;

public:
	Collider(const bool isTrigger, const ColliderType type, const std::string tag)
		: m_type(type), m_tag(tag), m_bIsTrigger(isTrigger)
	{}
	
	virtual ~Collider() {};

	virtual bool CheckCollision(const Collider& other) const = 0;
	virtual void Update() = 0;
	virtual void Debug() const = 0;

	inline bool getIsTrigger() const { return m_bIsTrigger; }
	inline ColliderType GetType() const { return m_type; }
	inline std::string GetTag() const { return m_tag; }
};