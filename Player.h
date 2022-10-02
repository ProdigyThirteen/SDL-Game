#pragma once

#include <stdio.h>
#include <string>

#include "GameObject.h"

class Player : public GameObject
{
private:
	
	
public:
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
};