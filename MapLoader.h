#pragma once

#include "SDL.h"
#include "SDL_image.h"

class MapLoader
{
private:
	static Uint32 getPixel(SDL_Surface* surface, int x, int y);

public:
	static bool loadMap(const char* path);
};

