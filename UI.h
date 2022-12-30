#pragma once

#include "SDL.h"
#include "SDL_image.h"

class UI
{
	
public:
	static void createButton(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Texture* texture);
};

