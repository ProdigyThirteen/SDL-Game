#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

struct textureData {
	SDL_Texture* texture;
	const int frames;
	int currentFrame = 0;
};

class textureManager
{
private:
	static std::map<std::string, textureData*> m_textureMap;
	//static textureManager* s_pInstance;
	
public:
	static bool loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer, int frames);
	
	static void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawRot(std::string id, int x, int y, int width, int height, float rotation, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawFrame(std::string id, int x, int y, int width, int height, int currentCol, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawFrameRot(std::string id, int x, int y, int width, int height, float rotation, int currentCol, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};