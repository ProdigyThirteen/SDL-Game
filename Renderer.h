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

class Renderer
{
private:
	//static textureManager* s_pInstance;
	static std::map<std::string, textureData*> m_textureMap;
	static SDL_Renderer* m_pRenderer;
	
public:
	static bool loadTexture(std::string fileName, std::string id, int frames);
	
	static void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawRot(std::string id, int x, int y, int width, int height, float rotation, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawFrame(std::string id, int x, int y, int width, int height, int currentCol, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	static void drawFrameRot(std::string id, int x, int y, int width, int height, float rotation, int currentCol, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static int getDrawCount();

	static SDL_Texture* getTexture(std::string id);

	static bool init(SDL_Window* pWindow);

	static void cleanup();

	static SDL_Renderer* getRenderer();

	static void clear();

	static void present();

	static void setDrawColor(int r, int g, int b, int a);
};