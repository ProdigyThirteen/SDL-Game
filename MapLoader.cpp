#include "MapLoader.h"

#include <stdio.h> // printf
#include <memory> // std::shared_ptr, std::make_shared
#include "Config.h" // SCREEN_WIDTH, SCREEN_HEIGHT, TILE_SIZE
#include "game.h" // game::addObject
#include "AssetLoader.h" // AssetLoader

// Objects to be created
#include "Player.h"
#include "Crate.h"
#include "Wall.h"
#include "Tilemap.h"
#include "AmmoDrop.h"

// I totally didn't find this on stackoverflow, I swear
Uint32 MapLoader::getPixel(SDL_Surface* surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

bool MapLoader::loadMap(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL)
	{
		printf("IMG_Load Error: %s", IMG_GetError());
		return false;
	}
	
	printf("Loading level: %s\n", path);

	// Player position
	int playerX = 0;
	int playerY = 0;

	// Tilemap size
	int tilemapWidth = surface->w;
	int tilemapHeight = surface->h;

	printf("Tilemap size: %d x %d\n", tilemapWidth, tilemapHeight);

	// Create tilemap
	std::shared_ptr<Tilemap> tilemap = std::make_shared<Tilemap>(tilemapWidth, tilemapHeight);

	// Add the tilemap to the game first to ensure it is drawn first
	game::Instance()->addObject(tilemap);

	for (int y = 0; y < tilemapHeight; y++)
	{
		for (int x = 0; x < tilemapWidth; x++)
		{
			Uint32 pixel = getPixel(surface, x, y);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, surface->format, &r, &g, &b);

			if (r == 255 && g == 255 && b == 255)
			{
				game::Instance()->addObject(std::make_shared<Wall>(new AssetLoader(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, "wall")));
				tilemap.get()->setTile(x, y, WALL);
			}
			else if (r == 0 && g == 0 && b == 0)
			{
				// Floor
				tilemap.get()->setTile(x, y, FLOOR);
			}
			else if (r == 255 && g == 0 && b == 0)
			{
				// Store the player position and place a floor tile
				playerX = x * TILE_SIZE;
				playerY = y * TILE_SIZE;
				tilemap.get()->setTile(x, y, FLOOR);
			}
			else if (r == 248 && g == 178 && b == 90)
			{
				// Crate
				game::Instance()->addObject(std::make_shared<Crate>(new AssetLoader(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, "crate")));
				tilemap.get()->setTile(x, y, CRATE);
			}
			else if (r == 0 && g == 255 && b == 0)
			{
				// Ammo drop
				game::Instance()->addObject(std::make_shared<AmmoDrop>(new AssetLoader(x * TILE_SIZE, y * TILE_SIZE, 32, 16, "gun")));
				tilemap.get()->setTile(x, y, FLOOR);
			}
			else if (r == 0 && g == 0 && b == 255)
			{
				//Exit
			}
			else
			{
				printf("Unknown color: %d, %d, %d at X: %i Y: %i\n", r, g, b, x, y);
				return false;
			}
		}
	}

	// Create the player to ensure it's on top of everything
	game::Instance()->addObject(std::make_shared<Player>(new AssetLoader(playerX, playerY, 48, 48, "playerIdle")));

	SDL_FreeSurface(surface);
	printf("Level loaded successfully\n");
	return true;
}


/*
 COLOUR KEY:
	WALL = 255, 255, 255
	FLOOR = 0, 0, 0
	PLAYER = 255, 0, 0
	CRATE = 248, 178, 90
	AMMO = 0, 255, 0
	EXIT = 0, 0, 255
*/