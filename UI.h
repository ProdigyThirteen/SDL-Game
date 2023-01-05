#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

class UI
{
private:
	static TTF_Font* m_pFont;
	static SDL_Renderer* m_pRenderer;
	
public:
	static bool init();
	static void cleanup();
	static bool loadFont(std::string path, int size);
	static void drawText(std::string text, int x, int y, SDL_Color color);
};

