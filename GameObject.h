#pragma once

#include <stdio.h>
#include <string>
#include "SDL.h"

#include "TextureManager.h"

class GameObject
{
private:

protected:
	std::string m_textureID;
	
	int m_currentRow;
	int m_currentFrame;
	
	int m_x;
	int m_y;
	
	int m_width;
	int m_height;
	
public:
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
	
};

