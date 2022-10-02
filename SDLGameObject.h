#pragma once

#include <string>
#include "GameObject.h"
#include "AssetLoader.h"

class SDLGameObject : public GameObject
{
protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;

public:
	SDLGameObject(const AssetLoader* pParams);
	
	virtual void draw();
	virtual void update() {};
	virtual void clean() {};
};

