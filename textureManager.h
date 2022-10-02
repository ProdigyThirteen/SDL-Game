#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class textureManager
{
private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	textureManager() {};
	static textureManager* s_pInstance;
	
public:
	static textureManager* Get()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new textureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentCol, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};