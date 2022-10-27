#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class textureManager
{
private:
	static std::map<std::string, SDL_Texture*> m_textureMap;
	//static textureManager* s_pInstance;
	
public:
	static bool loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	
	static void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawRot(std::string id, int x, int y, int width, int height, float rotation, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawFrame(std::string id, int x, int y, int width, int height, int currentCol, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawFrameRot(std::string id, int x, int y, int width, int height, float rotation, int currentCol, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};