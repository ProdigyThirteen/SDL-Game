#pragma once

#include <string>
#include "AssetLoader.h"

class GameObject
{
protected:
	GameObject(const AssetLoader* pParams) {}
	virtual ~GameObject() {}
	
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void cleanup() = 0;
	
};

