#pragma once

#include <string>
#include "GameObject.h"
#include "AssetLoader.h"
#include "Vec2.h"

class SDLGameObject : public GameObject
{
protected:
	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;

public:
	SDLGameObject(const AssetLoader* pParams);
	
	virtual void draw();
	virtual void update();
	virtual void cleanup() {};
};

